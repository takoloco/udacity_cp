#ifndef TRACKER_H
#define TRACKER_H

#include "Client.h"

class Tracker
{
public:
  Tracker();
  void Run();
private:
  HttpClient _client;
};

#endif
