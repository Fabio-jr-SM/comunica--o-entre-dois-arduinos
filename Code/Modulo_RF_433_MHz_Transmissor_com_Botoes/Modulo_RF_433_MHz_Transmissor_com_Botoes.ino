//Módulo RF 433 MHz Controlando LEDs a distancia
//Por GE Projetos e Tutoriais

#include <RH_ASK.h> //Biblioteca Radiohead
#include <SPI.h> 

//Definimos os pinos dos botões
#define botaoAzul 2
#define botaoVermelho 3
#define botaoVerde 4

//Declaramos uma variável RH_ASK que será nosso transmissor RF
RH_ASK transmissor;

void setup()
{
  //Declaramos os Botões como entradas
  pinMode(botaoAzul,INPUT);
  pinMode(botaoVermelho,INPUT);
  pinMode(botaoVerde,INPUT);
  //Inicializamos o transmissor
  transmissor.init();
}

void loop()
{
  //Declaramos 3 mensagens diferentes
  //para cada botao apertado sera enviada uma mensagem
    const char *verd = "1verd.......";
    const char *verm = "2verm.......";
    const char *azul = "3azul.......";
    if(digitalRead(botaoVerde)==HIGH) {
      transmissor.send((uint8_t *)verd, strlen(verd));
      transmissor.waitPacketSent();
      delay(1000);
    }
    if(digitalRead(botaoVermelho)==HIGH) {
      transmissor.send((uint8_t *)verm, strlen(verm));
      transmissor.waitPacketSent();
      delay(1000);
    }
    if(digitalRead(botaoAmarelo)==HIGH) {
      transmissor.send((uint8_t *)amar, strlen(amar));
      transmissor.waitPacketSent();
      delay(1000);
    }
}
