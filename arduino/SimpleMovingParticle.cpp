#include "SimpleMovingParticle.h"

SimpleMovingParticle::SimpleMovingParticle(
    Pixel start_pos, float speed, Pixel min_pos, Pixel max_pos, Color color)
        : MovingParticle(start_pos, speed, min_pos, max_pos), color(color) {
}

void SimpleMovingParticle::render(LPD8806* strip) {
  strip->addPixelColor(pos(), color);
}
