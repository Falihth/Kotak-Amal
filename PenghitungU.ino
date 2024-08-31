#define S0 5
#define S1 18
#define S2 15
#define S3 2
#define sensorOut 23

#include <Wire.h>
#include <WiFi.h> 
#include <HTTPClient.h>

const char* ssid = "Cihuy";
const char* password = "1sampai8";
const char* serverName = "http://amaldetect.000.pe/kirimdata.php";

int uang = 0;
bool statusUang = false;


void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Mengatur prescale frekuensi output
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" connected");

  // Check WiFi status
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
  } else {
    Serial.println("WiFi not connected");
  }
}

void loop() {
  // Mengukur warna merah
  int red = getRed();

  // Mengukur warna biru
  int blue = getBlue();

  // Mengukur warna hijau
  int green = getGreen();
/*
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" Blue: ");
  Serial.print(blue);
  Serial.print(" Green: ");
  Serial.println(green);
*/
  if (!statusUang) {
    if (red > 0 && red < 999999999 && green > 0  && green < 99999999 && blue > 0 && blue < 9999999) {
      Serial.println("2rb");
      uang += 2000;
      statusUang = true;
    }
  } else {
    // Jika statusUang sudah true, reset statusUang dan tunggu sebelum membaca lagi
    delay(500);
    statusUang = false;
  }

  // Menampilkan total uang yang terdeteksi
  Serial.print("Total Uang: ");
  Serial.println(uang);

  // Send uang value to the server (commented out for now)
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverPath = String(serverName) + "?uang=" + String(uang);

     Serial.print("Server Path: ");
    Serial.println(serverPath);
    
    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();  // Send the GET request and get response code

    
    http.end();
}


  delay(1000); // Penundaan sebelum pembacaan berikutnya
}

int getRed() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  return pulseIn(sensorOut, LOW); // Mendapatkan frekuensi warna merah
}

int getGreen() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW); // Mendapatkan frekuensi warna hijau
}

int getBlue() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  return pulseIn(sensorOut, LOW); // Mendapatkan frekuensi warna biru
}
