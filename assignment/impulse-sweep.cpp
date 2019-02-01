#include "everything.h"
using namespace diy;

int main(int argc, char* argv[]) {
  float startNote = 136; //MIDI
  float endNote = 0; //MIDI
  float dur = SAMPLE_RATE * 5; //sweep time in samples

  float frequency;
  if (argc > 1) frequency = atof(argv[1]);
  float phase = 0;
  float increment;
  int harmonicCount;

  // calculate and output a bandlimited impulse whose
  // frequency starts near Nyquist and ends near midi 0.

  // make all calculations per-sample. determine the
  // current frequency, the number of harmonics to use,
  // and the current amplitude. increment phase.

  // output a finite number of floats, one float per line
  //say(0.0);  use this function

  // use other functions and constants from everything.h

  float s;
  for (int t = 0; t < dur; ++t) {
    frequency = mtof(((startNote-endNote)/dur)*(dur-t));
    increment = frequency / SAMPLE_RATE;
    harmonicCount = 0;
    while (frequency * harmonicCount < SAMPLE_RATE / 2) harmonicCount++;

    s = 0;
    for (int h = 0; h < harmonicCount; ++h)
      s += cos(2 * pi * h * phase); //unipolar
      //s += sin(2 * pi * h * phase); //bipolar
      s /= harmonicCount;
    say(s);

    phase += increment;
  }
}
