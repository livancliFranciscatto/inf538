/*Trabalho final  INF-538 -  APLICAÇÃO PRÁTICA IoT
 * LIVANCLÍ FRANCISCATTO
 * MATHEUS SOUZA FERREIR
 * MANASSÉS LOIOLA DE SOUZA
 * THAINAN AUGUSTINHO MENEZES
 * Data: 20/09/2021
 * 
 * STATUS ATUAL: LEITURA DE DISTANCIA E ACIONAMENTO SAIDA D0 PARA DISTANCIAS MENORES QUE 11m)
 */

#include <ESP8266WiFi.h> //ESP8266 Core WiFi Library 
#include <math.h>

//nome da rede Wifi que iremos conectar // Possibilidade de criar um vetor com mais redes?
const char* SSID = "LIVA_2.4g";

//dB minimo para identificar a rede
#define MINdB -40

void setup() {
  Serial.begin(115200);
  pinMode(D1,OUTPUT); // Inicializando D1 como saída.
}


void loop() {

 
  int32_t rssi = getRSSI(SSID); //busca o RSSI da rede desejada 
  //double calcDist;
  double signalLevelInDb =double (rssi);;
  double freqInMHz = 2400;
  double dist = (27.55 - (20 * log10(freqInMHz)) + fabs(signalLevelInDb)) / 20.0;
  double calcDist = pow(10, dist);
  Serial.print(SSID);
  Serial.print("   Signal strength: ");
  Serial.print(rssi);
  Serial.println("dBm");
  Serial.print("Distancia: ");
  Serial.print(calcDist);
  Serial.println("m");

 //testando contato de  saida caso a distancia seja menor que 11m até o AP
    if (calcDist < 11){
       digitalWrite(D1, HIGH); //liga led verde SE DISTANCIA AO AP < 11M
    }
    else {
      digitalWrite(D1, LOW); //desliga led verde
    } 
}

//retorna o RSSI da rede buscada (caso não ache, retorna zero)
int32_t getRSSI(const char* target_ssid) {
  byte available_networks = WiFi.scanNetworks(); //escaneia as redes

  for (int network = 0; network < available_networks; network++) {
//    Serial.print(WiFi.SSID(network)); Serial.print(" | "); Serial.println(WiFi.RSSI(network));
    if (WiFi.SSID(network).compareTo(target_ssid) == 0) { //compara se alguma das redes encontradas é a que desejamos  
      return WiFi.RSSI(network); //retorna o SSID da rede
    }
  }
  return 0;
}
