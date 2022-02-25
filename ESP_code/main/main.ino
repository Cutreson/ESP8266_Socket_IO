#include <ESP8266WiFi.h>                // Thư viện dùng để kết nối WiFi của ESP8266
#include <WebSocketsClient.h>           // Thư viện WebSocketsClient
const char* ssid = "SUNHOUSENM";         // Tên của mạng WiFi mà bạn muốn kết nối đến
const char* password = "Shg@2021";   // Mật khẩu của mạng WiFi
const int led = 15;                      // Đèn led ở chân GPIO2
WebSocketsClient webSocket;
void setup() {
  Serial.begin(115200);                 // Khởi tạo kết nối Serial để truyền dữ liệu đến máy tính
  pinMode(led, OUTPUT);
  startWiFi();
  connectWebSocket();
}
void loop() {
  webSocket.loop();
}
void startWiFi() {
  WiFi.begin(ssid, password);           // Kết nối vào mạng WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  // Chờ kết nối WiFi được thiết lập
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n");
  Serial.println("Connection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());       // Gởi địa chỉ IP đến máy tinh
}
void connectWebSocket() {
  webSocket.begin("172.16.4.223", 3000, "/");          // Địa chỉ websocket server, port và URL
  webSocket.onEvent(webSocketEvent);
  // webSocket.setAuthorization("user", "password");        // Sử dụng thông tin chứng thực nếu cần
  webSocket.setReconnectInterval(5000);                     // Thử lại sau 5s nếu kết nối không thành công
}
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:                         // Sự kiện khi client ngắt kết nối
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:                            // Sự kiện khi client kết nối
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      webSocket.sendTXT("Connected");          // Thông báo kết nối thành công
      break;
    case WStype_TEXT:                                 // Sự kiện khi nhận được thông điệp dạng TEXT
      Serial.printf("[WSc] get text: %s\n", payload);
      webSocket.sendTXT("Hi Server!");               // Gởi thông điệp đến server
      break;
    case WStype_BIN:                                  // Sự kiện khi nhận được thông điệp dạng BINARY
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);
      // webSocket.sendBIN(payload, length);
      break;
  }
}
