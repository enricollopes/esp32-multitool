#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int pins[] = {5,18,23,19}; // UP, DOWN, OK, BACK
const char* menu[] = {"Wi-Fi scan", "BLE scan", "Hardware", "Sistema"};
int selected=0, page=0, offset=0, count=0;
String rows[40];
BLEScan* scanner;

void draw() {
  oled.clearDisplay(); oled.setTextSize(1); oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,0); oled.println(page ? menu[page-1] : "ESP32 MultiTool V1.0");
  oled.drawLine(0,10,127,10,SSD1306_WHITE);
  if (!page) {
    for(int i=0;i<4;i++){ oled.setCursor(0,15+i*12); oled.print(i==selected?"> ":"  "); oled.print(menu[i]); }
  } else {
    for(int i=offset;i<count && i<offset+5;i++){ oled.setCursor(0,13+(i-offset)*10); oled.print(rows[i].substring(0,21)); }
  }
  oled.display();
}
void openPage(){
  page=selected+1; offset=0; count=0;
  oled.clearDisplay(); oled.setCursor(0,0); oled.println("Aguarde..."); oled.display();
  if(page==1){
    WiFi.mode(WIFI_STA); WiFi.disconnect();
    int n=WiFi.scanNetworks();
    for(int i=0;i<n && count<40;i++){
      rows[count++]=WiFi.SSID(i).substring(0,20);
      rows[count++]=String(WiFi.RSSI(i))+" dBm CH "+String(WiFi.channel(i));
    }
    WiFi.scanDelete(); WiFi.mode(WIFI_OFF);
  } else if(page==2){
    BLEScanResults* results=scanner->start(5,false);
    if(results){
      for(int i=0;i<results->getCount() && count<40;i++){
        BLEAdvertisedDevice d=results->getDevice(i);
        rows[count++]=d.haveName()?String(d.getName().c_str()):String("Sem nome");
        rows[count++]=String(d.getRSSI())+" dBm";
      }
    }
    scanner->clearResults();
  } else if(page==3){
    rows[count++]=ESP.getChipModel(); rows[count++]="OLED SSD1306";
    rows[count++]="I2C: 21 / 22"; rows[count++]="Botoes: 5/18/23/19";
  } else {
    rows[count++]="CPU: "+String(ESP.getCpuFreqMHz())+" MHz";
    rows[count++]="Heap: "+String(ESP.getFreeHeap()/1024)+" KB";
    rows[count++]="Flash: "+String(ESP.getFlashChipSize()/1048576)+" MB";
    rows[count++]="Uptime: "+String(millis()/1000)+" s";
  }
  if(!count) rows[count++]="Nenhum resultado";
  draw();
}
void setup(){
  Serial.begin(115200);
  for(int p:pins) pinMode(p,INPUT_PULLUP);
  Wire.begin(21,22);
  if(!oled.begin(SSD1306_SWITCHCAPVCC,0x3C)){Serial.println("OLED indisponivel");while(true) delay(1000);}
  oled.setTextWrap(false);
  BLEDevice::init(""); scanner=BLEDevice::getScan(); scanner->setActiveScan(false);
  draw();
}
void loop(){
  static bool previous[4]={true,true,true,true};
  for(int i=0;i<4;i++){
    bool now=digitalRead(pins[i]);
    if(previous[i] && !now){
      delay(30);
      if(digitalRead(pins[i])==LOW){
        if(i==3){page=0;draw();}
        else if(!page){if(i==0)selected=(selected+3)%4; if(i==1)selected=(selected+1)%4; if(i==2)openPage();else draw();}
        else {if(i==0 && offset>0)offset--;if(i==1 && offset+5<count)offset++;draw();}
      }
    }
    previous[i]=now;
  }
  delay(15);
}
