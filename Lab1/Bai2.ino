Bài 2
const int ledPins[] = {2, 3, 4}; // Các chân kết nối với đèn LED
const int numLEDs = 3; // Số lượng đèn LED
const int potPin = A0; // Chân biến trở kết nối với chân analog A0

int potValue = 0; // Giá trị đọc từ biến trở
int delayTime = 0; // Thời gian trễ giữa các lần sáng đèn

void setup() {
  // Thiết lập các chân đèn LED là đầu ra
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Khởi tạo Serial để hiển thị giá trị
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị của biến trở từ 0 đến 1023
  potValue = analogRead(potPin);

  // Chia thành 3 mức: chậm, trung bình và nhanh
  if (potValue < 341) {
    delayTime = 500; // Mức chậm
    Serial.println("Chậm");
  } else if (potValue < 682) {
    delayTime = 250; // Mức trung bình
    Serial.println("Trung bình");
  } else {
    delayTime = 100; // Mức nhanh
    Serial.println("Nhanh");
  }

  // Sáng đèn từ trái sang phải
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], HIGH); // Bật đèn LED
    delay(delayTime);               // Chờ theo giá trị điều chỉnh
    digitalWrite(ledPins[i], LOW);  // Tắt đèn LED
  }

  // Sáng đèn từ phải sang trái
  for (int i = numLEDs - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH); // Bật đèn LED
    delay(delayTime);               // Chờ theo giá trị điều chỉnh
    digitalWrite(ledPins[i], LOW);  // Tắt đèn LED
  }
}
