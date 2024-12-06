#include <SoftwareSerial.h>

// 핀 설정
const int heelPin = A0;  // 뒤꿈치 압력 센서 핀
const int midPin = A1;   // 중간 압력 센서 핀
const int toePin = A2;   // 앞꿈치 압력 센서 핀
SoftwareSerial BTSerial(10, 11); // 블루투스 RX, TX 핀

// 임계값 및 상태 변수
const int pressureThreshold = 500; // 압력 임계값
int correctStepCount = 0;          // 올바른 걸음 수
int totalStepCount = 0;            // 총 걸음 수
bool isStepDetected = false;       // 걸음 상태 추적

void setup() {
  Serial.begin(9600);       // 시리얼 통신 시작
  BTSerial.begin(9600);     // 블루투스 통신 시작

  pinMode(heelPin, INPUT);
  pinMode(midPin, INPUT);
  pinMode(toePin, INPUT);

  Serial.println("스마트 인솔 시스템 시작");
}

void loop() {
  // 각 센서 값 읽기
  int heelPressure = analogRead(heelPin);
  int midPressure = analogRead(midPin);
  int toePressure = analogRead(toePin);

  // 총 압력 계산
  int totalPressure = heelPressure + midPressure + toePressure;

  // 데이터 디버깅
  Serial.print("뒤꿈치: ");
  Serial.print(heelPressure);
  Serial.print(" 중간: ");
  Serial.print(midPressure);
  Serial.print(" 앞꿈치: ");
  Serial.println(toePressure);

  // 걸음 유형 분석 및 걸음 수 업데이트
  if (totalPressure > pressureThreshold) {
    if (!isStepDetected) {
      totalStepCount++;
      isStepDetected = true;

      // 걸음 유형 분석
      if (heelPressure > midPressure && midPressure > toePressure) {
        correctStepCount++;
        Serial.println("올바른 걸음 감지!");
        BTSerial.println("올바른 걸음 감지!");
      } else {
        Serial.println("비정상 걸음 감지!");
        BTSerial.println("비정상 걸음 감지!");
      }
    }
  } else {
    isStepDetected = false; // 압력이 줄어들면 걸음 상태 초기화
  }

  // 총 걸음 수 출력
  Serial.print("총 걸음 수: ");
  Serial.println(totalStepCount);
  Serial.print("올바른 걸음 수: ");
  Serial.println(correctStepCount);

  BTSerial.print("총 걸음 수: ");
  BTSerial.println(totalStepCount);
  BTSerial.print("올바른 걸음 수: ");
  BTSerial.println(correctStepCount);

  delay(1000); // 데이터 읽기 주기
}
