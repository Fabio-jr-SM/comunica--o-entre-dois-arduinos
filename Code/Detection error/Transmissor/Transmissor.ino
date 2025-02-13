#include <RH_ASK.h> 
#include <SPI.h> 

#define botaoAzul 2
#define botaoVermelho 3
#define botaoVerde 4
#define botaoEnviar 5

RH_ASK transmissor;

char sequencia[10]; 
int indice = 0;

// Função para calcular o CRC8
uint8_t calcularCRC8(const uint8_t *dados, uint8_t tamanho) {
  uint8_t crc = 0x00;
  for (uint8_t i = 0; i < tamanho; i++) {
    crc ^= dados[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x07;  // Polinômio CRC-8 (x^8 + x^2 + x^1 + 1)
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
    if (indice < 9) {  // Mantemos um espaço para o CRC
      sequencia[indice++] = '1';
      Serial.println("Botão Verde pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoVermelho) == HIGH) {
    if (indice < 9) {
      sequencia[indice++] = '2';
      Serial.println("Botão Vermelho pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoAzul) == HIGH) {
    if (indice < 9) {
      sequencia[indice++] = '3';
      Serial.println("Botão Azul pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoEnviar) == HIGH) {
    // Calcula o CRC8 da sequência e adiciona ao final
    uint8_t crc = calcularCRC8((uint8_t *)sequencia, indice);

    //crc += 1;  // Modifica o CRC para testar erro

    sequencia[indice++] = crc;  // Adiciona o CRC na sequência
    sequencia[indice] = '\0';   // Adiciona o fim da string

    Serial.print("Enviando sequência com CRC: ");
    Serial.print(sequencia);
    Serial.print(" CRC Calculado: ");
    Serial.println(crc, HEX);  // Exibe o CRC em formato hexadecimal

    transmissor.send((uint8_t *)sequencia, indice);
    transmissor.waitPacketSent();

    // Limpa o buffer para a próxima sequência
    indice = 0;
    delay(1000);
  }
}
