/**
 * wm_strings_en.h
 * engligh strings for
 * WiFiManager, a library for the ESP8266/Arduino platform
 * for configuration of WiFi credentials using a Captive Portal
 *
 * @author Creator tzapu
 * @author tablatronix
 * @version 0.0.0
 * @license MIT
 */

#ifndef _WM_STRINGS_EN_H_
#define _WM_STRINGS_EN_H_


#ifndef WIFI_MANAGER_OVERRIDE_STRINGS
// !!! ABOVE WILL NOT WORK if you define in your sketch, must be build flag, if anyone one knows how to order includes to be able to do this it would be neat.. I have seen it done..

// strings files must include a consts file!
#include "wm_consts_en.h" // include constants, tokens, routes

const char WM_LANGUAGE[] PROGMEM = "en-US"; // i18n lang code

const char HTTP_HEAD_START[]       PROGMEM = "<!DOCTYPE html>"
"<html lang='en'><head>"
"<meta name='format-detection' content='telephone=no'>"
"<meta charset='UTF-8'>"
"<meta  name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'/>"
"<title>{v}</title>";

const char HTTP_SCRIPT[]           PROGMEM = "<script>function c(l){"
"document.getElementById('s').value=l.getAttribute('data-ssid')||l.innerText||l.textContent;"
"p = l.nextElementSibling.classList.contains('l');"
"document.getElementById('p').disabled = !p;"
"if(p)document.getElementById('p').focus();};"
"function f() {var x = document.getElementById('p');x.type==='password'?x.type='text':x.type='password';}"
"</script>"; // @todo add button states, disable on click , show ack , spinner etc

const char HTTP_HEAD_END[]         PROGMEM = "</head><body class='{c}'><div class='wrap'>"; // {c} = _bodyclass
// example of embedded logo, base64 encoded inline, No styling here
const char HTTP_ROOT_MAIN[]        PROGMEM = "<p style='text-align:center'><img width='120' src='data:image/png;base64,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' /> </p><h3 style='text-align:center'>{v}</h3>";
// const char HTTP_ROOT_MAIN[]        PROGMEM = "<h1>{t}</h1><h3>{v}</h3>";

const char * const HTTP_PORTAL_MENU[] PROGMEM = {
"<form action='/wifi'    method='get'><button>Configure WiFi</button></form><br/>\n", // MENU_WIFI
"<form action='/0wifi'   method='get'><button>Configure WiFi (No scan)</button></form><br/>\n", // MENU_WIFINOSCAN
"<form action='/info'    method='get'><button>Info</button></form><br/>\n", // MENU_INFO
"<form action='/param'   method='get'><button>Setup</button></form><br/>\n",//MENU_PARAM
"<form action='/close'   method='get'><button>Close</button></form><br/>\n", // MENU_CLOSE
"<form action='/restart' method='get'><button>Restart</button></form><br/>\n",// MENU_RESTART
"<form action='/exit'    method='get'><button>Exit</button></form><br/>\n",  // MENU_EXIT
"<form action='/erase'   method='get'><button class='D'>Erase</button></form><br/>\n", // MENU_ERASE
"<form action='/update'  method='get'><button>Update</button></form><br/>\n",// MENU_UPDATE
"<hr><br/>" // MENU_SEP
};

// const char HTTP_PORTAL_OPTIONS[]   PROGMEM = strcat(HTTP_PORTAL_MENU[0] , HTTP_PORTAL_MENU[3] , HTTP_PORTAL_MENU[7]);
const char HTTP_PORTAL_OPTIONS[]   PROGMEM = "";
const char HTTP_ITEM_QI[]          PROGMEM = "<div role='img' aria-label='{r}%' title='{r}%' class='q q-{q} {i} {h}'></div>"; // rssi icons
const char HTTP_ITEM_QP[]          PROGMEM = "<div class='q {h}'>{r}%</div>"; // rssi percentage {h} = hidden showperc pref
const char HTTP_ITEM[]             PROGMEM = "<div><a href='#p' onclick='c(this)' data-ssid='{V}'>{v}</a>{qi}{qp}</div>"; // {q} = HTTP_ITEM_QI, {r} = HTTP_ITEM_QP
// const char HTTP_ITEM[]            PROGMEM = "<div><a href='#p' onclick='c(this)'>{v}</a> {R} {r}% {q} {e}</div>"; // test all tokens

const char HTTP_FORM_START[]       PROGMEM = "<form method='POST' action='{v}'>";
const char HTTP_FORM_WIFI[]        PROGMEM = "<label for='s'>SSID</label><input id='s' name='s' maxlength='32' autocorrect='off' autocapitalize='none' placeholder='{v}'><br/><label for='p'>Password</label><input id='p' name='p' maxlength='64' type='password' placeholder='{p}'><input type='checkbox' id='showpass' onclick='f()'> <label for='showpass'>Show Password</label><br/>";
const char HTTP_FORM_WIFI_END[]    PROGMEM = "";
const char HTTP_FORM_STATIC_HEAD[] PROGMEM = "<hr><br/>";
const char HTTP_FORM_END[]         PROGMEM = "<br/><br/><button type='submit'>Save</button></form>";
const char HTTP_FORM_LABEL[]       PROGMEM = "<label for='{i}'>{t}</label>";
const char HTTP_FORM_PARAM_HEAD[]  PROGMEM = "<hr><br/>";
const char HTTP_FORM_PARAM[]       PROGMEM = "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>\n"; // do not remove newline!

const char HTTP_SCAN_LINK[]        PROGMEM = "<br/><form action='/wifi?refresh=1' method='POST'><button name='refresh' value='1'>Refresh</button></form>";
const char HTTP_SAVED[]            PROGMEM = "<div class='msg'>Saving Credentials<br/>Trying to connect ESP to network.<br />If it fails reconnect to AP to try again</div>";
const char HTTP_PARAMSAVED[]       PROGMEM = "<div class='msg S'>Saved<br/></div>";
const char HTTP_END[]              PROGMEM = "</div></body></html>";
const char HTTP_ERASEBTN[]         PROGMEM = "<br/><form action='/erase' method='get'><button class='D'>Erase WiFi config</button></form>";
const char HTTP_UPDATEBTN[]        PROGMEM = "<br/><form action='/update' method='get'><button>Update</button></form>";
const char HTTP_BACKBTN[]          PROGMEM = "<hr><br/><form action='/' method='get'><button>Back</button></form>";

const char HTTP_STATUS_ON[]        PROGMEM = "<div class='msg S'><strong>Connected</strong> to {v}<br/><em><small>with IP {i}</small></em></div>";
const char HTTP_STATUS_OFF[]       PROGMEM = "<div class='msg {c}'><strong>Not connected</strong> to {v}{r}</div>"; // {c=class} {v=ssid} {r=status_off}
const char HTTP_STATUS_OFFPW[]     PROGMEM = "<br/>Authentication failure"; // STATION_WRONG_PASSWORD,  no eps32
const char HTTP_STATUS_OFFNOAP[]   PROGMEM = "<br/>AP not found";   // WL_NO_SSID_AVAIL
const char HTTP_STATUS_OFFFAIL[]   PROGMEM = "<br/>Could not connect"; // WL_CONNECT_FAILED
const char HTTP_STATUS_NONE[]      PROGMEM = "<div class='msg'>No AP set</div>";
const char HTTP_BR[]               PROGMEM = "<br/>";

const char HTTP_STYLE[]            PROGMEM = "<style>"
".c,body{text-align:center;font-family:verdana}div,input,select{padding:5px;font-size:1em;margin:5px 0;box-sizing:border-box}"
"input,button,select,.msg{border-radius:.3rem;width: 100%}input[type=radio],input[type=checkbox]{width:auto}"
"button,input[type='button'],input[type='submit']{cursor:pointer;border:0;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%}"
"input[type='file']{border:1px solid #1fa3ec}"
".wrap {text-align:left;display:inline-block;min-width:260px;max-width:500px}"
// links
"a{color:#000;font-weight:700;text-decoration:none}a:hover{color:#1fa3ec;text-decoration:underline}"
// quality icons
".q{height:16px;margin:0;padding:0 5px;text-align:right;min-width:38px;float:right}.q.q-0:after{background-position-x:0}.q.q-1:after{background-position-x:-16px}.q.q-2:after{background-position-x:-32px}.q.q-3:after{background-position-x:-48px}.q.q-4:after{background-position-x:-64px}.q.l:before{background-position-x:-80px;padding-right:5px}.ql .q{float:left}.q:after,.q:before{content:'';width:16px;height:16px;display:inline-block;background-repeat:no-repeat;background-position: 16px 0;"
"background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAAAQCAMAAADeZIrLAAAAJFBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADHJj5lAAAAC3RSTlMAIjN3iJmqu8zd7vF8pzcAAABsSURBVHja7Y1BCsAwCASNSVo3/v+/BUEiXnIoXkoX5jAQMxTHzK9cVSnvDxwD8bFx8PhZ9q8FmghXBhqA1faxk92PsxvRc2CCCFdhQCbRkLoAQ3q/wWUBqG35ZxtVzW4Ed6LngPyBU2CobdIDQ5oPWI5nCUwAAAAASUVORK5CYII=');}"
// icons @2x media query (32px rescaled)
"@media (-webkit-min-device-pixel-ratio: 2),(min-resolution: 192dpi){.q:before,.q:after {"
"background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALwAAAAgCAMAAACfM+KhAAAALVBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADAOrOgAAAADnRSTlMAESIzRGZ3iJmqu8zd7gKjCLQAAACmSURBVHgB7dDBCoMwEEXRmKlVY3L//3NLhyzqIqSUggy8uxnhCR5Mo8xLt+14aZ7wwgsvvPA/ofv9+44334UXXngvb6XsFhO/VoC2RsSv9J7x8BnYLW+AjT56ud/uePMdb7IP8Bsc/e7h8Cfk912ghsNXWPpDC4hvN+D1560A1QPORyh84VKLjjdvfPFm++i9EWq0348XXnjhhT+4dIbCW+WjZim9AKk4UZMnnCEuAAAAAElFTkSuQmCC');"
"background-size: 95px 16px;}}"
// msg callouts
".msg{padding:20px;margin:20px 0;border:1px solid #eee;border-left-width:5px;border-left-color:#777}.msg h4{margin-top:0;margin-bottom:5px}.msg.P{border-left-color:#1fa3ec}.msg.P h4{color:#1fa3ec}.msg.D{border-left-color:#dc3630}.msg.D h4{color:#dc3630}.msg.S{border-left-color: #5cb85c}.msg.S h4{color: #5cb85c}"
// lists
"dt{font-weight:bold}dd{margin:0;padding:0 0 0.5em 0;min-height:12px}"
"td{vertical-align: top;}"
".h{display:none}"
"button{transition: 0s opacity;transition-delay: 3s;transition-duration: 0s;cursor: pointer}"
"button.D{background-color:#dc3630}"
"button:active{opacity:50% !important;cursor:wait;transition-delay: 0s}"
// invert
"body.invert,body.invert a,body.invert h1 {background-color:#060606;color:#fff;}"
"body.invert .msg{color:#fff;background-color:#282828;border-top:1px solid #555;border-right:1px solid #555;border-bottom:1px solid #555;}"
"body.invert .q[role=img]{-webkit-filter:invert(1);filter:invert(1);}"
":disabled {opacity: 0.5;}"
"</style>";

#ifndef WM_NOHELP
const char HTTP_HELP[]             PROGMEM =
 "<br/><h3>Available pages</h3><hr>"
 "<table class='table'>"
 "<thead><tr><th>Page</th><th>Function</th></tr></thead><tbody>"
 "<tr><td><a href='/'>/</a></td>"
 "<td>Menu page.</td></tr>"
 "<tr><td><a href='/wifi'>/wifi</a></td>"
 "<td>Show WiFi scan results and enter WiFi configuration.(/0wifi noscan)</td></tr>"
 "<tr><td><a href='/wifisave'>/wifisave</a></td>"
 "<td>Save WiFi configuration information and configure device. Needs variables supplied.</td></tr>"
 "<tr><td><a href='/param'>/param</a></td>"
 "<td>Parameter page</td></tr>"
 "<tr><td><a href='/info'>/info</a></td>"
 "<td>Information page</td></tr>"
 "<tr><td><a href='/u'>/u</a></td>"
 "<td>OTA Update</td></tr>"
 "<tr><td><a href='/close'>/close</a></td>"
 "<td>Close the captiveportal popup, config portal will remain active</td></tr>"
 "<tr><td>/exit</td>"
 "<td>Exit Config portal, config portal will close</td></tr>"
 "<tr><td>/restart</td>"
 "<td>Reboot the device</td></tr>"
 "<tr><td>/erase</td>"
 "<td>Erase WiFi configuration and reboot device. Device will not reconnect to a network until new WiFi configuration data is entered.</td></tr>"
 "</table>"
 "<p/>Github <a href='https://github.com/tzapu/WiFiManager'>https://github.com/tzapu/WiFiManager</a>.";
#else
const char HTTP_HELP[]             PROGMEM = "";
#endif

const char HTTP_UPDATE[] PROGMEM = "Upload new firmware<br/><form method='POST' action='u' enctype='multipart/form-data' onchange=\"(function(el){document.getElementById('uploadbin').style.display = el.value=='' ? 'none' : 'initial';})(this)\"><input type='file' name='update' accept='.bin,application/octet-stream'><button id='uploadbin' type='submit' class='h D'>Update</button></form><small><a href='http://192.168.4.1/update' target='_blank'>* May not function inside captive portal, open in browser http://192.168.4.1</a><small>";
const char HTTP_UPDATE_FAIL[] PROGMEM = "<div class='msg D'><strong>Update failed!</strong><Br/>Reboot device and try again</div>";
const char HTTP_UPDATE_SUCCESS[] PROGMEM = "<div class='msg S'><strong>Update successful.  </strong> <br/> Device rebooting now...</div>";

#ifdef WM_JSTEST
const char HTTP_JS[] PROGMEM =
"<script>function postAjax(url, data, success) {"
"    var params = typeof data == 'string' ? data : Object.keys(data).map("
"            function(k){ return encodeURIComponent(k) + '=' + encodeURIComponent(data[k]) }"
"        ).join('&');"
"    var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject(\"Microsoft.XMLHTTP\");"
"    xhr.open('POST', url);"
"    xhr.onreadystatechange = function() {"
"        if (xhr.readyState>3 && xhr.status==200) { success(xhr.responseText); }"
"    };"
"    xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');"
"    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');"
"    xhr.send(params);"
"    return xhr;}"
"postAjax('/status', 'p1=1&p2=Hello+World', function(data){ console.log(data); });"
"postAjax('/status', { p1: 1, p2: 'Hello World' }, function(data){ console.log(data); });"
"</script>";
#endif

// Info html
// @todo remove html elements from progmem, repetetive strings
#ifdef ESP32
	const char HTTP_INFO_esphead[]    PROGMEM = "<h3>esp32</h3><hr><dl>";
	const char HTTP_INFO_chiprev[]    PROGMEM = "<dt>Chip rev</dt><dd>{1}</dd>";
  	const char HTTP_INFO_lastreset[]  PROGMEM = "<dt>Last reset reason</dt><dd>CPU0: {1}<br/>CPU1: {2}</dd>";
  	const char HTTP_INFO_aphost[]     PROGMEM = "<dt>Access point hostname</dt><dd>{1}</dd>";
    const char HTTP_INFO_psrsize[]    PROGMEM = "<dt>PSRAM Size</dt><dd>{1} bytes</dd>";
	const char HTTP_INFO_temp[]       PROGMEM = "<dt>Temperature</dt><dd>{1} C&deg; / {2} F&deg;</dd>";
    const char HTTP_INFO_hall[]       PROGMEM = "<dt>Hall</dt><dd>{1}</dd>";
#else
	const char HTTP_INFO_esphead[]    PROGMEM = "<h3>esp8266</h3><hr><dl>";
	const char HTTP_INFO_fchipid[]    PROGMEM = "<dt>Flash chip ID</dt><dd>{1}</dd>";
	const char HTTP_INFO_corever[]    PROGMEM = "<dt>Core version</dt><dd>{1}</dd>";
	const char HTTP_INFO_bootver[]    PROGMEM = "<dt>Boot version</dt><dd>{1}</dd>";
	const char HTTP_INFO_lastreset[]  PROGMEM = "<dt>Last reset reason</dt><dd>{1}</dd>";
	const char HTTP_INFO_flashsize[]  PROGMEM = "<dt>Real flash size</dt><dd>{1} bytes</dd>";
#endif

const char HTTP_INFO_memsmeter[]  PROGMEM = "<br/><progress value='{1}' max='{2}'></progress></dd>";
const char HTTP_INFO_memsketch[]  PROGMEM = "<dt>Memory - Sketch size</dt><dd>Used / Total bytes<br/>{1} / {2}";
const char HTTP_INFO_freeheap[]   PROGMEM = "<dt>Memory - Free heap</dt><dd>{1} bytes available</dd>";
const char HTTP_INFO_wifihead[]   PROGMEM = "<br/><h3>WiFi</h3><hr>";
const char HTTP_INFO_uptime[]     PROGMEM = "<dt>Uptime</dt><dd>{1} mins {2} secs</dd>";
const char HTTP_INFO_chipid[]     PROGMEM = "<dt>Chip ID</dt><dd>{1}</dd>";
const char HTTP_INFO_idesize[]    PROGMEM = "<dt>Flash size</dt><dd>{1} bytes</dd>";
const char HTTP_INFO_sdkver[]     PROGMEM = "<dt>SDK version</dt><dd>{1}</dd>";
const char HTTP_INFO_cpufreq[]    PROGMEM = "<dt>CPU frequency</dt><dd>{1}MHz</dd>";
const char HTTP_INFO_apip[]       PROGMEM = "<dt>Access point IP</dt><dd>{1}</dd>";
const char HTTP_INFO_apmac[]      PROGMEM = "<dt>Access point MAC</dt><dd>{1}</dd>";
const char HTTP_INFO_apssid[]     PROGMEM = "<dt>Access point SSID</dt><dd>{1}</dd>";
const char HTTP_INFO_apbssid[]    PROGMEM = "<dt>BSSID</dt><dd>{1}</dd>";
const char HTTP_INFO_stassid[]    PROGMEM = "<dt>Station SSID</dt><dd>{1}</dd>";
const char HTTP_INFO_staip[]      PROGMEM = "<dt>Station IP</dt><dd>{1}</dd>";
const char HTTP_INFO_stagw[]      PROGMEM = "<dt>Station gateway</dt><dd>{1}</dd>";
const char HTTP_INFO_stasub[]     PROGMEM = "<dt>Station subnet</dt><dd>{1}</dd>";
const char HTTP_INFO_dnss[]       PROGMEM = "<dt>DNS Server</dt><dd>{1}</dd>";
const char HTTP_INFO_host[]       PROGMEM = "<dt>Hostname</dt><dd>{1}</dd>";
const char HTTP_INFO_stamac[]     PROGMEM = "<dt>Station MAC</dt><dd>{1}</dd>";
const char HTTP_INFO_conx[]       PROGMEM = "<dt>Connected</dt><dd>{1}</dd>";
const char HTTP_INFO_autoconx[]   PROGMEM = "<dt>Autoconnect</dt><dd>{1}</dd>";

const char HTTP_INFO_aboutver[]     PROGMEM = "<dt>WiFiManager</dt><dd>{1}</dd>";
const char HTTP_INFO_aboutarduino[] PROGMEM = "<dt>Arduino</dt><dd>{1}</dd>";
const char HTTP_INFO_aboutsdk[]     PROGMEM = "<dt>ESP-SDK/IDF</dt><dd>{1}</dd>";
const char HTTP_INFO_aboutdate[]    PROGMEM = "<dt>Build date</dt><dd>{1}</dd>";

const char S_brand[]              PROGMEM = "WiFiManager";
const char S_debugPrefix[]        PROGMEM = "*wm:";
const char S_y[]                  PROGMEM = "Yes";
const char S_n[]                  PROGMEM = "No";
const char S_enable[]             PROGMEM = "Enabled";
const char S_disable[]            PROGMEM = "Disabled";
const char S_GET[]                PROGMEM = "GET";
const char S_POST[]               PROGMEM = "POST";
const char S_NA[]                 PROGMEM = "Unknown";
const char S_passph[]             PROGMEM = "********";
const char S_titlewifisaved[]     PROGMEM = "Credentials saved";
const char S_titlewifisettings[]  PROGMEM = "Settings saved";
const char S_titlewifi[]          PROGMEM = "Config ESP";
const char S_titleinfo[]          PROGMEM = "Info";
const char S_titleparam[]         PROGMEM = "Setup";
const char S_titleparamsaved[]    PROGMEM = "Setup saved";
const char S_titleexit[]          PROGMEM = "Exit";
const char S_titlereset[]         PROGMEM = "Reset";
const char S_titleerase[]         PROGMEM = "Erase";
const char S_titleclose[]         PROGMEM = "Close";
const char S_options[]            PROGMEM = "options";
const char S_nonetworks[]         PROGMEM = "No networks found. Refresh to scan again.";
const char S_staticip[]           PROGMEM = "Static IP";
const char S_staticgw[]           PROGMEM = "Static gateway";
const char S_staticdns[]          PROGMEM = "Static DNS";
const char S_subnet[]             PROGMEM = "Subnet";
const char S_exiting[]            PROGMEM = "Exiting";
const char S_resetting[]          PROGMEM = "Module will reset in a few seconds.";
const char S_closing[]            PROGMEM = "You can close the page, portal will continue to run";
const char S_error[]              PROGMEM = "An error occured";
const char S_notfound[]           PROGMEM = "File not found\n\n";
const char S_uri[]                PROGMEM = "URI: ";
const char S_method[]             PROGMEM = "\nMethod: ";
const char S_args[]               PROGMEM = "\nArguments: ";
const char S_parampre[]           PROGMEM = "param_";

// debug strings
const char D_HR[]                 PROGMEM = "--------------------";


// softap ssid default prefix
#ifdef ESP8266
    const char S_ssidpre[]        PROGMEM = "ESP";
#elif defined(ESP32)
    const char S_ssidpre[]        PROGMEM = "ESP32";
#else
    const char S_ssidpre[]        PROGMEM = "WM";
#endif

// END WIFI_MANAGER_OVERRIDE_STRINGS
#endif

#endif
