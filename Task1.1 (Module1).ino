int PIR = 4;
int value = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop()
{
  value = digitalRead(PIR);
  if (value)
  {
    digitalWrite(LED_BUILTIN, 1);
    Serial.println("Motion Detected");
  }
  else
  {
    digitalWrite(LED_BUILTIN, 0);
    Serial.println("No Movement!");
  }
  delay(1000);
}