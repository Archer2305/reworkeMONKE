#include "main.h"
using namespace okapi;
extern Motor flywheel;
extern bool lock;
extern bool toggle;
extern bool held;
extern bool reverse;
extern bool toggleRumble;
extern bool TBHON;
extern double tbh;
extern double targetTBH;
// extern pros::Task moveFlywheel();
void updateFlywheel();
void TBH(void* ign);
// extern pros::Task task();