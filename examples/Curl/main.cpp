#include <curl/curl.h>
#include <BeeNeXT.h>

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((String*)userp)->concat((char*)contents, size * nmemb);
    return size * nmemb;
}

void setup() {
  Serial.begin(9600);
  Serial.println("HTTP GET Example");

  CURL* curl = curl_easy_init();
  if (curl) {
    String response;
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
      Serial.println("Response:");
      Serial.println(response);
    } else {
      Serial.print("Error: ");
      Serial.println(curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
  }
}

void loop() {
  BeeNeXT.update();
}