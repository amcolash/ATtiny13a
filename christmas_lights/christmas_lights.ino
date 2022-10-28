int PIN = 3;
int COUNT = 5;
int DELAY = 100;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN, OUTPUT);

  for (int i = 0; i < COUNT; i++) {
    digitalWrite(PIN, HIGH);
    delay(DELAY);
    digitalWrite(PIN, LOW);
    delay(DELAY);
  }
}

// the loop function runs over and over again forever
void loop() {
  while(1);
}
