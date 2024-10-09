#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // LED pins
const int buttonPin = 12; // Button pin
unsigned long lastButtonPress = 0; // Time of the last button press
int buttonState = 0; // Current button state
int lastButtonState = 0; // Last button state
int pressCount = 0; // Button press count
bool manualMode = false; // Whether in manual mode

void setup() {
  Serial.begin(9600);
  lightMeter.begin();
  pinMode(buttonPin, INPUT_PULLUP); // Setup button pin with pull-up resistor

  // Initialize LED pins
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    pressCount++;
    lastButtonPress = millis(); // Update time of the last button press

    if (pressCount > 2) {
      pressCount = 1; // Reset the press count after the second press
    }

    manualMode = true; // Switch to manual mode on button press
  }

  lastButtonState = buttonState;

  // Check for timeout (10 seconds) to switch back to sensor mode
  if (millis() - lastButtonPress > 10000 && manualMode) {
    manualMode = false; // Switch back to sensor mode after timeout
    pressCount = 0; // Reset press count
  }

  if (manualMode) {
    if (pressCount == 1) {
      updateLEDs(5); // First press, show 5 LEDs
    } else if (pressCount == 2) {
      updateLEDs(10); // Second press, show 10 LEDs
    }
  } else {
    // Read light sensor value after timeout
    float lux = lightMeter.readLightLevel();
    Serial.print("Lux: ");
    Serial.println(lux);

    // Adjust LED count based on light intensity
    int ledCount;
    if (lux < 100) {
      ledCount = 10; // Low light, turn on all LEDs
    } else if (lux < 300) {
      ledCount = 8; // Medium light, turn on 8 LEDs
    } else if (lux < 500) {
      ledCount = 6; // Good light, turn on 6 LEDs
    } else if (lux < 700) {
      ledCount = 4; // Almost enough light, turn on 4 LEDs
    } else if (lux < 900) {
      ledCount = 2; // Quite enough light, turn on 2 LEDs
    } else {
      ledCount = 0; // Enough light, turn off all LEDs
    }

    updateLEDs(ledCount);
  }

  delay(100); // Small delay for button debounce and stability
}

void updateLEDs(int count) {
  for (int i = 0; i < 10; i++) {
    if (i < count) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
