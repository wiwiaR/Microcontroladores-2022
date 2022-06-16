
#include <ESP8266WiFi.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Nome da rede e senha */
const char *ssid = "AP_TECLADO";
const char *password = "chihaya1";

WiFiServer server(80);

/* Acesse a rede em 192.168.4.1*/

void setup() {

  pinMode(D4, INPUT_PULLUP);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);

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
  if (request.indexOf("OFF") != -1) {
    Serial.println("o botão on foi apertado");
    digitalWrite(D1, LOW);
    pinMode(D1, INPUT);
  } else if (request.indexOf("ON") != -1) {
    Serial.println("o botão off foi apertado");
    pinMode(D1, OUTPUT);
    digitalWrite(D1, LOW);

  }

  delay(10);

  /* Construção do HTML */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>table{width:100%;margin:auto;}td{border:solid black;text-align:center;background-color:black;}a{display:block;font-size:200%;text-decoration:none;color:white;}</style></head>");
  client.println("<body><table class=\"table\">");
  client.println("<tr><td><a><br><b>Ventilador");

  client.println("</b><br><br></a></td></tr>");
  client.println("<tr><td><a href=\"/Cooler=ON\"\"><br>ON<br><br></a></td></tr>");
  client.println("<tr><td><a href=\"/Cooler=OFF\"\"><br>OFF<br><br></a></td></tr>");
  client.println("</table></body></html>");

  delay(1);
  Serial.println("Exiting Loop().");
  Serial.println("");

}
