#include <esp_now.h>
#include <WiFi.h>


uint8_t broadcastAddress[] = {0x6C, 0xC8, 0x40, 0x34, 0xBC, 0x10};

typedef struct struct_message {
  int x;
  int y;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

float currentX = 90;
float currentY = 90;
float speed = 1.0; 

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Baslatilamadi");
    return;
  }

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Eslesme Basarisiz");
    return;
  }
}

void loop() {
  int readX = analogRead(34);
  int readY = analogRead(35);

  bool moving = false;


  if (readX > 3200) { currentX += speed; moving = true; } 
  else if (readX < 800) { currentX -= speed; moving = true; }

  if (readY > 3200) { currentY += speed; moving = true; } 
  else if (readY < 800) { currentY -= speed; moving = true; }


  currentX = constrain(currentX, 0, 180);
  currentY = constrain(currentY, 0, 180);

  myData.x = (int)currentX;
  myData.y = (int)currentY;

  if (moving) {
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }
  
  delay(10); 
}
