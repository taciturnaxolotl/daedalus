#include <stdlib.h>

#include <cstring>
#include <stdio.h>

#include "pico/multicore.h"
#include "pico/stdlib.h"
#include <time.h>

// Define GPIO pins for rows and columns
#define ROWS 4
#define COLS 6

const uint ROW_PINS[4] = {12, 13, 14, 15};
const uint COL_PINS[6] = {17, 18, 19, 20, 21, 22};

// LED state matrix
uint8_t led_states[ROWS][COLS] = {0};

// brightness control
uint8_t brightness = 100;

// timing vars
bool fading = false;
absolute_time_t last_char_time;
absolute_time_t fade_start_time;
const uint32_t inactivity_timeout_ms = 0;
const uint32_t fade_duration_ms = 1200;

void randomize_matrix() {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      led_states[row][col] = rand() % 2;
    }
  }
}

// Function to update the display at variable frequencies
void update_led_display(uint32_t refresh_rate_hz) {
  static uint32_t last_update = 0;
  uint32_t current_time = to_ms_since_boot(get_absolute_time());
  uint32_t update_interval = 1000 / refresh_rate_hz;

  // Only update at the specified frequency
  if (current_time - last_update < update_interval) {
    return;
  }

  last_update = current_time;

  uint32_t time_since_last_char = absolute_time_diff_us(last_char_time, get_absolute_time()) / 1000;

  if (!fading && time_since_last_char > inactivity_timeout_ms) {
    // start fading
    fading = true;
    fade_start_time = get_absolute_time();
  }

  if (fading) {
    uint32_t fade_elapsed_ms = absolute_time_diff_us(fade_start_time, get_absolute_time()) / 1000;

    if (fade_elapsed_ms >= fade_duration_ms) {
      brightness = 0;
    } else {
      brightness = 100 - ((fade_elapsed_ms * 100) / fade_duration_ms);
    }
  }

  // Skip display update if brightness is 0
  if (brightness == 0) {
    // Turn off all rows and set all columns high to ensure LEDs are off
    for (int i = 0; i < ROWS; i++) {
      gpio_put(ROW_PINS[i], 0);
    }
    for (int j = 0; j < COLS; j++) {
      gpio_put(COL_PINS[j], 1);
    }

    return;
  }

  // Software PWM cycle
  for (uint8_t pwm_cycle = 0; pwm_cycle < brightness; pwm_cycle++) {
    // For each row
    for (int row = 0; row < ROWS; row++) {
      // Activate row
      gpio_put(ROW_PINS[row], 1);

      // Set column states for this row
      for (int col = 0; col < COLS; col++) {
        gpio_put(COL_PINS[col], led_states[row][col] ? 0 : 1);
      }

      // Keep row active for a short time
      sleep_us(50);

      // Deactivate row
      gpio_put(ROW_PINS[row], 0);
    }
  }
}
void setup_pins() {
  // Set up row pins
  for (int i = 0; i < ROWS; i++) {
    gpio_init(ROW_PINS[i]);
    gpio_set_dir(ROW_PINS[i], GPIO_OUT);
    gpio_put(ROW_PINS[i], 0);  // Start with LEDs off
  }

  // Set up column pins
  for (int j = 0; j < COLS; j++) {
    gpio_init(COL_PINS[j]);
    gpio_set_dir(COL_PINS[j], GPIO_OUT);
    gpio_put(COL_PINS[j], 1);  // Start with LEDs off
  }
}

void core1_main() {
  while (true) {
    update_led_display(1000);  // Update at 60Hz for smoother display
    sleep_ms(1);  // Small delay to prevent tight loop
  }
}

int main() {
  stdio_init_all();
  setup_pins();

  // seed the random number generator
  srand(time_us_32());

  last_char_time = get_absolute_time();

  multicore_launch_core1(core1_main);

  while (true) {
    // check if there are characters available from the input
    int c = getchar_timeout_us(0);

    if (c != PICO_ERROR_TIMEOUT) {
      // echo char back
      printf("%c", c);

      last_char_time = get_absolute_time();

      fading = false;
      brightness = 100;

      randomize_matrix();

      while (getchar_timeout_us(0) != PICO_ERROR_TIMEOUT) {}
    }

    sleep_ms(10);
  }
}
