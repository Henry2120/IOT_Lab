int led1 = 13;  // LED 1 nối với chân số 13
int led2 = 12;  // LED 2 nối với chân số 12
int pirSensor = 2;  // Cảm biến PIR nối với chân số 2
int sensorState = 0;  // Trạng thái cảm biến PIR

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pirSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorState = digitalRead(pirSensor);  // Đọc tín hiệu từ cảm biến PIR
 
  if (sensorState == HIGH) {  // Khi phát hiện chuyển động
    Serial.println("Motion detected!");
    digitalWrite(led1, HIGH);  // LED 1 bật
    digitalWrite(led2, LOW);  // LED 2 bật
    delay(200);  // Đèn bật trong 200ms
    digitalWrite(led1, LOW);   // LED 1 tắt
    digitalWrite(led2, HIGH);   // LED 2 tắt
    delay(200);  // Đèn tắt trong 200ms
  } else {  // Không có chuyển động
    Serial.println("No motion.");
    digitalWrite(led1, LOW);  // Đèn ở trạng thái bình thường
    digitalWrite(led2, LOW);  // Đèn ở trạng thái bình thường
  }
}
