// Libraries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <driver/adc.h>
#include <ATM90E3x.h>
#include "IPEM_Hardware.h"
#include <WiFiManager.h>
#include "OTA_cert.h"
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "time.h"
#include <ArduinoJson.h>

//---------------------------------------------------------------  *WiFi Manager setup* ---------------------------------------------------------------
#define CAPTIVE_PORTAL_TIMEOUT 30

bool runWiFiManager()
{

  /*
   * Initialize WiFi and start captive portal to set connection credentials
   */
  WiFi.setHostname("Abacus eWall");
  WiFi.mode(WIFI_AP); // explicitly set mode, esp defaults to STA+AP
  WiFi.enableAP(true);

  WiFiManager wifiManager;
  // wifiManager.setDebugOutput(true);
  //  wifiManager.debugPlatformInfo();
  wifiManager.setTitle("Wallbox Configuration Portal");
  wifiManager.setParamsPage(true);
  //  const char *bufferStr = R"(

  //   <!-- INPUT SELECT -->
  //   <br/>
  //   <label for='input_select'>INPUT 1</label>
  //   <select name="input_select" id="input_select" class="button">
  //   <option value="0">Analog </option>
  //   <option value="1" selected>Digital</option>
  //   </select>
  //   )";

  //   WiFiManagerParameter custom_html_inputs(bufferStr);
  //   wifiManager.addParameter(&custom_html_inputs);
  wifiManager.setSaveParamsCallback([&wifiManager]()
                                    {
                                      // inputs(*DI1);
                                    });

  wifiManager.setDarkMode(true);

  // wifiManager.setConfigPortalTimeout(CAPATITIVE_PORTAL_TIMEOUT / 1000); //if nobody logs in to the portal, continue after timeout
  wifiManager.setTimeout(CAPTIVE_PORTAL_TIMEOUT); // if nobody logs in to the portal, continue after timeout
  wifiManager.setConnectTimeout(CAPTIVE_PORTAL_TIMEOUT);
  // wifiManager.setSaveConnect(true);
  wifiManager.setAPClientCheck(true); // avoid timeout if client connected to softap
  Serial.println("[main] Start capatitive portal");

  if (wifiManager.startConfigPortal("Abacus eWall", "12345678"))
  {
    return true;
  }
  else
  {
    return wifiManager.autoConnect("Abacus eWall", "12345678");
  }
}
//---------------------------------------------------------------  *WiFi Manager setup* ---------------------------------------------------------------

//---------------------------------------------------------------  *OTA setup* ---------------------------------------------------------------
String FirmwareVer = {"1.0"};
#define URL_fw_Version "https://raw.githubusercontent.com/Abdullah-python/SMART_METER/main/firmware_version.txt"
#define URL_fw_Bin "https://raw.githubusercontent.com/Abdullah-python/SMART_METER/main/fw/firmware.bin"
void firmwareUpdate();
int FirmwareVersionCheck();

unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long previousMillis_2 = 0;
const long interval = 60000;
const long mini_interval = 1000;

void repeatedCall()
{
    static int num = 0;
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis) >= interval)
    {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        if (FirmwareVersionCheck())
        {
            firmwareUpdate();
        }
    }
    if ((currentMillis - previousMillis_2) >= mini_interval)
    {
        previousMillis_2 = currentMillis;
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("wifi connected");
        }
        else
        {
            if (!runWiFiManager())
            {
                // couldn't connect
                Serial.println("[main] Couldn't connect to WiFi after multiple attempts");
                delay(5000);
                ESP.restart();
            }
            Serial.println("Connected");
        }
    }
}

void firmwareUpdate(void)
{
    WiFiClientSecure client;
    client.setCACert(OTAcert);
    httpUpdate.setLedPin(2, LOW);
    t_httpUpdate_return ret = httpUpdate.update(client, URL_fw_Bin);

    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

    case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
}

int FirmwareVersionCheck(void)
{
    String payload;
    int httpCode;
    String fwurl = "";
    fwurl += URL_fw_Version;
    fwurl += "?";
    fwurl += String(rand());
    Serial.println(fwurl);
    WiFiClientSecure *client = new WiFiClientSecure;

    if (client)
    {
        client->setCACert(OTAcert);

        // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is
        HTTPClient https;

        if (https.begin(*client, fwurl))
        { // HTTPS
            Serial.print("[HTTPS] GET...\n");
            // start connection and send HTTP header
            delay(100);
            httpCode = https.GET();
            delay(100);
            if (httpCode == HTTP_CODE_OK) // if version received
            {
                payload = https.getString(); // save received version
            }
            else
            {
                Serial.print("error in downloading version file:");
                Serial.println(httpCode);
            }
            https.end();
        }
        delete client;
    }

    if (httpCode == HTTP_CODE_OK) // if version received
    {
        payload.trim();
        if (payload.equals(FirmwareVer))
        {
            Serial.printf("\nDevice already on latest firmware version:%s\n", FirmwareVer);
            return 0;
        }
        else
        {
            Serial.println(payload);
            Serial.println("New firmware detected");
            return 1;
        }
    }
    return 0;
}
//---------------------------------------------------------------  *OTA setup* ---------------------------------------------------------------

//---------------------------------------------------------------  *Time setup* ---------------------------------------------------------------
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600 * 4;
const int daylightOffset_sec = 3600;

struct tm timeinfo;

String ntp_time = "";

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  char timeSec[3];
  strftime(timeSec, 3, "%S", &timeinfo);
  char timeMin[3];
  strftime(timeMin, 3, "%M", &timeinfo);
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  char timeDay[10];
  strftime(timeDay, 10, "%e", &timeinfo);
  char timeMonth[3];
  strftime(timeMonth, 3, "%m", &timeinfo);
  char timeYear[5];
  strftime(timeYear, 5, "%Y", &timeinfo);
  char timeZone[4];
  strftime(timeZone, 4, "%Z", &timeinfo);

  ntp_time = String(timeMonth);
  ntp_time += String(timeDay);
  ntp_time += String(timeYear);
  ntp_time += String(timeHour);
  ntp_time += String(timeMin);
  ntp_time += String(timeSec);
  ntp_time += String(timeZone);
}
//---------------------------------------------------------------  *Time setup* ---------------------------------------------------------------

//---------------------------------------------------------------  *MQTT setup* ---------------------------------------------------------------
const char *mqtt_server = "192.168.18.67";

String ch_port = "Station 001"; 
String ch_status = "";
String message_title;

int ch_wattage;
int current_wattage = 0;
int ch_time;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Changes the output state according to the message
  if (String(topic) == "commands")
  {

  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client"))
    {
      Serial.println("connected");
      // Subscribe
      client.subscribe("commands");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//---------------------------------------------------------------  *MQTT setup* ---------------------------------------------------------------