// Define the pins for the sensors and push button
#define PIR_SENSOR_PIN 2
#define SOIL_SENSOR_PIN A0
#define BUTTON_PIN 8
#define LED_PIN 13

// Define the variables for the sensors and push button
int pirSensorValue = LOW;
float soilMoistureVoltage = 0;
int soilMoistureValue = 0;
int buttonState = LOW;
int ledState = LOW;

// Define the timer variables
int timerCount = 0;
const int userTime = 7000; // 7 seconds

void setup() {
  // Set the input/output pins for the sensors, push button, and the LED
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Enable the PCINT library for the PIR sensor
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18);

  // Enable the PCINT library for the soil moisture sensor
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT8);

  // Enable the PCINT library for the push button
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);

  // Set up the timer interrupt
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624; // (16MHz / (prescaler * desired interrupt frequency)) - 1
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  TIMSK1 |= (1 << OCIE1A);

  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Do nothing in the main loop, all sensing and processing is done in the interrupt routines
}

// Interrupt routine for the PIR sensor
ISR(PCINT2_vect) {
  pirSensorValue = digitalRead(PIR_SENSOR_PIN);
  if (pirSensorValue == HIGH) {
    Serial.println("Motion detected!");
  }
}

// Interrupt routine for the soil moisture sensor
ISR(PCINT1_vect) {
  soilMoistureValue = analogRead(SOIL_SENSOR_PIN);
  soilMoistureVoltage = soilMoistureValue * (5.0 / 1023.0);
  if (soilMoistureVoltage < 2.5) {
    digitalWrite(LED_PIN, HIGH);
    ledState = HIGH;
    Serial.println("Water tank is empty!");
  } else {
    digitalWrite(LED_PIN, LOW);
    ledState = LOW;
  }
}

// Interrupt routine for the push button
ISR(PCINT0_vect) {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.println("Button pressed!");
  }
}

// Interrupt routine for the timer
ISR(TIMER1_COMPA_vect) {
  timerCount++;
  if (timerCount == (userTime / 1000)) {
    Serial.println("Time expired.. Alarm is ON!");
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    timerCount = 0;
  }
}
