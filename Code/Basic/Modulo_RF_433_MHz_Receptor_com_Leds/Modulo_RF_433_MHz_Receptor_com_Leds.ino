#include <RH_ASK.h>
#include <SPI.h>

#define ledAzul 2
#define ledVermelho 3
#define ledVerde 4

RH_ASK receptor;

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  
  receptor.init();
  Serial.println("Receptor RF iniciado.");
}

void loop() {
  uint8_t buf[10]; 
  uint8_t buflen = sizeof(buf);

  if (receptor.recv(buf, &buflen)) {
    buf[buflen] = '\0'; // Garante que seja uma string válida
    Serial.print("Mensagem recebida: ");
    Serial.println((char*)buf);

    // Percorre a sequência recebida e aciona os LEDs na ordem certa
    for (int i = 0; i < buflen; i++) {
      if (buf[i] == '1') {
        Serial.println("Acendendo LED Verde.");
        digitalWrite(ledVerde, HIGH);
        delay(500);
        digitalWrite(ledVerde, LOW);
      }
      if (buf[i] == '2') {
        Serial.println("Acendendo LED Vermelho.");
        digitalWrite(ledVermelho, HIGH);
        delay(500);
        digitalWrite(ledVermelho, LOW);
      }
      if (buf[i] == '3') {
        Serial.println("Acendendo LED Azul.");
        digitalWrite(ledAzul, HIGH);
        delay(500);
        digitalWrite(ledAzul, LOW);
      }
      delay(500); // Pequena pausa entre os LEDs
    }
  }
}
