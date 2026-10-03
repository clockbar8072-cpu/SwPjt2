// Arduino pin assignment
#define PIN_LED   9
#define PIN_TRIG 12   // sonar sensor TRIGGER
#define PIN_ECHO 13   // sonar sensor ECHO

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec) ★ 25ms로 변경
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 300.0   // maximum distance to be measured (unit: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL) // coefficent to convert duration to distance

unsigned long last_sampling_time;   // unit: msec

void setup() {
  // initialize GPIO pins
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // sonar TRIGGER
  pinMode(PIN_ECHO, INPUT);   // sonar ECHO
  digitalWrite(PIN_TRIG, LOW);  // turn-off Sonar 
  
  // initialize serial port
  Serial.begin(57600);
}

void loop() { 
  float distance;
  int pwm_value = 255; // 기본값: LED OFF (Active Low)

  // polling
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // read distance

  // 거리 구간별 LED 밝기(PWM) 계산 (Active Low: 0=최대밝기, 255=꺼짐)
  if (distance <= _DIST_MIN || distance >= _DIST_MAX) {
      pwm_value = 255; // 범위를 벗어나면 꺼짐
  } else if (distance <= 200.0) {
      // 100mm(255:꺼짐) -> 200mm(0:최대밝기)
      pwm_value = (int)(255.0 - (distance - 100.0) * (255.0 / 100.0));
  } else {
      // 200mm(0:최대밝기) -> 300mm(255:꺼짐)
      pwm_value = (int)((distance - 200.0) * (255.0 / 100.0));
  }

  // Active Low 제어를 위해 analogWrite 적용
  analogWrite(PIN_LED, pwm_value);

  // output the distance to the serial port
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",pwm:");       Serial.print(pwm_value);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.println("");
  
  
  // update last sampling time
  last_sampling_time += INTERVAL;
}

// get a distance reading from USS. return value is in millimeter.
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}
