/*
  Group xx

*/

// Global includes
#include <ArduinoJson.h>

// wifi comms includes
#include <WiFi.h>
#include <HTTPClient.h>


// local includes

// check device MAC table to get wifi password
#define MAN_SSID "Mans So HOT"
#define MAN_PSWD "Du83887199"  

// --------------------------------------------------------------------


// --------------------------------------------------------------------

static volatile bool wifiConnected = false;
String localSSID, localPSWD;
String regURL;
String postStr;

static volatile bool tog = false;
static volatile int userCount = 0;


// -------------------------------------------------------



/*********************** SETUP ******************************/
void setup(){

  // configure the i/o
  Serial.begin(115200);

  delay(50);
  Serial.println("DSC190 IoT Web call example");
  
  WiFi.onEvent(WiFiEvent);
  WiFi.mode(WIFI_MODE_STA);

  scanWiFiNetworks();

  localSSID = MAN_SSID;
  localPSWD = MAN_PSWD;
  
  // setup STA mode
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("Trying SSID: " + localSSID + " (" + localPSWD + ")");

  delay(50);
  // connect to the local wifi
  WiFi.begin(localSSID.c_str(), localPSWD.c_str());

  // show MAC address
  Serial.println();
  Serial.println("my MAC:"+getMacStr());

  // wait till we are connected
  while (!wifiConnected)
      ; 
      
  String mac=getMacStr();
  String ip=getIPStr();
  String gid="03";
  String url="http://dsc-iot.ucsd.edu/gid03/cgi-bin/API.py";
  String jReg="\"cmd\": \"REG\", \"ip\":\""+ip+"\", \"mac\":\""+\
              mac+"\", \"gid\": \"03\"";
  String jLoad="{"+jReg+"}";
  postJsonHTTP(url, jLoad);
  
}

// ------------------------------ MAIN LOOP --------------------------------
void loop(){
  String mac=getMacStr();
  String ip=getIPStr();
  String url="http://dsc-iot.ucsd.edu/gid03/cgi-bin/API.py";
  String rs=String(WiFi.RSSI());
  String jLOG="\"cmd\": \"LOGDEV\", \"RSSI\":\""+rs+"\", \"mac\":\""+\
              mac+"\", \"gid\": \"03\"";
  String jLoad2="{"+jLOG+"}";
  postJsonHTTP(url, jLoad2);
  delay(10000); 
  Serial.print("10s passed");


}
