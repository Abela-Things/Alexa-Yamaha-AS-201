/*
 * This code works for both ESP32 and ESP8266 on ArduinoIDE 1.8.16
 * 
 * Wiring:
 * - IR Data to pin 12
 */

#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif //ESP32

#include <Arduino.h>
#include <fauxmoESP.h>
#include <IRremote.hpp>

#define SERIAL_BAUDRATE     115200

#define ID_POWER             "ampli power"
#define ID_LINE1             "ampli line 1"
#define ID_LINE2             "ampli line 2"
#define ID_PHONO             "ampli phono"
#define ID_CD                "ampli cd"
#define ID_TUNER             "ampli tuner"

#define POWER_CODE  0xD42A817E
#define LINE1_CODE  0x3FC1857A
#define LINE2_CODE  0xE618857A
#define PHONO_CODE  0xEA14857A
#define CD_CODE     0xEB15857A
#define TUNER_CODE  0xE816857A

#define WIFI_SSID "..."
#define WIFI_PASS "..."

fauxmoESP fauxmo;

void blink()
{
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
}

void setupWifi()
{
    WiFi.mode(WIFI_STA); //setting up wifi client mode
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
    Serial.printf("Successful connexion to %s\nIP: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup()
{
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();

    // setup status led to alert when an IR code is being sent
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // setup IR library on pin12 for the emitter
    IrSender.begin(12);

    setupWifi();

    // By default, fauxmoESP creates it's own webserver on the defined port
    // The TCP port must be 80 for gen3 devices (default is 1901)
    // This has to be done before the call to enable()
    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // Disabling the library will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // Add the virtual devices that will be seen by Alexa
    fauxmo.addDevice(ID_POWER);
    fauxmo.addDevice(ID_LINE1);
    fauxmo.addDevice(ID_LINE2);
    fauxmo.addDevice(ID_PHONO);
    fauxmo.addDevice(ID_CD);
    fauxmo.addDevice(ID_TUNER);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value)
    {    
        // Callback for when a command from Alexa is received.
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        if (!strcmp(device_name, ID_POWER)) {
            IrSender.sendNECRaw(POWER_CODE, 0);
            blink();
        } else if (!strcmp(device_name, ID_LINE1)) {
            IrSender.sendNECRaw(LINE1_CODE, 0);
            blink();
        } else if (!strcmp(device_name, ID_LINE2)) {
            IrSender.sendNECRaw(LINE2_CODE, 0);
            blink();
        } else if (!strcmp(device_name, ID_PHONO)) {
            IrSender.sendNECRaw(PHONO_CODE, 0);
            blink();
        } else if (!strcmp(device_name, ID_CD)) {
            IrSender.sendNECRaw(CD_CODE, 0);
            blink();
        } else if (!strcmp(device_name, ID_TUNER)) {
            IrSender.sendNECRaw(TUNER_CODE, 0);
            blink();
        }
    });
}

void loop()
{
    fauxmo.handle(); //does the different checks needed to monitor for incoming async traffic.
}
