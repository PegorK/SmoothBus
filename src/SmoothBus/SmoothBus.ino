//==========================================
// Title:  SmoothBus.ino
// Author: Pegor Karoglanian
// Date:   11/1/24
// Notes:  Code for SmoothBus fuel gauge conversion for VW Bus.
//==========================================

#include <ATTinyCore.h>
#include <Arduino.h>
#include <Servo.h>

#ifdef DEBUG
  #define SERVO_PIN 9
  #define LOW_FUEL_LED 2
#else
  #define SERVO_PIN 0
  #define LOW_FUEL_LED 1
#endif

#define WINDOW_SIZE 35 // window for moving average
#define SENDER_PIN 1 // analog pin
#define R1 101 // resistor for voltage divider
#define VIN 5
#define VREF 5
#define SERVO_STEP_DELAY 15 // delay between steps in servo moves for smoother motion
#define READ_DELAY_MS 200 // fuel read frequency
#define MIN_RAW 10 // fuel sender tabs should be bent so that at FULL its 10 ohms
#define MAX_RAW 79 // fuel sender tabs should be bent so that at EMPTY its 79 ohms

class SmoothBus {
  private:
    Servo servo;
    int servo_pin;
    int sender_pin;
    int low_fuel_indicator_pin;

    int raw = 0;
    // resistance values based on info from here:
    // https://www.thesamba.com/vw/forum/viewtopic.php?t=693930
    int in_full = 10;
    int in_half = 21;
    int in_quarter = 33;
    int in_r = 45;
    int in_empty = 79;

    // servo values that matched my setup
    int out_full = 28;
    int out_half = 53;
    int out_quarter = 71;
    int out_r = 81;
    int out_empty = 98;


    int servo_pos = out_empty;
    int index = 0;
    bool filled = false;
    float avg_arr[WINDOW_SIZE];
    float total = 0;
  
  public:
    SmoothBus(int servo_pin, int sender_pin, int low_fuel_indicator_pin) {
      this->servo_pin = servo_pin;
      this->sender_pin = sender_pin;
      this->low_fuel_indicator_pin = low_fuel_indicator_pin;

      init();
    }

    void init() {
      pinMode(this->low_fuel_indicator_pin, OUTPUT);
      servo.attach(this->servo_pin);
      servoBootSequence();
    }

    void servoBootSequence() {
      servo.write(this->out_empty);
      delay(1000);
      for (int pos = this->out_empty; pos >= this->out_full; pos -= 1) { // goes from out_empty degrees to out_full degrees
        servo.write(pos);
        delay(13);
      }
      delay(500);
      for (int pos = this->out_full; pos <= this->out_empty; pos += 1) { // goes from out_full degrees to out_empty degrees
        servo.write(pos);
        delay(13);
      }
      delay(750);
    }

    void readFuelSender() {
      this->raw = analogRead(this->sender_pin);
#ifdef DEBUG
  Serial.print("Analog read: ");
  Serial.println(this->raw);
#endif
      if(this->raw) {
        float Vout = (raw/1023.0) * VREF;
        float fuel_sender = R1 * (Vout/(VIN - Vout));
        if (fuel_sender < MIN_RAW) {
          fuel_sender = MIN_RAW;
        } else if (fuel_sender > MAX_RAW) {
          fuel_sender = MAX_RAW;
        }
        // possible TODO - drop values that are a certain percentage over the last
        // but keep track of back to back repetition for scenarios like filling up tank
        int current_avg = round(runningAverage(fuel_sender));
#ifdef DEBUG
  Serial.print("Current Avg: ");
  Serial.println(current_avg);
#endif

        // map to ranges based on fuel sender calibration data from above forum.
        int sender_pos = 0;
        int out_min = 0;
        int out_max = 0;
        int in_min = 0;
        int in_max = 0;

        digitalWrite(this->low_fuel_indicator_pin, LOW);
        if (current_avg >= this->in_full && current_avg <= this->in_half) { // 1/2 to FULL
          out_min = this->out_full;
          out_max = this->out_half;
          in_min = this->in_full;
          in_max = this->in_half;
#ifdef DEBUG
  Serial.println("1/2 to FULL");
#endif
        } else if (current_avg >= (this->in_half-1) && current_avg <= this->in_quarter) { //  1/4 to 1/2
          out_min = this->out_half;
          out_max = this->out_quarter;
          in_min = this->in_half;
          in_max = this->in_quarter;
#ifdef DEBUG
  Serial.println("1/4 to 1/2");
#endif
        } else if (current_avg >= (this->in_quarter-1) && current_avg <= this->in_r) { // R to 1/4
          out_min = this->out_quarter;
          out_max = this->out_r;
          in_min = this->in_quarter;
          in_max = this->in_r;
#ifdef DEBUG
  Serial.println("R to 1/4");
#endif
        } else { // E to R
          out_min = this->out_r;
          out_max = this->out_empty;
          in_min = this->in_r;
          in_max = this->in_empty;
          digitalWrite(this->low_fuel_indicator_pin, HIGH);
#ifdef DEBUG
  Serial.println("E to R");
#endif
        }

        sender_pos = out_min + (out_max - out_min) * (current_avg - in_min) / (in_max - in_min);
        if (sender_pos != this->servo_pos) {
          setServoPos(sender_pos);
        }
      }
    }

    void setServoPos(int pos) {
      // go in steps instead of shoot to position
      while (this->servo_pos != pos) {
        if (pos > this->servo_pos) {
          servo.write(this->servo_pos++);
        } else if (pos < this->servo_pos) {
          servo.write(this->servo_pos--);
        }
        delay(SERVO_STEP_DELAY);
      }
    }

    float runningAverage(float resistance) {
      if (this->filled) {
          this->total -= this->avg_arr[this->index];
      }

      // Replace the oldest value with the new value
      this->avg_arr[this->index] = resistance;
      this->total += resistance;  // Add the new value to the total

      // Move the index for the next new value
      this->index = (this->index + 1) % WINDOW_SIZE;

      // Check if the window has been filled at least once
      if (this->index == 0) {
          this->filled = true;
      }

      // Calculate and return the average
      float running_average = this->total / (this->filled ? WINDOW_SIZE : this->index);
      return running_average;
    }
};



void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void loop() {
  SmoothBus smooth_bus(SERVO_PIN, SENDER_PIN, LOW_FUEL_LED);
  while(1) {
    smooth_bus.readFuelSender();
    delay(READ_DELAY_MS);
  }
}
