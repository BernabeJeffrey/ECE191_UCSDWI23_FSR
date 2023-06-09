//Code inspiration and instructions: https://randomnerdtutorials.com/esp-now-two-way-communication-esp32/

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


Adafruit_BME280 bme;


// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };


float cf = 19.5;  // caliberation factor
int ffs1 = A0;    // FlexiForce sensor is connected analog pin A0 of arduino or mega.
int ffsdata = 0;
float voutFFS = 0;
float vout;


// Define variables to store incoming readings
float incomingffsdata;


// Variable to store if sending data was successful
String success;


//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  float data;
} struct_message;


// Create a struct_message called BME280Readings to hold sensor readings
struct_message BME280Readings;


// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;


esp_now_peer_info_t peerInfo;




// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success = "Delivery Success :)";
  } else {
    success = "Delivery Fail :(";
  }
}
// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingffsdata = incomingReadings.data;
}
void setup() {
  // Init Serial Monitor
  Serial.begin(9600);
  pinMode(ffs1, INPUT);


  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);


  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
  getReadings();
  // Set values to send
  BME280Readings.ffsdata = ffsdata;


  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&BME280Readings, sizeof(BME280Readings));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  updateDisplay();
  delay(10000);
}
void getReadings() {
  ffsdata = analogRead(ffs1);
  voutFFS = (ffsdata * 5.0) / 1023.0;
  voutFFS = voutFFS * cf;
}




void updateDisplay() {
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("ffsdata: ");
  Serial.print(incomingReadings.ffsdata);
}


/*
void setup()
{
 Serial.begin(9600);
 pinMode(ffs1, INPUT);
}


void loop()
{
ffsdata = analogRead(ffs1);
voutFFS = (ffsdata * 5.0) / 1023.0;
voutFFS = voutFFS * cf ;


Serial.print("Flexi Force sensor: ");
Serial.print(voutFFS,3);
Serial.println("");


//digitalWrite(pump, LOW);
Serial.print("HIgh Flexi Force sensor: ");
Serial.print(voutFFS,3);
Serial.println("");
}
delay(1); 
}
*/
