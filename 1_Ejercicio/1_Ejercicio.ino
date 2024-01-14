#include <ESP8266WiFi.h>

// Configuración básica : SSID y contraseña.
const char SSID[] = "NodeMCU-ESP8266";
const char PASSWORD[] = "12345678";

void setup() {
  Serial.begin(9600);

  // Se establece el modo como punto de acceso.
  WiFi.mode(WIFI_AP);

  // Se establece la configuración básica.
  WiFi.softAP(SSID, PASSWORD);
  
  // Primero imprimimos la dirección del punto de acceso sin configurar.
  Serial.print("Direccion IP Access Point - por defecto: ");
  Serial.println(WiFi.softAPIP());
  
  // En segundo lugar, se imprime la dirección MAC del dispositivo.
  Serial.print("Direccion MAC Access Point: ");
  Serial.println(WiFi.softAPmacAddress());

  // Otros elementos de configuración de la red.
  IPAddress local_ip(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  // Se imprime esta nueva configuración.
  Serial.print("Access Point - Nueva direccion IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}