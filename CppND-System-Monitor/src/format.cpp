#include <time.h>
#include <iostream>
#include <string>

#include "format.h"

using std::string;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  struct tm* ptm = gmtime(&seconds);
  return to_string(ptm->tm_hour) + ":" + to_string(ptm->tm_min) + ":" +
         to_string(ptm->tm_sec);
}