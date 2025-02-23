//==========================================
// Title:   SmoothBus.ino
// Author:  Pegor Karoglanian
// Date:    2/22/25
// Notes:   Code for SmoothBus fuel gauge conversion for VW Bus.
// Version: 2.0
//==========================================

#include <Arduino.h>
#include <Servo.h>

#define CLASSIC_LINE_8115800400_SENDER 1

#define SERVO_PIN             0 // (PB0)
#define LOW_FUEL_LED          1 // (PB1)(D1)
#define SENDER_PIN            1 // analog pin (PB2)(A1)
#define WDT_PIN               3 // watchdog time reset pin (PB3)(D3)
#define WDT_PW_US             2 // STWD100YNYWY3F asks at least 1us pulse width.
#define WINDOW_SIZE           70 // window for moving average.
#define READ_DELAY_MS         200 // fuel read frequency
#define SERVO_STEP_DELAY_MS   15 // delay between steps in servo moves for smoother motion
#define INPUT_RESISTANCE      4 // resistance difference measured at sender and dash.
#define R1                    50 // resistor for voltage divider
#define VIN                   5
#define VREF                  5

#if CLASSIC_LINE_8115800400_SENDER
// these resistance values were found by testing my sender
// using a bucket with markings at the corresponding fuel 
// level heights (35mm = R, 75mm = 1/4 tank, 130mm = 1/2 tank, 200mm = Full)
  #define IN_FULL     11
  #define IN_HALF     37
  #define IN_QUARTER  58
  #define IN_R        77
  #define IN_EMPTY    89
#else
// these resistance values are based on info from here:
// https://www.thesamba.com/vw/forum/viewtopic.php?t=693930
  #define IN_FULL     10
  #define IN_HALF     21
  #define IN_QUARTER  33
  #define IN_R        45
  #define IN_EMPTY    79
#endif

// servo position values that matched my setup
#define OUT_FULL      28
#define OUT_HALF      53
#define OUT_QUARTER   74
#define OUT_R         88
#define OUT_EMPTY     102

class SmoothBus {
  private:
    Servo servo;
    int servo_pin;
    int sender_pin;
    int low_fuel_indicator_pin;
    int wdt_pin;
    int raw = 0;

    int servo_pos = OUT_EMPTY;
    int sender_pos = 0;
    int index = 0;
    bool filled = false;
    float avg_arr[WINDOW_SIZE];
    float total = 0;
  
  public:
    SmoothBus(int servo_pin, int sender_pin, int low_fuel_indicator_pin, int wdt_pin) {
      this->servo_pin = servo_pin;
      this->sender_pin = sender_pin;
      this->low_fuel_indicator_pin = low_fuel_indicator_pin;
      this->wdt_pin = wdt_pin;

      init();
    }

    void init() {
      clearWdt();
      pinMode(this->low_fuel_indicator_pin, OUTPUT);
      pinMode(this->wdt_pin, OUTPUT);
      servo.attach(this->servo_pin);
      // only do boot sequence on power up NOT on resets. (WDT)
      if(bit_is_set(MCUSR, PORF)) {
        MCUSR = 0;
        servoBootSequence();
      }
    }

    // sliding boot sequence going from E to Full and back.
    void servoBootSequence() {
      clearWdt();
      servo.write(OUT_EMPTY);
      delay(500);
      clearWdt();
      delay(500);
      clearWdt();
      for (int pos = OUT_EMPTY; pos >= OUT_FULL; pos -= 1) {
        servo.write(pos);
        delay(13);
        clearWdt();
      }
      delay(500);
      for (int pos = OUT_FULL; pos <= OUT_EMPTY; pos += 1) {
        servo.write(pos);
        delay(13);
        clearWdt();
      }
      delay(750);
      clearWdt();
    }

    void readFuelSender() {
      this->raw = analogRead(this->sender_pin);
  
      if (this->raw) {
        float v_out = (this->raw/1023.0) * VREF;
        float fuel_sender = R1 * (v_out/(VIN - v_out));
        fuel_sender -= INPUT_RESISTANCE;

        if (fuel_sender < IN_FULL) {
          fuel_sender = IN_FULL;
        } else if (fuel_sender > IN_EMPTY) {
          fuel_sender = IN_EMPTY;
        }

        int current_avg = round(runningAverage(fuel_sender));

        if (current_avg >= IN_FULL && current_avg <= IN_HALF) { // 1/2 to FULL
          this->sender_pos = mapSenderPos(current_avg, OUT_FULL, OUT_HALF, IN_FULL, IN_HALF);
        } else if (current_avg > (IN_HALF) && current_avg <= IN_QUARTER) { //  1/4 to 1/2
          this->sender_pos = mapSenderPos(current_avg, OUT_HALF, OUT_QUARTER, IN_HALF, IN_QUARTER);
        } else if (current_avg > (IN_QUARTER) && current_avg <= IN_R) { // R to 1/4
          this->sender_pos = mapSenderPos(current_avg, OUT_QUARTER, OUT_R, IN_QUARTER, IN_R);
        } else { // E to R
          this->sender_pos = mapSenderPos(current_avg, OUT_R, OUT_EMPTY, IN_R, IN_EMPTY);
        }
      }
    }

    // map to ranges based on fuel sender calibration data from above forum.
    int mapSenderPos(int current_avg, int out_min, int out_max, int in_min, int in_max) {
       return out_min + (out_max - out_min) * (current_avg - in_min) / (in_max - in_min);
    }

    void updateServoPos() {
      // go in steps instead of shoot to position
      if (this->sender_pos > this->servo_pos) {
        servo.write(this->servo_pos++);
      } else if (this->sender_pos < this->servo_pos) {
        servo.write(this->servo_pos--);
      }

      if (this->servo_pos >= OUT_R ) {
        digitalWrite(this->low_fuel_indicator_pin, HIGH);
      } else if (this->servo_pos < OUT_R) {
        digitalWrite(this->low_fuel_indicator_pin, LOW);
      }
    }

    float runningAverage(float resistance) {
      if (this->filled) {
          this->total -= this->avg_arr[this->index];
      }

      this->avg_arr[this->index] = resistance;
      this->total += resistance;
      this->index = (this->index + 1) % WINDOW_SIZE;

      if (this->index == 0) {
          this->filled = true;
      }

      float running_average = this->total / (this->filled ? WINDOW_SIZE : this->index);
      return running_average;
    }

    void clearWdt() {
      digitalWrite(this->wdt_pin, HIGH);
      delayMicroseconds(WDT_PW_US);
      digitalWrite(this->wdt_pin, LOW);
    }
};

void setup() {
  analogReference(DEFAULT);
}

void loop() {
  SmoothBus smooth_bus(SERVO_PIN, SENDER_PIN, LOW_FUEL_LED, WDT_PIN);
  unsigned long last_read = millis();
  unsigned long last_servo_update = millis();
  while(1) {
    if ((millis() - last_read) >= READ_DELAY_MS) {
      smooth_bus.readFuelSender();
      last_read = millis();
    }

    if ((millis() - last_servo_update) >= SERVO_STEP_DELAY_MS) {
      smooth_bus.updateServoPos();
      last_servo_update = millis();
    }

    smooth_bus.clearWdt();
  }
}
