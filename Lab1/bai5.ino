#include <Wire.h>
#include <hd44780.h>                    // Thư viện core hd44780
#include <hd44780ioClass/hd44780_I2Cexp.h>  // Thư viện cho I2C

#define NUM_LEDS 10
#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3
#define LED_START_PIN 4

hd44780_I2Cexp lcd;  // Tạo đối tượng LCD cho giao tiếp I2C

int level = 1;
int score = 0;
int num_lights_on = 0;
int correct_button = 0;
unsigned long start_time;
int timeout;

void setup() {
  lcd.begin(16, 2);  // Khởi tạo màn hình LCD với kích thước 16x2
  lcd.backlight();   // Bật đèn nền LCD

  // Set LED pins as outputs
  for (int i = LED_START_PIN; i < LED_START_PIN + NUM_LEDS; i++) {
    pinMode(i, OUTPUT);
  }

  // Set button pins as inputs with internal pull-up resistors
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);

  startGame();
}

void loop() {
  // Display LEDs based on the level
  num_lights_on = random(1, NUM_LEDS + 1);
  correct_button = num_lights_on % 3;

  lightUpLEDs(num_lights_on);
  start_time = millis();
  timeout = max(1000, (4000 - (level * 1000)));  // Ensure timeout doesn't go below 1000ms

  // Display the correct button on the LCD for debugging
  updateLCD("Correct Button:", correct_button + 1);  // Display the button number (1-based index)

  // Wait for the player's input within the timeout period
  while (millis() - start_time < timeout) {
    int pressed_button = getButtonPress();
    if (pressed_button != -1) {
      checkButton(pressed_button);
      break;
    }
  }

  if (millis() - start_time >= timeout) {
    // No button pressed, deduct points and reset level
    score = max(0, score - 1);  // Ensure score doesn't go below 0
    level = 1;
    updateLCD("Time out! Score:", score);
  }

  delay(2000);
  startGame();  // Start a new round
}

void startGame() {
  updateLCD("Level", level);
  delay(1000);
}

void lightUpLEDs(int num) {
  // Turn on num LEDs
  for (int i = 0; i < num; i++) {
    digitalWrite(LED_START_PIN + i, HIGH);
  }
  delay(1000);  // LEDs stay on for 1 second
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_START_PIN + i, LOW);  // Turn off LEDs
  }
}

int getButtonPress() {
  // The buttons are using INPUT_PULLUP, so a pressed button will read LOW
  if (digitalRead(BUTTON1_PIN) == LOW) return 0;
  if (digitalRead(BUTTON2_PIN) == LOW) return 1;
  if (digitalRead(BUTTON3_PIN) == LOW) return 2;
  return -1;  // No button pressed
}

void checkButton(int button) {
  if (button == correct_button) {
    // Correct button pressed
    score += 1;
    level = min(level + 1, 3);  // Increase level, max is 3
    updateLCD("Correct! Score:", score);
  } else {
    // Incorrect button, reset level and deduct points
    score = max(0, score - 1);  // Ensure score doesn't go below 0
    level = 1;
    updateLCD("Wrong! Score:", score);
  }
}

void updateLCD(String message, int value) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print(value);
}
