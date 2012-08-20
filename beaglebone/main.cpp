#include "BeagleBone.h"
#include "Colors.h"
#include "CometVisualizer.h"
#include "DebugVisualizer.h"
#include "LogicalLightStrip.h"
#include "PhysicalLightStrip.h"
#include "MasterVisualizer.h"
#include "SimpleParticleVisualizer.h"
#include "SimpleVisualizer.h"
#include "PhysicalPiano.h"
#include "Util.h"

#include <stdio.h>
#include <unistd.h>

static int num_pins = 1000;
static SPI spi(4e6);
static PhysicalLightStrip strip(spi, num_pins);

static void showRainbow() {
  int offset = 0;

  uint32_t last_time = Util::millis();

  int x = 0;

  int counter = 0;

  while(true) {
    for (int i = 0; i < num_pins; ++i) {
      strip.setPixel(i, Colors::rainbow((i + offset) % 360));
    }

    strip.show();

//    Util::delay(10);

    if ((++counter % 30) == 0) {
      uint32_t millis = Util::millis();
      printf("frame %d fps\n", 30000 / (millis - last_time));
      last_time = millis;
    }

    ++offset;
    x = (x + 1) % 10;

  }
}

static void backAndForth() {
  int pos = 0;
  int direction = 1;
  while(true) {
    strip.setPixel(pos, 0);
    pos += direction;
    if (pos < 0 || pos >= num_pins) {
      direction *= -1;
      pos += 2 * direction;
    }
    strip.setPixel(pos, 0x7f7f7f);
    strip.show();
  }
}

static void christmas() {
  while(1) {
    for (int i = 0; i < num_pins; ++i) {
      if ((i / 10) % 2 == 0) {
        strip.setPixel(i, Colors::rgb(127, 0, 0));
      } else {
        strip.setPixel(i, Colors::rgb(0, 127, 0));
      }
    }
    strip.show();
    Util::delay(100);
  }
}

static void ranges() {
  while(true) {
    for (int i = 0; i < num_pins; ++i) {
      Color c;
      if (i < 80) {
        // back half of top
        c = Colors::rgb(127, 0, 0);
      } else if (i < 92) {
        // front right half of top
        c = Colors::rgb(127, 0, 0);
      } else if (i < 136) {
        // front of top row
        c = Colors::rgb(0, 127, 0);
      } else if (i < 148) {
        // front half of top
        c = Colors::rgb(127, 0, 0);
      } else if (i < 163) {
        // front left 2nd row from top
        c = Colors::rgb(0, 0, 127);
      } else if (i < 204) {
        // directly above keys
        c = Colors::rgb(127, 127, 127);
      } else if (i < 219) {
        // front right 2nd row from top
        c = Colors::rgb(127, 127, 0);
      } else if (i < 298) {
        // back 2nd row from top
        c = Colors::rgb(127, 0, 127);
      } else if (i < 320) {
        // right 2nd row from bottom
        c = Colors::rgb(0, 127, 127);
      } else if (i < 364) {
        // front 2nd row from bottom
        c = Colors::rgb(127, 0, 0);
      } else if (i < 458) {
        // back 2nd row from bottom
        c = Colors::rgb(0, 127, 0);
      } else if (i < 478) {
        // front left bottom row
        c = Colors::rgb(0, 0, 127);
      } else if (i < 522) {
        // front bottom row
        c = Colors::rgb(127, 0, 127);
      } else if (i < 542) {
        // front right bottom row
        c = Colors::rgb(0, 127, 127);
      } else if (i < 560) {
        // up the back of the right leg
        c = Colors::rgb(127, 127, 127);
      } else if (i < 578) {
        // down the front of the right leg
        c = Colors::rgb(127, 0, 0);
      } else {
        c = Colors::rgb(0, 0, 0);
      }
      strip.setPixel(i, c);
    }
    strip.show();
    Util::delay(100);
  }
}

static void glow() {
  int brightness = 0;
  int direction = 1;
  while(true) {
    brightness += direction;
    if (brightness < 1 || brightness > 127) {
      direction *= -1;
      brightness += 2 * direction;
    }

    Color color = Colors::hsv(0, 0.0, brightness / 127.0);
    for(int i = 0; i < num_pins; ++i) {
      strip.setPixel(i, color);
    }
    strip.show();

//    Util::delay(10);
  }
}

static void blinkForever(Pin& pin) {
  pin.setPinMode(OUTPUT);
  while(true) {
    printf("pin ON\n");
    pin.digitalWrite(ON);
    sleep(1);
    printf("pin OFF\n");
    pin.digitalWrite(OFF);
    sleep(1);
  }
}

static void readTest(Pin& out_pin, Pin& in_pin) {
  out_pin.setPinMode(OUTPUT);
  out_pin.digitalWrite(ON);
  in_pin.setPinMode(INPUT);
  bool prev_value = false;
  int counter = 0;
  bool out_pin_value = true;
  while(true) {
    bool value = in_pin.digitalRead();
    if (value != prev_value) {
      Util::log("new value: %d", value);
      prev_value = value;
    }
    if(++counter % 1000 == 0) {
      fprintf(stderr, ".");
//      out_pin_value ^= true;
//      out_pin.digitalWrite(out_pin_value);
    }
  }
}

static Visualizer* makeDebugVisualizer() {
  return new DebugVisualizer();
}

static Visualizer* makeSimpleParticleVisualizer() {
  return new SimpleParticleVisualizer(strip, 300);
}

static Visualizer* makeCometVisualizer() {
  return new CometVisualizer(strip, 300);
}

static void piano() {
  MasterVisualizer master_viz;

  // add visualizers
  LogicalLightStrip* above_keyboard = LogicalLightStrip::fromRange(strip, 163, 203);
  Visualizer* simple_viz = new SimpleVisualizer(*above_keyboard);

  master_viz.addVisualizer(simple_viz);
//  master_viz.addVisualizer(makeSimpleParticleVisualizer);
//  master_viz.addVisualizer(makeCometVisualizer);
//  master_viz.addVisualizer(makeDebugVisualizer);

  PhysicalPiano piano(&master_viz);
  while(true) {
    piano.scan();
    strip.show();
  }
}

int main(int argc, char** argv) {
  strip.reset();
  strip.show();
  strip.show();

//  blinkForever(Pin::P8_4);
  showRainbow();
//  backAndForth();
//  glow();

//  readTest(Pin::pin(8, 7), Pin::pin(8, 22));
//  piano();
//  ranges();
// getc(stdin);
//  christmas();
}
