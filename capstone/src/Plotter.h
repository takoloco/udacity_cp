#ifndef PLOTTER_H
#define PLOTTER_H

#include <memory>

#include "EntityData.h"

class Plotter
{
  public:
    void plot(std::shared_ptr<EntityDataCsv<JHUGlobalConfirmedData>> data);
  private:
};

#endif
