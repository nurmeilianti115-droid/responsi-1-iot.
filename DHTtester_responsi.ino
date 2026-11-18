#include <WiFi.h>
#include <DHT.h>

// Ganti dengan WiFi hotspot HP kamu biar cepat terhubung
const char* ssid = "Aji";
const char* password = "11111111";

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  Serial.println();
  Serial.print("Menghubungkan WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Terhubung!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000);

  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();

  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("Gagal membaca sensor!");
    return;
  }

  Serial.println("===== MONITORING IoT ESP32 =====");
  Serial.print("Suhu       : ");
  Serial.print(suhu);
  Serial.println(" °C");
  
  Serial.print("Kelembapan : ");
  Serial.print(kelembapan);
  Serial.println(" %");
  Serial.println("================================");
}