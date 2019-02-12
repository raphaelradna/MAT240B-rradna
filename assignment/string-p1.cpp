#include "everything.h"
using namespace diy;

std::vector<float> excitation;
int L = 512;

struct Delay { //adapted from https://ccrma.stanford.edu/~jos/pasp/Software_Delay_Line.html
    std::vector<float> buffer;
    int index = 0;
    float operator()(float x) {
        float y = buffer[index];
        buffer[index++] = x;
        if (index >= L) index -= L;
        return y;
    }
  };

int main(int argc, char* argv[]) {
  Delay delay;
  delay.buffer.reserve(L);
  excitation.reserve(L);
  for (int i = 0; i < L; ++i) excitation[i] = uniform(-1, 1);
  float out = 0;
  float fb = 0;
  float avg = 0;
  for (int t = 0; t <= SAMPLE_RATE * 5; ++t) {
    out = delay(excitation[t]+avg);
    say(excitation[t]+out);
    avg = (out+fb)/2;
    fb = out*0.975;
  }
}
