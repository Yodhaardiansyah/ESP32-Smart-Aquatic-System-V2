# **ESP32 Smart Aquatic System**  

### **Overview**  
This project is a smart aquatic monitoring and control system using an **ESP32**. It integrates **MQTT communication** to control relays, a servo motor, and monitors **soil moisture and water level** using sensors.  

---

## **Features**  
✅ **Remote Control via MQTT** – Control pumps, valves, and other actuators remotely.  
✅ **Soil Moisture Monitoring** – Measure soil moisture levels for irrigation purposes.  
✅ **Water Level Detection** – Uses an ultrasonic sensor to measure water depth.  
✅ **Servo Control** – Adjust mechanisms such as feeder or valve using servo motor.  
✅ **WiFi Connectivity** – Connects to a WiFi network for remote monitoring and control.  

---

## **Hardware Requirements**  
- **ESP32**  
- **Soil Moisture Sensor** (Analog)  
- **HC-SR04 Ultrasonic Sensor** (Water level detection)  
- **Relay Module (x2)** (For controlling external devices)  
- **Servo Motor** (For adjustable mechanisms)  
- **WiFi Network** (For MQTT communication)  

---

## **Wiring Diagram**  
| **Component**          | **ESP32 Pin** |
|------------------------|--------------|
| Soil Moisture Sensor  | GPIO 33      |
| Relay 1               | GPIO 14      |
| Relay 2               | GPIO 27      |
| Servo Motor           | GPIO 25      |
| Ultrasonic Sensor (Trig) | GPIO 12  |
| Ultrasonic Sensor (Echo) | GPIO 13  |

---

## **Software Setup**  
### **1. Install Required Libraries**  
Ensure you have installed the following libraries in **Arduino IDE**:  
- `WiFi.h` (Built-in ESP32 WiFi library)  
- `PubSubClient.h` (For MQTT communication)  
- `ESP32Servo.h` (For controlling the servo motor)  

To install libraries, go to **Arduino IDE → Sketch → Include Library → Manage Libraries**, then search and install:  
- **PubSubClient**  
- **ESP32Servo**  

---

## **2. Configure WiFi & MQTT**  
Edit the **WiFi credentials** and **MQTT broker details** in the code:  

```cpp
// WiFi Configuration (Replace with your credentials)
const char* ssid = "YOUR_WIFI_SSID";    
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT Configuration (Replace with your MQTT broker details)
const char* mqtt_server = "YOUR_MQTT_SERVER";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";
```

---

## **3. MQTT Topics**  
The ESP32 subscribes to and publishes data using the following MQTT topics:  

| **Feature**            | **Topic Name**              | **Message Format** |
|------------------------|----------------------------|--------------------|
| Relay 1 Control       | `smartaquatic/relay1`       | `"ON"` / `"OFF"`  |
| Relay 2 Control       | `smartaquatic/relay2`       | `"ON"` / `"OFF"`  |
| Servo Angle Control   | `smartaquatic/servo`        | `"0"` to `"180"`  |
| Soil Moisture Data    | `smartaquatic/moisture`     | Integer Value     |
| Distance Sensor Data  | `smartaquatic/distance`     | Integer Value (cm) |

---

## **4. Upload Code to ESP32**  
1. **Connect ESP32 to your PC via USB**  
2. **Select ESP32 Board** in Arduino IDE  
   - Go to **Tools → Board → ESP32 Dev Module**  
3. **Select the Correct Port**  
   - Go to **Tools → Port**  
4. **Upload the Code**  

---

## **5. Monitor Data**  
- **Use Serial Monitor** (Baud rate: `115200`)  
- **Use MQTT Client** (e.g., [MQTT Explorer](http://mqtt-explorer.com/))  
- **Use a Web Dashboard** to visualize sensor data  

---

## **6. Expected Output**  
After running the program, the ESP32 will:  
✔ Connect to **WiFi**  
✔ Subscribe to **MQTT topics**  
✔ Send **sensor data** periodically  
✔ Control **relays and servo** based on received MQTT commands  

---

## **Future Enhancements**  
🔹 Add **OLED display** for local sensor readings  
🔹 Implement **Blynk or Home Assistant** integration  
🔹 Enable **automatic pump activation** based on soil moisture levels  

---

## **Credits**  
👤 **Author:** Yodha Ardiansyah  
🌐 **Website:** [arunovasi.my.id](https://arunovasi.my.id)  
📌 **Project Type:** IoT Smart Aquatic Monitoring  

---

Let me know if you need modifications or additional details! 🚀
