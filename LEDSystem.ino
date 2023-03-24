int analogInput = 0;
int f = 2;
int e = 3;
int d = 4;
int c = 5;
int b = 6;
int a = 7;
int s = 13;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000;
float R2 = 10000;
int value = 0;
void setup() {
  Serial.begin(9600);
  pinMode(analogInput, INPUT);
  pinMode(s, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  digitalWrite(s, LOW);
  digitalWrite(a, HIGH);
  delay(500);
  digitalWrite(b, HIGH);
  delay(500);
  digitalWrite(c, HIGH);
  delay(500);
  digitalWrite(d, HIGH);
  delay(500);
  digitalWrite(e, HIGH);
  delay(500);
  digitalWrite(f, HIGH);
  delay(500);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
}
void loop() {
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024;
  vin = vout / (R2 / (R1 + R2));
  Serial.println("Input Voltage = ");
  Serial.println(vin);
  if (vin > 12.46) {
    digitalWrite(a, HIGH);
  } else {
    digitalWrite(a, LOW);
  }
  if (vin <= 12.46 && vin > 12.28) {
    digitalWrite(b, HIGH);
  } else {
    digitalWrite(b, LOW);
  }
  if (vin <= 12.28 && vin > 12.12) {
    digitalWrite(c, HIGH);
  } else {
    digitalWrite(c, LOW);
  }
  if (vin <= 12.12 && vin > 11.98) {
    digitalWrite(d, HIGH);
  } else {
    digitalWrite(d, LOW);
  }
  if (vin <= 11.98 && vin > 11.90) {
    digitalWrite(e, HIGH);
  } else {
    digitalWrite(e, LOW);
  }
  if (vin <= 11.90) {
    digitalWrite(f, HIGH);
  } else {
    digitalWrite(f, LOW);
  }
  delay(2000);
}
