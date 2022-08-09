const int ledPin =  LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
long interval = 1000;
int d = 0;
int state = 0;
unsigned long currentMillis = micros();
/*
void alarm()
  { 
  currentMillis = micros(); 
  if (currentMillis - previousMillis >= interval)
  {   previousMillis = currentMillis;
    if (ledState == LOW) 
    {
      ledState = HIGH;
    } else 
    {
      ledState = LOW;
    }
    digitalWrite(D2, ledState);
    interval = interval+d;
    if (interval == 0)
      {
        d = -d;
        digitalWrite(ledPin, HIGH);
      }
    if (interval == 1000) 
      {
        d = -d;
        digitalWrite(ledPin, LOW);
      }
  }
  Serial.println ("good");
  }
*/

void buzz()
{
  digitalWrite(D2, HIGH);  
}

void buzzoff()
{
  digitalWrite(D2, LOW);  
}

void setup() {
  // set the digital pin as output:
  Serial.begin (115200);
  d = -1;
  pinMode(ledPin, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D5, INPUT_PULLUP);
}

void loop() 
{
//while (digitalRead(D5) == 1){delay (100);};
  if (state == 0)
  {
    if (digitalRead(D5) == 0) 
    {
      state = 1;
    }
  }
  if (state == 1)
  {
    buzz();
    if (digitalRead(D5) == 1) state = 2;
    delay (10);   
  }
  {
    if (state == 2) 
    {
      if (digitalRead(D5) == 0) state = 3;
      delay (10);
    }
  }
  {
    if (state == 3)
    {
      if (digitalRead(D5) == 1) state = 0;
      delay (10);
      buzzoff();
    }
  }
  Serial.println (state);

}