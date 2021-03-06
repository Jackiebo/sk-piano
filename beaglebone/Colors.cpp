#include "Colors.h"
#include <math.h>

const Color Colors::BLACK = 0;
const Color Colors::WHITE = 0x7f7f7f;

Color Colors::hsv(float h, float s, float v) {
  float r, g, b;
  if( s == 0 ) {
    // achromatic (grey)
    r = g = b = v;
  } else {
    h /= 60;                      // sector 0 to 5
    int i = floor(h);
    float f = h - i;                      // factorial part of h
    float p = v * (1 - s);
    float q = v * (1 - s * f);
    float t = v * (1 - s * (1 - f));
    switch(i) {
      case 0:
        r = v;
        g = t;
        b = p;
        break;
      case 1:
        r = q;
        g = v;
        b = p;
        break;
      case 2:
        r = p;
        g = v;
        b = t;
        break;
      case 3:
        r = p;
        g = q;
        b = v;
        break;
      case 4:
        r = t;
        g = p;
        b = v;
        break;
      default:                // case 5:
        r = v;
        g = p;
        b = q;
        break;
    }
  }
  return Colors::rgb(r * 127, g * 127, b * 127);
}

// 360 values, hue=index, saturation=1.0, value=1.0
static uint32_t _cached_rainbow[] = { 0x80ff80, 0x82ff80, 0x84ff80, 0x86ff80, 0x88ff80, 0x8aff80, 0x8cff80, 0x8eff80, 0x90ff80, 0x93ff80, 0x95ff80, 0x97ff80, 0x99ff80, 0x9bff80, 0x9dff80, 0x9fff80, 0xa1ff80, 0xa3ff80, 0xa6ff80, 0xa8ff80, 0xaaff80, 0xacff80, 0xaeff80, 0xb0ff80, 0xb2ff80, 0xb4ff80, 0xb7ff80, 0xb9ff80, 0xbbff80, 0xbdff80, 0xbfff80, 0xc1ff80, 0xc3ff80, 0xc5ff80, 0xc7ff80, 0xcaff80, 0xccff80, 0xceff80, 0xd0ff80, 0xd2ff80, 0xd4ff80, 0xd6ff80, 0xd8ff80, 0xdbff80, 0xddff80, 0xdfff80, 0xe1ff80, 0xe3ff80, 0xe5ff80, 0xe7ff80, 0xe9ff80, 0xebff80, 0xeeff80, 0xf0ff80, 0xf2ff80, 0xf4ff80, 0xf6ff80, 0xf8ff80, 0xfaff80, 0xfcff80, 0xffff80, 0xfffc80, 0xfffa80, 0xfff880, 0xfff680, 0xfff480, 0xfff280, 0xfff080, 0xffee80, 0xffeb80, 0xffe980, 0xffe780, 0xffe580, 0xffe380, 0xffe180, 0xffdf80, 0xffdd80, 0xffdb80, 0xffd880, 0xffd680, 0xffd480, 0xffd280, 0xffd080, 0xffce80, 0xffcc80, 0xffca80, 0xffc780, 0xffc580, 0xffc380, 0xffc180, 0xffbf80, 0xffbd80, 0xffbb80, 0xffb980, 0xffb780, 0xffb480, 0xffb280, 0xffb080, 0xffae80, 0xffac80, 0xffaa80, 0xffa880, 0xffa680, 0xffa380, 0xffa180, 0xff9f80, 0xff9d80, 0xff9b80, 0xff9980, 0xff9780, 0xff9580, 0xff9380, 0xff9080, 0xff8e80, 0xff8c80, 0xff8a80, 0xff8880, 0xff8680, 0xff8480, 0xff8280, 0xff8080, 0xff8082, 0xff8084, 0xff8086, 0xff8088, 0xff808a, 0xff808c, 0xff808e, 0xff8090, 0xff8093, 0xff8095, 0xff8097, 0xff8099, 0xff809b, 0xff809d, 0xff809f, 0xff80a1, 0xff80a3, 0xff80a6, 0xff80a8, 0xff80aa, 0xff80ac, 0xff80ae, 0xff80b0, 0xff80b2, 0xff80b4, 0xff80b7, 0xff80b9, 0xff80bb, 0xff80bd, 0xff80bf, 0xff80c1, 0xff80c3, 0xff80c5, 0xff80c7, 0xff80ca, 0xff80cc, 0xff80ce, 0xff80d0, 0xff80d2, 0xff80d4, 0xff80d6, 0xff80d8, 0xff80db, 0xff80dd, 0xff80df, 0xff80e1, 0xff80e3, 0xff80e5, 0xff80e7, 0xff80e9, 0xff80eb, 0xff80ee, 0xff80f0, 0xff80f2, 0xff80f4, 0xff80f6, 0xff80f8, 0xff80fa, 0xff80fc, 0xff80ff, 0xfc80ff, 0xfa80ff, 0xf880ff, 0xf680ff, 0xf480ff, 0xf280ff, 0xf080ff, 0xee80ff, 0xeb80ff, 0xe980ff, 0xe780ff, 0xe580ff, 0xe380ff, 0xe180ff, 0xdf80ff, 0xdd80ff, 0xdb80ff, 0xd880ff, 0xd680ff, 0xd480ff, 0xd280ff, 0xd080ff, 0xce80ff, 0xcc80ff, 0xca80ff, 0xc780ff, 0xc580ff, 0xc380ff, 0xc180ff, 0xbf80ff, 0xbd80ff, 0xbb80ff, 0xb980ff, 0xb780ff, 0xb480ff, 0xb280ff, 0xb080ff, 0xae80ff, 0xac80ff, 0xaa80ff, 0xa880ff, 0xa680ff, 0xa380ff, 0xa180ff, 0x9f80ff, 0x9d80ff, 0x9b80ff, 0x9980ff, 0x9780ff, 0x9580ff, 0x9380ff, 0x9080ff, 0x8e80ff, 0x8c80ff, 0x8a80ff, 0x8880ff, 0x8680ff, 0x8480ff, 0x8280ff, 0x8080ff, 0x8082ff, 0x8084ff, 0x8086ff, 0x8088ff, 0x808aff, 0x808cff, 0x808eff, 0x8090ff, 0x8093ff, 0x8095ff, 0x8097ff, 0x8099ff, 0x809bff, 0x809dff, 0x809fff, 0x80a1ff, 0x80a3ff, 0x80a6ff, 0x80a8ff, 0x80aaff, 0x80acff, 0x80aeff, 0x80b0ff, 0x80b2ff, 0x80b4ff, 0x80b7ff, 0x80b9ff, 0x80bbff, 0x80bdff, 0x80bfff, 0x80c1ff, 0x80c3ff, 0x80c5ff, 0x80c7ff, 0x80caff, 0x80ccff, 0x80ceff, 0x80d0ff, 0x80d2ff, 0x80d4ff, 0x80d6ff, 0x80d8ff, 0x80dbff, 0x80ddff, 0x80dfff, 0x80e1ff, 0x80e3ff, 0x80e5ff, 0x80e7ff, 0x80e9ff, 0x80ebff, 0x80eeff, 0x80f0ff, 0x80f2ff, 0x80f4ff, 0x80f6ff, 0x80f8ff, 0x80faff, 0x80fcff, 0x80ffff, 0x80fffc, 0x80fffa, 0x80fff8, 0x80fff6, 0x80fff4, 0x80fff2, 0x80fff0, 0x80ffee, 0x80ffeb, 0x80ffe9, 0x80ffe7, 0x80ffe5, 0x80ffe3, 0x80ffe1, 0x80ffdf, 0x80ffdd, 0x80ffdb, 0x80ffd8, 0x80ffd6, 0x80ffd4, 0x80ffd2, 0x80ffd0, 0x80ffce, 0x80ffcc, 0x80ffca, 0x80ffc7, 0x80ffc5, 0x80ffc3, 0x80ffc1, 0x80ffbf, 0x80ffbd, 0x80ffbb, 0x80ffb9, 0x80ffb7, 0x80ffb4, 0x80ffb2, 0x80ffb0, 0x80ffae, 0x80ffac, 0x80ffaa, 0x80ffa8, 0x80ffa6, 0x80ffa3, 0x80ffa1, 0x80ff9f, 0x80ff9d, 0x80ff9b, 0x80ff99, 0x80ff97, 0x80ff95, 0x80ff93, 0x80ff90, 0x80ff8e, 0x80ff8c, 0x80ff8a, 0x80ff88, 0x80ff86, 0x80ff84, 0x80ff82 };

Color Colors::rainbow(uint16_t hue) {
  return _cached_rainbow[hue];
}
    
uint8_t Colors::red(Color color) {
  return 0x7f & (color >> 8);
}

uint8_t Colors::green(Color color) {
  return 0x7f & (color >> 16);
}

uint8_t Colors::blue(Color color) {
  return 0x7f & (color);
}

static inline uint8_t addComponent(uint8_t a, uint8_t b) {
  // this works because the colors are only 0-127
  uint8_t c = (a + b);
  if (c > 0x7f) {
    c = 0x7f;
  }
  return c;
}

Color Colors::add(Color a, Color b) {
  return Colors::rgb(
      addComponent(Colors::red(a), Colors::red(b)),
      addComponent(Colors::green(a), Colors::green(b)),
      addComponent(Colors::blue(a), Colors::blue(b)));
}

Color Colors::average(Color* colors, int num_colors) {
  int red_accum = 0;
  int green_accum = 0;
  int blue_accum = 0;
  for (int i = 0; i < num_colors; ++i) {
    Color color = colors[i];
    red_accum += Colors::red(color);
    green_accum += Colors::green(color);
    blue_accum += Colors::blue(color);
  }

  return Colors::rgb(red_accum / num_colors, green_accum / num_colors, blue_accum / num_colors);
}

static inline int min(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

Color Colors::multiply(Color color, float multiplier) {
  return Colors::rgb(
      min(Colors::red(color) * multiplier, 127),
      min(Colors::green(color) * multiplier, 127),
      min(Colors::blue(color) * multiplier, 127));
}

Color Colors::gammaCorrect(Color color, float gamma) {
  float gc = 1 / gamma;
  uint8_t red = 127.0f * pow((float)Colors::red(color) / 127.0f, gc);
  uint8_t green = 127.0f * pow((float)Colors::green(color) / 127.0f, gc);
  uint8_t blue = 127.0f * pow((float)Colors::blue(color) / 127.0f, gc);
  return Colors::rgb(red, green, blue);
}
