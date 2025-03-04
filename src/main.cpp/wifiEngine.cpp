#include "wifiEngine.h"
using namespace std;

int level; 
int lastlevel = 0;

class wifiEngine {
private:
    int foundwifi = 0;
    int displaystate = 0;
    std::map<string, set <string>> wifiList;

    set <string> uniquekeys;
    vector <string> keys;

    
    
    
    void wifiHashMap(int  networksFound){
        
        for(int i = 0; i < networksFound ; i++)
        {
          
          string key = WiFi.SSID(i).c_str();
          if(!uniquekeys.count(key))
          {
            keys.push_back(key);
            uniquekeys.insert(key);
          }

          std::set <string> WifiMetadata = { WiFi.SSID(i).c_str(), to_string(WiFi.RSSI(i)), to_string(WiFi.channel(i)), to_string(WiFi.encryptionType(i))};
          wifiList[key] =  WifiMetadata;
        }
    }

public:
    int getFoundWifi() { return foundwifi; }
    void setFoundWifi(int value) { foundwifi = value; }
    std::vector <pair<int,int>> positions = {{5,12},{5,32},{5,52}, {5,72},{5,92},{5,112}} ;
    String screenstring;

    void scanForNetworks() {
        foundwifi = WiFi.scanComplete();
        if (foundwifi < 0 ) {
            if (foundwifi == WIFI_SCAN_FAILED) {
                Serial.println("WiFi Scan failed. Restarting scan...");
                WiFi.scanNetworks(true);
            }
        } else {
            wifiHashMap(foundwifi);
            wifiStatusPrinter(foundwifi);
            Serial.println("Starting new scan...");
            WiFi.scanNetworks(true);
        }
    }


    //function is used for debugging 

    int getWifiList()
    {
        return wifiList.size();
    }

    void displayNetworks()
    {   tft.setCursor(5, 1);
        tft.print("Wifi Sniffer");

        if (foundwifi > 1 && !wifiList.empty()){
          int size = wifiList.size();
            int maxRectangles = min(size, 6); // Ensure at most 6 rectangles

            for (int i = 0; i < maxRectangles; i++) { 
              tft.drawRect(5, 10 + (i * 20), 150, 15, ST7735_BLACK);
            }

            for(int i = 0 ; i < 6; i++){
              tft.setCursor(positions[i].first + 3, positions[i].second+3);
              auto& data =  wifiList[keys[i]];
              screenstring  = data.rbegin()->c_str();
              auto  end = screenstring.length();
            
              if(end > 14){
                screenstring.remove(13, end-14);
                tft.print(screenstring + "....");
              }else{
                tft.print(screenstring);
              }
            
            }
        }else if(foundwifi == 1){
            tft.setCursor(40,64);
            tft.print("No Network Found");
        }
    }


    void clearEntrys()
    {   
      for(int i = 1 ; i < 7; i++){
        tft.fillRect(5,(20*i)-10,150,15, ST7735_WHITE);
      }
    }

    void  updateCursor()
    {
      tft.fillRect(120, 14 + (lastlevel * 20),25, 10, ST7735_WHITE);
      tft.drawRect(120, 14 + (level * 20), 25, 10, ST7735_WHITE);
      tft.setCursor(130,  14 + (level * 20));
      tft.print("<-");
    }

};

void wifisetup() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println("Setup done");
    WiFi.scanNetworks(true);
}

void wifiStatusPrinter(uint16_t networksFound) {
    if (networksFound == 0) {
        Serial.println("No networks found");
    } else {
        Serial.println("\nScan done");
        Serial.print(networksFound);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");

        for (int i = 0; i < networksFound; ++i) {
            Serial.printf("%2d | %-32.32s | %4ld | %2ld | ",
                          i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), WiFi.channel(i));

            switch (WiFi.encryptionType(i)) {
                case WIFI_AUTH_OPEN:            Serial.print("Open"); break;
                case WIFI_AUTH_WEP:             Serial.print("WEP"); break;
                case WIFI_AUTH_WPA_PSK:         Serial.print("WPA"); break;
                case WIFI_AUTH_WPA2_PSK:        Serial.print("WPA2"); break;
                case WIFI_AUTH_WPA_WPA2_PSK:    Serial.print("WPA+WPA2"); break;
                case WIFI_AUTH_WPA2_ENTERPRISE: Serial.print("WPA2-EAP"); break;
                case WIFI_AUTH_WPA3_PSK:        Serial.print("WPA3"); break;
                case WIFI_AUTH_WPA2_WPA3_PSK:   Serial.print("WPA2+WPA3"); break;
                case WIFI_AUTH_WAPI_PSK:        Serial.print("WAPI"); break;
                default:                        Serial.print("Unknown");
            }
            Serial.println();
            delay(10);
        }

        Serial.println("");
        WiFi.scanDelete();
    }
}

void wifirun() {
    int previousMappedValue = 0;
    tft.fillScreen(ST7735_WHITE);
    tft.setCursor(70, 60);
    tft.setTextColor(ST7735_BLACK,ST7735_WHITE);

    wifiEngine engine1;
    Potentiometer potentiometer2;
    cursorArrow arrow1;
    //Potentiometer Potentiometer2;
    wifisetup();
    delay(100);
    engine1.scanForNetworks();

    delay(100);
    
    engine1.displayNetworks();
    engine1.clearEntrys();

    while(true){
      char key = loopy();
      level = arrow1.getcursorLevel();
      delay(10);
      potentiometer2.getPotValue();

      delay(10);

      if(engine1.getWifiList() > 0){
        engine1.updateCursor();
      }
      
      delay(10);

      if(key == 'E'){ //RELOADS WIFI SCAN
        Serial.print("Refreshing...");
        engine1 = wifiEngine(); // Reinitialize engine1
        engine1.clearEntrys();// clear the menu boxes 
        delay(200);

        engine1.scanForNetworks(); 
        
        engine1.displayNetworks();
      }

      if(mappedValue > previousMappedValue + 4){
        arrow1.increase();
        cout<< "increasing"<<endl;
      }

      if(mappedValue < previousMappedValue -4 ){
        arrow1.decrease();
        cout<< "decreasing"<<endl;
      }
  

      lastlevel = level;
      previousMappedValue = mappedValue;
      cout << mappedValue << "and" << level <<endl;
    }
}
