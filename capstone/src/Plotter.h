#ifndef PLOTTER_H
#define PLOTTER_H

#include <memory>
#include <string>

#include "EntityData.h"

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
    void SetSuperTitle(std::string title);
    void SetSubPlotPosition(int row_num, int column_num, int index);

    template <typename T>
    void Plot(std::shared_ptr<EntityDataCsv<T>> data, std::vector<int> rows,
    int row_num, int column_num, int index);
  private:
};

#include "Plotter.tpp"

#endif
