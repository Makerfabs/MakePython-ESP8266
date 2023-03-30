#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Define WiFi credentials
const char* ssid = "Makerfabs";
const char* password = "20160704";
// Define NTP server
const char* ntpServerName = "pool.ntp.org";
// Define timezone
const int timeZone = 8;
// Define NTP client
WiFiUDP udp;
NTPClient timeClient(udp, ntpServerName, timeZone * 3600, 60000);
// Define SSD1306 screen
// SSD1306
#define SDA 4ta
#define SCL 5
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {
  // Start serial communication
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Initialize SSD1306 screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Initialize NTP client
  timeClient.begin();
}
void loop() {
  // Update time
  timeClient.update();
  // Print time to SSD1306 screen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Time:");
  display.setCursor(0, 20);
  display.printf("%02d:%02d:%02d", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
  display.setCursor(0, 40);
  display.print("This is Makerfabs!");
  display.display();
  // Wait for 1 second
  delay(1000);
}
