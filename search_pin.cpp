#include <Arduino.h>
#include <WiFi.h>

// --- Config WiFi ---
const char* ssid = "SSID_NAME";
const char* password = "password";

// --- Liste des GPIO utilisables en test ---
int safePins[] = {4, 5, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
int pinCount = sizeof(safePins) / sizeof(safePins[0]);

void setup() {
  Serial.begin(115200);

  // --- Connexion WiFi ---
  Serial.print("Connexion au WiFi...");
  WiFi.begin(ssid, password);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 20) {
    delay(500);
    Serial.print(".");
    tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi OK !");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nEchec connexion WiFi.");
  }

  // --- Init GPIO safe ---
  for (int i = 0; i < pinCount; i++) {
    pinMode(safePins[i], OUTPUT);
    digitalWrite(safePins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < pinCount; i++) {
    int pin = safePins[i];
    digitalWrite(pin, HIGH);
    Serial.printf("Test GPIO %d\n", pin);
    delay(2000);
    digitalWrite(pin, LOW);
    delay(200);
  }
}
