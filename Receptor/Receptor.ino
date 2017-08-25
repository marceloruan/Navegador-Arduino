// Programa : NRF24L01 Receptor - Servo motor
// Autor : Arduino e Cia

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Inicializa o NRF24L01 nos pinos 9 (CE) e 10(CS) do Arduino Uno
RF24 radio(9,10);

// Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE13CBAF433LL;

//Variáveis de armazenamento de tempo
unsigned long startTime;
unsigned long elapsedTime;
unsigned long totalTime;
unsigned long mean;

unsigned int samples;

void setup()
{
  while (!Serial);
  Serial.begin(57600);
  
  radio.begin();
  
  radio.openReadingPipe(0, pipe);
  
  radio.startListening();
}

void loop()
{
  while (samples < 40){
    //Tempo em que se inicia a captação
    startTime = micros();
    if (radio.available()){
      char text[32] = {0};
      radio.read(&text, sizeof(text));
      //Tempo decorrido do início até o recebimento
      elapsedTime = micros() - startTime;
      totalTime = totalTime + elapsedTime;
      Serial.print(elapsedTime);
      Serial.println(" µs");
      Serial.println(text);
      samples++;
    }
  }
  
  mean = totalTime/samples;
  Serial.print("Média após ");
  Serial.print(samples);
  Serial.print(" amostras: ");
  Serial.print(mean);
  Serial.println(" µs");
  
  while(1){}
}
