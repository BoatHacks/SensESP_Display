#ifndef _AZTOUCH_H_
#define _AZTOUCH_H_

#include <Adafruit_GFX.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controllers/system_status_controller.h"
#include "system/enable.h"

#define SCREEN_WIDTH 240  // TFT display width, in pixels
#define SCREEN_HEIGHT 320  // TFT display height, in pixels

class TFTDisplayController : public ValueConsumer<SystemStatus>,
                                 public ValueConsumer<int>,
                                 public ValueConsumer<float>,
                                 public ValueConsumer<bool>,
                                 public ValueConsumer<String>,
                                 public Enable {
 protected:
  TFT_eSPI* display;
  Networking* networking;
  WSClient* ws_client;

  virtual void set_wifi_no_ap();
  virtual void set_wifi_disconnected();
  virtual void set_wifi_connected();
  virtual void set_wifimanager();

  virtual void set_ws_disconnected();
  virtual void set_ws_authorizing();
  virtual void set_ws_connecting();
  virtual void set_ws_connected();

  void show_text(int baseline, const char* text);

 public:
  TFTDisplayController();

  virtual void enable() override;

  // ValueConsumer interface for ValueConsumer<SystemStatus>
  virtual void set_input(SystemStatus input,
                         uint8_t input_channel = 0) override;

  virtual void set_input(int input, uint8_t input_channel = 0) override;

  virtual void set_input(float input, uint8_t input_channel = 0) override;

  virtual void set_input(bool input, uint8_t input_channel = 0) override;

  virtual void set_input(String input, uint8_t input_channel = 0) override;

  void update_slot(int slot);
  void update_float(int slot, float input);
  void update_int(int slot, int input);
  void update_str(int slot, String input);

  void blip(int duration);
};

#endif
