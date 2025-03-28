#include <Servo.h>
#include <Keypad.h>

  /("Pressione '' para criar ou resetar senha.");
  ("Pressione 'A' para autenticar.");
  ("Pressione '#' para encerrar.");/

Servo myServo;
String password = "";  // Usando String para facilitar a manipulação

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  pinMode(12, OUTPUT);  // Para o buzzer
  myServo.attach(10);
  myServo.write(0); //Posição inicial do servo(cofre trancado)
}

void loop() {
  char key = keypad.getKey();

  if (key == '*') {
    // Processo para criar ou resetar senha
    password = "";  // Resetando a senha
    while (password.length() < 4) {
      char key = keypad.getKey();
      if (key) {
        password += key;
      }
    }
  }

  else if (key == 'A') {
    // Processo para autenticação
    String temp = "";

    while (temp.length() < 4) {
      char key = keypad.getKey();
      if (key) {
        temp += key;
      }
    }
    // Verificação da senha
    if (temp == password) {
      tone(12,440); //Som senha correta
      delay(100);
      noTone(12);
      myServo.write(90); //Posição do servo quando cofre aberto
    } 
    else {
      tone(12, 262); //Som senha incorreta
      delay(100);
      noTone(12);
    }
  }
    else if(key == '#'){
      tone(12, 262); //Som cofre trancado
      delay(100);
      noTone(12);
      myServo.write(0); //Retorna o servo na posição inicial
    }
