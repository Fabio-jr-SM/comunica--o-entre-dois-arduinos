#include <RH_ASK.h>
#include <SPI.h>

#define ledAzul 2
#define ledVermelho 3
#define ledVerde 4

RH_ASK receptor;

// Função para calcular o CRC8 (mesma do transmissor)
uint8_t calcularCRC8(const uint8_t *dados, uint8_t tamanho) {
  uint8_t crc = 0x00;
  for (uint8_t i = 0; i < tamanho; i++) {
    crc ^= dados[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x07;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

void setup() {
  Serial.begin(9600);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  
  receptor.init();
  Serial.println("Receptor RF iniciado.");
}

void loop() {
  uint8_t buf[11];  // Buffer maior para receber dados + CRC
  uint8_t buflen = sizeof(buf);

  if (receptor.recv(buf, &buflen)) {
    if (buflen < 2) return; // Mensagem inválida

    uint8_t crcRecebido = buf[buflen - 1];  // Último byte é o CRC
    uint8_t crcCalculado = calcularCRC8(buf, buflen - 1);  // Recalcula o CRC

    // Exibe o CRC recebido e o calculado
    Serial.print("CRC Recebido: ");
    Serial.println(crcRecebido, HEX);
    Serial.print("CRC Calculado: ");
    Serial.println(crcCalculado, HEX);

    if (crcCalculado == crcRecebido) {
      buf[buflen - 1] = '\0';  // Remove o CRC da string
      Serial.print("Mensagem válida recebida: ");
      Serial.println((char*)buf);

      // Ação com base na sequência recebida
      for (int i = 0; i < buflen - 1; i++) {
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
        delay(500);
      }
    } else {
      Serial.println("Erro: CRC inválido! Mensagem descartada.");
    }
  }
}
