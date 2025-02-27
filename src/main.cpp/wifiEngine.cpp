#include "wifiEngine.h"
#include "DisplayInit.h"
#include  <map>
#include <string.h>
#include <set>
#include <iostream>

using namespace std;

class wifiEngine {
private:
    int foundwifi = 0;
    int displaystate = 0;
    std::map<string, set <string>> wifiList;
    
    
    void wifiHashMap(int  networksFound){
        for(int i = 0; i < networksFound ; i++)
        {
          string key = WiFi.SSID(i).c_str();

          std::set <string> WifiMetadata = { WiFi.SSID(i).c_str(), to_string(WiFi.RSSI(i)), to_string(WiFi.channel(i))};
          wifiList[key] =  WifiMetadata;
        }
    }

public:
    int getFoundWifi() { return foundwifi; }
    void setFoundWifi(int value) { foundwifi = value; }

    void scanForNetworks() {
        foundwifi = WiFi.scanComplete();
        if (foundwifi < 0) {
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
    {
        if(foundwifi < 0){
            tft.setCursor(80,64);
            tft.print("No Network Found");
        }else{
            
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
    while(true){
        wifiEngine engine1;
        engine1.scanForNetworks();
        engine1.displayNetworks();
        
    }
}
