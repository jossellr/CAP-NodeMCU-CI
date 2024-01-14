#include <ESP8266WiFi.h>

// Configuración de la comunicación.
const char* SSID = "MY_SSID";
const char* PASSWORD = "MY_PASSWORD";

void setup() {
  Serial.begin(9600);

  // Se establece la conexión.
  WiFi.mode(WIFI_STA);
  WiFi.hostname("NodeMCU-ESP8266");
  WiFi.setAutoReconnect(true);
  WiFi.begin(SSID, PASSWORD);

  // Comprobamos el si se ha conectado satisfactoriamente.
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.println("Connecting to WiFi..");
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Mostramos información de la comunicación.
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("My IP:");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
}

void loop() {
  // No hacemos nada, por ahora.
}