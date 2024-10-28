#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "UiTiOt-E3.1";  
const char* password = "UiTiOtAP";  
const char* serverUrl = "http://172.31.11.11:5000/api/sensors"; // Adjust to your server's IP

// Pin connections
const int lightSensorPin = A0;  
const int trigPin = D1;          
const int echoPin = D2;          
const int led1Pin = D3;          
const int led2Pin = D4;          
const int led3Pin = D5;          

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    initializePins();
}

void loop() {
    int lightValue = analogRead(lightSensorPin);
    long distance = readDistance();

    if (WiFi.status() == WL_CONNECTED) {
        sendDataToServer(lightValue, distance);
    } else {
        Serial.println("WiFi disconnected, attempting to reconnect...");
        connectToWiFi();
    }
    
    delay(5000);  // Send data every 5 seconds
}

void connectToWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void initializePins() {
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(led3Pin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long readDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return (duration * 0.034) / 2; // Convert to cm
}

void updateLEDs(int ledCount) {
    digitalWrite(led1Pin, ledCount >= 1 ? HIGH : LOW);
    digitalWrite(led2Pin, ledCount >= 2 ? HIGH : LOW);
    digitalWrite(led3Pin, ledCount >= 3 ? HIGH : LOW);
}

void sendDataToServer(int lightValue, long distance) {
    HTTPClient http;
    WiFiClient client;  
    http.begin(client, serverUrl);  
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload
    DynamicJsonDocument doc(256);
    doc["light"] = lightValue;
    doc["distance"] = distance;
    
    String payload;
    serializeJson(doc, payload);
    
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response from server: " + response);

        // Parse server response
        DynamicJsonDocument responseDoc(1024);
        DeserializationError error = deserializeJson(responseDoc, response);

        if (!error) {
            bool errorFlag = responseDoc["error"];
            String message = responseDoc["message"];
            int ledCount = responseDoc["data"]["led_count"];

            // Output message to Serial Monitor
            Serial.println("Error: " + String(errorFlag) + ", Message: " + message);
            Serial.println("LED Count: " + String(ledCount));
            updateLEDs(ledCount);
        } else {
            Serial.println("Failed to parse JSON response: " + String(error.c_str()));
        }
    } else {
        Serial.println("Error on sending POST: " + String(httpResponseCode));
    }
    http.end();
}