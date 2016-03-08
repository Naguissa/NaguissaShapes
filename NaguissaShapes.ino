#include <SPI.h>

#include <Adafruit_GFX.h>
#include "Adafruit_ILI9340_esp.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>

#define COLOR_BLACK ILI9340_BLACK
#define COLOR_BLUE ILI9340_BLUE
#define COLOR_RED ILI9340_RED
#define COLOR_GREEN ILI9340_GREEN
#define COLOR_CYAN ILI9340_CYAN
#define COLOR_MAGENTA ILI9340_MAGENTA
#define COLOR_YELLOW ILI9340_YELLOW
#define COLOR_WHITE ILI9340_WHITE

#define COLOR_BROWN 0xA145
#define COLOR_PINK 0xFD77
#define COLOR_ORANGE 0xFBE0


const char index_html[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<head><title>Clase Motos</title></head>
<style>
body{background-color:#000;}
.shape{float:left;width:320px;height:240px;cursor:pointer;margin-right:20px;}
.shape svg {display:inline-block;}
.color{float:left;background-color:#ff0000;width:150px;height:150px;cursor:pointer;margin-right:20px;}
#result{width:320px;height:240px;margin-left:auto;margin-right:auto;}
</style>
<script>
var colorv="#f00",lshape='',lcolor='f';
function shape(id) {if (id != '') {lshape=id; document.getElementById("result").innerHTML=document.getElementById(id).innerHTML.replace('#00ff00',colorv);document.getElementById('ifr').src='/paint/?s='+lshape+'&c='+lcolor;}}
function color(id,c) {colorv=c;lcolor=id;shape(lshape);}
</script>
<body>

<div class="shape" onclick="shape('t');" id="t">
<svg height="240" width="320">
<polygon points="160,5,30,235,310,235" style="fill:#00ff00;"/>
</svg> 
</div>

<div class="shape" onclick="shape('r');" id="r">
<svg height="240" width="320">
<polygon points="10,10,310,10,310,230,10,230" style="fill:#00ff00;" />
</svg> 
</div>

<div class="shape" onclick="shape('s');" id="s">
<svg height="240" width="320">
<polygon points="50,10,270,10,270,230,50,230" style="fill:#00ff00;" />
</svg> 
</div>

<div class="shape" onclick="shape('c');" id="c">
<svg height="240" width="320">
<circle cx="160" cy="120" r="110" fill="#00ff00" />
</svg> 
</div>

<br style="clear:left;"><br><br>

<div class="color" style="background-color:#00f;" onclick="color('a', '#00f')"></div>
<div class="color" style="background-color:#A52A2A;" onclick="color('b', '#A52A2A')"></div>
<div class="color" style="background-color:#FAAFBE;" onclick="color('c', '#FAAFBE')"></div>
<div class="color" style="background-color:#FF0;" onclick="color('d', '#FF0')"></div>
<div class="color" style="background-color:#FF8000;" onclick="color('e', '#FF8000')"></div>
<div class="color" style="background-color:#f00;" onclick="color('f', '#f00')"></div>
<div class="color" style="background-color:#0f0;" onclick="color('g', '#0f0')"></div>
<div class="color" style="background-color:#fff;" onclick="color('h', '#fff')"></div>

<br style="clear:left;"><br><br>

<div id="result">
</div>
<iframe style="width:1px; height:1px; position:absolute; top:-5px; right:-5px;" id="ifr"></iframe>
</body>
</html>
)=====";


#define _sclk 14
#define _miso 12
#define _mosi 13
#define _cs 15
#define _dc 2
#define _rst 4

const char* ssid = "NaguissaShapes";
const char* password = "";

//MDNSResponder mdns;
ESP8266WebServer server(80);


// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);


//#define min(a,b) (a<b?a:b)

char lastColor = ' ';
char lastShape = ' ';


void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleNotFound() {
  server.send(200, "text/html", "<h1>Not found</h1>");
}



void triangle(uint16_t color) {
  tft.fillScreen(COLOR_BLACK);
  tft.fillTriangle(160, 5, 30, 235, 310, 235, color);
}

void rectangle(uint16_t color) {
  tft.fillScreen(COLOR_BLACK);
  tft.fillRect(10, 10, 300, 220, color);
}

void square(uint16_t color) {
  tft.fillScreen(COLOR_BLACK);
  tft.fillRect(50, 10, 220, 220, color);
}

void circle(uint16_t color) {
  tft.fillScreen(COLOR_BLACK);
  tft.fillCircle(160, 120, 110, color);
}


void shapeWeb() {
    server.send(200, "text", "1");
  char shape = server.arg(0).charAt(0);
  char color = server.arg(1).charAt(0);

if (lastColor != color && lastShape != shape) {
lastColor = color;
lastShape = shape;

  
  uint16_t scolor = COLOR_GREEN;

  switch (color) {
	case 'a': scolor = COLOR_BLUE; break;
	case 'b': scolor = COLOR_BROWN; break;
	case 'c': scolor = COLOR_PINK; break;
	case 'd': scolor = COLOR_YELLOW; break;
	case 'e': scolor = COLOR_ORANGE; break;
	case 'f': scolor = COLOR_RED; break;
	case 'g': scolor = COLOR_GREEN; break;
	case 'h': scolor = COLOR_WHITE; break;
  }
  switch (shape) {
	case 's': square(scolor); break;
	case 'r': rectangle(scolor); break;
	case 'c': circle(scolor); break;
	case 't': triangle(scolor); break;
  }
}
}



unsigned long IPText() {
  tft.fillScreen(COLOR_BLACK);
  yield();
  tft.setCursor(0, 0);
  tft.setTextColor(COLOR_WHITE);  tft.setTextSize(3);
  tft.println();
  tft.println("Preparado");
  tft.println();
  tft.setTextColor(COLOR_RED);    tft.setTextSize(3);
  IPAddress myIP = WiFi.softAPIP();
  tft.println("IP del AP:");
  tft.setTextColor(COLOR_GREEN);
  tft.println(myIP);
}




void setupTFT() {
  tft.begin();
  tft.setRotation(1);
}

void setupSerial() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
}

void setupWifi(void) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 11);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/paint/", HTTP_GET, shapeWeb);
  server.onNotFound(handleNotFound);

  server.begin();
}




void setup() {
    setupSerial();
    Serial.println("Serial OK");
  setupTFT();
    Serial.println("TFT OK");
  setupWifi();
    Serial.println("Wifi OK");
  IPText();
    Serial.println("IP OK");
    Serial.println("-- Setup done --");


}

void loop() {
  yield();
  server.handleClient();
}

