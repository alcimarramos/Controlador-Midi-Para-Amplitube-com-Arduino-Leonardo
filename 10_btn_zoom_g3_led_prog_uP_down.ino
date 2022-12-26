/*
 * Código criado para ZOOM G3/G3x provavelmente funcional na linha G1on e MS.
 * 10 pedais para patches.
 * O 5º pedal de cima, e 5º pedal de baixo sobem e descem banco ao serem pressionados por 2 segundos.
 * Criado por Alcimar Ramos
 * https://youtube.com/c/alcimarramos
 * https://www.instagram.com/alcimar_ramos
 */

/* Bibliotecas utilizadas */
#include <MIDI.h>
#include <Usb.h>
#include <usbhub.h>
#include <usbh_midi.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/* Definindo nome para os pinos de entrada, onde ficam os botões */ 
#define pino2 2   /*  pedal patch1 */
#define pino3 3   /*  pedal patch2 */
#define pino4 4   /*  pedal patch3 */
#define pino5 5   /*  pedal patch4 */
#define pino6 6   /*  pedal patch5 e Bank Down */
#define pino7 A0  /*  pedal patch6 */
#define pino8 A1  /*  pedal patch7 */
#define pino9 A2  /*  pedal patch8 */
#define pino10 A3 /*  pedal patch9 */
#define pino11 A4 /*  pedal patch10 e Bank Up */

/* Pino onde liga o DIN dos LEDs */
#define PIN 7

/* Numero de leds */
#define NUMPIXELS 10

Adafruit_NeoPixel pixels=Adafruit_NeoPixel(NUMPIXELS,PIN,NEO_GRB+NEO_KHZ800);

//Definindo comunicação Midi USB
USB Usb; 
USBH_MIDI Midi(&Usb);

/* Variáveis recebendo patches do Banco A */
byte patchA0 = 0x00;
byte patchA1 = 0x01;
byte patchA2 = 0x02;
byte patchA3 = 0x03;
byte patchA4 = 0x04;
byte patchA5 = 0x05;
byte patchA6 = 0x06;
byte patchA7 = 0x07;
byte patchA8 = 0x08;
byte patchA9 = 0x09;

/* Variáveis que receberão  o acionamento dos botões nos pinos de entrada */
int pedal1;
int pedal2;
int pedal3;
int pedal4;
int pedal5;
int pedal6;
int pedal7;
int pedal8;
int bank_Down;
int bank_Up;
int i = 0;
int bank = 0;

unsigned long tempoInicio = 0;
unsigned long tempoBotao = 0;

bool estadoBotao;
bool estadoBotaoAnt;

bool estadoBotao2;
bool estadoBotaoAnt2;
int espera = 333; /* Tempo em ms até poder enviar o comando novamente */

void setup() {

/* Definindo pinos de entrada */
  pinMode(pino2, INPUT_PULLUP);
  pinMode(pino3, INPUT_PULLUP);
  pinMode(pino4, INPUT_PULLUP);
  pinMode(pino5, INPUT_PULLUP);
  pinMode(pino6, INPUT_PULLUP);
  pinMode(pino7, INPUT_PULLUP);
  pinMode(pino8, INPUT_PULLUP);
  pinMode(pino9, INPUT_PULLUP);
  pinMode(pino10, INPUT_PULLUP);
  pinMode(pino11, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(50);
  apagaLed();

  Serial.begin(115200); /* inicia comunicação serial e define a velocidade */
  iniciar();            /* inicia comunicação MIDI USB */

}


void loop() {
/*
Aqui a brincadeira começa rsrsrs
*/

//Variáveis que recebem  o acionamento dos botões nos pinos de entrada

   pedal1 = digitalRead(pino2);
   pedal2 = digitalRead(pino3);
   pedal3 = digitalRead(pino4);
   pedal4 = digitalRead(pino5);
   bank_Down = !digitalRead(pino6);
   pedal5 = digitalRead(pino7);
   pedal6 = digitalRead(pino8);
   pedal7 = digitalRead(pino9);
   pedal8 = digitalRead(pino10);
   bank_Up = !digitalRead(pino11);


//////////////////// PEDAL 1 ////////////////////
  if ( pedal1 == LOW ) { /*----------------------- Se o pedal 1 for pressionado */
      SendMIDI(patchA1 + (bank * 10)); /*--------- Envia o patch A1, e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led1on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 2 ////////////////////
  if ( pedal2 == LOW ) { /*----------------------- Se o pedal 2 for pressionado */
      SendMIDI(patchA2 + (bank * 10)); /*--------- Envia o patch A2 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led2on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 3 ////////////////////
  if ( pedal3 == LOW ) { /*----------------------- Se o pedal 3 for pressionado */
      SendMIDI(patchA3 + (bank * 10)); /*--------- Envia o patch A3 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led3on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 4 ////////////////////
  if ( pedal4 == LOW ) { /*----------------------- Se o pedal 4 for pressionado */
      SendMIDI(patchA4 + (bank * 10)); /*--------- Envia o patch A4 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led4on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 6 ////////////////////
  if ( pedal5 == LOW ) { /*----------------------- Se o pedal 5 for pressionado */
      SendMIDI(patchA6 + (bank * 10)); /*--------- Envia o patch A5 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led10on(); /*------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 7 ////////////////////
  if ( pedal6 == LOW ) { /*----------------------- Se o pedal 6 for pressionado */
      SendMIDI(patchA7 + (bank * 10)); /*--------- Envia o patch A6 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led9on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 8 ////////////////////
  if ( pedal7 == LOW ) { /*----------------------- Se o pedal 7 for pressionado */
      SendMIDI(patchA8 + (bank * 10)); /*--------- Envia o patch A7 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led8on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

//////////////////// PEDAL 9 ////////////////////
  if ( pedal8 == LOW ) { /*----------------------- Se o pedal 8 for pressionado */
      SendMIDI(patchA9 + (bank * 10)); /*--------- Envia o patch A8 e sobe, ou desce, 10 presets cada vez que o pedal benco é acionado */
      led7on(); /*-------------------------------- Liga o Led do pedal */
      delay(espera); /*--------------------------- Tempo até poder enciar o comando novamente */ 
  }

////////////// PEDAL 10 - BANK UP ///////////////

   //Se o pedal 10 for pressionado
   if ( bank_Up && !estadoBotaoAnt2 ) {
      if (tempoInicio == 0) {
      tempoInicio = millis();
    }
  }  

  //Ao soltar o pedal 10
  if (tempoInicio > 200) {  //Filtro Debounce
      if (!bank_Up && estadoBotaoAnt2) {
      tempoBotao = millis() - tempoInicio;
      tempoInicio = 0;
  }

  //Comando 1
  if ((tempoBotao > 0) && (tempoBotao <= 500)) {
     tempoBotao = 0;
     Serial.println("Comando 1 executado");
     SendMIDI(patchA0 + (bank * 10));
     led6on();
 }
 
  //Comando 2
  if ( tempoBotao > 500 ) {
     tempoBotao = 0;
     Serial.println("Comando 2 executado");
     bankUp();
     led6on_();
     ledsoff();
     led6on_();
     ledsoff();
     led6on_();
     ledsoff();
    }
  
  estadoBotaoAnt2 = bank_Up;
  delay(20);
  }

////////////// PEDAL 5 - BANK DOWN //////////////

   //Se o pedal 5 for pressionado
   if ( bank_Down && !estadoBotaoAnt ) {
      if (tempoInicio == 0) {
      tempoInicio = millis();
    }
  }  

  //Ao soltar o pedal 5
  if (tempoInicio > 200) {  //Filtro Debounce
      if (!bank_Down && estadoBotaoAnt) {
      tempoBotao = millis() - tempoInicio;
      tempoInicio = 0;
  }

  //Comando 1
  if ((tempoBotao > 0) && (tempoBotao <= 500)) {
     tempoBotao = 0;
     Serial.println("Comando 1 executado");
     SendMIDI(patchA5 + (bank * 10));
     led5on();
 }
 
  //Comando 2
  if ( tempoBotao > 500 ) {
     tempoBotao = 0;
     Serial.println("Comando 2 executado");
     bankDown();
     led5on_();
     ledsoff();
     led5on_();
     ledsoff();
     led5on_();
     ledsoff();
    }
  
  estadoBotaoAnt = bank_Down;
  delay(20);
  }
  
}


/* --------------------------------------------------------------------- */
/* ****************************** FUNÇÔES ****************************** */
/* --------------------------------------------------------------------- */


void iniciar(){
  if (Usb.Init() == -1) { /* Testa se o USB foi conectado e aguarda conectar */
    while (1);
  }
  while (Usb.getUsbTaskState() != USB_STATE_RUNNING) {
    Usb.Task(); /* se USB iniciou, continue */
  }
  for (int i = 0; i < 4; i++) { /* forçando os 4 primeiros comandos enviados pra pedaleira que são ignorados */
    SendMIDI(patchA1);
    delay(200);
  }
  led1on(); //Acende o Led 1
}

void SendMIDI(byte number) { /* Função para enviar os comandos Midi */
  Usb.Task();                /* Iniciando tarefa Midi */
  byte Message[2];           /* Construindo mensagem midi (2 bytes) */
  Message[0] = 0xC0;         /* 0xC0 para Program Change */
  Message[1] = number;       /* Number é o program/patch */
  Midi.SendData(Message);    /* Envia a mensagem */
  delay(10);
}

/* Acende o Led 1 e apaga os demais */
void led1on() {
  pixels.setPixelColor(9, pixels.Color(255,0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}
  
void led1on_() {
  pixels.setPixelColor(9, pixels.Color(0, 255,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 2 e apaga os demais */
void led2on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(255, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

void led2on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 255, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 3 e apaga os demais */
void led3on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(255, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  }
  
void led3on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 255, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 4 e apaga os demais */
void led4on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(255, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}
  
void led4on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 255, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 5 e apaga os demais */
void led5on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(255, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

void led5on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 255, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay (70);
}

/* Acende o Led 6 e apaga os demais */
void led6on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(255, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  }
  
  void led6on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 255, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay (70);
}

/* Acende o Led 7 e apaga os demais */
  void led7on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

  void led7on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 255, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 8 e apaga os demais */
  void led8on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(255, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

  void led8on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 255, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 9 e apaga os demais */
  void led9on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

  void led9on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 255, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

/* Acende o Led 10 e apaga os demais */
  void led10on() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();
}

  void led10on_() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
}

  void ledsoff() {
  pixels.setPixelColor(9, pixels.Color(0, 0,0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
  pixels.setPixelColor(7, pixels.Color(0, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 0));
  pixels.setPixelColor(5, pixels.Color(0, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay (70);
}

/* Função que apaga todos os Leds */
void apagaLed() {
  for (int i = 0; i <= 6 ; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
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
  if( i >= 0 && i <= 9){
      i++;
      bank = i;
      delay(50);
   }
    if( i > 9 ) { 
       i = 0;
       bank = i;
       delay(50);
      }
}
