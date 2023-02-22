const int PIR_PIN = 2; // Pin 2 is set to PIR 
const int MOISTURE_PIN = 3; // Pin 3 is set to get input from Soil Moisture Sensor

const int LED_PIN_1 = 8; // Pin 8 set to output LED 1
const int LED_PIN_2 = 9; // Pin 9 set to output LED 2

volatile int motionDetected = 0; // set to 0 if no motion and set to 1 if motion detected
volatile int moistureDetected = 0; // To know if any moisture is detected throught the sensor 

void setup()
{
    pinMode(PIR_PIN, INPUT);
    pinMode(MOISTURE_PIN, INPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(PIR_PIN), motion, CHANGE); // Attaching the interrupt to the PIR sensor
    attachInterrupt(digitalPinToInterrupt(MOISTURE_PIN), soilMoisture, CHANGE); // Attaching the interrupt to Soil moisture 

    Serial.begin(9600); 
}

void loop()
{
    
}

void motion()
{
    motionDetected = digitalRead(PIR_PIN);
    if (motionDetected == 1)        // Motion Detected
    {                              
        digitalWrite(LED_PIN_1, HIGH); 
        Serial.println("Movement Interrupted");
    }
    else            // Motion not Detected
    {                             
        digitalWrite(LED_PIN_1, LOW); 
    }
}

void soilMoisture()
{
    moistureDetected = digitalRead(MOISTURE_PIN);
    if (moistureDetected != 0)      // If moisture is detected and value of moistureDetected is changed
    {
        digitalWrite(LED_PIN_2, HIGH);
        Serial.println("Soil Moisture Interrupted");
    }
    else            // If moisture is not detected
    {
        digitalWrite(LED_PIN_2, LOW);
    }
}
