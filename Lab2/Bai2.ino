// Khai báo chân LED 7 đoạn
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};

// Các giá trị bật/tắt cho từng con số trên LED 7 đoạn (Cathode chung)
byte numbers[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

// Khai báo chân cảm biến HC-SR04
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // Cài đặt chân cho LED 7 đoạn
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Cài đặt chân cho cảm biến HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Khởi tạo giao tiếp serial để debug
}

void loop() {
  long duration;
  int distance;

  // Phát tín hiệu từ chân Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Nhận tín hiệu từ chân Echo
  duration = pulseIn(echoPin, HIGH);

  // Tính khoảng cách (cm)
  distance = duration * 0.034 / 2;

  // Hiển thị số tương ứng với khoảng cách
  if (distance < 5 || distance > 400) {
    displayDigit(0);  // Nếu khoảng cách ngoài phạm vi, hiển thị 0
  } else {
    // Tính số hiển thị dựa trên khoảng cách (mỗi 5 cm tương ứng với một số)
    int displayValue = distance / 5; // Số hiển thị = khoảng cách / 5
    if (displayValue > 9) { // Giới hạn hiển thị đến 9
      displayValue = 0;
    }
    displayDigit(displayValue);
  }

  delay(500);
}

// Hàm hiển thị số trên LED 7 đoạn
void displayDigit(int num) {
  Serial.print("Displaying: ");
  Serial.println(num); // In ra số đang hiển thị
  for (int i = 0; i < 7; i++) {
    // Nếu LED là Active Low, hãy đảo ngược giá trị
    digitalWrite(segmentPins[i], numbers[num][i] == 1 ? LOW : HIGH);
  }
}
