#define trigPin 13
#define echoPin 12

long minLongestDistance = 5000;
long margin = 10;                         // in cm
int startupTime = 5;                      // in seconds
int delayBetweenMeasurements = 250;       // in ms
int passes = 0;
bool passInPreviousFrame = false;

bool graph = false;
bool logPass = true;

void setup() {
  Serial.begin (9600);

  Serial.println("Startup");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  int tries = startupTime * 1000 / delayBetweenMeasurements;

  // Test to see what the lowest value is if noone passes
  for (int i = 0; i < tries; i++) {
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;

    if (distance < minLongestDistance)
      minLongestDistance = distance;
      
    delay(delayBetweenMeasurements);
  }

  digitalWrite(LED_BUILTIN, HIGH);
   Serial.println("Done");
}

void loop() {
  long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;

    if (distance < minLongestDistance - margin) {
      if (!passInPreviousFrame) {
        passes++;
        if (logPass) {      
          Serial.println("pass");
        }
      }
      passInPreviousFrame = true;
    } else {
      passInPreviousFrame = false;
    }

    if (graph) {
      Serial.print(passes);
      Serial.print("\t");
      Serial.print(minLongestDistance - margin);
      Serial.print("\t");
      Serial.println(distance);
    }
      
    delay(delayBetweenMeasurements);
}
