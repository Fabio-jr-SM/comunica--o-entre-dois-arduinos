#include <RH_ASK.h> 
#include <SPI.h> 

#define botaoAzul 2
#define botaoVermelho 3
#define botaoVerde 4
#define botaoEnviar 5

RH_ASK transmissor;

char sequencia[10]; 
int indice = 0;

// Definição de delimitadores para enquadramento
#define STX 0x02  // Início da mensagem
#define ETX 0x03  // Fim da mensagem

// Função para calcular o CRC8
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
  pinMode(botaoAzul, INPUT);
  pinMode(botaoVermelho, INPUT);
  pinMode(botaoVerde, INPUT);
  pinMode(botaoEnviar, INPUT);
  
  transmissor.init();
  Serial.println("Transmissor RF iniciado.");
}

void loop() {
  if (digitalRead(botaoVerde) == HIGH) {
    if (indice < 7) {  // Mantemos espaço para STX, ETX e CRC
      sequencia[indice++] = '1';
      Serial.println("Botão Verde pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoVermelho) == HIGH) {
    if (indice < 7) {
      sequencia[indice++] = '2';
      Serial.println("Botão Vermelho pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoAzul) == HIGH) {
    if (indice < 7) {
      sequencia[indice++] = '3';
      Serial.println("Botão Azul pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoEnviar) == HIGH) {
    char frame[12];  // Buffer para a mensagem enquadrada
    frame[0] = STX;  // Adiciona cabeçalho
    memcpy(&frame[1], sequencia, indice);  // Copia a sequência
    uint8_t crc = calcularCRC8((uint8_t *)sequencia, indice);
    //crc++; //Teste para Erro de CRC
    frame[indice + 1] = crc;  // Adiciona CRC
    frame[indice + 2] = ETX;  // Adiciona rodapé
    frame[indice + 3] = '\0'; // Finaliza string
    
    Serial.print("Enviando sequência com CRC: ");
    Serial.print(frame);
    Serial.print(" CRC Calculado: ");
    Serial.println(crc, HEX);

    transmissor.send((uint8_t *)frame, indice + 3);
    transmissor.waitPacketSent();

    indice = 0;  // Reseta buffer
    delay(1200);  // Pequeno atraso para controle de fluxo
  }
}
