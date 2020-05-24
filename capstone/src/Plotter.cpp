#include "Plotter.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

Plotter::Plotter()
{
  plt::title("Confirmed Cases - Global - Daily");
  plt::figure_size(1200, 780);
  plt::legend();
}

void Plotter::plot(EntityData* data)
{
  plt::plot(data->getX(), data->getY());
  plt::show();
}
