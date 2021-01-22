#include <Adafruit_GFX.h>  // Core graphics library
#include <Arduino.h>

#include "sensesp_app.h"
#include "aztouch.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define ROW0 0
#define ROW1 20
#define ROW2 40

#define DELTA_GRAPH_HEIGHT 60

TFTDisplayController::TFTDisplayController()
    : networking{networking}, ws_client{ws_client} {

  display = new TFT_eSPI();
  display->begin();
  display->setRotation(0);
  display->fillScreen(TFT_BLACK);
}

void TFTDisplayController::enable() {
  // nothing here yet
}

void TFTDisplayController::set_wifi_no_ap() {
  this->show_text(ROW0, "No AP");
  this->show_text(ROW2, "");
}

void TFTDisplayController::set_wifi_disconnected() {
  this->show_text(ROW0, "WiFi disconnected");
  this->show_text(ROW2, "");
}

void TFTDisplayController::set_wifi_connected() {
  this->show_text(ROW0, WiFi.SSID().c_str());
  this->show_text(ROW2, WiFi.localIP().toString().c_str());
}

void TFTDisplayController::set_wifimanager() {
  this->show_text(ROW0, "WifiManager");
  this->show_text(ROW2, WiFi.localIP().toString().c_str());
}

void TFTDisplayController::set_ws_disconnected() {
  this->show_text(ROW1, "WebSocket disconnected");
}

void TFTDisplayController::set_ws_authorizing() {
  this->show_text(ROW1, "Authorizing");
}

void TFTDisplayController::set_ws_connecting() {
  this->show_text(ROW1, "WS connecting");
}

void TFTDisplayController::set_ws_connected() {
  this->show_text(ROW1,
                  sensesp_app->get_ws_client()->get_server_address().c_str());
}

void TFTDisplayController::set_input(SystemStatus input,
                                         uint8_t input_channel) {
  // FIXME: If pointers to member functions would be held in an array,
  // this would be a simple array dereferencing
  switch (input) {
    case SystemStatus::kWifiNoAP:
      this->set_wifi_no_ap();
      break;
    case SystemStatus::kWifiDisconnected:
      this->set_wifi_disconnected();
      break;
    case SystemStatus::kWifiManagerActivated:
      this->set_wifimanager();
      break;
    case SystemStatus::kWSDisconnected:
      this->set_wifi_connected();
      this->set_ws_disconnected();
      break;
    case SystemStatus::kWSAuthorizing:
      this->set_wifi_connected();
      this->set_ws_authorizing();
      break;
    case SystemStatus::kWSConnecting:
      this->set_wifi_connected();
      this->set_ws_connecting();
      break;
    case SystemStatus::kWSConnected:
      this->set_wifi_connected();
      this->set_ws_connected();
      break;
  }
}

void TFTDisplayController::update_float(int slot, float input) {
  display->setTextColor(TFT_WHITE, TFT_BLUE);
  display->setTextPadding(SCREEN_WIDTH);
  display->setTextDatum(TR_DATUM);
  display->drawFloat(input, 2, SCREEN_WIDTH, slot*SCREEN_HEIGHT/5, 7);
}

void TFTDisplayController::update_int(int slot, int input) {
  display->setTextColor(TFT_WHITE, TFT_BLUE);
  display->setTextPadding(SCREEN_WIDTH);
  display->setTextDatum(TR_DATUM);
  display->drawNumber(input, SCREEN_WIDTH, slot*SCREEN_HEIGHT/5, 7);
}

void TFTDisplayController::update_str(int slot, String input) {
  display->setTextColor(TFT_WHITE, TFT_BLUE);
  display->setTextPadding(SCREEN_WIDTH);
  display->setTextDatum(TR_DATUM);
  display->setTextSize(3);
  display->drawString(input, SCREEN_WIDTH, slot*SCREEN_HEIGHT/5, 2);
  display->setTextSize(1);
}

void TFTDisplayController::show_text(int baseline, const char* text) {
  display->setTextColor(TFT_WHITE, TFT_BLACK);
  display->setCursor(0, baseline);
  display->fillRect(0, baseline, SCREEN_WIDTH, 20, TFT_BLACK);
  display->setTextFont(2);
  display->print(text);
}

void TFTDisplayController::set_input(float input, uint8_t input_channel) {
  // nothing here yet
}

void TFTDisplayController::set_input(int input, uint8_t input_channel) {
  // nothing here yet
}

void TFTDisplayController::set_input(bool input, uint8_t input_channel) {
  // nothing here yet
}

void TFTDisplayController::set_input(String input, uint8_t input_channel) {
  // nothing here yet
}

