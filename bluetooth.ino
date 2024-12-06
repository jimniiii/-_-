
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // 블루투스 TX(2), RX(3)

void setup(){
  Serial.begin(9600);         // 시리얼 모니터용
  BTSerial.begin(9600);       // 블루투스 통신 시작
  Serial.println("Bluetooth Ready!");
}

void loop(){
  int sensorValue = analogRead(A0); // 센서 값 읽기
  BTSerial.println(sensorValue);   // 블루투스 모듈로 데이터 전송
  delay(500);                      // 0.5초 대기
}
