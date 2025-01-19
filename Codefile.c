#include <Wire.h>
#include "WiFi.h"
#include "Audio.h"
#include <ThingSpeak.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>

#define GPS_BAUDRATE 9600 
#define OLED_ADDR     0x3C
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26
float latitude, longitude;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Audio audio;

WiFiClient client;
unsigned long counterChannelNumber = "";  // Channel ID
const char *myCounterReadAPIKey = ""; // Read API Key
const char* writeAPIKey = "";
const int FieldNumber1 = 1;
String presentStr, previousStr = "";
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  Serial2.begin(GPS_BAUDRATE,SERIAL_8N1, 16, 17);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin("username","Password");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(50); // Set a reasonable volume 

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Infinite loop to halt further execution
  }
}

void loop() {
  bool newData = false;
  presentStr = ThingSpeak.readStringField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  if (presentStr.length() > 0 && presentStr != previousStr) {
    previousStr = presentStr; // Update the previous string
    Serial.println("Received data: " + presentStr);
    presentStr=presentStr.substring(1);
    

    // Assuming presentStr should be spoken out, modify this as needed
    audio.connecttospeech(presentStr.c_str(), "en"); // Assuming the library expects a c-string
   
    while (audio.isRunning()) {
      audio.loop();
    }
     display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(presentStr);
    display.display();
  } else if (presentStr.length() == 0) {
    Serial.println("No data or unchanged data received from ThingSpeak");
  }
  while (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      newData = true;
    }
  }

  if (newData && gps.location.isValid()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);  // Show more decimal places for accuracy in debug
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);

    // Send data to ThingSpeak
    ThingSpeak.setField(2, static_cast<float>(latitude));
    ThingSpeak.setField(3, static_cast<float>(longitude));

    int response = ThingSpeak.writeFields(counterChannelNumber, writeAPIKey);
    if (response == 200) {
      Serial.println("Data sent successfully!");
    } else {
      Serial.print("Error sending data. HTTP error code: ");
      Serial.println(response);
    }
  } else if (newData && !gps.location.isValid()) {
    Serial.println("GPS location not valid.");
  }

  delay(10000); // Poll every 10 seconds
}

void audio_info(const char *info) { 
  Serial.print("audio_info: ");
  Serial.println(info);
}
