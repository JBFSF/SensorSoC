# ML

This directory is used to produce RTL using NNGen. 
taketwo.v is the final MLP model in RTL that has been transferred into our main sleep_soc directory, all other files in this directory are used to produce this trained model

* Dataset
  * Dataset taken from https://physionet.org/content/sleep-accel/1.0.0/
    * The dataset is licensed under the Open Data Commons Attribution License v1.0 (ODC-BY 1.0): https://physionet.org/content/sleep-accel/1.0.0/LICENSE.txt
  * Features proccessing done with https://github.com/ojwalch/sleep_accel
    * *Motion and heart rate from a wrist-worn wearable and labeled sleep from polysomnography* (Version 1.0.0) [Dataset]. PhysioNet, 2019

* ML Pipeline
  * Train Model (taketwo.py) → Export .ONNX (taketwo.py) → NNGen script (writeverilog.py) → Verilog RTL (taketwo.v) → sleep_soc.
  * To Run:
    ```
    python3 taketwo.py
    python3 writeverilog.py
    ```
  * Move synthesized verilog and tb into ../sleep_soc/rtl and ../sleep_soc/sim/tb
# Inside this Directory
* taketwo.py
  * Python version of the ML model, outputs .onnx and .onnx.data files that will be fed into writeverilog.py
* writeverilog.py
  * NNGen script that produces our ML model in verilog (taketwo.v), as well as the weights and biases (taketwo_params.bin)
* processed_sleep_dataset.csv
  * Our current training dataset
* compiled_sleep_dataset.csv
  * Old data Format
  * Unused Currently
* shortencsv.py
  * Used to downsample and process csv data
* nngen_out
  * Subdirectory for our writeverilog.py to output NNGen files, also contains old testing files
     * taketwo.v
       * Our primary ML model in RTL
     * taketwo_params.bin
       * Binary containing training outputs (weights and biases), these are loaded into the ML model
