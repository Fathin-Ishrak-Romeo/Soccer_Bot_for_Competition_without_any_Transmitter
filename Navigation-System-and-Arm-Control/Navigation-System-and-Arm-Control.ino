#include "BluetoothSerial.h"
#include <Arduino.h>
#include <ESP32Servo.h>

BluetoothSerial serialBT;
char BT;
int Speed = 50;     //let's start at a much lower speed to provide stability: next experiment

// ── Motor Pins ──────────────────────────────────────
int R1PWM = 19;
int R2PWM = 21;
int L1PWM = 23;
int L2PWM = 22;

// ── LEDC Channels (4-7 to avoid conflict with ESP32Servo) ──
#define rmf 4
#define rmb 5
#define lmf 6
#define lmb 7

// ── Servo ────────────────────────────────────────────
#define SERVO_PIN 18
Servo myServo;
int servoPosition = 0;  // tracks current position: 0° or 140°

// ── Setup ────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  serialBT.begin("RoboKit Garage's Humanoid Robot");  // Your BOT Name

  pinMode(R1PWM, OUTPUT);
  pinMode(R2PWM, OUTPUT);
  pinMode(L1PWM, OUTPUT);
  pinMode(L2PWM, OUTPUT);

  // Motor PWM channels
  ledcSetup(rmf, 5000, 8);
  ledcAttachPin(R1PWM, rmf);
  ledcSetup(rmb, 5000, 8);
  ledcAttachPin(R2PWM, rmb);
  ledcSetup(lmf, 5000, 8);
  ledcAttachPin(L1PWM, lmf);
  ledcSetup(lmb, 5000, 8);
  ledcAttachPin(L2PWM, lmb);

  // Servo - initializes at 0°, stays still on power on
  myServo.attach(SERVO_PIN);
  myServo.write(servoPosition);
}

// ── Main Loop ─────────────────────────────────────────
void loop() {
  while (serialBT.available()) {
    BT = serialBT.read();

    // Speed control
    if (BT == '0') Speed = 50;
    if (BT == '1') Speed = 55;
    if (BT == '2') Speed = 60;
    if (BT == '3') Speed = 65;
    if (BT == '4') Speed = 70;
    if (BT == '5') Speed = 70;
    if (BT == '6') Speed = 70;
    if (BT == '7') Speed = 75;
    if (BT == '8') Speed = 75;
    if (BT == '9') Speed = 75;
    if (BT == 'q') Speed = 75;

    // Movement (unchanged)
    if      (BT == 'F') go_forward();
    else if (BT == 'B') go_backward();
    else if (BT == 'R') go_left();
    else if (BT == 'L') go_right();
    else if (BT == 'S') stop_motors();
    else if (BT == 'G') forward_right();
    else if (BT == 'H') backward_right();
    else if (BT == 'I') forward_left();
    else if (BT == 'J') backward_left();

    // Horn button → toggle servo
    else if (BT == 'V') toggle_servo();
  }
}

// ── Servo Toggle ──────────────────────────────────────
void toggle_servo() {
  servoPosition = (servoPosition == 0) ? 140 : 0;
  myServo.write(servoPosition);
}

// ── Motor Functions (completely unchanged) ─────────────
void go_forward() {
  ledcWrite(rmf, Speed);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, Speed);
  ledcWrite(lmb, 0);
}
void go_backward() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, Speed);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, Speed);
}
void go_left() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, Speed);
  ledcWrite(lmf, Speed);
  ledcWrite(lmb, 0);
}
void go_right() {
  ledcWrite(rmf, Speed);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, Speed);
}
void stop_motors() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, 0);
}
void forward_right() {
  ledcWrite(rmf, Speed);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, 0);
}
void backward_right() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, Speed);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, 0);
}
void forward_left() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, Speed);
  ledcWrite(lmb, 0);
}
void backward_left() {
  ledcWrite(rmf, 0);
  ledcWrite(rmb, 0);
  ledcWrite(lmf, 0);
  ledcWrite(lmb, Speed);
}