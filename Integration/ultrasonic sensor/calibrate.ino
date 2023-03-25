// Define the pins used by the ultrasonic sensor
#define trigPin 2
#define echoPin 3

// Define variables for distance and duration
long duration;
int distance;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Set the trigPin as an OUTPUT and echoPin as an INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo signal
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for a short period of time before taking another measurement
  delay(500);
}
