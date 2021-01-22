# SensESPStatusDisplay

SensESP_Display is a display library for the 
[SensESP Signal K sensor device library](https://github.com/SignalK/SensESP)
to get information from your SignalK server onto a small TFT screen.

It is based in big parts upon [SensESPStatusDisplay](https://github.com/mairas/SensESPStatusDisplay) by Matti Airas.

The current code assumes you are using an [AZ-Touch wallmount TFT display](https://www.az-delivery.de/en/products/az-touch-wandgehauseset-mit-2-8-zoll-touchscreen-fur-esp8266-und-esp32)

The status part of the display currently shows:
- Wifi status or the access point SSID
- Signal K server address
- Current local IP address of the display

The SignalK paths for the four value display slots can be changed in main.cpp

The touchscreen of the AZ-Touch kit isn't yet supported.

Plans for the future include using LVGL as a graphics and touch-input library, and making the display slots configurable through the SensESP web interface.

SensESP supports Over-The-Air (OTA) updates, so once you have the firmware installed on your wallmount unit, you can upload subsequent versions with:

    pio run --target upload --upload-port <your_display_IP-address>

To use the  display library in your own projects, you have to include
it in your `platformio.ini` lib_deps section:

    lib_deps =
        SignalK/SensESP
        https://github.com/BoatHacks/SensESP_Display.git#latest
