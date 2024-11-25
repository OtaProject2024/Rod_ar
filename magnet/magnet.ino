#include <Arduino.h>

const int PIN_MAGNET = 21; // 磁石センサーピン
const int PIN_IN1 = 23;    // バイブレーションモータのピン1
const int PIN_IN2 = 24;    // バイブレーションモータのピン2
const int PIN_MUSIC = 18;  // 音楽再生用ピン

bool magnetState = false;

// バイブレーションのセットアップ
void setupVibration() {
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  motorOff(); // 初期化時にモーターをオフ
}

// 音楽のセットアップ
void setupMusic() {
  pinMode(PIN_MUSIC, OUTPUT);
}

// モーターのオン/オフ
void motorOn() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  Serial.println("vib on");
}

void motorOff() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  Serial.println("vib off");
}

// 音楽のオン/オフ
void musicOn() {
  digitalWrite(PIN_MUSIC, HIGH);
  Serial.println("music on");
  // 音楽再生機能の追加が必要 (例えば、サウンドモジュール)
}

void musicOff() {
  digitalWrite(PIN_MUSIC, LOW);
  Serial.println("music off");
}

// センサーの初期化
void setup() {
  Serial.begin(9600);
  pinMode(PIN_MAGNET, INPUT_PULLUP); // プルアップで設定
  setupVibration();
  setupMusic();
}

// メインループ
void loop() {
  bool currentState = digitalRead(PIN_MAGNET);

  if (currentState != magnetState) {
    if (currentState == LOW) {
      stick(); // 磁石が付いた場合
    } else {
      leave(); // 磁石が離れた場合
    }
    magnetState = currentState;
  }

  delay(100); // 短い遅延
}

// 磁石が付いた時の処理
void stick() {
  motorOff();
  musicOff();
  Serial.println("magnets stick");
}

// 磁石が離れた時の処理
void leave() {
  Serial.println("magnets leave");
  musicOn();
  motorOn();
}
