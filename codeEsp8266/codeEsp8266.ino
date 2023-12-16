#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Wifi name
#define WLAN_SSID       "wifi"
//Wifi password
#define WLAN_PASS       "03062003"

//setup Adafruit
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
//fill your username                   
#define AIO_USERNAME    "vuongadonis"
//fill your key
#define AIO_KEY         "aio_BuuH970UXJ7BwfVNzXus747Yyth8"

//setup MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//setup publish
Adafruit_MQTT_Publish game_play_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/game-play");
Adafruit_MQTT_Publish game_finish_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/game-finish");
Adafruit_MQTT_Publish sensor_info_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensor-info");
Adafruit_MQTT_Publish score_avg_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/game-statistic");
Adafruit_MQTT_Publish time_avg_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/game-time-avg");


// //setup subcribe
Adafruit_MQTT_Subscribe game_play_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/game-play", MQTT_QOS_1);
Adafruit_MQTT_Subscribe game_finish_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/game-statistic", MQTT_QOS_1);
Adafruit_MQTT_Subscribe sensor_info_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/sensor-info", MQTT_QOS_1);
Adafruit_MQTT_Subscribe score_avg_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/game-statistic", MQTT_QOS_1);
Adafruit_MQTT_Subscribe time_avg_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/game-time-avg", MQTT_QOS_1);

int led_counter = 0;
int led_status = HIGH;
String parts[5];
void devideString(String inputString)
{
  int numberOfParts = 0; // Số lượng phần được tách
  int startPos = 0; // Vị trí bắt đầu tìm ký tự phân cách

  for (int i = 0; i < inputString.length(); i++) {
    if (inputString.charAt(i) == '#') {
      parts[numberOfParts] = inputString.substring(startPos, i);
      startPos = i + 1;
      numberOfParts++;
    }
  }
  // Xử lý phần cuối cùng
  if (startPos < inputString.length()) {
    parts[numberOfParts] = inputString.substring(startPos);
    numberOfParts++; 
  }

  // // Hiển thị kết quả
  // for (int i = 0; i < numberOfParts; i++) {
  //   Serial.println(parts[i]);
  // }

}

void lightcallback(char* value, uint16_t len){
  if(value[0] == '0') Serial.print('a');
  if(value[0] == '1') Serial.print('A');
}

void erasePart()
{
  parts[0] = "";
  parts[1] = "";
  parts[2] = "";
  parts[3] = "";
  parts[4] = "";
}

void setup() {
  // put your setup code here, to run once:
  //set pin 2,5 as OUTPUT
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  //set busy pin HIGH
  digitalWrite(5, LOW);

  Serial.begin(115200);

  //connect Wifi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //subscribe light feed
  // light_sub.setCallback(lightcallback);
  mqtt.subscribe(&game_play_sub);
  mqtt.subscribe(&game_finish_sub);
  mqtt.subscribe(&sensor_info_sub);
  mqtt.subscribe(&score_avg_sub);
  mqtt.subscribe(&time_avg_sub);

  //connect MQTT
  while (mqtt.connect() != 0) { 
    mqtt.disconnect();
    delay(500);
  }

  //finish setup, set busy pin LOW
  digitalWrite(5, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  //receive packet
  mqtt.processPackets(1);
  
  //read serial
  if(Serial.available()){
    char msg = Serial.read();

    String receivedString = ""; // Khởi tạo chuỗi để lưu trữ dữ liệu
    receivedString += msg;
    while (Serial.available()) { // Kiểm tra nếu có dữ liệu trong cổng UART
      char incomingByte = Serial.read(); // Đọc dữ liệu từ cổng UART
      receivedString += incomingByte; // Nối dữ liệu vào chuỗi
      delay(2); // Đợi để nhận các byte tiếp theo (tùy thuộc vào tốc độ baudrate)
    }
    devideString(receivedString);
    if(parts[0] == "GAME_FINISH")
    {
      const char *message = parts[1].c_str();
      game_finish_pub.publish(message);
      int message2 = parts[2].toInt();
      score_avg_pub.publish(message2);
      int message3 = parts[3].toInt();
      time_avg_pub.publish(message3);
    }
    if(parts[0] == "GAME_PLAY")
    {
      const char *message = parts[1].c_str();
      game_play_pub.publish(message);
    }
    if(parts[0] == "SENSOR_INFO")
    {
      const char *message = parts[1].c_str();
      sensor_info_pub.publish(message);
    }
    erasePart();
  }
  delay(10);
}