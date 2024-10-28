#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// HTML webpage contents
const char MAIN_page[] PROGMEM = R"=====( 
<!DOCTYPE html> 
<html> 
<body> 
<center> 
<h1>Click "Start" to Begin the Game</h1><br> 
<a href="startGame"><button>Start</button></a><br><br> 
<h1>How many LEDs were ON? (n % 3)</h1><br> 
<a href="guess?num=0"><button>0</button></a><br> 
<a href="guess?num=1"><button>1</button></a><br> 
<a href="guess?num=2"><button>2</button></a><br> 
<p>Your Score: __SCORE__</p> 
<p>Status: __STATUS__</p>
</center> 
</body> 
</html> 
)=====";

// LED pins
const int ledPins[] = {D1, D2, D3, D4, D5};
int score = 10;  // Starting score
int numLedsOn = 0;
bool gameStarted = false;
bool guessMade = false;  // Track if player made a guess
unsigned long displayTime = 2000;  // 2 seconds for LED display
unsigned long guessTime = 2000;  // 2 seconds for guessing
unsigned long startMillis = 0;  // Start time for guessing phase
String gameStatus = "Waiting to start";

// Wi-Fi credentials
const char* ssid = "UiTiOt-E3.1";
const char* password = "UiTiOtAP";

// Web server
ESP8266WebServer server(80);

// Function to display LEDs left to right and back
void displayLEDSequence() {
  // Left to right
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);  // Quick display for each LED
    digitalWrite(ledPins[i], LOW);
  }
  // Right to left
  for (int i = 4; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}

// Generate a random pattern of LEDs
void generateRandomLEDs() {
  numLedsOn = random(1, 6);  // Random number of LEDs to turn ON (1 to 5)
  // Turn off all LEDs
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  // Turn ON random LEDs
  for (int i = 0; i < numLedsOn; i++) {
    int randomLed = random(0, 5);
    digitalWrite(ledPins[randomLed], HIGH);
  }
  delay(displayTime);  // Display LEDs for 2 seconds
  // Turn off all LEDs
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Function to handle root page
void handleRoot() {
  Serial.println("Root page called");
  String html = MAIN_page;
  html.replace("__SCORE__", String(score));
  html.replace("__STATUS__", gameStatus);
  server.send(200, "text/html", html);
}

// Function to start the game
void handleStartGame() {
  if (score <= 0) {
    gameStatus = "Game Over!";
    handleRoot();
    return;
  }
  
  Serial.println("Game started");
  gameStarted = true;
  guessMade = false;
  gameStatus = "Game in progress...";
  
  // Show LED sequence
  displayLEDSequence();
  // Display random LEDs
  generateRandomLEDs();
  // Start the timer for guessing phase
  startMillis = millis();
  handleRoot();
}

// Function to handle player guess
void handleGuess() {
  if (gameStarted && !guessMade && millis() - startMillis <= guessTime) {
    if (server.hasArg("num")) {
      int guess = server.arg("num").toInt();
      Serial.print("Player guessed: ");
      Serial.println(guess);
      guessMade = true;
      
      // Check the player's guess
      if (guess == (numLedsOn % 3)) {
        score++;
        gameStatus = "Correct! Score increased.";
      } else {
        score--;
        gameStatus = "Incorrect! Score decreased.";
      }
    }
  } else if (!guessMade && millis() - startMillis > guessTime) {
    // Timeout case
    score--;
    gameStatus = "Time's up! Score decreased.";
    guessMade = true;
  }
  
  if (score <= 0) {
    gameStatus = "Game Over!";
    gameStarted = false;
  }
  
  handleRoot();
}

// Setup function
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define server routes
  server.on("/", handleRoot);
  server.on("/startGame", handleStartGame);
  server.on("/guess", handleGuess);
  
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  server.handleClient();
}