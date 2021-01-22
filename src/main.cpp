#include <Arduino.h>

#include "controllers/aztouch.h"
#include "sensesp_app.h"
#include "sensesp_app_builder.h"
#include "signalk/signalk_output.h"
#include "sensors/digital_output.h"
#include "signalk/signalk_listener.h"
#include "signalk/signalk_output.h"
#include "signalk/signalk_value_listener.h"
#include "transforms/transform.h"

#include "user_settings.h"

ReactESP app([]() {
#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif
  
  // enable TFT backlight
  ledcSetup(0, 5000, 8);  // set up channel 0 with 5000 Hz PWM, 8 bit duty cycle resolution
  ledcAttachPin(15, 0);   // attach backlight pin 15 to channel 0
  ledcWrite(0, 0);        // backlight is inverted: 0 is full brightness, 255 is off
  delay(1);               // not sure if necessary, works better this way

/*
  // setup piezo buzzer
  ledcSetup(1,1E5,12);    // set up channel 1 with 100000 Hz
  ledcAttachPin(21,1);    // attach pin 21 to channel 1
  ledcWriteTone(1,1000);  // play 1000Hz tone on channel 1
  delay(150);             // wait 150ms
  ledcWriteTone(1,2000);  // play 2000Hz tone on channel 1
  delay(250);             // wait 250ms
  ledcWriteTone(1,0);     // silence on channel 1
*/

  SensESPAppBuilder builder;

  sensesp_app = builder.set_hostname("AZTouch")
                    ->set_wifi(WIFI_SSID, WIFI_PASSWD)
                    ->set_sk_server(SK_SERVER, SK_PORT)
                    ->set_standard_sensors()
                    ->get_app();
  

  // create the TFT display controller
  TFTDisplayController* display_controller =
      new TFTDisplayController();

  sensesp_app->get_system_status_controller()->connect_to(display_controller);


  const char* sk_path1 = "environment.outside.humidity";  
  auto* slot1 = new SKNumericListener(sk_path1);
  auto* slot1_consumer = new LambdaConsumer<float>([display_controller](float input) {
    display_controller->update_float(1, input);
  });
  slot1->connect_to(slot1_consumer);

  const char* sk_path2 = "environment.outside.pressure";
  auto* slot2 = new SKNumericListener(sk_path2);
  auto* slot2_consumer = new LambdaConsumer<float>([display_controller](float input) {
    display_controller->update_float(2, input/100);
  });
  slot2->connect_to(slot2_consumer);

  const char* sk_path3 = "environment.outside.temperature";
  auto* slot3 = new SKNumericListener(sk_path3);
  auto* slot3_consumer = new LambdaConsumer<float>([display_controller](float input) {
    display_controller->update_float(3, input-273.15);
  });
  slot3->connect_to(slot3_consumer);

  const char* sk_path4 = "navigation.state";
  auto* slot4 = new SKStringListener(sk_path4, 1000);
  auto* slot4_consumer = new LambdaConsumer<String>([display_controller](String input) {
    display_controller->update_str(4, input);
  });
  slot4->connect_to(slot4_consumer);

  sensesp_app->enable();

});
