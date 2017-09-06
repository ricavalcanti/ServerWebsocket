#include <Arduino.h>
#include <Hash.h>
#include <SocketIoClient.h>
#include <WiFiManager.h>
#include<ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

//===================================================================================
// DEFINES
//===================================================================================
#define HOST "10.7.227.77" // host de envio
#define PORT 3000 // porta para envio


//===================================================================================
// VARIABLES
//===================================================================================

SocketIoClient socket;
WiFiManager wifi;
String ipStr;
char JSON[200];
//String JSON;

StaticJsonBuffer<100> jsonBuffer1;
StaticJsonBuffer<100> jsonBuffer2;
StaticJsonBuffer<100> jsonBuffer3;

enum commType{sincrona, assincrona};

/*struct dataClient{
  String id;
  String tag;
  String description;
  String ipDisp;
  commType communicationType; //o que é banda morta e timeout
  int state; //ligado ou desligado
  double intensity; //para lampada, perde-se dados de intensidade qdo desliga?
  double consumption;
  String actionAdress; //o que e
};*/

//===================================================================================
// FUNCTIONS
//===================================================================================

void imprime(const char* payload, size_t tam) {
  Serial.println(payload);
}

/*void sendDataClient(const char* dado, size_t tam){
  gerarJson();
  socket.emit("sendDataEvent",jsonChar);
}*/

/*void sendData(dataClient d){

  JSON = String("{ \"status\":{");
  JSON = JSON + String("\"dispositiveId\": \"") + String(d.id) + String("\",");
  JSON = JSON + String("\"tag\":\"")+ String(d.tag) + String("\",");
  JSON = JSON + String("\"ip\":\"") + d.ipDisp + String("\",");
  JSON = JSON + String("\"communicationType\":\"") + String(d.communicationType) + String("\"},");
  JSON = JSON + String("\"configuration\":{");
  JSON = JSON + String("\"state\":\"") + String(d.state) + String("\",");
  JSON = JSON + String("\"consumption\":\"") + String(d.consumption)+ String("\",");
  JSON = JSON + String("\"actionAdress\":\"") + String(d.actionAdress) + String("\"}}");

  const char *jsonChar = JSON.c_str();
  Serial.println(JSON);

  socket.emit("on_test",jsonChar);
}
*/
//===================================================================================
// SETUP
//=================================================================================

void setup() {
  Serial.begin(115200); // inicia o serial
  wifi.autoConnect(); // conectar no ultimo wifi salvo
  socket.begin(HOST, PORT); // inicia a conexão com o servidor

  IPAddress ip = WiFi.localIP();
  ipStr = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);

  //Criando Json
  JsonObject& dataClient = jsonBuffer1.createObject();
  JsonObject& statusData = jsonBuffer2.createObject();
  JsonObject& configurationData = jsonBuffer3.createObject();

  //Atribuindo Valores aos Objetos
  statusData["dispositiveId"] = "ESP001";
  statusData["ip"] = ipStr;
  statusData["tag"] = "LAMPADA";
  statusData["communicationType"] = "sincrona";

  configurationData["state"] = "0";
  configurationData["consumption"] = "100";
  configurationData["actionAdress"] ="endereco";

  dataClient["Status"] = statusData;
  dataClient["Parameters"] = configurationData;

  dataClient.printTo(JSON);
  Serial.println(JSON);  //impressao de teste*/
  socket.emit("on_test",JSON);


//para testar no servidor de Judson
//  socket.on("debug", imprime);

//para testar no servidor de Guilherme
//socket.on("emit_test", imprime);

/*dataClient teste;

teste.id = "ESP001\0";
teste.ipDisp = ipStr;
teste.tag = "LAMPADA\0";
teste.communicationType = sincrona;
teste.description = "este eh um exemplo de descricao\0";
teste.state = 1;
teste.intensity = 75.5;
teste.consumption = 1001.256;
teste.actionAdress = "endereco.teste.com\0";

sendData(teste);*/



}

//===================================================================================
// LOOP
//===================================================================================

void loop() {
  socket.loop();
}
