# Comunicação entre Dois Arduinos com RF 433 MHz

## Introdução
A comunicação sem fio entre dispositivos é uma tecnologia amplamente utilizada na eletrônica e na automação. Este projeto tem como objetivo demonstrar a transmissão de dados entre dois microcontroladores Arduino Uno utilizando um módulo de RF 433 MHz (transmissor e receptor). A comunicação implementada segue princípios da camada de enlace, incluindo fragmentação de dados e controle do enlace.

## Funcionamento
O sistema consiste em dois Arduinos: um transmissor e um receptor. O transmissor possui três botões que representam cores (vermelho, verde e azul). Quando uma sequência de botões é pressionada, um botão de envio deve ser acionado para transmitir os dados ao receptor. No lado receptor, há três LEDs que piscam conforme a ordem em que os botões foram pressionados.

### Componentes Utilizados
- 2x Arduino Uno
- 1x Módulo RF 433 MHz (transmissor e receptor)
- 3x Push Buttons
- 1x Botão de envio
- 3x LEDs (vermelho, verde e azul)
- Resistores adequados
- Protoboard e jumpers

### Objetivos
- Projetar e montar um circuito para comunicação RF entre dois Arduinos.
- Implementar um protocolo de transmissão de dados na camada de enlace.
- Desenvolver um código-fonte para transmissão e recepção dos sinais via RF.
- Demonstrar a funcionalidade do sistema com a transmissão e recepção de sequências de cores.

## Critérios de Avaliação
| Critério               | Descrição | Pontos |
|-----------------|----------------------------------|--------|
| **Design**        | Diagrama de circuito detalhado e lista de componentes. | 2.5 |
| **Construção**   | Montagem organizada e funcionamento correto. | 2.5 |
| **Código-Fonte** | Implementação clara e estruturada. | 2.5 |
| **Demonstração** | Apresentação e funcionamento prático. | 2.5 |

## Observações
- O projeto pode incluir componentes adicionais, como capacitores, transistores e displays LCD.
- O uso de outros módulos de comunicação não é permitido.
- O código deve implementar funcionalidades de controle de enlace e detecção de erros.
- Relatórios devem ser entregues ao final do projeto, explicando o algoritmo adotado.

## Referência
[Implementação da comunicação RF 433 MHz com Arduino](https://www.youtube.com/watch?v=ccz_2Q1tMt0)

