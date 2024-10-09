// Khai báo chân cảm biến và đèn LED
const int pulsePin = A0;  // Cảm biến Pulse Sensor
const int ledPin = 13;    // Đèn LED
int pulseValue = 0;       // Giá trị đọc từ cảm biến
unsigned long previousMillis = 0;  // Để điều khiển tốc độ chớp của LED
int heartRate = 0;  // Nhịp tim tính toán
int ledState = LOW; // Trạng thái của LED

// Các thông số tốc độ chớp LED theo nhịp tim
const int fastBlinkInterval = 200;    // Nhịp tim cao: chớp nhanh
const int mediumBlinkInterval = 500;  // Nhịp tim trung bình: chớp trung bình
const int slowBlinkInterval = 1000;   // Nhịp tim thấp: chớp chậm

void setup() {
  pinMode(ledPin, OUTPUT);  // Đặt chế độ cho chân LED
  Serial.begin(9600);       // Khởi tạo Serial để theo dõi dữ liệu
}

void loop() {
  pulseValue = analogRead(pulsePin);  // Đọc giá trị từ cảm biến nhịp tim
  heartRate = map(pulseValue, 0, 1023, 40, 180);  // Giả định nhịp tim từ 40 - 180 bpm

  // Kiểm tra nếu không có tín hiệu từ cảm biến (giá trị rất nhỏ hoặc không thay đổi)
  if (pulseValue < 20 || pulseValue > 1000) {  // Thêm điều kiện kiểm tra tín hiệu bị lỗi hoặc ngoài khoảng
    digitalWrite(ledPin, HIGH);  // Đèn luôn sáng nếu không có tín hiệu
  } else {
    // Điều khiển tốc độ chớp đèn LED dựa trên nhịp tim
    unsigned long currentMillis = millis();

    int blinkInterval;  // Thời gian chớp LED theo mức độ nhịp tim

    // Xác định tốc độ chớp theo nhịp tim
    if (heartRate > 120) {
      blinkInterval = fastBlinkInterval;  // Nhịp tim cao: chớp nhanh
    } else if (heartRate > 80) {
      blinkInterval = mediumBlinkInterval;  // Nhịp tim trung bình: chớp trung bình
    } else {
      blinkInterval = slowBlinkInterval;  // Nhịp tim thấp: chớp chậm
    }

    // Đổi trạng thái LED nếu đã tới thời gian chớp tiếp theo
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = (ledState == LOW) ? HIGH : LOW;  // Đảo trạng thái LED
      digitalWrite(ledPin, ledState);
    }
  }

  // In ra nhịp tim để kiểm tra
  Serial.print("Heart Rate: ");
  Serial.println(heartRate);
}