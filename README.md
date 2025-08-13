# M5Stack + Water Sensor (Seeed Studio 101020018)

This repository contains code for using the **Seeed Studio Water Sensor (SKU: 101020018)** with **M5Stack Basic**.  
The official sample code provided by Seeed Studio supports **Arduino** and **Raspberry Pi**, but not M5Stack — so this version is adapted specifically for the M5 environment.

## Features
- Detects water using the Seeed Studio Water Sensor.
- Sends a **Webhook notification** to external services when water is detected.
- Designed to run on **M5Stack Basic**.

## Important Notes
- **Voltage level warning:**  
  M5Stack GPIO inputs are **3.3V logic**, but the sensor outputs **5V**.  
  You **cannot** connect the Grove connector directly to the M5Stack grove port.  
  (I actually chose M5Stack thinking it would connect directly… but no such luck)

- **Voltage divider requirement:**  
  Due to the sensor's internal design, the voltage divider must use **very high resistance values** (e.g., 1 MΩ / 2 MΩ) to avoid pulling the voltage down unintentionally.

## Hardware Setup
1. **Sensor VCC**(Red) → M5Stack 5V  
2. **Sensor GND**(Black) → M5Stack GND  
3. **Sensor SIG**(Yellow) → Voltage divider (1 MΩ top, 2 MΩ bottom) → M5Stack GPIO input (in this code, 26)  
