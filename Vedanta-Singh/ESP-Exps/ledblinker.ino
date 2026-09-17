
const int potPin = 25; // Pin connected to the potentiometer output
const int ledPin = 23; // Pin connected to the LED
const int buttonPin = 18; // Pin connected to the button

bool isRunning = false; // State of the program

void setup() {
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as an input with pullup
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // Check if the button is pressed
    delay(20); // Debounce delay
    if (digitalRead(buttonPin) == LOW) { // Confirm the button press
      isRunning = !isRunning; // Toggle the running state
      while (digitalRead(buttonPin) == LOW); // Wait for button release
      delay(20); // Debounce delay
    }
  }

  if (isRunning) {
    pinMode(ledPin, OUTPUT);
    int potValue = analogRead(potPin); // Read the potentiometer value (0-4095)
    int interval = map(potValue, 0, 4095, 50, 500); // Map to delay range
    digitalWrite(ledPin, HIGH); // Turn the LED on
    delay(interval); // Wait for the mapped delay interval
    digitalWrite(ledPin, LOW); // Turn the LED off
    delay(interval); // Wait for the mapped delay interval
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Delay Interval: ");
    Serial.println(interval);
  } else {
    int potValue = analogRead(potPin); // Read the potentiometer value (0-4095)
    int voltage = map(potValue, 0, 4095, 255, 0); // Map to PWM
    float volt = voltage*3.3/255.0; // Map to screen
    analogWrite(ledPin,voltage);
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(" | Napeti: ");
    Serial.println(volt);
    delay(100);
  }
}

