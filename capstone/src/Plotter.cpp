#include <algorithm>
#include <memory>
#include <string>

#include "Plotter.h"
#include "matplotlibcpp.h"

#define PLOT_HEIGHT_DEFAULT 1560
#define PLOT_LEGEND_LOC "upper left"
#define PLOT_FONTSIZE_LABEL "x-small"
#define PLOT_FONTSIZE_LEGEND "xx-small"
#define PLOT_FONTSIZE_TICKS "xx-small"
#define PLOT_FONTSIZE_TITLE "small"
#define PLOT_PADDING_H 0.4
#define PLOT_PADDING_W 0.4
#define PLOT_WIDTH_DEFAULT 3000

namespace plt = matplotlibcpp;

namespace matplotlibcpp
{
  /**
   * Overloads Matplotlib's legend function to accept keyword parameters.
   *
   * Overloads Matplotlib's legend function to accept keyword parameters to
   * enable repositioning of legends.
   *
   * @param keywords Keyword parameters to be passed to `legend` function.
   */
  void legend(const std::map<std::string, std::string>& keywords)
  {
    detail::_interpreter::get();

    // construct keyword args
    PyObject* kwargs = PyDict_New();
    for(std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it)
    {
      PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
    }

    PyObject* res =
    PyObject_Call(detail::_interpreter::get().s_python_function_legend,
    detail::_interpreter::get().s_python_empty_tuple,
    kwargs);
    if(!res) throw std::runtime_error("Call to legend() failed.");

    Py_DECREF(kwargs);
    Py_DECREF(res);  
  }
}

/**
 * Sets super title of the plot as well as defining the figure size.
 *
 * Sets super title (title for the entire plot as opposed to subplots) of the
 * plot as well as defining the figure size.
 *
 * @param title Title to be set.
 */
void Plotter::SetSuperTitle(const std::string title)
{
  plt::figure_size(PLOT_WIDTH_DEFAULT, PLOT_HEIGHT_DEFAULT);
  plt::suptitle(title);
}

void Plotter::Plot(std::vector<std::shared_ptr<EntityDataCsv>> csvs,
std::vector<std::vector<int>> rows, int row_num, int column_num)
{
  int index = 0;
  for(std::shared_ptr<EntityDataCsv> data : csvs)
  {
    for(int i=1; i < data->GetNumRows(); i++)
    {
      plt::subplot(row_num, column_num, index+1);
      if(std::find(rows[index].begin(), rows[index].end(), i) == rows[index].end())
        continue;

      std::vector<int> y = data->GetY(i);
      std::vector<int> x;

      // C++ version of Matplot does not accept date type as its X input.
      // We will use the number of days since data->GetStartDate() instead
      int j = 0;
      while(x.size() < y.size()) {
        x.push_back(++j);
      }

      std::shared_ptr<EntityData> row = data->GetRow(i);
      std::map<std::string, std::string> args = {{"label", row->GetName()}};
      plt::plot(x, y, args);
    }
    plt::title(data->GetChartTitle(), {{"fontsize", PLOT_FONTSIZE_TITLE}});
    plt::xlabel(data->GetChartXLabel(), {{"fontsize", PLOT_FONTSIZE_LABEL}});
    plt::ylabel(data->GetChartYLabel(), {{"fontsize", PLOT_FONTSIZE_LABEL}});
    plt::tick_params({{"labelsize", PLOT_FONTSIZE_TICKS}});
    plt::legend({{"loc", PLOT_LEGEND_LOC}, {"fontsize", PLOT_FONTSIZE_LEGEND}});
    index++;
  }
  plt::subplots_adjust({{"hspace", PLOT_PADDING_H}, {"wspace", PLOT_PADDING_W}});
  plt::show();
}
