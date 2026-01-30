ESP-NOW ile Kablosuz Pan-Tilt Servo Kontrolü

Bu proje, iki adet ESP32 kartının ESP-NOW protokolü üzerinden haberleşerek, bir joystick aracılığıyla iki adet servo motoru (Pan ve Tilt) kablosuz olarak kontrol etmesini sağlar.

🚀 Özellikler
ESP-NOW Protokolü: Wi-Fi ağına ihtiyaç duymadan, düşük gecikmeli doğrudan haberleşme.

Pürüzsüz Hareket (Interpolation): Alıcı tarafındaki matematiksel filtreleme sayesinde servo motorlar titreme yapmadan, akıcı bir şekilde hareket eder.

Hız Kontrolü: Verici üzerindeki speed değişkeni ile hareket hızı ayarlanabilir.

🛠️ Bağlantı Şeması
1. Verici (Transmitter) - Joystick Ünitesi
Joystick'in hareket eksenleri ESP32'nin analog pinlerine bağlanır.

Joystick X Ekseni: GPIO 34
Joystick Y Ekseni: GPIO 35
VCC: 3.3V
GND: GND

2. Alıcı (Receiver) - Servo Ünitesi
Servo motorlar sinyal pinlerinden ESP32'ye bağlanır.

Pan Servosu (Yatay): GPIO 18
Tilt Servosu (Dikey): GPIO 19
VCC: 5V (Servolar için harici güç kaynağı önerilir)
GND: GND (ESP32 ve Güç Kaynağı GND'leri birleştirilmelidir)

💻 Kurulum ve Kullanım
MAC Adresini Öğrenin: Alıcı ESP32'nin MAC adresini öğrenmeniz gerekir. (Bunun için bir "MAC Address Sniffer" kodu kullanabilirsiniz).

Verici Kodunu Güncelleyin: Verici kodundaki broadcastAddress[] dizisine alıcı kartınızın MAC adresini yazın.
C++
uint8_t broadcastAddress[] = {0x6C, 0xC8, 0x40, 0x34, 0xBC, 0x10};

Kütüphaneleri Yükleyin: Arduino IDE üzerinden ESP32Servo kütüphanesini kurduğunuzdan emin olun.

Yükle: Önce alıcıyı sonra vericiyi programlayın.
