#define PIN_LED 13
unsigned int count, toggle;

int toggle_state(int toggle);

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    // Wait for serial port to connect
  } 
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, toggle); // turn off led

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(++count);
  toggle = toggle_state(toggle); // toggle LED value
  digitalWrite(PIN_LED, toggle); // update LEd status
  delay(1000); // wait for 1000 milliseconds
}

int toggle_state(int toggle) {
  return !toggle;
}
