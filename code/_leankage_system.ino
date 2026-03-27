#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Replace with your network credentials
const char* ssid = "Sophiya";
const char* password = "sophiya8";

// ThingSpeak settings
unsigned long myChannelNumber = 3091154; 
const char* myWriteAPIKey = "W8L3K2VYLPO6X7UA";

WiFiClient client;

// Gas Sensor connected to analog pin
int gasSensorPin = A0; // ESP32 ADC pin (adjust if different)
int buzzer1 = D0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  ThingSpeak.begin(client);
  pinMode(buzzer1, OUTPUT);
  digitalWrite(buzzer1, LOW);

}

void loop() {
  // Read sensor value
  int gasValue = analogRead(A0);

  float gasPPM = map(gasValue, 0, 1023, 0, 1000); 
  // mapping to ppm range (0–1000 ppm) – adjust depending on your sensor calibration

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasPPM);

  // Write to ThingSpeak (field1)
  int response = ThingSpeak.writeField(myChannelNumber, 1, gasPPM, myWriteAPIKey);

  if (response == 200) {
    Serial.println("Data uploaded to ThingSpeak successfully");
  } else {
    Serial.print("Error uploading data. HTTP error code: ");
    Serial.println(response);
  }
  if(gasPPM > 100)
  {
    digitalWrite(buzzer1,HIGH);
    Serial.println("Gas level HIGH!!!");
  }
  else{
    digitalWrite(buzzer1, LOW);
  }
  delay(3000); // ThingSpeak allows updates every 15 seconds
}
