#include <ESP8266WiFi.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Nome da rede e senha */
const char *ssid = "AP_TECLADO";
const char *password = "teste123";

WiFiServer server(80);

/* Acesse a rede em 192.168.4.1*/

void setup() {

  delay(1000);
  Serial.begin(115200);

  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  int codigo[4];
  int pos = 0;

  /* Disponibilidade de cliente no servidor */
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  /* Novo cliente no servidor */
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  /* Requerimento do cliente */
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  /* Transformando o comando do botão em um comando digital */
  if (request.indexOf("1") != -1) {
    codigo[pos++] = 1;
    Serial.println("1");
  } else if (request.indexOf("2") != -1) {
    codigo[pos++] = 2;
    Serial.println("2");
  }else if (request.indexOf("3") != -1) {
    codigo[pos++] = 3;
    Serial.println("3");
  }else if (request.indexOf("4") != -1) {
    codigo[pos++] = 4;
    Serial.println("4");
  }else if (request.indexOf("5") != -1) {
    codigo[pos++] = 5;
    Serial.println("5");
  }else if (request.indexOf("6") != -1) {
    codigo[pos++] = 6;
    Serial.println("6");
  }else if (request.indexOf("7") != -1) {
    codigo[pos++] = 7;
    Serial.println("7");
  }else if (request.indexOf("8") != -1) {
    codigo[pos++] = 8;
    Serial.println("8");
  }else if (request.indexOf("9") != -1) {
    codigo[pos++] = 9;
    Serial.println("9");
  }else if (request.indexOf("0") != -1) {
    codigo[pos++] = 0;
    Serial.println("0");
  }else if ((request.indexOf("*") != -1) || (request.indexOf("#") != -1)) {
    Serial.println("S");
  }
  if (pos == 4) {
    pos = 0;
  }

  delay(10);

  /* Construção do HTML */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><title>Teclado</title><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='stylesheet' type='text/css' media='screen' href='main.css'></head>");
  client.println("<body><div><a href=\"1\"><button>1</button></a><a href=\"2\"><button>2</button></a><a href=\"3\"><button>3</button></a>");
  client.println("<br><input type='submit' value='4' style='width: 70px; height: 70px;'><input type='submit' value='5' style='width: 70px; height: 70px;'><input type='submit' value='6' style='width: 70px; height: 70px;'>");
  client.println("<br><input type='submit' value='7' style='width: 70px; height: 70px;'><input type='submit' value='8' style='width: 70px; height: 70px;'><input type='submit' value='9' style='width: 70px; height: 70px;'>");
  client.println("<br><input type='submit' value='*' style='width: 70px; height: 70px;'><input type='submit' value='0' style='width: 70px; height: 70px;'><input type='submit' value='#' style='width: 70px; height: 70px;'>");
  client.println("</div></body></html>");

  delay(1);
  Serial.println("Exiting Loop().");
  Serial.println("");

}
