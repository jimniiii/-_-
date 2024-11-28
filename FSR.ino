const int FSR_Pins[] = {A3, A2, A1};
int FSR_Values[3];

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  for (int i = 0; i < 3; i++) {
    FSR_Values[i] = analogRead(FSR_Pins[i]);
    Serial.print(FSR_Values[i]);
    Serial.print(",");
  }
  Serial.println();
  delay(1000);
  // put your main code here, to run repeatedly:

}
