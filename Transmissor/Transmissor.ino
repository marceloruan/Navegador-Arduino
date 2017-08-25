#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Inicializa o NRF24L01 nos pinos 9 (CE) e 10 (CS) do Arduino Uno
RF24 radio(9,10);

// Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE13CBAF433LL;

void setup()
{ 
 
  while (!Serial)
  Serial.begin(57600);
  Serial.println("Iniciando transmissão");
  
  // Inicializa a comunicacao do NRF24L01
  radio.begin();

  //Retentativas
  radio.setRetries(15, 15);
  
  // Entra em modo de transmissao
  radio.openWritingPipe(pipe);
  
}

void loop()
{
  
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  
  delay(1000);
}
