#ifndef PLOTTER_H
#define PLOTTER_H

#include <memory>
#include <string>

#include "EntityDataFactory.h"

/**
 * Implements plotting logic using MatPlotlib. 
 *
 * Implements plotting logic using C++ adaptation of MatPlotlib
 * (https://github.com/lava/matplotlib-cpp).
 */
class Plotter
{
  public:
    // Setters
    void SetSuperTitle(const std::string title);
    void SetSubPlotPosition(const int row_num, const int column_num,
    const int index);
    void Plot(const std::vector<std::shared_ptr<EntityDataCsv>> &csvs,
    const std::vector<std::vector<int>> &rows, const int row_num,
    const int column_num);
  private:
};

#endif
