
// Khai báo các chân LED
const int ledPins[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2}; 
const int numLEDs = 12; // Có 12 đèn LED
const int buttonPin = 1; // Chân của nút bấm là chân số 1
int buttonState = 0; // Trạng thái của nút bấm
int ledCount = 0; // Số đèn đang sáng

void setup() {
  // Thiết lập các chân LED là đầu ra
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Thiết lập chân nút bấm là đầu vào với điện trở kéo lên
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  // Đọc trạng thái của nút bấm
  buttonState = digitalRead(buttonPin);

  // Khi nhấn nút (mức LOW do điện trở kéo lên)
  if (buttonState == LOW) {
    delay(200); // Chống dội nút
    ledCount++; // Tăng số lượng đèn sáng

    // Nếu đạt đến 12 đèn, quay lại 1 đèn
    if (ledCount > numLEDs) {
      ledCount = 1;
    }

    // Tắt tất cả các đèn
    for (int i = 0; i < numLEDs; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    // Bật số lượng đèn tương ứng với ledCount
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(ledPins[i], HIGH);
    }

    // Đợi một thời gian để tránh xử lý lặp lại khi giữ nút
    while (digitalRead(buttonPin) == LOW);
  }
}
