#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>

const char* ssid = "wifi";
const char* password = "yyyyyyyy";

// Initialize Telegram BOT
#define BOTtoken "7044773971:AAFuvxfaeOBlUq_HZLaZewRP96631D7OmwM"


#define CHAT_ID "2101894598"
//
#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

//Data Parsing
String dataIn;
String dt[10];
int i;
boolean parsing = false;
int kondisi = 1;
const int ledPin = 2;
bool ledState = LOW;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {

  for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/cektemperature") {
      bot.sendMessage(chat_id, String("Temperature: ") + dt[0] + String(" °C"), "");
    }


    if (text == "/cekhumidity") {
      bot.sendMessage(chat_id, String("Humidity: ") + dt[1] + String(" %"), "");
    }


    if (text == "/cekcarbon") {
      bot.sendMessage(chat_id, String("Carbon Concentration: ") + dt[2] + String(" PPM"), "");
    }
  }
}

void setup() {
  Serial.begin(115200);

#ifdef ESP8266
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
#endif

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
#ifdef ESP32
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
#endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

}

void loop() {

  if (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    dataIn += inChar;
    if (inChar == '\n') {
      parsing = true;
    }
  }
  if (parsing) {
    parsingData();
    parsing = false;
    dataIn = "";
  }

  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}


void parsingData() {
  int j = 0;
  dt[j] = "";
  for (i = 1; i < dataIn.length(); i++) {
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
      j++;
      dt[j] = "";
    }
    else
    {
      dt[j] = dt[j] + dataIn[i];
    }
  }
}