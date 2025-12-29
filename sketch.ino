#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// [IOT ADDITION] Include Network Libraries
#include <WiFi.h>
#include <ThingSpeak.h>

// --- COMPONENTS & PINOUT ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo scannerServo;

const int trigPin = 5;
const int echoPin = 18;
const int servoPin = 23;
const int buzzerPin = 13;

// Motor Pins
const int mL_fwd = 26;
const int mL_back = 27;
const int mR_fwd = 12;
const int mR_back = 14;

// Line Sensors
const int ir[5] = {15, 4, 16, 17, 19}; 

// Mode: 0 = Auto Line Follower, 1 = Manual Keyboard Control
int operationMode = 1; // Default to Manual

// [IOT ADDITION] Network & Cloud Configuration
const char* ssid = "Wokwi-GUEST"; // Virtual Wi-Fi
const char* password = "";
WiFiClient  client;

// !!! REPLACE WITH YOUR DETAILS !!!
unsigned long myChannelNumber = CHANNEL ID;         // <--- PASTE CHANNEL ID HERE
const char * myWriteAPIKey = "API KEY";  // <--- PASTE WRITE API KEY HERE

// Timer variables (ThingSpeak allows 1 update every 15 seconds)
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

void setup() {
  Serial.begin(115200); 
  
  lcd.init(); lcd.backlight();
  scannerServo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  for(int i=0; i<5; i++) pinMode(ir[i], INPUT);
  
  pinMode(mL_fwd, OUTPUT); pinMode(mL_back, OUTPUT);
  pinMode(mR_fwd, OUTPUT); pinMode(mR_back, OUTPUT);

  // [IOT ADDITION] Initialize Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected.");
  
  // [IOT ADDITION] Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Initial Feedback
  lcd.setCursor(0,0); lcd.print("SYSTEM READY");
  lcd.setCursor(0,1); lcd.print("MANUAL MODE");
  
  Serial.println("\n\n=========================================");
  Serial.println("      ROBOT CONTROL SYSTEM V1.0      ");
  Serial.println("=========================================");
  Serial.println("[ CONTROL GUIDE ]");
  Serial.println("  [W] or [F] : Move Forward");
  Serial.println("  [S] or [B] : Move Backward");
  Serial.println("  [A] or [L] : Turn Left");
  Serial.println("  [D] or [R] : Turn Right");
  Serial.println("  [X]        : Stop Immediately");
  Serial.println("  [1]        : Switch Mode (Auto/Manual)");
  Serial.println("=========================================");
  Serial.println("System Ready. Waiting for input...\n");
}

void loop() {
  // --- 1. OBSTACLE CHECK ---
  int distance = getDistance();
  bool obstacleDetected = (distance > 0 && distance <= 20);

  // [IOT ADDITION] Send Data to Cloud (Every 15 Seconds)
  if ((millis() - lastTime) > timerDelay) {
    
    // Field 1: Distance
    ThingSpeak.setField(1, distance);
    // Field 2: Status (1 if obstacle detected, 0 if safe)
    ThingSpeak.setField(2, obstacleDetected ? 1 : 0);
    
    // Push to cloud
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
      Serial.println(">> ThingSpeak Update Successful.");
    } else {
      Serial.println(">> ThingSpeak Error: " + String(x));
    }
    lastTime = millis();
  }

  if (obstacleDetected) {
    
    // CASE A: We are in AUTO MODE -> Take Action!
    if (operationMode == 0) {
       // 1. Stop and Warn
       stopBot();
       tone(buzzerPin, 1000);
       lcd.setCursor(0,0); lcd.print("!! OBSTACLE !!  ");
       Serial.println(">> AUTO: Obstacle! Taking Evasive Action...");
       delay(1000); // Wait 1 second
       
       // 2. Go Back (Reverse)
       noTone(buzzerPin);
       lcd.setCursor(0,0); lcd.print("AVOIDING: BACK  ");
       moveBack();
       delay(800); // Back up for 0.8 seconds
       
       // 3. Turn Right
       lcd.setCursor(0,0); lcd.print("AVOIDING: RIGHT ");
       turnRight();
       delay(600); // Turn right for 0.6 seconds
       
       // 4. Resume
       stopBot();
       lcd.setCursor(0,0); lcd.print("MODE: AUTO LINE ");
       Serial.println(">> AUTO: Path Cleared. Resuming.");
    } 
    
    // CASE B: We are in MANUAL MODE -> Just Stop (Safety)
    else {
       stopBot();
       tone(buzzerPin, 1000); 
       lcd.setCursor(0,0); lcd.print("!! OBSTACLE !!  ");
    }
  } 
  
  // IF NO OBSTACLE
  else {
    noTone(buzzerPin);
    
    // Refresh Display Text (to clear any old "Avoiding" messages)
    if(operationMode == 0) { lcd.setCursor(0,0); lcd.print("MODE: AUTO LINE "); }
    else { lcd.setCursor(0,0); lcd.print("MODE: MANUAL    "); }
  }

  // --- 2. KEYBOARD INPUT ---
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    // In Manual Mode, if obstacle is there, block Fwd/Turn
    if (obstacleDetected && operationMode == 1 && toupper(cmd) != 'S' && cmd != '1') {
       Serial.println("!! BLOCKED: Path Obstructed !!");
    } else {
       handleKeyboard(cmd);
    }
  }

  // --- 3. AUTO PILOT ---
  // Only run if safe AND in Auto Mode
  if (!obstacleDetected && operationMode == 0) {
    runAutoPilot(); 
  }
}

void handleKeyboard(char cmd) {
  cmd = toupper(cmd);

  if (cmd == '1') {
    operationMode = !operationMode;
    stopBot();
    lcd.clear();
    if(operationMode == 1) {
      lcd.print("MODE: MANUAL");
      Serial.println("\n>> Switched to MANUAL MODE");
    } else {
      lcd.print("MODE: AUTO LINE");
      Serial.println("\n>> Switched to AUTO LINE MODE");
    }
    return;
  }

  if (operationMode == 1) {
    if (cmd == 'W' || cmd == 'F') { 
      moveFwd(); updateScreen("MOVING: FORWARD"); 
    } 
    else if (cmd == 'S' || cmd == 'B') { 
      moveBack(); updateScreen("MOVING: BACKWARD"); 
    } 
    else if (cmd == 'A' || cmd == 'L') { 
      turnLeft(); updateScreen("MOVING: LEFT"); 
    } 
    else if (cmd == 'D' || cmd == 'R') { 
      turnRight(); updateScreen("MOVING: RIGHT"); 
    } 
    else if (cmd == 'X') { 
      stopBot(); updateScreen("STOPPED"); 
    }
  }
}

void runAutoPilot() {
  int s_center = digitalRead(ir[2]);
  int s_left = digitalRead(ir[1]);
  int s_right = digitalRead(ir[3]);

  if (s_center == 0) moveFwd();
  else if (s_left == 0) turnLeft();
  else if (s_right == 0) turnRight();
  else stopBot();
}

void updateScreen(String msg) {
  lcd.setCursor(0,1); lcd.print("                "); 
  lcd.setCursor(0,1); lcd.print(msg);
  Serial.print(">> Command: ");
  Serial.println(msg);
}

// --- MOVEMENT ---
void moveFwd() {
  digitalWrite(mL_fwd, HIGH); digitalWrite(mR_fwd, HIGH);
  digitalWrite(mL_back, LOW); digitalWrite(mR_back, LOW);
}
void moveBack() {
  digitalWrite(mL_fwd, LOW); digitalWrite(mR_fwd, LOW);
  digitalWrite(mL_back, HIGH); digitalWrite(mR_back, HIGH);
}
void turnLeft() {
  digitalWrite(mL_fwd, LOW); digitalWrite(mR_fwd, HIGH);
  digitalWrite(mL_back, HIGH); digitalWrite(mR_back, LOW); 
}
void turnRight() {
  digitalWrite(mL_fwd, HIGH); digitalWrite(mR_fwd, LOW);
  digitalWrite(mL_back, LOW); digitalWrite(mR_back, HIGH); 
}
void stopBot() {
  digitalWrite(mL_fwd, LOW); digitalWrite(mR_fwd, LOW);
  digitalWrite(mL_back, LOW); digitalWrite(mR_back, LOW);
}

int getDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long d = pulseIn(echoPin, HIGH);
  return (d==0)? 400 : (d*0.034/2);
}