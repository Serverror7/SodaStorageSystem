/* * Hardware Specs:
 * Serial  -> Input from User/Laptop
 * Serial2 -> Output to Nucleo (TX: 16, RX: 17)
 * GPIO 18 -> Trigger Pin (Rising Edge)
 */
const int TRIGGER_PIN = 18;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); 
  
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, HIGH);
  
  Serial.println("Ready. Enter a number to update stock, or any key for a trigger pulse.");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() > 0) {
      if (isNumeric(input)) {
        // Condition: It's a number -> Send stock to Nucleo
        Serial2.println(input);
        Serial.print("Stock Sent: ");
        Serial.println(input);
      } else {
        // Condition: Not a number -> Pulse GPIO 18
        digitalWrite(TRIGGER_PIN, LOW);
        delay(10); 
        digitalWrite(TRIGGER_PIN, HIGH);
        Serial.println("Non-numeric input detected: Falling edge triggered on GPIO 18.");
      }
    }
  }
}

// Helper function to check if the string contains only digits
bool isNumeric(String str) {
  for (byte i = 0; i < str.length(); i++) {
    if (!isDigit(str.charAt(i))) return false;
  }
  return true;
}