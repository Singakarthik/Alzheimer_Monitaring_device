## Hi there 👋
Develop a compact wearable device tailored for individuals with Alzheimer's  disease.
Integrate tracking capabilities to monitor daily activities, including food intake and  medication timings.
Implement reminder and alert features to support users in better self-management  and reduce cognitive load.
Enhance	the	independence	and	overall	quality	of	life	for	individuals	with  Alzheimer's through the wearable device.
Assist caregivers in managing care responsibilities more effectively by providing  support through the wearable technology.


<!--
**Singakarthik/singakarthik** is a ✨ _special_ ✨ repository because its `README.md` (this file) appears on your GitHub profile.

Here are some ideas to get you started:

- 🔭 I’m currently working on ...
- 🌱 I’m currently learning ...
- 👯 I’m looking to collaborate on ...
- 🤔 I’m looking for help with ...
- 💬 Ask me about ...
- 📫 How to reach me: ...
- 😄 Pronouns: ...
- ⚡ Fun fact: ...
-->

# IoT and GPS-Based Alzheimer's Disease Patient Monitoring System

This project is an IoT-based solution designed to monitor and display real-time GPS data while integrating with cloud platforms like ThingSpeak for data visualization and storage. The project leverages the ESP32 microcontroller, an OLED display, audio processing capabilities, and GPS modules to provide a comprehensive monitoring system.

## Features

- **GPS Tracking**: Real-time acquisition of latitude and longitude using TinyGPS++.
- **WiFi Connectivity**: Enables seamless data communication via the ESP32.
- **ThingSpeak Integration**: Logs data to a ThingSpeak channel for analysis and visualization.
- **Audio Processing**: Supports audio output using the I2S protocol.
- **OLED Display**: Visualizes real-time data on a 128x64 OLED screen.

## Hardware Requirements

- ESP32 microcontroller
- GPS module (configured at 9600 baud)
- Adafruit SSD1306 OLED display
- WiFi-enabled environment
- I2S-compatible audio output components

## Software Requirements

- Arduino IDE with the following libraries:
  - `TinyGPS++`
  - `Adafruit_GFX`
  - `Adafruit_SSD1306`
  - `ThingSpeak`
  - `Audio`
  - `WiFi`

## Setup Instructions

1. **Hardware Connections**:
   - Connect the GPS module to the ESP32's designated pins.
   - Attach the OLED display to the I2C pins (default address: 0x3C).
   - Connect the audio components to the specified I2S pins (DOUT: 25, BCLK: 27, LRC: 26).

2. **Library Installation**:
   Install the required libraries via the Arduino Library Manager or manually place them in the `libraries` folder.

3. **WiFi Configuration**:
   Update the following lines in the code with your WiFi credentials:
   ```cpp
   WiFi.begin("YourSSID", "YourPassword");
   ```

4. **ThingSpeak Configuration**:
   Replace the placeholders in the code with your ThingSpeak channel ID and API keys:
   ```cpp
   unsigned long counterChannelNumber = YOUR_CHANNEL_ID;
   const char *myCounterReadAPIKey = "YOUR_READ_API_KEY";
   const char* writeAPIKey = "YOUR_WRITE_API_KEY";
   ```

5. **Upload Code**:
   Compile and upload the code to your ESP32 using the Arduino IDE.

6. **Monitor Output**:
   Use the serial monitor to debug and verify GPS data and WiFi status.

## Usage
- Track GPS data and visualize it on the OLED display.
- Monitor and analyze data remotely via ThingSpeak.
- Utilize audio alerts for notifications or alarms.

## Contributing
Contributions are welcome! Feel free to fork this repository, open issues, or submit pull requests to enhance functionality.

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgments
- Special thanks to the creators of the libraries used in this project.
- Inspiration from IoT and GPS-based applications.
---
