// Define pins
const int trigPin = 9;
const int echoPin = 8;
const int ledPin = 7;

// Variables for sensor and timing
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // For debugging
}

void loop() {
  // Send a trigger pulse to the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the echo time
  duration = pulseIn(echoPin, HIGH);
  
  // Convert time to distance (in cm)
  distance = duration * 0.034 / 2;
  
  // Flash LED based on distance (5 levels)
  if (distance > 50) {
    // Far away (no flash or slow flash)
    digitalWrite(ledPin, LOW);
    delay(1000);
  } else if (distance > 40) {
    // Level 1
    flashLed(500);  // Slow flash
  } else if (distance > 30) {
    // Level 2
    flashLed(400);
  } else if (distance > 20) {
    // Level 3
    flashLed(300);
  } else if (distance > 10) {
    // Level 4
    flashLed(200);
  } else {
    // Level 5 (Very close, fast flash)
    flashLed(100);
  }

  // Debugging output
  Serial.print("Distance: ");
  Serial.println(distance);
}

// Function to flash the LED with a given delay
void flashLed(int delayTime) {
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
  delay(delayTime);
}
