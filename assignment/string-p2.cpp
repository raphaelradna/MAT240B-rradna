/*
Implement Karplus-Strong using allolib and the offerings in our synths.h header.
Make sure this version supports triggering “plucks” and setting the fundamental frequency of the synth.
*/

#include "al/core.hpp"
#include "al/util/ui/al_ControlGUI.hpp"
#include "al/util/ui/al_Parameter.hpp"
#include "al/util/ui/al_Preset.hpp"
using namespace al;

#include "synths.h"
using namespace diy;

#include <iostream>
using namespace std;

struct KS {
  Parameter pitch{"/pitch", "", 60., "", 0., 127.};
  Parameter feedback{"/feedback", "", 0.975, "", 0., 1.};

  Noise noise;
  Array excitation;
  Delay delay;
  Biquad filter;

  int L = delay.capacity * SAMPLE_RATE;

  void initialize() {
    excitation.reserve(L);
    for (int i = 0; i < L; ++i) excitation.data[i] = uniform();
  }

  float operator()() {
    float increment = ((mtof(pitch.get(int(index))) * NUMPOINTS) / SAMPLE_RATE);
    index += increment;

    if (index > NUMPOINTS) {
      index -= NUMPOINTS;
      update();
    }

    float gain;
    switch (playMode)
    {
    default:
    case 0:
        gain = 1.0;
        break;
    case 1:
        gain = gateSmooth();
        break;
    }

    return amp.get(index) * gain;
  }
};

struct MyApp : App
{
    float background = 0.0;

    KS ks;

    ControlGUI gui;
    PresetHandler presetHandler{"ksPresets"};
    PresetServer presetServer{"0.0.0.0", 9011};

    void onCreate() override {
      ks.initialize();

      gui.init();
      gui << presetHandler << ks.pitch << ks.feedback;
      presetHandler << ks.pitch << ks.feedback;
      presetHandler.setMorphTime(1.0);
      parameterServer() << ks.pitch << ks.feedback;
      parameterServer().print();
    }

    void onAnimate(double dt) override {
      navControl().active(!gui.usingInput());
    }

    void onDraw(Graphics &g) override {
      g.clear(background);
      gui.draw(g);
    }

    void onSound(AudioIOData &io) override {
      while (io()) {
        float s = ks();
        s *= 0.25;
        io.out(0) = s;
        io.out(1) = s;
      }
    }
};

int main() {
  MyApp app;
  app.initAudio(SAMPLE_RATE, BLOCK_SIZE, OUTPUT_CHANNELS, INPUT_CHANNELS);
  app.start();
}
