#include <FastLED.h> // Manage Libraries -> Install FastLED



//#define DEBUG
#define SOUND

//#define DEBUG_GESTURE
#define GESTURE

#ifdef GESTURE
#include <Wire.h>
#include "PAJ7620U2.h"
#endif

#define MOTION_PIN        2
#define MIC_PIN           A0
#ifdef SOUND
  #define BUZZER_PIN      11
#endif
#define BUTTON_PIN        3

#define SLEEP_TIMEOUT     60000 // in milliseconds (seconds * 1000)
#define BUTTON_PRESS      1500
#define ENABLE_SLEEP      0

#define MODE_LISTEN       0
#define MODE_KNOCKBACK    1
#define MODE_SECURITY     2
#define MODE_SIZE         3

#define LED_LEFT          3
#define LED_MIDDLE        6
#define LED_RIGHT         0
#define LED_TOP_LEFT      2
#define LED_TOP_RIGHT     1
#define LED_BOTTOM_LEFT   4
#define LED_BOTTOM_RIGHT  5

#ifdef SOUND
#include "BrailleSpeak.h"
BrailleSpeak brailleSpeak(BUZZER_PIN);
#endif

unsigned long last_movement; // Last time motion was detected

unsigned long touch_start; // start of last touch

byte mode; // Which mode should we be running?

int ignore_motion = 0;

#include "ledhelper.h" // SETUP: configure #defines here
LEDHelper ledHelper;

#include "listener.h"
Listener listener(MIC_PIN);

#include "knockback.h"
#ifdef SOUND
  KnockBack knockback(MIC_PIN, BUZZER_PIN, &ledHelper);
#else
  KnockBack knockback(MIC_PIN, NULL, &ledHelper);
#endif


#ifdef GESTURE
unsigned short  Gesture_Data;
#endif

void setup()
{
#ifdef SOUND  
  pinMode(BUZZER_PIN, OUTPUT);
#endif
  pinMode(MOTION_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
#ifdef DEBUG
  Serial.begin(9600);
#endif

  last_movement = 0;
#ifdef SOUND
  Serial.println("hi");
  brailleSpeak.speak("hi");
#endif

  mode = MODE_LISTEN;
  show_mode(50);
//  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), log_press, RISING); // Doesn't work
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), log_release, FALLING);

  #ifdef GESTURE
  uint8_t i;
  #ifdef DEBUG_GESTURE
  Serial.begin(115200);
  Serial.print("\nGesture Sensor Test Program ...\n");
  #endif
  delayMicroseconds(800);
  Wire.begin();
  delayMicroseconds(10);
  while(!PAJ7620U2_init())
  { 
    #ifdef DEBUG_GESTURE
    Serial.print("\nGesture Sensor Error\n");
    #endif
    delay(500);
  }
  #ifdef DEBUG_GESTURE
  Serial.print("\nGesture Sensor OK\n");
  #endif
  I2C_writeByte(PAJ_BANK_SELECT, 0);//Select Bank 0
  for (i = 0; i < Gesture_Array_SIZE; i++)
  {
    I2C_writeByte(Init_Gesture_Array[i][0], Init_Gesture_Array[i][1]);//Gesture register initializes
  }
  #endif
}

void log_press()
{
  // Doesn't work!
  Serial.println("press");
  touch_start = millis();
}
void log_release()
{
  unsigned long touch_end = millis();
  // Track button presses and length

  Serial.println("release");
  ledHelper.setEye(0, 0, 0);
//  FastLED.show();

//  if (mode == MODE_LISTEN) {
//    ledHelper.setEye(0, 10, 0);
//    delay(200);
//    ledHelper.setEye(0, 0, 0);
//  }

  // Cycle through modes if press is greater than BUTTON_PRESS
  if (touch_end - touch_start > BUTTON_PRESS) {
    mode = mode + 1;
    if (mode >= MODE_SIZE) mode = MODE_LISTEN;
    show_mode(50);
    Serial.println(mode);
#ifdef SOUND
    brailleSpeak.speak(mode + 'a');
#endif
  }
//  Serial.println(touch_end - touch_start);
  touch_start = NULL;

}

char getRandomLetter()
{
  byte randomValue = random(0, 26);
  char letter = randomValue + 'a';
  //   if(randomValue > 26)
  //      letter = (randomValue - 26) + '0';
  //   Serial.println(letter);
  return letter;
}

void show_mode(int val)
{
  
  ledHelper.set(7, (mode == MODE_SECURITY) * val, (mode == MODE_KNOCKBACK) * val, (mode == MODE_LISTEN) * val);
}



void loop()
{
    #ifdef GESTURE
    Gesture_Data = I2C_readU16(PAJ_INT_FLAG1);
    if (Gesture_Data)
    {
      switch (Gesture_Data)
      {
        case PAJ_UP:                   
//          Serial.print("Up\r\n");            
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_TOP_LEFT, 0, 0, 50);
          break;
        case PAJ_DOWN:                 
//          Serial.print("Down\r\n");          
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_BOTTOM_LEFT, 0, 0, 50);
          break;
        case PAJ_LEFT:                 
//          Serial.print("Left\r\n");          
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_LEFT, 0, 0, 50);
          break;
        case PAJ_RIGHT:                
//          Serial.print("Right\r\n");         
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_RIGHT, 0, 0, 50);
          break;
        case PAJ_FORWARD:
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_TOP_RIGHT, 0, 0, 50);
          ledHelper.set(LED_TOP_LEFT, 0, 0, 50);
          break;
        case PAJ_BACKWARD:
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_BOTTOM_RIGHT, 0, 0, 50);
          ledHelper.set(LED_BOTTOM_LEFT, 0, 0, 50);
          break;
        case PAJ_CLOCKWISE:
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_BOTTOM_RIGHT, 0, 0, 50);
          ledHelper.set(LED_TOP_LEFT, 0, 0, 50);
          break;
        case PAJ_COUNT_CLOCKWISE:
          ledHelper.setEye(0, 0, 0);
          ledHelper.set(LED_TOP_RIGHT, 0, 0, 50);
          ledHelper.set(LED_BOTTOM_LEFT, 0, 0, 50);
          break;
        case PAJ_WAVE: // Doesn't work
          ledHelper.setAll(0, 0, 50);
          ledHelper.setEye(0, 0, 0);
          break;
        default: break;
      }
      
      Gesture_Data=0;
    }
    #endif

  
  if (touch_start == NULL && digitalRead(BUTTON_PIN) == HIGH) touch_start = millis();
//  Serial.println(digitalRead(BUTTON_PIN));
  if (ignore_motion == 0) {
    if (digitalRead(MOTION_PIN) == HIGH) {
//      Serial.println("Movement");
      last_movement = millis();
    }
  }
  else ignore_motion--;

  double sound = 0.0;
  ledHelper.breathe();
  switch (mode) {
    case MODE_KNOCKBACK:
      knockback.play();
      break;
    case MODE_SECURITY:
      //      Serial.println(last_movement);
//            Serial.print(last_movement);
//            Serial.print(",");
//            Serial.println(ignore_motion);
      if (last_movement == 0 || last_movement <= millis() - 3000) {
        ledHelper.setEye(0, 0, 0);
        if (last_movement != 0 && ignore_motion == 0) {
          ignore_motion = 500;
          last_movement = 0;
        }
      }
      else ledHelper.setEye(255, 255, 255);
      break;
    case MODE_LISTEN:
      if (ENABLE_SLEEP && last_movement <= millis_minus_timeout()) {
        // I'm asleep becauase i haven't felt you move for SLEEP_TIMEOUT milliseconds
        ledHelper.setEye(0, 0, 0);
      }
      else {
        // I'm awake and listening to noises
        sound = listener.sample_sound();
//        Serial.println(sound);
        ledHelper.look();
        show_mode(sound); // Flash mode LED instead of eye
      }
      break;
     default:
      break;
  }
  
  FastLED.show();
}

int millis_minus_timeout() {
  if (millis() < SLEEP_TIMEOUT) return 0;
  return millis() - SLEEP_TIMEOUT;
}
