#include <WiFi.h>

#define CAPTIVE_PORTAL_TIMEOUT 30

bool runWiFiManager() {

  /*
     * Initialize WiFi and start captive portal to set connection credentials
     */
  WiFi.setHostname("Abacus eWall");
  WiFi.mode(WIFI_AP);  // explicitly set mode, esp defaults to STA+AP
  WiFi.enableAP(true);

  WiFiManager wifiManager;
  //wifiManager.setDebugOutput(true);
  // wifiManager.debugPlatformInfo();
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
  wifiManager.setSaveParamsCallback([&wifiManager]() {


    // inputs(*DI1);
  });

  wifiManager.setDarkMode(true);

  //wifiManager.setConfigPortalTimeout(CAPATITIVE_PORTAL_TIMEOUT / 1000); //if nobody logs in to the portal, continue after timeout
  wifiManager.setTimeout(CAPTIVE_PORTAL_TIMEOUT);  //if nobody logs in to the portal, continue after timeout
  wifiManager.setConnectTimeout(CAPTIVE_PORTAL_TIMEOUT);
  //wifiManager.setSaveConnect(true);
  wifiManager.setAPClientCheck(true);  // avoid timeout if client connected to softap
  Serial.println("[main] Start capatitive portal");

  if (wifiManager.startConfigPortal("Abacus eWall", "12345678")) {
    return true;
  } else {
    return wifiManager.autoConnect("Abacus eWall", "12345678");
  }
}