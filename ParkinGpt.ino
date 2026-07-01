#include <WiFi.h>
#include <PubSubClient.h>

// Pines en el ESP32
const int TRIG_PIN       = 5;   // D5
const int ECHO_PIN       = 18;  // D18
const int LED_RED_PIN    = 22;  // D22
const int LED_GREEN_PIN  = 21;  // D21

// Credenciales WiFi y broker MQTT
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASS     = "YOUR_WIFI_PASSWORD";
const char* MQTT_SERVER   = "broker.hivemq.com";

// Tópicos MQTT de ejemplo
const char* SENSOR_TOPIC   = "grupo_1/canal_sensor";
const char* ACTUATOR_TOPIC = "grupo_1/canal_actuador";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

bool remoteControl = false;

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  msg.trim();
  if (msg.equalsIgnoreCase("ON")) {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    remoteControl = true;
  } else if (msg.equalsIgnoreCase("OFF")) {
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    remoteControl = true;
  } else if (msg.equalsIgnoreCase("AUTO")) {
    remoteControl = false;
  }
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi conectado");
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando a broker MQTT...");
    if (mqttClient.connect("ParkinGpt")) {
      Serial.println("conectado");
      mqttClient.subscribe(ACTUATOR_TOPIC);
    } else {
      Serial.print(" fallo, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" reintentando en 2s");
      delay(2000);
    }
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);

  Serial.begin(9600);
  Serial.println("HC-SR04 + LEDs inicializado");

  connectWiFi();
  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(mqttCallback);
  connectMQTT();
}

void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();

  // Generar pulso de trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leer eco
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calcular distancia
  float distance = duration * 0.034f / 2.0f;

  Serial.printf("Distancia: %.2f cm\n", distance);

  char payload[64];
  snprintf(payload, sizeof(payload), "{\"id_sensor\": 1, \"valor\": %.2f}", distance);
  mqttClient.publish(SENSOR_TOPIC, payload);

  if (!remoteControl) {
    if (distance > 0 && distance <= 10.0f) {
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(LED_GREEN_PIN, LOW);
    } else {
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, HIGH);
    }
  }

  delay(1000);
}
