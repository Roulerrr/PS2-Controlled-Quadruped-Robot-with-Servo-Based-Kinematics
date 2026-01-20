#include <Arduino.h>
#include <Servo.h>
#include <PS2X_lib.h>

// Servo definitions - 4 legs (8 servos total)
Servo pivotFrontLeft, liftFrontLeft;
Servo pivotFrontRight, liftFrontRight;
Servo pivotBackLeft, liftBackLeft;
Servo pivotBackRight, liftBackRight;

// Calibration settings
int high = 130;           // Lift height
int walk_speed = 150;     // Default walking speed (delay in ms)

// PS2 Controller
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

// ฟังก์ชันกลับไปตำแหน่งกลาง
void center_servos() {
  pivotFrontLeft.write(90);
  liftFrontLeft.write(110);
  pivotFrontRight.write(90);
  liftFrontRight.write(110);
  pivotBackLeft.write(90);
  liftBackLeft.write(110);
  pivotBackRight.write(90);
  liftBackRight.write(110);
}

// เดินไปข้างหน้า
void WALK_SEQUENCE() {
  // Left front
  liftFrontLeft.write(high);
  delay(50);
  pivotFrontLeft.write(60);
  delay(walk_speed);
  liftFrontLeft.write(110);
  delay(50);
  pivotFrontLeft.write(90);

  // Right back
  liftBackRight.write(high);
  delay(50);
  pivotBackRight.write(140);
  delay(walk_speed);
  liftBackRight.write(110);
  delay(50);
  pivotBackRight.write(90);

  // Right front
  liftFrontRight.write(high);
  delay(50);
  pivotFrontRight.write(120);
  delay(walk_speed);
  liftFrontRight.write(110);
  delay(50);
  pivotFrontRight.write(90);

  // Left back
  liftBackLeft.write(high);
  delay(50);
  pivotBackLeft.write(40);
  delay(walk_speed);
  liftBackLeft.write(110);
  delay(50);
  pivotBackLeft.write(90);
}

// เดินถอยหลัง
void WALKBACK_SEQUENCE() {
  // Right back
  liftBackRight.write(high);
  delay(50);
  pivotBackRight.write(60);
  delay(walk_speed);
  liftBackRight.write(110);
  delay(50);
  pivotBackRight.write(90);

  // Left front
  liftFrontLeft.write(high);
  delay(50);
  pivotFrontLeft.write(140);
  delay(walk_speed);
  liftFrontLeft.write(110);
  delay(50);
  pivotFrontLeft.write(90);

  // Left back
  liftBackLeft.write(high);
  delay(50);
  pivotBackLeft.write(120);
  delay(walk_speed);
  liftBackLeft.write(110);
  delay(50);
  pivotBackLeft.write(90);

  // Right front
  liftFrontRight.write(high);
  delay(50);
  pivotFrontRight.write(40);
  delay(walk_speed);
  liftFrontRight.write(110);
  delay(50);
  pivotFrontRight.write(90);
}

// หมุนซ้าย
void TURN_LEFT_SEQUENCE() {
  liftFrontLeft.write(high);
  delay(50);
  pivotFrontLeft.write(120);
  delay(walk_speed);
  liftFrontLeft.write(110);
  delay(50);
  pivotFrontLeft.write(90);

  liftFrontRight.write(high);
  delay(50);
  pivotFrontRight.write(120);
  delay(walk_speed);
  liftFrontRight.write(110);
  delay(50);
  pivotFrontRight.write(90);

  liftBackRight.write(high);
  delay(50);
  pivotBackRight.write(120);
  delay(walk_speed);
  liftBackRight.write(110);
  delay(50);
  pivotBackRight.write(90);

  liftBackLeft.write(high);
  delay(50);
  pivotBackLeft.write(120);
  delay(walk_speed);
  liftBackLeft.write(110);
  delay(50);
  pivotBackLeft.write(90);
}

// หมุนขวา
void TURN_RIGHT_SEQUENCE() {
  liftFrontRight.write(high);
  delay(50);
  pivotFrontRight.write(60);
  delay(walk_speed);
  liftFrontRight.write(110);
  delay(50);
  pivotFrontRight.write(90);

  liftFrontLeft.write(high);
  delay(50);
  pivotFrontLeft.write(60);
  delay(walk_speed);
  liftFrontLeft.write(110);
  delay(50);
  pivotFrontLeft.write(90);

  liftBackLeft.write(high);
  delay(50);
  pivotBackLeft.write(60);
  delay(walk_speed);
  liftBackLeft.write(110);
  delay(50);
  pivotBackLeft.write(90);

  liftBackRight.write(high);
  delay(50);
  pivotBackRight.write(60);
  delay(walk_speed);
  liftBackRight.write(110);
  delay(50);
  pivotBackRight.write(90);
}

// ขยับขึ้น-ลง
void UP_DOWN() {
  liftFrontLeft.write(high);
  liftFrontRight.write(high);
  liftBackLeft.write(high);
  liftBackRight.write(high);
  delay(500);

  liftFrontLeft.write(110);
  liftFrontRight.write(110);
  liftBackLeft.write(110);
  liftBackRight.write(110);
  delay(500);
}

// เดินไปทางขวา
void WALK_RIGHT_SEQUENCE() {
  liftFrontRight.write(high);
  delay(50);
  pivotFrontRight.write(40);
  delay(walk_speed);
  liftFrontRight.write(110);
  delay(50);
  pivotFrontRight.write(90);

  liftBackLeft.write(high);
  delay(50);
  pivotBackLeft.write(140);
  delay(walk_speed);
  liftBackLeft.write(110);
  delay(50);
  pivotBackLeft.write(90);

  liftBackRight.write(high);
  delay(50);
  pivotBackRight.write(140);
  delay(walk_speed);
  liftBackRight.write(110);
  delay(50);
  pivotBackRight.write(90);

  liftFrontLeft.write(high);
  delay(50);
  pivotFrontLeft.write(40);
  delay(walk_speed);
  liftFrontLeft.write(110);
  delay(50);
  pivotFrontLeft.write(90);
}

// เดินไปทางซ้าย
void WALK_LEFT_SEQUENCE() {
  liftBackLeft.write(high);
  delay(50);
  pivotBackLeft.write(40);
  delay(walk_speed);
  liftBackLeft.write(110);
  delay(50);
  pivotBackLeft.write(90);

  liftFrontRight.write(high);
  delay(50);
  pivotFrontRight.write(140);
  delay(walk_speed);
  liftFrontRight.write(110);
  delay(50);
  pivotFrontRight.write(90);

  liftFrontLeft.write(high);
  delay(50);
  pivotFrontLeft.write(140);
  delay(walk_speed);
  liftFrontLeft.write(110);
  delay(50);
  pivotFrontLeft.write(90);

  liftBackRight.write(high);
  delay(50);
  pivotBackRight.write(40);
  delay(walk_speed);
  liftBackRight.write(110);
  delay(50);
  pivotBackRight.write(90);
}

// ท่านั่ง-ลุก
void SIT_UP() {
  liftFrontRight.write(high);
  liftBackLeft.write(high);
  delay(150);
  pivotFrontRight.write(140);
  pivotBackLeft.write(140);
  delay(walk_speed);
  liftFrontRight.write(110);
  liftBackLeft.write(110);
  delay(150);
  pivotFrontRight.write(90);
  pivotBackLeft.write(90);
  delay(150);

  liftFrontLeft.write(high);
  liftBackRight.write(high);
  delay(150);
  pivotFrontLeft.write(140);
  pivotBackRight.write(140);
  delay(walk_speed);
  liftFrontLeft.write(110);
  liftBackRight.write(110);
  delay(150);
  pivotFrontLeft.write(90);
  pivotBackRight.write(90);
  delay(150);
}

// โบกมือขวา
void HELLO_RIGHT() {
  liftBackLeft.write(130);
  liftBackRight.write(130);
  liftFrontLeft.write(30);
  liftFrontRight.write(30);
  delay(300);
  liftFrontRight.write(110);
  pivotFrontRight.write(120);
  delay(100);
  pivotFrontRight.write(90);
  delay(100);

  for (int i = 0; i < 3; i++) {
    pivotFrontRight.write(120);
    delay(100);
    pivotFrontRight.write(90);
    delay(100);
  }
  delay(100);
}

// โบกมือซ้าย
void HELLO_LEFT() {
  liftBackLeft.write(130);
  liftBackRight.write(130);
  liftFrontLeft.write(30);
  liftFrontRight.write(30);
  delay(300);
  liftFrontLeft.write(110);
  pivotFrontLeft.write(60);
  delay(100);
  pivotFrontLeft.write(90);
  delay(100);

  for (int i = 0; i < 3; i++) {
    pivotFrontLeft.write(60);
    delay(100);
    pivotFrontLeft.write(90);
    delay(100);
  }
  delay(100);
}

void setup() {
  Serial.begin(57600);
  
  // ตั้งค่า PS2 Controller
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true);
  if (error == 0) {
    Serial.println("Found Controller, configured successfully");
  } else {
    Serial.println("Error configuring controller");
  }

  type = ps2x.readType();
  if (type == 1) {
    Serial.println("DualShock Controller Found");
  }

  // เชื่อมต่อ Servos
  pivotFrontLeft.attach(2);
  liftFrontLeft.attach(3);
  pivotFrontRight.attach(4);
  liftFrontRight.attach(5);
  pivotBackLeft.attach(6);
  liftBackLeft.attach(7);
  pivotBackRight.attach(8);
  liftBackRight.attach(9);

  // ตั้งค่าเริ่มต้น
  center_servos();
  Serial.println("Spider Robot Ready!");
}

void loop() {
  if (error == 1) return;

  ps2x.read_gamepad(false, vibrate);

  // เดินไปข้างหน้า (กดปุ่มขึ้นค้าง)
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("Walking Forward");
    WALK_SEQUENCE();
  }
  // เดินถอยหลัง (กดปุ่มลงค้าง)
  else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("Walking Backward");
    WALKBACK_SEQUENCE();
  }
  // เดินไปทางขวา (กดปุ่มขวาค้าง)
  else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("Walking Right");
    WALK_RIGHT_SEQUENCE();
  }
  // เดินไปทางซ้าย (กดปุ่มซ้ายค้าง)
  else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("Walking Left");
    WALK_LEFT_SEQUENCE();
  }
  // หมุนซ้าย (กด L2 ค้าง)
  else if (ps2x.Button(PSB_L2)) {
    Serial.println("Turning Left");
    TURN_LEFT_SEQUENCE();
  }
  // หมุนขวา (กด R2 ค้าง)
  else if (ps2x.Button(PSB_R2)) {
    Serial.println("Turning Right");
    TURN_RIGHT_SEQUENCE();
  }
  // ท่าพิเศษ - กดครั้งเดียว
  else if (ps2x.ButtonPressed(PSB_GREEN)) {
    Serial.println("Triangle - Up/Down");
    UP_DOWN();
    center_servos();
  }
  else if (ps2x.ButtonPressed(PSB_RED)) {
    Serial.println("Circle - Sit Up");
    SIT_UP();
    center_servos();
  }
  else if (ps2x.ButtonPressed(PSB_R1)) {
    Serial.println("R1 - Hello Right");
    HELLO_RIGHT();
    center_servos();
  }
  else if (ps2x.ButtonPressed(PSB_L1)) {
    Serial.println("L1 - Hello Left");
    HELLO_LEFT();
    center_servos();
  }
  // ถ้าไม่กดปุ่มใดเลย ให้กลับตำแหน่งกลาง
  else {
    center_servos();
  }

  // ปรับความเร็ว
  if (ps2x.ButtonPressed(PSB_BLUE)) {  // X - เร็วขึ้น
    walk_speed -= 50;
    if (walk_speed < 50) walk_speed = 50;
    Serial.print("Speed increased, delay: ");
    Serial.println(walk_speed);
  }
  
  if (ps2x.ButtonPressed(PSB_SQUARE)) {  // Square - รีเซ็ตความเร็ว
    walk_speed = 150;
    Serial.println("Speed reset to default: 150");
  }

  delay(50);
}