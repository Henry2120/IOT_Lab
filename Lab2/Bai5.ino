#define PIR_PIN 2  // Chân kết nối với cảm biến PIR
unsigned long motionDetectedTime = 0; 
bool lastState = LOW; // Trạng thái trước đó
bool motionState = false; // Trạng thái hiện tại

void setup() {
    Serial.begin(9600);    // Khởi động Serial Monitor
    pinMode(PIR_PIN, INPUT); // Đặt chân PIR là đầu vào
}

void loop() {
    int pirValue = digitalRead(PIR_PIN); // Đọc giá trị từ cảm biến PIR

    if (pirValue == HIGH) {
        // Nếu cảm biến phát hiện chuyển động
        if (lastState == LOW) { // Chỉ khi trạng thái trước đó là LOW
            motionDetectedTime = millis(); // Bắt đầu đếm thời gian
            motionState = true; // Cập nhật trạng thái chuyển động
        }
    } else {
        motionState = false; // Đặt lại trạng thái khi không có chuyển động
    }

    // Kiểm tra nếu đã có chuyển động liên tục trong 2 giây
    if (motionState && (millis() - motionDetectedTime >= 2000)) {
        Serial.println("Motion detected!");
    } else if (!motionState) {
        Serial.println("No motion.");
    }

    lastState = pirValue; // Cập nhật trạng thái trước đó
    delay(100); // Giảm thời gian delay để cải thiện độ nhạy
}

