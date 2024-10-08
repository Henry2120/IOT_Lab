// Khai báo các chân LED
int ledPins[] = {2, 3, 4, 5, 6, 7}; // Các chân nối với LED
const int buttonPin = 8;  // Chân nối với nút bấm
int buttonState = 0;      // Biến lưu trạng thái nút bấm hiện tại
int lastButtonState = 0;  // Biến lưu trạng thái nút bấm trước đó
int diceNumber = 0;       // Biến lưu kết quả xúc xắc

void setup() {
  // Cài đặt các chân LED là đầu ra
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Cài đặt chân nút bấm là đầu vào
  pinMode(buttonPin, INPUT);

  // Khởi tạo Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Đọc trạng thái nút bấm hiện tại
  buttonState = digitalRead(buttonPin);

  // Kiểm tra nếu trạng thái nút chuyển từ LOW (thả) sang HIGH (nhấn)
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Sáng đèn lần lượt từ trái sang phải
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(200); // Dừng 200ms giữa mỗi lần sáng đèn
      digitalWrite(ledPins[i], LOW);
    }
    
    // Sáng đèn lần lượt từ phải sang trái
    for (int i = 5; i >= 0; i--) {
      digitalWrite(ledPins[i], HIGH);
      delay(200); // Dừng 200ms giữa mỗi lần sáng đèn
      digitalWrite(ledPins[i], LOW);
    }

    // Tạo số ngẫu nhiên từ 1 đến 6
    diceNumber = random(1, 7);

    // Hiển thị số xúc xắc bằng cách bật số đèn tương ứng
    showDice(diceNumber);

    // In kết quả ra Serial Monitor
    Serial.print("Số xúc xắc tung ra: ");
    Serial.println(diceNumber);

    // Dừng lại 1 giây để người dùng xem
    delay(1000);

    // Chớp tắt các đèn hiển thị số xúc xắc 6 lần
    for (int i = 0; i < 6; i++) {
      blinkDiceLEDs(diceNumber);
    }

    // Sau khi chớp tắt, tắt tất cả các đèn
    turnOffAllLEDs();
  }

  // Cập nhật trạng thái nút bấm trước đó
  lastButtonState = buttonState;
}

// Hàm để hiển thị số xúc xắc
void showDice(int num) {
  // Tắt tất cả các đèn trước
  turnOffAllLEDs();

  // Bật đúng số đèn dựa trên giá trị xúc xắc
  for (int i = 0; i < num; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// Hàm để tắt tất cả các đèn
void turnOffAllLEDs() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Hàm để chớp tắt các đèn dựa trên số xúc xắc
void blinkDiceLEDs(int num) {
  // Tắt các đèn đang hiển thị số xúc xắc
  for (int i = 0; i < num; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(500); // Dừng trong nửa giây

  // Bật lại các đèn dựa trên số xúc xắc
  for (int i = 0; i < num; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(500); // Dừng trong nửa giây
}
