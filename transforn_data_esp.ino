#include <WiFi.h>
#include <PubSubClient.h>

// Thay đổi các thông số kết nối WiFi và MQTT tại đây
const char* ssid = "iMyth";
const char* password = "anhhoangdepchai";
const char* mqttServer = "103.1.238.175";
const int mqttPort = 1885;
const char* mqttUser = "test";
const char* mqttPassword = "testadmin";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Đang kết nối WiFi...");
  }

  client.setServer(mqttServer, mqttPort);
  
  while (!client.connected()) {
    Serial.println("Đang kết nối tới máy chủ MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Đã kết nối thành công!");
    } else {
      Serial.print("Kết nối thất bại, mã lỗi = ");
      Serial.print(client.state());
      Serial.println(" Thử kết nối lại sau 5 giây...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Gửi dữ liệu "hello" lên máy chủ MQTT
  client.publish("topic", "hello anh giang, khong di' em nua~ nha");

  delay(5000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Đang kết nối tới máy chủ MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Đã kết nối thành công!");
    } else {
      Serial.print("Kết nối thất bại, mã lỗi = ");
      Serial.print(client.state());
      Serial.println(" Thử kết nối lại sau 5 giây...");
      delay(5000);
    }
  }
}