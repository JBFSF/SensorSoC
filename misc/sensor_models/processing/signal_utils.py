import numpy as np

# Normalize signal (simulate sensor calibration)
def normalize_signal(signal):
    signal = signal - np.mean(signal)
    signal = signal / (np.std(signal) + 1e-8)
    return signal

# Simulate analog noise
def add_analog_noise(signal, noise_std=0.02):
    noise = np.random.normal(0, noise_std, size=len(signal))
    return signal + noise

# Simulate ADC quantization
def adc_quantize(signal, bits=10):
    levels = 2 ** bits
    min_val = np.min(signal)
    max_val = np.max(signal)
    
    # Map to 0–1
    normalized = (signal - min_val) / (max_val - min_val + 1e-8)
    
    # Quantize
    quantized = np.round(normalized * (levels - 1)) / (levels - 1)
    
    return quantized

# Full sensor pipeline
def simulate_sensor_pipeline(raw_signal):
    analog = normalize_signal(raw_signal)
    analog_noisy = add_analog_noise(analog)
    digital = adc_quantize(analog_noisy)
    return analog_noisy, digital
