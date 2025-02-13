#include <RH_ASK.h> 
#include <SPI.h> 

// Definição dos pinos
#define botaoAzul 2
#define botaoVermelho 3
#define botaoVerde 4
#define botaoEnviar 5

// Criando o transmissor RF
RH_ASK transmissor;

// Array para armazenar a sequência de cores pressionadas
char sequencia[10]; 
int indice = 0;

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(botaoAzul, INPUT);
  pinMode(botaoVermelho, INPUT);
  pinMode(botaoVerde, INPUT);
  pinMode(botaoEnviar, INPUT);
  
  transmissor.init();
  Serial.println("Transmissor RF iniciado.");
}

void loop() {
  if (digitalRead(botaoVerde) == HIGH) {
    if (indice < 10) {
      sequencia[indice++] = '1'; // Adiciona '1' para o LED verde
      Serial.println("Botão Verde pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoVermelho) == HIGH) {
    if (indice < 10) {
      sequencia[indice++] = '2'; // Adiciona '2' para o LED vermelho
      Serial.println("Botão Vermelho pressionado.");
    }
    delay(300);
  }

  if (digitalRead(botaoAzul) == HIGH) {
    if (indice < 10) {
      sequencia[indice++] = '3'; // Adiciona '3' para o LED azul
      Serial.println("Botão Azul pressionado.");
    }
    delay(300);
  }

  // Se o botão de enviar for pressionado, a sequência é transmitida
  if (digitalRead(botaoEnviar) == HIGH) {
    sequencia[indice] = '\0'; // Adiciona fim de string
    Serial.print("Enviando sequência: ");
    Serial.println(sequencia);
    
    transmissor.send((uint8_t *)sequencia, strlen(sequencia));
    transmissor.waitPacketSent();
    
    // Limpa o buffer para a próxima sequência
    indice = 0;
    delay(1000);
  }
}
