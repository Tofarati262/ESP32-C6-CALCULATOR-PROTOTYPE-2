#include "wifiEngine.h"
#include "DisplayInit.h"
#include  <map>
#include <vector>
#include <string.h>
#include <set>
#include <iostream>
#include "Exiomatrix.h"

using namespace std;

class wifiEngine {
private:
    int foundwifi = 0;
    int displaystate = 0;
    std::map<string, set <string>> wifiList;

    vector <string> keys;


    
    
    void wifiHashMap(int  networksFound){
        for(int i = 0; i < networksFound ; i++)
        {
          string key = WiFi.SSID(i).c_str();
          keys.push_back(key);

          std::set <string> WifiMetadata = { WiFi.SSID(i).c_str(), to_string(WiFi.RSSI(i)), to_string(WiFi.channel(i)), to_string(WiFi.encryptionType(i))};
          wifiList[key] =  WifiMetadata;
        }
    }

public:
    int getFoundWifi() { return foundwifi; }
    void setFoundWifi(int value) { foundwifi = value; }
    std::vector <pair<int,int>> positions = {{5,12},{5,32},{5,52}, {5,72},{5,92},{5,112}} ;

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

    void getWifiList()
    {
        if(wifiList.empty())
        {
            cout<<"Empty Wifi List"<< endl;
        }else{
            for(auto wifi : wifiList)
            {
                cout<<"SSID: " << wifi.first << endl;

                cout << "Metadata: ";
                for (const auto& data : wifi.second) {  
                    cout << data << " | ";  // RSSI and channel info
                }
                cout << endl;
            }
        }

    }

    void displayNetworks()
    {   tft.setCursor(5, 1);
        tft.print("Wifi Sniffer");

         if (foundwifi > 1 && !wifiList.empty()){
            tft.drawRect(5,10,150,15, ST7735_BLACK);
            tft.drawRect(5,30,150,15, ST7735_BLACK);
            tft.drawRect(5,50,150,15, ST7735_BLACK);
            tft.drawRect(5,70,150,15, ST7735_BLACK);
            tft.drawRect(5,90,150,15, ST7735_BLACK);
            tft.drawRect(5,110,150,15, ST7735_BLACK);

            for(int i = 0 ; i < 6; i++){
              tft.setCursor(positions[i].first + 3, positions[i].second);
              auto& data =  wifiList[keys[i]];
              tft.print(data.rbegin()->c_str());
            }
        }else if(foundwifi == 1){
            tft.setCursor(40,64);
            tft.print("No Network Found");
        }
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
    tft.fillScreen(ST7735_WHITE);
    tft.setCursor(70, 60);
    tft.setTextColor(ST7735_BLACK,ST7735_WHITE);

    wifiEngine engine1;
    //Potentiometer Potentiometer2;
    wifisetup();
    engine1.scanForNetworks();
    engine1.displayNetworks();

    while(true){
       char key = loopy();
        //mappedValue = Potentiometer2.getPotValue();
        if(key == 'E'){ //RELOADS WIFI SCAN
          Serial.print("Refreshing...");
          wifiEngine engine1;
          engine1.scanForNetworks(); 
          engine1.displayNetworks();
        }
    }
}
