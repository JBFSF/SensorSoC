# taketwo.py
# Python ML component for the sensing SOC group in CSE 127A 
#
# This is our best of many attempts at building an ML model to predict sleep
# stages based on sensor data. The main features we are using from the current dataset
# are mody movement, cosine, and heart rate.
#
# Built by Jackson Friday and Shane Stearns
# Updated 2/4/2026
# 
# We obtained our train and test data from:
# https://physionet.org/content/sleep-accel/1.0.0/
# https://academic.oup.com/sleep/article/42/12/zsz180/5549536

# Libraries
import torch
from sklearn.datasets import make_moons 
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, classification_report
from torch.utils.data import TensorDataset, DataLoader, WeightedRandomSampler
import torch.nn as nn
import pandas as pd
import numpy as np

SETUP_MAX_SAMPLES = 10 * 60 * 1        # Using the first 10 minutes of data to get a baseline HR
MIN_SETUP_SAMPLES = 0                  
EPS = 1e-8                             
ACCEL_SHIFT = 6                        # Used to scale and normalize accel data

WINDOW_SEC = 60                        # Size of sliding window (in samples/seconds) for HRV/RMSSD calculation
STEP_SEC = 300                         # Compute every 5 minutes
WINDOW_SAMPLES = WINDOW_SEC            
STEP_SAMPLES = STEP_SEC                

SEED = 39                              # Random seed
EPOCHS = 50                            # How many times the data is passed through the model
LR = 1e-3                              # Learning rate, or how much the model updates weights each time


# Load & clean up data from CSVs
df = pd.read_csv("compiled_sleep_dataset.csv")
need = ["subject_id", "movement", "cosine","time", "hr", "ss"]
df = df.dropna(subset=need).copy()


# each subject's heart rate baseline
resting_hr = {}

for sid, g in df.groupby("subject_id", sort=False):
    idx = g.index
    g = g.reset_index(drop=True)
    early = g.iloc[:SETUP_MAX_SAMPLES]
    wake_hr = early.loc[early["ss"] == "W", "hr"].values
    if len(wake_hr) >= MIN_SETUP_SAMPLES:
        resting_hr[sid] = np.median(wake_hr)
    else:
        resting_hr[sid] = early["hr"].mean()
df["hr_baseline"] = df["subject_id"].map(resting_hr)
df["delta_hr"] = (df["hr"] - df["hr_baseline"]) / (df["hr_baseline"] + EPS)

df = df[~df['ss'].isin(['W'])] # removing wake stages

# mapping sleep stages
label_map = {"N1": 0, "N2": 0, "R": 0,"N3": 1}
df = df[df["ss"].isin(label_map)]
df["label"] = df["ss"].map(label_map).astype(int)


# hrv
hr = df["hr"].to_numpy()

# --- online causal RMSSD (reset per subject) ---
df["hr_rmssd"] = np.zeros(len(df), dtype=float)

for sid, g in df.groupby("subject_id", sort=False):
    idxs = g.index.to_numpy()
    hr = g["hr"].to_numpy()

    rmssd = np.zeros(len(hr), dtype=float)

    # ---- persistent hardware state ----
    prev_hr = hr[0]
    diff2_buf = np.zeros(WINDOW_SEC - 1)
    buf_idx = 0
    sum_diff2 = 0.0

    # ---- streaming update ----
    for n in range(1, len(hr)):
        diff = hr[n] - prev_hr
        diff2 = diff * diff

        # subtract oldest, add newest
        sum_diff2 -= diff2_buf[buf_idx]
        sum_diff2 += diff2
        diff2_buf[buf_idx] = diff2

        # advance circular buffer
        buf_idx += 1
        if buf_idx == (WINDOW_SEC - 1):
            buf_idx = 0

        # valid only after full window
        #if n >= (WINDOW_SEC - 1):
        rmssd[n] = sum_diff2 / (WINDOW_SEC - 1)   # sqrt intentionally omitted

        prev_hr = hr[n]

    df.loc[idxs, "hr_rmssd"] = rmssd



# # combining hrv and movement
# df["hrv_mov"] = df["hr_rmssd"] / (df["movement"] + EPS)



features = [
    "movement",    # body movement magnitude from accel
    "cosine",      # cosine of time in seconds over 24 hr period
    "delta_hr",    # change in heartrate from baseline
    "hr_rmssd"     # hrv
   # "label"        # label
    #"hrv_mov"      # hrv and movement
]

# normalize features (except cosine, which is already bounded)
df["movement"] /= 8.0
df["delta_hr"] /= 4.0
df["hr_rmssd"] /= 0.05
# cosine already bounded


# clamp features to [-1, 1] to avoid outliers dominating training and to match quantization range
for col in features:
    df[col] = df[col].clip(-8.0, 7.0)

X = df[features].fillna(0).to_numpy()
y = df["label"].to_numpy()
data_ex = df[features].copy()
data_ex.to_csv("processed_sleep_dataset.csv", index=False)


# train / test split by ID
np.random.seed(SEED)
subject_ids = df["subject_id"].unique()
print(subject_ids)
train_subs = np.random.choice(subject_ids, size=22, replace=False)
test_subs = np.array([sid for sid in subject_ids if sid not in train_subs])

print("Train subjects:", train_subs)
print("Test subjects:", test_subs)

train_df = df[df["subject_id"].isin(train_subs)]
test_df = df[df["subject_id"].isin(test_subs)]

X_train = train_df[features].to_numpy()
y_train = train_df["label"].to_numpy()
X_test = test_df[features].to_numpy()
y_test = test_df["label"].to_numpy()

class_sample_counts = np.bincount(y_train)

weights = 1.0 / class_sample_counts
sample_weights = weights[y_train]

sampler = WeightedRandomSampler(
    weights=sample_weights,
    num_samples=len(sample_weights),
    replacement=True
)

# dataloaders

train_ds = TensorDataset(
    torch.tensor(X_train, dtype=torch.float32),
    torch.tensor(y_train, dtype=torch.long)
)

train_loader = DataLoader(
    train_ds,
    batch_size=WINDOW_SEC,
    sampler=sampler
)

test_ds = TensorDataset(
    torch.tensor(X_test, dtype=torch.float32),
    torch.tensor(y_test, dtype=torch.long)
)

test_loader = DataLoader(
    test_ds,
    batch_size=WINDOW_SEC,
    shuffle=False
)


classes, counts = np.unique(y_train, return_counts=True)

weights = counts.sum() / (len(classes) * counts)
class_weights = torch.tensor(weights, dtype=torch.float32)

print("Class weights:", class_weights)

# model

class TransitionMLP(nn.Module):
    def __init__(self, in_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(in_dim, 16),
            nn.ReLU(),
            nn.Linear(16, 8),
            nn.ReLU(),
            nn.Linear(8, 2),
        )

    def forward(self, x):
        return self.net(x)

model = TransitionMLP(X_train.shape[1])

opt = torch.optim.Adam(model.parameters(), lr=LR, weight_decay=1e-4)

loss_fn = nn.CrossEntropyLoss()

# training loop

train_losses = []

for epoch in range(EPOCHS):
    epoch_loss = 0.0

    for X_batch, y_batch in train_loader:
        outputs = model(X_batch)
        loss = loss_fn(outputs, y_batch)

        opt.zero_grad()
        loss.backward()
        opt.step()

        epoch_loss += loss.item() * X_batch.size(0)

    avg_loss = epoch_loss / len(train_loader.dataset)
    train_losses.append(avg_loss)

    print(f"Epoch {epoch+1}/{EPOCHS}, Loss: {avg_loss:.4f}")

# evaluation / testing

model.eval()

with torch.no_grad():
    X_test_tensor = torch.tensor(X_test, dtype=torch.float32)
    test_output = model(X_test_tensor)

    test_pred = torch.argmax(test_output, dim=1)

    y_test_tensor = torch.tensor(y_test, dtype=torch.long)

    accuracy = (test_pred == y_test_tensor).float().mean()

print(f"Test Accuracy: {accuracy.item() * 100:.2f}%")

print(confusion_matrix(y_test, test_pred, labels=[0,1]))
print(classification_report(y_test, test_pred, labels=[0,1]))

class ExportWrapper(nn.Module):
    def __init__(self, base):
        super().__init__()
        self.base = base

    def forward(self, x):
        # Force a real Flatten op into ONNX by going 4D -> Flatten -> 2D
        x = x.unsqueeze(-1).unsqueeze(-1)     # (N, C) -> (N, C, 1, 1)
        x = torch.flatten(x, 1)               # emits ONNX Flatten
        return self.base(x)
 # ============================================================
# Export model to ONNX (NNgen)
# ============================================================

model.eval()
export_model = ExportWrapper(model).eval()

dummy_input = torch.tensor(X_train[:1], dtype=torch.float32)  # shape (1, in_dim)

for name, param in model.named_parameters(): #checking parameter ranges before export
    print(name, param.abs().max().item())


onnx_path = "taketwo_nngen.onnx"
torch.onnx.export(
    export_model,
    dummy_input,
    onnx_path,
    export_params=True,
    opset_version=11,
    do_constant_folding=True,
    input_names=["x"],
    output_names=["logits"],
    dynamic_axes=None,
    dynamo=False,
)

print(f"Exported ONNX model to {onnx_path}")
