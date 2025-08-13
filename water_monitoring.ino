#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define WATER_SENSOR 26  // Port B の GPIO26（分圧後の信号）
const char* ssid = "***";
const char* password = "***";
const char* webhook_url = "***";
boolean status_flag = 0;

void setup() {
  M5.begin();
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("WiFi connecting...");
    delay(300);
  }
  M5.Speaker.begin();
  M5.Speaker.setVolume(1);
  Serial.begin(9600);
  pinMode(WATER_SENSOR, INPUT);  
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Water Sensor on GPIO26");
}

void loop() {
  int v = digitalRead(WATER_SENSOR); // 1=乾き, 0=濡れ
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.printf("RAW: %d   ", v);
  M5.Lcd.setCursor(0, 70);
  if (v == LOW) {
    M5.Lcd.print("STATUS: WET     ");
    M5.Speaker.beep();
    delay(100);
    M5.Speaker.mute();
    if (status_flag == 0){
      slack_notify();
      status_flag = 1;
    }
  } else {
    M5.Lcd.print("STATUS: DRY     ");
    status_flag = 0;
  }
  delay(200);
}

boolean slack_notify() {   ///If you use the Get method, include "String msg" as an argument for the function.
  HTTPClient client;
  if(!client.begin(webhook_url)) {
    Serial.println("connect error!");
    return false;
  }
  //client.addHeader("Content-Type", "application/json");
  //String payload = "{\"msg_type\":\"text\",\"content\":{\"text\":\"" + msg + "\"}}";
  //int httpCode = client.POST(payload);
  int httpCode = client.GET();
  if(httpCode > 0) {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK) {
      String line = client.getString();
      Serial.println(line);
    } 
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", client.errorToString(httpCode).c_str());
  }
  client.end();
  return true;
}
