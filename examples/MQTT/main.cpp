#include <BeeNeXT.h>
#include <mqtt/async_client.h>

mqtt::async_client* client_global = nullptr;
static int pub_counter = 0;

class Callback : public virtual mqtt::callback {
public:
  void connected(const std::string& cause) override {
    Serial.print("Connected! cause=");
    Serial.println(cause.c_str());
  }

  void connection_lost(const std::string& cause) override {
    Serial.print("Connection lost: ");
    Serial.println(cause.c_str());
  }

  void message_arrived(mqtt::const_message_ptr msg) override {
    Serial.print("Message arrived [");
    Serial.print(msg->get_topic().c_str());
    Serial.print("]: ");
    Serial.println(msg->to_string().c_str());
  }
};
Callback cb;

class ConnectListener : public virtual mqtt::iaction_listener {
public:
  void on_success(const mqtt::token&) override {
    Serial.println("Async connect success");
    if (client_global) {
      try {
        client_global->subscribe("test/beeui", 1);
        Serial.println("Subscribed to topic: test/beeui");
      } catch (const mqtt::exception& exc) {
        Serial.print("Subscribe failed: ");
        Serial.println(exc.what());
      }
    }
  }

  void on_failure(const mqtt::token&) override {
    Serial.println("Async connect failed, retrying...");
    static SoftTimer t_retry;
    t_retry.delay(1000, [](){
      static ConnectListener conn_listener_retry;
      mqtt::connect_options connOpts;
      connOpts.set_keep_alive_interval(20);
      connOpts.set_clean_session(true);
      if (client_global) client_global->connect(connOpts, nullptr, conn_listener_retry);
    });
  }
};

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("BeeNeXT MQTT Async Publish + Subscribe Example");

  client_global = new mqtt::async_client("tcp://test.mosquitto.org:1883", "BeeNotify_Win");
  client_global->set_callback(cb);

  mqtt::connect_options connOpts;
  connOpts.set_keep_alive_interval(20);
  connOpts.set_clean_session(true);

  static ConnectListener conn_listener;
  client_global->connect(connOpts, nullptr, conn_listener);

  // Timer for publishing
  static SoftTimer t_pub;
  t_pub.setInterval(2000, [](){
    if (client_global && client_global->is_connected()) {
      String msg = String("Hello from BeeArduino : ") + String(pub_counter++);
      try {
        client_global->publish(mqtt::make_message("test/beeui", msg.c_str()));
        Serial.print("Published: ");
        Serial.println(msg);
      } catch (const mqtt::exception& exc) {
        Serial.print("Publish failed: ");
        Serial.println(exc.what());
      }
    }
  });
}

void loop() {
  BeeNeXT.update();
}

