// Khai báo chân LED 7 đoạn
const int segPins[] = {3, 4, 5, 6, 7, 8, 9}; // Các chân cho LED 7 đoạn (a, b, c, d, e, f, g)
const int commonPin = 5; // Chân chung (common anode) của LED 7 đoạn

// Khai báo chân LED giao lộ A
const int greenA = 10; // Đèn xanh giao lộ A
const int yellowA = 11; // Đèn vàng giao lộ A
const int redA = 12; // Đèn đỏ giao lộ A

// Khai báo chân LED giao lộ B
const int greenB = 13; // Đèn xanh giao lộ B
const int yellowB = A0; // Đèn vàng giao lộ B
const int redB = A1; // Đèn đỏ giao lộ B

int timeLeft; // Thời gian còn lại cho LED 7 đoạn

// Các chữ số trên LED 7 đoạn (0-9)
// Vì là common anode, bật LED = LOW và tắt LED = HIGH
const byte digits[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // Số 0
  {1, 0, 0, 1, 1, 1, 1}, // Số 1
  {0, 0, 1, 0, 0, 1, 0}, // Số 2
  {0, 0, 0, 0, 1, 1, 0}, // Số 3
  {1, 0, 0, 1, 1, 0, 0}, // Số 4
  {0, 1, 0, 0, 1, 0, 0}, // Số 5
  {0, 1, 0, 0, 0, 0, 0}, // Số 6
  {0, 0, 0, 1, 1, 1, 1}, // Số 7
  {0, 0, 0, 0, 0, 0, 0}, // Số 8
  {0, 0, 0, 0, 1, 0, 0}  // Số 9
};

// Hàm hiển thị số trên LED 7 đoạn
void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}

void setup() {
  // Cài đặt chân LED 7 đoạn
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  pinMode(commonPin, OUTPUT);
  digitalWrite(commonPin, HIGH); // Chân chung (common anode) được nối với VCC

  // Cài đặt các chân đèn giao thông là đầu ra
  pinMode(greenA, OUTPUT);
  pinMode(yellowA, OUTPUT);
  pinMode(redA, OUTPUT);
  pinMode(greenB, OUTPUT);
  pinMode(yellowB, OUTPUT);
  pinMode(redB, OUTPUT);
}

void loop() {
  // Giao lộ A: Đèn đỏ - Giao lộ B: Đèn xanh
  digitalWrite(redA, HIGH);
  digitalWrite(greenB, HIGH);
  digitalWrite(redB, LOW);
  timeLeft = 9;
  while (timeLeft > 0) {
    displayDigit(timeLeft);
    delay(1000);
    timeLeft--;
  }
  digitalWrite(redA, LOW);

  // Giao lộ A: Đèn xanh - Giao lộ B: Đèn đỏ
  digitalWrite(greenA, HIGH);
  digitalWrite(redB, HIGH);
  digitalWrite(greenB, LOW);
  timeLeft = 6;
  while (timeLeft > 0) {
    displayDigit(timeLeft);
    delay(1000);
    timeLeft--;
  }
  digitalWrite(greenA, LOW);

  // Giao lộ A: Đèn vàng
  digitalWrite(yellowA, HIGH);
  timeLeft = 3;
  while (timeLeft > 0) {
    displayDigit(timeLeft);
    delay(1000);
    timeLeft--;
  }
  digitalWrite(yellowA, LOW);
}
