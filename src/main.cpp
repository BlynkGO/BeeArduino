#include <curl/curl.h>
#include <BeeNeXT.h>
#include <ArduinoJson.h>

static String response_data = "";

// Callback สำหรับ curl write
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
  size_t total_size = size * nmemb;
  response_data += String((char*)contents, total_size);
  return total_size;
}

// ดึงข้อมูล weather
void fetch_weather(String url) {
  response_data = "";

  CURL* curl = curl_easy_init();
  if (!curl) {
    Serial.println("Failed to init curl");
    return;
  }

  // const char* url = "https://api.open-meteo.com/v1/forecast?latitude=13.7563&longitude=100.5018&hourly=temperature_2m";

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
  // ข้ามการตรวจ SSL
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    Serial.print("Curl failed: ");
    Serial.println(curl_easy_strerror(res));
  }

  curl_easy_cleanup(curl);
}

// Parse JSON โดยใช้ const char*
void parse_weather_json() {
  DynamicJsonDocument doc(4096);

  const char* json_cstr = response_data.c_str();
  DeserializationError error = deserializeJson(doc, json_cstr);
  if (error) {
    Serial.print("JSON parse failed: ");
    Serial.println(error.c_str());
    return;
  }

  double lat = doc["latitude"];
  double lon = doc["longitude"];
  Serial.print("Location: ");
  Serial.print(lat);
  Serial.print(", ");
  Serial.println(lon);

  JsonArray times = doc["hourly"]["time"];
  JsonArray temps = doc["hourly"]["temperature_2m"];

  Serial.println("Hourly Temperature:");
  for (size_t i = 0; i < times.size() && i < 24; i++) {
    Serial.print(times[i].as<const char*>());
    Serial.print(" : ");
    Serial.print(temps[i].as<float>());
    Serial.println(" °C");
  }
}

void setup() {
  Serial.begin(9600); Serial.println();
  Serial.println("BeeArduino Weather Example");

  fetch_weather("https://api.open-meteo.com/v1/forecast?latitude=13.7563&longitude=100.5018&hourly=temperature_2m");
  parse_weather_json();
}

void loop() {
  BeeNeXT.update();
}
