#include <DHT.h>

#define DHTPIN 2          // Pin kết nối cảm biến DHT
#define DHTTYPE DHT22     // Loại cảm biến DHT (DHT22)
#define LED1 3            // LED cho mức 1
#define LED2 4            // LED cho mức 2
#define LED3 5            // LED cho mức 3

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

void loop() {
    // Đọc dữ liệu từ cảm biến
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Kiểm tra xem giá trị có hợp lệ không
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Điều khiển LED dựa trên nhiệt độ và độ ẩm
    if (temperature > 35) {
        // Nhiệt độ ở mức cao nhất
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
    } else if (temperature > 30) {
        // Mức 2
        if (humidity > 70) {
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
        } else {
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, LOW);
        }
    } else if (temperature > 25) {
        // Mức 1
        if (humidity > 70) {
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
        } else {
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
        }
    } else {
        // Nhiệt độ thấp
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
    }

    // Đợi một chút trước khi đọc lại
    delay(2000);
}
