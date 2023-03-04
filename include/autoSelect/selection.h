#pragma once

#include <string>

//selector configuration
#define HUE 340
#define DEFAULT 1
#define AUTONS "Left", "Right", "Full AWP"

namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
