
/*
 * BIBLIOGRAFIA
 * 
 * Las paginas utilizadas para conocer el manejo de la pantlla TFT fueron las siguientes:
 * 
 * https://www.rinconingenieril.es/guia-uso-tft-arduino/
 * 
 * https://www.elecrow.com/wiki/index.php?title=1.44%27%27_128x_128_TFT_LCD_with_SPI_Interface
 */

/*
 * LIBRARIES
 */

#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h> 

/*
 * PINES
 */

#define BUTTON 2
#define SENSOR_MOV_1 5
#define SENSOR_MOV_2 7
#define DIMMER 6
#define LDR A0

/*
 * DEFINES
 */

#define ANTI_BOUNCE 40
#define ZERO 0
#define DIMMED 10
#define FULL 255

/*
 * TFT SCREEN
 */

#define __DC 9
#define __CS 10
// MOSI --> (SDA) --> D11
#define __RST 12
// SCLK --> (SCK) --> D13

TFT_ILI9163C screen = TFT_ILI9163C(__CS, __DC, __RST);

/*
 * COLOR DEFINITIONS
 */
 
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

/*
 * MILLIS()
 */

uint32_t current_time = 0;

/*
 * FUNCTIONS
 */

void fsm_init (void);
void fsm_update (void);
void buttonPressed (void);
void system_init (void);
void LDR_read (int);
void system_off (void);
void system_on (bool, bool, int);
void system_always_on (bool, bool, int);
void screen_update (void);
void screen_update_interface (void);
void screen_update_mode_off (void);
void screen_update_mode_on (void);
void screen_update_mode_always_on (void);
void screen_update_motion_body (char);

/*
 * FSM
 */
 
typedef enum
{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
}fsm;

/*
 * LIGHT SYSTEM
 */

typedef enum
{
  off,
  on,
  always_on,  
}light_system;

/*
 * MOTION SENSOR
 */

typedef enum
{
  nothing,
  something,
}sensor;

/*
 * DAY/NIGHT
 */

typedef enum
{
  day,
  night,
}state;

fsm fsm_state;
light_system mode;
sensor motion;
state current_state;

void setup()
{
  pinMode(BUTTON, INPUT);
  pinMode(SENSOR_MOV_1, INPUT);
  pinMode(SENSOR_MOV_2, INPUT);
  pinMode(DIMMER, OUTPUT);
  Serial.begin(9600);
  screen.begin();
  current_time = millis();
  system_init();
  fsm_init();
}

void loop()
{
  int LDR_output = analogRead(LDR);
  bool MOV_output_1 = digitalRead(SENSOR_MOV_1);
  bool MOV_output_2 = digitalRead(SENSOR_MOV_2);
  fsm_update();
  if (mode == off) system_off();
  if (mode == on) system_on(MOV_output_1, MOV_output_2, LDR_output);
  if (mode == always_on) system_always_on();
}

void system_init (void)
{
  mode == off;
  screen_update();
}

void fsm_init(void)
{
  fsm_state = BUTTON_UP;
}

void fsm_update()
{
  switch (fsm_state)
  {
    case BUTTON_UP:
      current_time = millis();
      if (digitalRead(BUTTON) == HIGH) fsm_state = BUTTON_FALLING;
      break;
    case BUTTON_FALLING:
      if (millis() - current_time > ANTI_BOUNCE)
      {
        current_time = millis();
        if (digitalRead(BUTTON) == HIGH)
        {
          fsm_state = BUTTON_DOWN;
          buttonPressed();
        }
        else fsm_state = BUTTON_UP;  
      }
      break;
    case BUTTON_DOWN:
      current_time = millis();
      if (digitalRead(BUTTON) == LOW) fsm_state = BUTTON_RAISING;
      break;
    case BUTTON_RAISING:
      if (millis() - current_time > ANTI_BOUNCE)
      {
        current_time = millis();
        if (digitalRead(BUTTON) == LOW)
        {
          fsm_state = BUTTON_UP;
        }
        else fsm_state = BUTTON_DOWN;
      }
      break;
  }
}

void buttonPressed()
{
  switch (mode)
  {
    case off:
      mode = on;
      screen_update();
      break;
    case on:
      mode = always_on;
      screen_update();
      break;
    case always_on:
      mode = off;
      screen_update();
      break;
  }
}

void system_off (void)
{
  analogWrite(DIMMER, 0);
}

void system_on (bool x, bool y, int z)
{
  static bool blocker_day = false;
  static bool blocker_night = false;
  static bool blocker_motion_x = false;
  static bool blocker_motion_y = false;
  static bool blocker_error = false;
  LDR_read(z);
  if (current_state == day)
  {
    analogWrite(DIMMER, ZERO);
    if (blocker_day == false)
    {
       screen_update();
       blocker_day = true;
       blocker_night = false;
       blocker_error = false;
    }
  }
  else if (current_state == night)
  {
    if (blocker_night == false)
    {
      if (blocker_error == false)
      {
        analogWrite(DIMMER, DIMMED);
        blocker_error = true;
      }
      screen_update();
      blocker_night = true;
      blocker_day = false;
    }
    if (((x == LOW) and (y == LOW)) and (blocker_motion_x == false))
    {
      analogWrite(DIMMER, DIMMED);
      motion = nothing;
      blocker_night = false;
      blocker_motion_x = true;
      blocker_motion_y = false;
    }
    else if (((x == HIGH) or (y == HIGH)) and (blocker_motion_y == false))
    {
      analogWrite(DIMMER, FULL);
      motion = something;
      blocker_night = false;
      blocker_motion_y = true;
      blocker_motion_x = false;
    }
  }
}

void system_always_on (void)
{
  analogWrite(DIMMER, FULL);
}

void LDR_read (int x)
{
  if (x <= 600) current_state = day;
  else current_state = night;
}

void screen_update (void)
{  
  screen_update_interface();
  if (mode == off) screen_update_mode_off();
  if (mode == on) screen_update_mode_on();
  if (mode == always_on) screen_update_mode_always_on();
}

void screen_update_interface (void)
{
  screen.setTextSize(1);
  screen.setCursor(6, 0); 
  screen.print("====================");
  screen.setCursor(9, 6); 
  screen.setTextColor(CYAN);
  screen.print("   CONTROL PANEL   ");
  screen.setTextColor(WHITE);
  screen.setCursor(6, 12); 
  screen.print("====================");
  screen.setCursor(6, 20); 
  screen.print("------- MODE -------");
  screen.setCursor(6, 40);
  screen.print("====================");
  screen.setCursor(6, 48); 
  screen.print("---- CONDITIONS ----");
  screen.setCursor(8, 83);
  screen.print("- - - - - - - - - - ");
}

void screen_update_mode_off (void)
{
  screen.setCursor(6, 30); 
  screen.setTextColor(RED);
  screen.print("OFF");
  screen.setTextColor(WHITE);
  screen.setCursor(40, 30); 
  screen.print("ON");
  screen.setCursor(71, 30); 
  screen.print("ALWAYS ON");
  screen.fillCircle(25, 70, 10, BLACK);
  screen.setCursor(21, 64);
  screen.setTextColor(WHITE);
  screen.setTextSize(2);
  screen.print("?");
  screen.setCursor(55, 66);
  screen.setTextSize(1);
  screen.print("DAY");
  screen.print("/");
  screen.print("NIGHT");
  screen.setTextColor(WHITE);
  screen.setCursor(55, 105);
  screen.print("MOVEMENT");
  screen_update_motion_body ('W');
}

void screen_update_mode_on (void)
{
  screen.setCursor(6, 30); 
  screen.print("OFF");
  screen.setCursor(40, 30); 
  screen.setTextColor(GREEN);
  screen.print("ON");
  screen.setTextColor(WHITE);
  screen.setCursor(71, 30); 
  screen.print("ALWAYS ON");
  if (current_state == day)
  {
    screen.fillCircle(25, 70, 10, YELLOW);
    screen.setCursor(55, 66);
    screen.setTextColor(GREEN);
    screen.print("DAY");
    screen.setTextColor(WHITE);
    screen.print("/");
    screen.setTextColor(RED);
    screen.print("NIGHT");
    screen.setTextColor(WHITE);
    screen.setCursor(55, 105);
    screen.print("MOVEMENT");
    screen_update_motion_body ('W');
  }
  if (current_state == night)
  {
    screen.fillCircle(25, 70, 10, WHITE);
    screen.setCursor(55, 66);
    screen.setTextColor(RED);
    screen.print("DAY");
    screen.setTextColor(WHITE);
    screen.print("/");
    screen.setTextColor(GREEN);
    screen.print("NIGHT");
    screen.setTextColor(WHITE);
    if (motion == nothing)
    {
      screen.setCursor(55, 105);
      screen.setTextColor(RED);
      screen.print("MOVEMENT");
      screen.setTextColor(WHITE);
      screen_update_motion_body ('R');
    }
    if (motion == something)
    {
      screen.setCursor(55, 105);
      screen.setTextColor(GREEN);
      screen.print("MOVEMENT");
      screen.setTextColor(WHITE);
      screen_update_motion_body ('G');
    }
  }
}

void screen_update_mode_always_on (void)
{
  screen.setCursor(6, 30); 
  screen.print("OFF");
  screen.setCursor(40, 30); 
  screen.print("ON");
  screen.setCursor(71, 30); 
  screen.setTextColor(BLUE);
  screen.print("ALWAYS ON");
  screen.setTextColor(WHITE);
  screen.fillCircle(25, 70, 10, BLACK);
  screen.setCursor(21, 64);
  screen.setTextColor(WHITE);
  screen.setTextSize(2);
  screen.print("?");
  screen.setCursor(55, 66);
  screen.setTextSize(1);
  screen.print("DAY");
  screen.print("/");
  screen.print("NIGHT");
  screen.setCursor(55, 105);
  screen.setTextColor(WHITE);
  screen.print("MOVEMENT");
  screen_update_motion_body ('W');
}

void screen_update_motion_body (char carac)
{
  switch (carac)
  {
    case 'W':
      screen.fillCircle(25, 95, 4, WHITE);
      screen.fillRect(22, 102, 6, 13, WHITE);   // torso izq
      screen.fillRect(23, 102, 6, 13, WHITE);   // torso der
      screen.fillRect(18, 102, 3, 9, WHITE);    // brazo izq
      screen.fillRect(30, 102, 3, 9, WHITE);    // brazo der
      screen.fillRect(22, 116, 3, 13, WHITE);   // pierna izq
      screen.fillRect(26, 116, 3, 13, WHITE);   // pierna der 
      break;
    case 'G':
      screen.fillCircle(25, 95, 4, GREEN);
      screen.fillRect(22, 102, 6, 13, GREEN);   // torso izq
      screen.fillRect(23, 102, 6, 13, GREEN);   // torso der
      screen.fillRect(18, 102, 3, 9, GREEN);    // brazo izq
      screen.fillRect(30, 102, 3, 9, GREEN);    // brazo der
      screen.fillRect(22, 116, 3, 13, GREEN);   // pierna izq
      screen.fillRect(26, 116, 3, 13, GREEN);   // pierna der
      break;
    case 'R':
      screen.fillCircle(25, 95, 4, RED);
      screen.fillRect(22, 102, 6, 13, RED);   // torso izq
      screen.fillRect(23, 102, 6, 13, RED);   // torso der
      screen.fillRect(18, 102, 3, 9, RED);    // brazo izq
      screen.fillRect(30, 102, 3, 9, RED);    // brazo der
      screen.fillRect(22, 116, 3, 13, RED);   // pierna izq
      screen.fillRect(26, 116, 3, 13, RED);   // pierna der
      break;       
  }
}
