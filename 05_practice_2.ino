
const int LED_PIN = 7;




void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

  for (int i = 0; i < 5; i++){
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);

  }

  digitalWrite(LED_PIN, LOW);

  while (1) {

  }

}






