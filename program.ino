#include <SoftwareSerial.h>

// Definování pinů pro Bluetooth modul
#define RX_PIN 10
#define TX_PIN 11

// Definování pinů pro motory
#define MOTOR1_PWM 3
#define MOTOR1_DIR 4
#define MOTOR2_PWM 5
#define MOTOR2_DIR 6

// Nastavení SoftwareSerial pro Bluetooth
SoftwareSerial BTSerial(RX_PIN, TX_PIN);

void setup() {
  // Nastavení pinů motorů jako výstupy
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR1_DIR, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);
  pinMode(MOTOR2_DIR, OUTPUT);

  // Nastavení komunikace s Bluetooth modulem a sériového monitoru
  BTSerial.begin(9600);
  Serial.begin(9600);

  // Výchozí stav motorů - zastavení
  stopMotors();
}

void loop() {
  // Kontrola, zda je k dispozici nějaký znak z Bluetooth
  if (BTSerial.available()) {
    char command = BTSerial.read();
    Serial.println(command); // Pro zobrazení přijatého příkazu v sériovém monitoru

    // Zpracování přijatého příkazu
    switch (command) {
      case 'F': // Dopředu
        moveForward();
        break;
      case 'B': // Dozadu
        moveBackward();
        break;
      case 'L': // Doleva
        turnLeft();
        break;
      case 'R': // Doprava
        turnRight();
        break;
      case 'S': // Zastavit
        stopMotors();
        break;
    }
  }
}

// Funkce pro pohyb dopředu
void moveForward() {
  digitalWrite(MOTOR1_DIR, HIGH);
  analogWrite(MOTOR1_PWM, 255);
  digitalWrite(MOTOR2_DIR, HIGH);
  analogWrite(MOTOR2_PWM, 255);
}

// Funkce pro pohyb dozadu
void moveBackward() {
  digitalWrite(MOTOR1_DIR, LOW);
  analogWrite(MOTOR1_PWM, 255);
  digitalWrite(MOTOR2_DIR, LOW);
  analogWrite(MOTOR2_PWM, 255);
}

// Funkce pro zatáčení doleva
void turnLeft() {
  digitalWrite(MOTOR1_DIR, LOW);
  analogWrite(MOTOR1_PWM, 255);
  digitalWrite(MOTOR2_DIR, HIGH);
  analogWrite(MOTOR2_PWM, 255);
}

// Funkce pro zatáčení doprava
void turnRight() {
  digitalWrite(MOTOR1_DIR, HIGH);
  analogWrite(MOTOR1_PWM, 255);
  digitalWrite(MOTOR2_DIR, LOW);
  analogWrite(MOTOR2_PWM, 255);
}

// Funkce pro zastavení motorů
void stopMotors() {
  analogWrite(MOTOR1_PWM, 0);
  analogWrite(MOTOR2_PWM, 0);
}