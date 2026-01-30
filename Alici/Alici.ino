#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo panServo;
Servo tiltServo;

typedef struct struct_message {
  int x;
  int y;
} struct_message;

struct_message incomingReadings;
float targetX = 90, targetY = 90;
float currentX = 90, currentY = 90;
float smoothing = 0.1; 

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  targetX = incomingReadings.x;
  targetY = incomingReadings.y;
}

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  panServo.attach(18);
  tiltServo.attach(19);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() == ESP_OK) {
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  }
}

void loop() {

  currentX += (targetX - currentX) * smoothing;
  currentY += (targetY - currentY) * smoothing;

  panServo.write((int)currentX);
  tiltServo.write((int)currentY);
  
  delay(15); 
}
