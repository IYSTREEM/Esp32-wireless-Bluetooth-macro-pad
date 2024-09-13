#include <BleKeyboard.h>

const int buttonPin1 = 13; // D13
const int buttonPin2 = 12; // D12
const int buttonPin3 = 14; // D14
const int buttonPin4 = 27; // D27
const int buttonPin5 = 26; // D26yy
const int buttonPin6 = 25; // D25
const int buttonPin7 = 33; // D33
const int buttonPin8 = 32; // D32
const int buttonPin9 = 4;  // D04
const int buttonPin10 = 15; // D15
// Rotary Encoder Pins
const int rotaryEncoderPinCLK = 18;
const int rotaryEncoderPinDT = 19;
const int rotaryEncoderPinSW = 21;

BleKeyboard bleKeyboard;

int lastClkState;  // Variable to store the last state of rotary encoder CLK
bool isMuted = false; // Variable to keep track of mute state

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP); // GPIO26 now used
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);

  pinMode(rotaryEncoderPinCLK, INPUT_PULLUP);
  pinMode(rotaryEncoderPinDT, INPUT_PULLUP);
  pinMode(rotaryEncoderPinSW, INPUT_PULLUP);

  lastClkState = digitalRead(rotaryEncoderPinCLK); // Initialize lastClkState
}

void loop() {
  if (bleKeyboard.isConnected()) {
    // Check each button
    if (digitalRead(buttonPin1) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("p");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 1");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin2) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("y");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 2");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin3) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("z");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 3");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin4) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("l");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 4");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin5) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("x");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 5");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin6) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("h");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 6");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin7) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("j");
      bleKeyboard.releaseAll();
      Serial.println("Button 7");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin8) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("n");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 8");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin9) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("m");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 9");
      delay(200); // Debounce delay
    }
    if (digitalRead(buttonPin10) == LOW) {
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("r");
      delay(100);
      bleKeyboard.releaseAll();
      Serial.println("Button 10");
      delay(200);
    }

    // Rotary encoder volume control
    int clkState = digitalRead(rotaryEncoderPinCLK);
    
    if (clkState != lastClkState) {
      // Check direction of rotation
      if (digitalRead(rotaryEncoderPinDT) != clkState) {
        Serial.println("Volume Up");
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP); // Volume up
      } else {
        Serial.println("Volume Down");
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN); // Volume down
      }
    }
    
    lastClkState = clkState; // Update lastClkState

    // Rotary encoder button for mute/unmute
    if (digitalRead(rotaryEncoderPinSW) == LOW) {
      delay(50); // Debounce delay
      if (digitalRead(rotaryEncoderPinSW) == LOW) { // Check again after debounce
        Serial.println(isMuted ? "Unmuting" : "Muting");
        bleKeyboard.write(KEY_MEDIA_MUTE);
        isMuted = !isMuted;
        delay(500); // Delay to prevent multiple triggers
      }
    }
  }
}
