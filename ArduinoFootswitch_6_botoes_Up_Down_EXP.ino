/*
 * Código criado para Amplitube e Plugins de Guitarra.
 * 6 pedais, sendo 4 para patches e 2 para subir e descer bancos.
 * 1 potenciômetro para pedal de Expressão e Volume.
 * Criado por Alcimar Ramos
 * https://youtube.com/c/alcimarramos
 */

/* Bibliotecas utilizadas */
#include "MIDIUSB.h"
#include <Control_Surface.h> /* Biblioteca para uso de Potênciometros */
USBMIDI_Interface midi;

/* Definindo nome para os pinos de entrada, onde ficam os botões */ 
#define pino2 2  /*  pedal patch1 */
#define pino3 3  /*  pedal patch2 */
#define pino4 4  /*  pedal patch3 */
#define pino5 5  /*  pedal patch4 */
#define pino6 6 /* pedal Bank Down */
#define pino7 7 /* pedal Bank Up */

/* Variáveis que receberão  o acionamento dos botões nos pinos de entrada */
int pedal1;
int pedal2;
int pedal3;
int pedal4;
int bank_Down;
int bank_Up;

int i = 0;
int bank = 0;
int numBank = 32; /* aqui você escolhe o número de bancos que deseja usar, 32 é a quantidade do Amplitube 4 */

unsigned long tempoInicio = 0;
unsigned long tempoBotao = 0;

bool estadoBotao;
bool estadoBotaoAnt;

bool estadoBotao2;
bool estadoBotaoAnt2;

int espera = 333; /* Tempo em ms até poder enviar o comando novamente */
byte channel = 0; 

void SendMIDI(byte channel, byte patch) {
     midiEventPacket_t event = {0x0C, 0xC0  | channel, patch};
     MidiUSB.sendMIDI(event);
}

/* Potenciômetro CC para pedal ed Expressão */
CCPotentiometer potentiometer {
   A5, /*--------------------------------- Pino Analógico do Potênciometro */
  {MIDI_CC::Channel_Volume, CHANNEL_1}, /* Channel volume para channel 1 */
};

void setup() {
  Serial.begin(115200); /* inicia comunicação serial e define a velocidade */

/* Initializando Control Surface */
  Control_Surface.begin();

/* Definindo pinos de entrada */
  pinMode(pino2, INPUT_PULLUP);
  pinMode(pino3, INPUT_PULLUP);
  pinMode(pino4, INPUT_PULLUP);
  pinMode(pino5, INPUT_PULLUP);
  pinMode(pino6, INPUT_PULLUP);
  pinMode(pino7, INPUT_PULLUP);
  
/* Definindo saída dos pinos dos LEDs dos Patches */
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  apagaLed();/*-------------- Apaga todos os LEDs */
  SendMIDI(channel, 0);/*---- Inicia o primeiro Patch */
  digitalWrite(A0, HIGH);/*-- Inicia o primeiro LED aceso */
    
}

void loop() {
/*
Aqui a brincadeira começa rsrsrs
Algumas funções foram definidas em um arquivo separado gerando uma guia chamada "func" , visando a organização do código.
*/

/* loop da biblioteca o Control Surface */
   Control_Surface.loop(); 

/* Variáveis que recebem  o acionamento dos botões nos pinos de entrada */
   pedal1 = digitalRead(pino2);
   pedal2 = digitalRead(pino3);
   pedal3 = digitalRead(pino4);
   pedal4 = digitalRead(pino5);
   bank_Down = digitalRead(pino6);
   bank_Up = !digitalRead(pino7);

/*/////////////////// PEDAL 1 ///////////////////*/
  if ( pedal1 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      SendMIDI(channel, 0 + (bank * 4)); /*------- Envia o patch 1, e sobe, ou desce, 4 presets cada vez que o pedal benco é acionado */
      MidiUSB.flush();  /*------------------------ Enviar mensagem imediatamente */
      led1on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

/*/////////////////// PEDAL 2 ///////////////////*/
  if ( pedal2 == LOW ) { /*----------------------- Se o pedal 2 for pressionado */
      SendMIDI(channel, 1 + (bank * 4)); /*------- Envia o patch 2 e sobe, ou desce, 4 presets cada vez que o pedal benco é acionado */
      MidiUSB.flush();  /*------------------------ Enviar mensagem imediatamente */
      led2on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

/*/////////////////// PEDAL 3 ///////////////////*/
  if ( pedal3 == LOW ) { /*----------------------- Se o pedal 3 for pressionado */
      SendMIDI(channel, 2 + (bank * 4)); /*------- Envia o patch 3 e sobe, ou desce, 4 presets cada vez que o pedal benco é acionado */
      MidiUSB.flush();  /*------------------------ Enviar mensagem imediatamente */
      led3on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

/*/////////////////// PEDAL 4 ///////////////////*/
  if ( pedal4 == LOW ) { /*----------------------- Se o pedal 4 for pressionado */
      SendMIDI(channel, 3 + (bank * 4)); /*------- Envia o patch 4 e sobe, ou desce, 4 presets cada vez que o pedal benco é acionado */
      MidiUSB.flush();  /*------------------------ Enviar mensagem imediatamente */
      led4on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

/*/////////////////// BANK UP / DOWN /////////////////*/

   //Ao apertar o botão banco
  if ( bank_Up && !estadoBotaoAnt2 ) {
    if (tempoInicio == 0) {
      tempoInicio = millis();
    }
  }  

  //Ao soltar o botão banco
  if (tempoInicio > 200) {  //Filtro Debounce
    if (!bank_Up && estadoBotaoAnt2) {
      tempoBotao = millis() - tempoInicio;
      tempoInicio = 0;
  }

 //Comando 1
  if ((tempoBotao > 0) && (tempoBotao <= 500)) {
       tempoBotao = 0;
       Serial.println("Comando 1 executado");
       bankUp();
 }
 
  //Comando 2
  if (tempoBotao > 500) {
      tempoBotao = 0;
      Serial.println("Comando 2 executado");
      bankDown();
    }
  
  estadoBotaoAnt2 = bank_Up;
  delay(20);
  } 
}


/* --------------------------------------------------------------------- */
/* ****************************** FUNÇÔES ****************************** */
/* --------------------------------------------------------------------- */


/* Acende o Led 1 e apaga os demais */
void led1on() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
}

/* Acende o Led 2 e apaga os demais */
void led2on() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
}

/* Acende o Led 3 e apaga os demais */
void led3on() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  }

/* Acende o Led 4 e apaga os demais */
void led4on() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
}

/* Função que apaga todos os Leds */
void apagaLed() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
}

/* Função para Descer os Bancos */
void bankDown() {
  if( i > 0 ){
      i--;
      bank = i;
      delay(50);
   }
    if( i == 0 ) { 
       i = 0;
       bank = i;
       delay(50);
      }
}

/* Função para Subir os Bancos */
void bankUp() {
  if( i >= 0 && i <= numBank){
      i++;
      bank = i;
      delay(50);
   }
    if( i > numBank ) { 
       i = 0;
       bank = i;
       delay(50);
      }
}
