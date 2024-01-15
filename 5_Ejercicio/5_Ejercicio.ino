#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define MSG_BUFFER_SIZE (50)

// Configuración.
const char* SSID = "MY_SSID";
const char* PASSWORD = "MY_PASSWORD";
const char* BROKER_IP = "BROKER_IP";
const char* TOPIC = "mensaje";

const int PIN_LED = 13;

int value = 0;
unsigned long last_msg = 0;
char msg[MSG_BUFFER_SIZE];

// Cliente MQTT.
WiFiClient esp_client;
PubSubClient client_mqtt(esp_client);

void setup_wifi() {
  // Se establece la conexión.
  WiFi.mode(WIFI_STA);
  WiFi.hostname("NodeMCU-ESP8266 2");
  WiFi.begin(SSID, PASSWORD);

  // Comprobamos el si se ha conectado satisfactoriamente.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  Serial.print("My IP:");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client_mqtt.connected()) {
    String client_name;
    client_name += "esp8266-";
    client_name += String(random(0xffff), HEX);

    Serial.print("Connecting to");
    Serial.println(BROKER_IP);
    Serial.print("as");
    Serial.println(client_name);

    if (client_mqtt.connect((char*)client_name.c_str())) {
      Serial.println("Connecting to MQTT broker");
      Serial.print("Topic to subscribe is: ");
      Serial.println(TOPIC);
      client_mqtt.subscribe(TOPIC);

    } else {
      Serial.println("MQTT connect failed");
      Serial.println("will reset and try again...");
      delay(1000);
      abort();
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  // Encendemos el LED cuando nos llegue un mensaje "ledon".
  if (!strncmp((char*)payload, "ledon", length)) {
    digitalWrite(PIN_LED, HIGH);
  }

  // Encendemos el LED cuando nos llegue un mensaje "ledoff".
  if (!strncmp((char*)payload, "ledoff", length)) {
    digitalWrite(PIN_LED, LOW);
  }

  Serial.println();
  Serial.println("---------");
}

void setup() {
  Serial.begin(9600);

  // Configuración LED.
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // Conexión con el punto de acceso.
  setup_wifi();

  // Configuración del cliente MQTT.
  client_mqtt.setServer(BROKER_IP, 1883);
  client_mqtt.setCallback(callback);
}

void loop() {
  if (!client_mqtt.connected()) {
    reconnect();
  }

  client_mqtt.loop();

  unsigned long now = millis();
  if (now - last_msg > 2000) {
    last_msg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "hello ESP8266 #%ld", value);
    Serial.print("Mensaje publicado: ");
    Serial.println(msg);
    client_mqtt.publish(TOPIC, msg);
  }
}
