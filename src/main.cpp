#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <NeoPixelBus.h>

char auth[] = "cd79be1316f14c81bef73f3c43438059";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pilate2";
char pass[] = "asdfghjklqwer";

#define colorSaturation 255

const uint16_t PixelCount = 128; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 4;  // make sure to set this to the correct pin, ignored for Esp8266

// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, Neo400KbpsMethod> strip(PixelCount, PixelPin);

// For Esp8266, the Pin is omitted and it uses GPIO3 due to DMA hardware use.  
// There are other Esp8266 alternative methods that provide more pin options, but also have
// other side effects.
//NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
//
// NeoEsp8266Uart800KbpsMethod uses GPI02 instead

// You can also use one of these for Esp8266, 
// each having their own restrictions
//
// These two are the same as above as the DMA method is the default
// NOTE: These will ignore the PIN and use GPI03 pin
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266Dma400KbpsMethod> strip(PixelCount, PixelPin);

// Uart method is good for the Esp-01 or other pin restricted modules
// NOTE: These will ignore the PIN and use GPI02 pin
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266Uart400KbpsMethod> strip(PixelCount, PixelPin);

// The bitbang method is really only good if you are not using WiFi features of the ESP
// It works with all but pin 16
//NeoPixelBus<NeoGrbFeature, NeoEsp8266BitBang800KbpsMethod> strip(PixelCount, PixelPin);
//NeoPixelBus<NeoRgbFeature, NeoEsp8266BitBang400KbpsMethod> strip(PixelCount, PixelPin);

// four element pixels, RGBW
//NeoPixelBus<NeoRgbwFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

int redShade = 0;
int greenShade = 0;
int blueShade = 0;

int OnOffState = 0;

RgbColor BlynkColor(redShade,greenShade,blueShade);

BLYNK_WRITE(V1)
{
  redShade = param.asInt();
  BlynkColor = RgbColor(redShade, greenShade, blueShade);
  if (OnOffState == 1){
    for(int i=0;i<PixelCount;i++){
      strip.SetPixelColor(i, BlynkColor);
    }
    strip.Show(); // This sends the updated pixel color to the hardware.
  }
}

BLYNK_WRITE(V2)
{
  greenShade = param.asInt();
  BlynkColor = RgbColor(redShade, greenShade, blueShade);
  if (OnOffState == 1){
    for(int i=0;i<PixelCount;i++){
      strip.SetPixelColor(i, BlynkColor);
    }
    strip.Show(); // This sends the updated pixel color to the hardware.
  }
}

BLYNK_WRITE(V3)
{
  blueShade = param.asInt();
  BlynkColor = RgbColor(redShade, greenShade, blueShade);
  if (OnOffState == 1){
    for(int i=0;i<PixelCount;i++){
      strip.SetPixelColor(i, BlynkColor);
    }
    strip.Show(); // This sends the updated pixel color to the hardware.
  }
}

BLYNK_WRITE(V0)
{
  int tempButtonState = param.asInt();
  OnOffState = tempButtonState;
  if (tempButtonState == 0){
    BlynkColor = RgbColor(0,0,0);
  }
  else{
    BlynkColor = RgbColor(redShade, greenShade, blueShade);
  }
  for(int i=0;i<PixelCount;i++){
    strip.SetPixelColor(i, BlynkColor);
  }
  strip.Show(); // This sends the updated pixel color to the hardware.
}

BLYNK_WRITE(V4)
{
  int tempButtonState = param.asInt();
  OnOffState = tempButtonState;
  if (tempButtonState == 0){
    BlynkColor = RgbColor(0,0,100);
    Serial.println("off");
  }
  else{
    BlynkColor = RgbColor(redShade, greenShade, blueShade);
    Serial.println("on");

  }
  for(int i=0;i<PixelCount;i++){
    strip.SetPixelColor(i, BlynkColor);
  }

  strip.Show(); // This sends the updated pixel color to the hardware.
}

void setup() {

  Serial.begin(115200);

  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}