#include "everything.h"
using namespace diy;

int main(int argc, char* argv[]) {
  float startNote = 136; //MIDI value
  float endNote = 0; //MIDI value
  float note = startNote;
  float length = SAMPLE_RATE * 5.0; //sweep time in samples
  float frequency;
  if (argc > 1) frequency = atof(argv[1]);
  float phase = 0;
  float increment;
  int harmonicCount;
  float s;

  for (int n = 0; n < length; ++n) {
    note = scale(n, 0, length - 1, startNote, endNote);
    frequency = mtof(note);
    increment = frequency / SAMPLE_RATE;
    harmonicCount = 0;
    while (frequency * harmonicCount < SAMPLE_RATE / 2.0) harmonicCount++;
    s = 0;
    for (int h = 0; h < harmonicCount; ++h) {
      //s += cos(2.0 * pi * h * phase); //unipolar
      if (h == 0) continue;
      s += (sin(2.0 * pi * h * phase)) / h; //bipolar
    }
    say(s);
    phase += increment;
  }
}
