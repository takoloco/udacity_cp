#ifndef TRACKER_H
#define TRACKER_H

#include <memory>

#include "Client.h"
#include "EntityData.h"
#include "Plotter.h"

class Tracker
{
public:
  Tracker();
  void GetData();
  void PlotData();
  void Run();
private:
  HttpClient _client;
  std::shared_ptr<EntityDataCsv<JHUGlobalConfirmedData>> _csv;
  std::unique_ptr<Plotter> _plotter;
};

#endif
