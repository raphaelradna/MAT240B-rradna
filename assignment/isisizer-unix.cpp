#include "everything.h"
using namespace diy;

struct Phasor {
  float phase = 0.0;        // on the interval [0, 1)
  float increment = 0.001;  // led to an low F

  void period(float seconds) { frequency(1 / seconds); }
  void frequency(float hertz) { increment = hertz / SAMPLE_RATE; }
  //float frequency() { return SAMPLE_RATE * increment; }
  void modulate(float hertz) { increment += hertz / SAMPLE_RATE; }

  float operator()() {
    // increment and wrap phase; this only works correctly for frequencies in
    // (-SAMPLE_RATE, SAMPLE_RATE) because otherwise increment will be greater
    // than 1 or less than -1 and phase will get away from us.
    //
    phase += increment;
    if (phase > 1) phase -= 1;
    if (phase < 0) phase += 1;
    return phase;
  }
};

float wrap(float value, float min, float max) {
    if (value > max) value -= max;
    if (value < min) value += min;
    return value;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("read <.wav> # open and dump from a .wav file");
    return 1;
  }

  drwav* pWav = drwav_open_file(argv[1]);
  if (pWav == nullptr) {
    return -1;
  }

  float* pSampleData = (float*)malloc((size_t)pWav->totalPCMFrameCount *
                                      pWav->channels * sizeof(float));
  drwav_read_f32(pWav, pWav->totalPCMFrameCount, pSampleData);

  drwav_close(pWav);

  Phasor phasor;
  float freq = 220;
  float _ = 0;
  float twopi = pi*2;

  if (pWav->channels == 1)
    for (unsigned n = 0; n < pWav->totalPCMFrameCount; ++n) {
      float x = asin(pSampleData[n]);
      float y = asin(_);
      float phasFreq = (((x-y)/twopi)+1)*freq;
      phasor.frequency(phasFreq);
      say(sin((wrap(phasor()+y,0,1))*twopi)-sin(phasor()*twopi));
      _ = pSampleData[n];
    }
  else if (pWav->channels == 2) {
    for (unsigned i = 0; i < pWav->totalPCMFrameCount; ++i)
      printf("%f\n", (pSampleData[2 * i] + pSampleData[2 * i + 1]) / 2);
  } else {
    printf("can't handle %d channels\n", pWav->channels);
    return 1;
  }
}
