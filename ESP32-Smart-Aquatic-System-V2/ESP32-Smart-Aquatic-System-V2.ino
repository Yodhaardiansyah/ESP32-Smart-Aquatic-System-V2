/*
 * ESP32 Smart Aquatic System
 * Author: Yodha Ardiansyah
 * Website: https://arunovasi.my.id
 * Description: This program controls relays and a servo via MQTT and 
 *              monitors soil moisture and distance using sensors.
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// WiFi Configuration (Replace with your own credentials)
const char* ssid = "YOUR_WIFI_SSID";      // WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD";  // WiFi Password

// MQTT Configuration (Replace with your MQTT broker details)
const char* mqtt_server = "YOUR_MQTT_SERVER";
const int mqtt_port = 1883;
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";

// MQTT Topics
const char* topic_relay1 = "smartaquatic/relay1";
const char* topic_relay2 = "smartaquatic/relay2";
const char* topic_servo = "smartaquatic/servo";
const char* topic_soil_moisture = "smartaquatic/moisture";
const char* topic_distance = "smartaquatic/distance";

// Pin Configuration
#define MOISTURE_PIN 33
#define RELAY1_PIN 14
#define RELAY2_PIN 27
#define SERVO_PIN 25
#define TRIG_PIN 12
#define ECHO_PIN 13

// MQTT & Servo Objects
WiFiClient espClient;
PubSubClient client(espClient);
Servo myServo;

// WiFi Connection
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

// MQTT Callback Function
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Received Message: ");
  Serial.println(message);

  if (String(topic) == topic_relay1) {
    digitalWrite(RELAY1_PIN, message == "ON" ? HIGH : LOW);
  } else if (String(topic) == topic_relay2) {
    digitalWrite(RELAY2_PIN, message == "ON" ? HIGH : LOW);
  } else if (String(topic) == topic_servo) {
    int angle = message.toInt();
    myServo.write(angle);
  }
}

// MQTT Reconnect Function
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT");
      client.subscribe(topic_relay1);
      client.subscribe(topic_relay2);
      client.subscribe(topic_servo);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Distance Measurement Function
long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Convert to cm
}

// Setup Function
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(SERVO_PIN);
}

// Main Loop
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read Soil Moisture Sensor
  int moistureValue = analogRead(MOISTURE_PIN);
  client.publish(topic_soil_moisture, String(moistureValue).c_str());

  // Read Distance Sensor
  long distance = readDistance();
  client.publish(topic_distance, String(distance).c_str());

  delay(1000); // Data transmission interval
}
