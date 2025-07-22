
#define TRIGGER 2
#define ECHO 7
#define ALARM 10

int echoAlarm;
long duration;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ALARM, OUTPUT);
  pinMode(ECHO, INPUT);
}


void loop() {
  digitalWrite(TRIGGER, LOW);

  if (distance && distance < 70) {

    // Serial.println("ECHO-ALARM: " + echoAlarm);
    digitalWrite(ALARM, HIGH);
    delay(100);

    if ((int)distance > 10) {
      digitalWrite(ALARM, LOW);

      if (distance > 50) delay(300);
      else if (distance > 40) delay(200);
      else if (distance > 30) delay(100);
      else if (distance > 20) delay(50);
      else delay(0);
    }
  } else digitalWrite(ALARM, LOW);

  digitalWrite(TRIGGER, HIGH);
  digitalWrite(TRIGGER, LOW);

  // Reads the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);

  // Calculate the distance in centimeters
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);
}
