// Declarations
const int PIR_PIN = 2; // Initializing the pin 2 as PIR pin
const int LED_PIN = 13; // Initializing the pin 13 as LED pin

volatile int motionDetected = 0; // To know if motion is detected or not

void setup() {
    pinMode(PIR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), motion, CHANGE); // Attaching the motion detection interrupt
}

void loop() {       // Since we are using interrupts in this task, so loop do not have any functions/instructions
    
}

void motion() {
    motionDetected = digitalRead(PIR_PIN);
    if (motionDetected == 1) { // Motion Detected
        digitalWrite(LED_PIN, HIGH); 
    }
    else { // Motion Not Detected
        digitalWrite(LED_PIN, LOW); 
    }
}
