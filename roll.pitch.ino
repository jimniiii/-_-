#include <Wire.h>

int ADXL345 = 0x53;  // ADXL345 I2C 주소

float X_out, Y_out, Z_out;  // 축 데이터 저장
float roll, pitch;          // 실시간 roll, pitch 계산 값
float rollF = 0, pitchF = 0; // 필터링된 값

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // ADXL345 초기화
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D); // Power Control Register
  Wire.write(0x08); // 측정 모드 활성화
  Wire.endTransmission();
  
  delay(100); // 센서 안정화 대기
}

void loop() {
  // ADXL345에서 데이터 읽기
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // 데이터 시작 주소
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // 6바이트 요청

  // X, Y, Z 데이터 읽기
  X_out = (Wire.read() | (Wire.read() << 8));
  Y_out = (Wire.read() | (Wire.read() << 8));
  Z_out = (Wire.read() | (Wire.read() << 8));

  // 센서 값 범위 조정
  X_out = X_out / 256;
  Y_out = Y_out / 256;
  Z_out = Z_out / 256;

  // Roll 및 Pitch 계산
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;

  // 필터링된 값 계산
  rollF = 0.94 * rollF + 0.06 * roll;
  pitchF = 0.94 * pitchF + 0.06 * pitch;

  // 시리얼 모니터 출력
  Serial.print("Roll: ");
  Serial.print(rollF);
  Serial.print(" / Pitch: ");
  Serial.println(pitchF);

  delay(1000); // 데이터 전송 간격
}
