#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>

#define IN1 25   // Motor maju
#define IN3 26   // Motor mundur
#define SERVO_PIN 15

Servo steering;

void setup() {
  Serial.begin(115200);
  Dabble.begin("ESP32_RC_CAR"); // Nama Bluetooth

  steering.attach(SERVO_PIN);
  steering.write(90); // posisi netral

  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);

  berhenti();
}

void loop() {
  Dabble.processInput();

  // === Kontrol motor ===
  if (GamePad.isCrossPressed()) {      // Tombol X
    maju();
  }
  else if (GamePad.isTrianglePressed()) { // Tombol segitiga
    mundur();
  }
  else {
    berhenti();
  }

  // === Kontrol steering (servo) ===
  int steerAngle = 90; // netral

  if (GamePad.isLeftPressed()) {
    steerAngle = 60;  // belok kiri
  } 
  else if (GamePad.isRightPressed()) {
    steerAngle = 120; // belok kanan
  }

  steering.write(steerAngle);
}

// === Fungsi motor ===
void maju() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, LOW);
}

void mundur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, HIGH);
}

void berhenti() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
}
