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
#define SDA 4
#define SCL 5
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int count=0;
void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize SSD1306 screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  for(int16_t x=0; x<display.width(); x+=1) //SCREEN_WIDTH
  {
    for(int16_t y=0; y<display.height(); y+=1) //  
    {
      display.drawPixel(x, y, SSD1306_WHITE);
      //display.display(); // Update screen with each newly-drawn rectangle
    }
    delay(1);
  }
  display.display();
  delay(2000);  
  
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Connecting WiFi...");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
    display.print(".");
    display.display();
        
    count++;
    if(count >10)
    {
        Serial.println("Timedout!");
        display.print("Timedout!");
        display.display();
        break;        
    }
  }

  // Initialize NTP client
  if(count <10)
  {
      // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    timeClient.begin();
  }
}
void loop() {
  // Update time
  if(count <10)
    timeClient.update();
  // Print time to SSD1306 screen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("MaESP ESP8266 OLED");
  display.print("Time:");
  display.setCursor(0, 20);
  if(count <10)
    display.printf("%02d:%02d:%02d", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
  else
    display.printf("2023/06/25 10:05:56");
  display.setCursor(0, 40);
  display.print("This is Makerfabs!");
  display.display();
  // Wait for 1 second
  delay(1000);
}
