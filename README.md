# Alexa-Yamaha-AS-201-remote

## Description
This Arduino Sketch creates 6 virtual Philips Hue lights that are detectable by Alexa. Each one of them when turned ON or OFF will send an IR code for a specific function of the Yamaha AS-201 Sound Amplifier

This code works for both ESP32 and ESP8266 on ArduinoIDE 1.8.16 with the latest versions available of AsyncTCP and ESPAsyncTCP on the 28th of march 2022.

You will need to change the Wifi SSID and password, and use the "search for devices" functionality of the Alexa App to set it up, the virtual device you create will appear as Philips Hue lights but you can program them to behave as anything other than a light through Alexa routines if needed.

If you happen to have this kind of crappy IR emmiter (https://www.amazon.fr/iHaospace-Infrared-Transmitter-Receiver-Compatible/dp/B0893BD1V6/) to be used as a remote, you will have to desolder the IR LED resistance and replace it with a wire as it was not even powerful enough to work against the IRreceiver of the amplifier. (This is a risk for the ESP8266 or ESP32 as the maximum theorical current output of their GPIO pins is only 20mA and the LED may be drawing more from the data line in this circuit, but it didn't cause any issues for me.)

Or you can try finding another one, or pairing a transistor and a powerful enough IR LED on your own circuit.

## functionalities:

* Power On/OFF
* Line 1 input
* Line 2 input
* Phono input
* CD input
* Tuner input

## Wiring:
* IR Data to Pin 12

## Dependencies:
* AsyncTCP for the ESP32
* ESPAsyncTCP for the ESP8266
* fauxmoESP for the Philips Hue emulation library
* IRremote for the IR control library (used for emitting only here but is capable of both receiving and sending IR codes)

## Pour The B:
Un hôte qui se respecte se doit de servir le saucisson dans une saucissonette.
