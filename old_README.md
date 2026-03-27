# Sleep Sensor SoC
A UCSC Chip Design Capstone project By: Ananya Manduva, Jackson Friday, Nathan Nakamoto, Nithin Duvvuru, Rishi Govindan, and Shane Stearns  
   
Our goal for the project is to create a custom ASIC SoC that intakes Accelerometer and PPG sensor data, processes, and creates features for a lightweight, three layer MLP model which determines whether the user is in an good stage to wake up (NREM/light sleep) or a bad time to wake (REM/deep sleep). This output is given to a small PicoRV32 core on the chip which then sends out a GPIO alarm signal to prompt wake up. The chip is set to sleep until a wachdog timer, set prior, fires off, indicating it's time to start checking sleep states.

# Directories
* src
   * All the sources required for build
* cocotb
   * Sim sources for testing 
* scripts
   * WIP: Additional scripts for generating ML model, Sensor data, etc...
* librelane
   * LibreLane constraint files
* ip
   * PDK and logo
* misc
   * Need to move around stuff
 


# Dataset Used for ML Training and Sensor Modeling:   
Walch, Olivia. "Motion and heart rate from a wrist-worn wearable and labeled sleep from polysomnography" (version 1.0.0). PhysioNet (2019). RRID:SCR_007345.   https://doi.org/10.13026/hmhs-py35  
