#include <stdlib.h>

#include <cstring>

#include "pico/multicore.h"
#include "pico/stdlib.h"

// Define GPIO pins for rows and columns
const uint ROW_PINS[4] = {12, 13, 14, 15};
const uint COL_PINS[6] = {17, 18, 19, 20, 21, 22};

#define ROWS 4
#define COLS 6

// LED state matrix
uint8_t led_states[ROWS][COLS] = {0};

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

  // Display the current state
  for (int row = 0; row < ROWS; row++) {
    // Set row active
    gpio_put(ROW_PINS[row], 1);

    // Set column states for this row
    for (int col = 0; col < COLS; col++) {
      // LED on = column LOW, LED off = column HIGH
      gpio_put(COL_PINS[col], led_states[row][col] ? 0 : 1);
    }

    // Small delay for this row to be visible
    sleep_us(100);

    // Deactivate row
    gpio_put(ROW_PINS[row], 0);
  }
}

// Function to set a specific LED state
void set_led(int row, int col, bool state) {
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
    led_states[row][col] = state ? 1 : 0;
  }
}

// Function to set the entire matrix state
void set_matrix_state(const uint8_t new_state[ROWS][COLS]) {
  memcpy(led_states, new_state, sizeof(led_states));
}

void random_state(float density) {
  // clamp
  if (density > 1.0f)
    density = 1.0f;
  if (density < 0.0f)
    density = 0.0f;

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      float r = (float)rand() / (float)RAND_MAX;
      led_states[row][col] = (r < density) ? 1 : 0;
    }
  }
}

const uint8_t ALL_ON[ROWS][COLS] = {{1, 1, 1, 1, 1, 1},
                                    {1, 1, 1, 1, 1, 1},
                                    {1, 1, 1, 1, 1, 1},
                                    {1, 1, 1, 1, 1, 1}};

const uint8_t ALL_OFF[ROWS][COLS] = {{0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 0}};

void core1_main() {
  while (true) {
    update_led_display(1000);
  }
}

int main() {
  stdio_init_all();
  setup_pins();

  multicore_launch_core1(core1_main);

  while (true) {
    random_state(0.5);  // Turn random LEDs ON
    // set_matrix_state(ALL_ON);
    sleep_ms(200);
    // set_matrix_state(ALL_OFF);
    // sleep_ms(500);
  }
}
