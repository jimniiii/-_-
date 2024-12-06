void setup() {
  Serial.begin(9600);
}

void loop() {
  int heelPressure = analogRead(A0); // 뒤꿈치
  int midPressure = analogRead(A1); // 중간
  int toePressure = analogRead(A2); // 앞꿈치

  Serial.print("뒤꿈치: ");
  Serial.print(heelPressure);
  Serial.print(" 중간: ");
  Serial.print(midPressure);
  Serial.print(" 앞꿈치: ");
  Serial.println(toePressure);

  delay(1000);
}
