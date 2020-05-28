#include <memory>
#include <string>

#include "EntityData.h"
#include "Plotter.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

void Plotter::plot(std::shared_ptr<EntityDataCsv<JHUGlobalConfirmedData>> data)
{
  for(int i=1; i < data->GetLines().size(); i++)
  {
    std::vector<int> x;
    //std::vector<std::string> x = data->GetX<std::string>();
    std::vector<int> y = data->GetY<int>(i);

    int j = 0;
    while(x.size() < y.size()) {
      x.push_back(++j);
    }

    /*while(x.size() > y.size()) {
      x.pop_back();
    }*/

    plt::title("Confirmed Cases - Global - Daily");
    plt::figure_size(5000, 780);
    plt::plot(x, y);
    plt::legend();
    plt::show();
    break;
  }
}
