// TrinketKeyboard library from Adafruit
// https://learn.adafruit.com/trinket-usb-keyboard/code
#include <TrinketKeyboard.h>

#define NUM_BUTTONS 6
#define button1 0
#define button2 1
#define button3 2

void Trinket_wrapper(byte key);
void debounce_poll(int deb);

byte value = 0;
byte state;
byte last_state = 0;
long last_debounce_time = 0;
long debounce_delay = 30;

char *keycode[8] = {"null", "blue", "brown", "red", "green", "clear", "black", "null"};

typedef struct {
  char modifiers;
  char key0;
  char key1;
  char key2;
  char key3;
  char key4;
  char key5;
} keypress;

keypress keymap[8] = {
  {0,         0,          0,          0,          0,          0,          0}, //NC
  {0,         KEYCODE_L,        0,          0,          0,          0,          0}, //Top Left
  {0,         KEYCODE_B,        0,          0,          0,          0,          0}, //Top Middle
  {0,         KEYCODE_R,        0,          0,          0,          0,          0}, //Top Right
  {0,         KEYCODE_G,        0,          0,          0,          0,          0}, //Bottom Left
  {0,         KEYCODE_C,        0,          0,          0,          0,          0}, //Bottom Middle
  {0,         KEYCODE_K,        0,          0,          0,          0,          0}, //Bottom Right
  {0,         0,          0,          0,          0,          0,          0}  //NC
};
void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  TrinketKeyboard.begin();
}

void loop()
{

  //debounce_poll(DEBOUNCE);
  TrinketKeyboard.poll();
  value |= (!digitalRead(button1) << 0);
  value |= (!digitalRead(button2) << 1);
  value |= (!digitalRead(button3) << 2);
  
  // Debounce code inspiration from arduino tutorial.
  // https://www.arduino.cc/en/Tutorial/Debounce
    if (value != last_state) {
    last_debounce_time = millis();
  }
  if ((millis() - last_debounce_time) > debounce_delay) {
    if (value != state) {
      state = value;
      if ( state > 0x00 && state < 0x07 ) {
        Trinket_pressKey_wrapper(state);
        TrinketKeyboard.pressKey(0, 0);
      }
    }
  }
  last_state = value;
  value = 0;

}
void Trinket_pressKey_wrapper(byte key)
{
  TrinketKeyboard.pressKey(keymap[key].modifiers, keymap[key].key0,
                           keymap[key].key1, keymap[key].key2,
                           keymap[key].key3, keymap[key].key4,
                           keymap[key].key5);
}
void debounce_poll(int deb)
{
  for (byte i = 0; i < deb / 5; i++) {
    TrinketKeyboard.poll();
    delay(5);
  }

}
