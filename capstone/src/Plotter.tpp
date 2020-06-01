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
void Plotter::SetSuperTitle(std::string title)
{
  plt::figure_size(PLOT_WIDTH_DEFAULT, PLOT_HEIGHT_DEFAULT);
  plt::suptitle(title);
}

/**
 * Plots graph given X and Y input and parameters.
 *
 * Given X and Y input, plots graph as an Matplotlib subplot and configures
 * necessary parameters.
 *
 * @tparam T The type of EntityData class stored in EntityDataCsv.
 * @param data EntityDataCsv object containing data to be plotted.
 * @param rows Vector of int used in specifying which rows in CSV to be plotted.
 * @param row_num Number of rows of subplots to be displayed.
 * @param column_num Number of columns of subplots to be displayed.
 * @param index Index representing current subplot position.
 */
template <typename T>
void Plotter::Plot(std::shared_ptr<EntityDataCsv<T>> data,
std::vector<int> rows, int row_num, int column_num, int index)
{
  plt::subplot(row_num, column_num, index);
  for(int i=1; i < data->GetNumRows(); i++)
  {
    if(std::find(rows.begin(), rows.end(), i) == rows.end())
      continue;

    std::vector<int> y = data->template GetY<int>(i);
    std::vector<int> x;

    // C++ version of Matplot does not accept date type as its X input.
    // We will use the number of days since data->GetStartDate() instead
    int j = 0;
    while(x.size() < y.size()) {
      x.push_back(++j);
    }

    std::shared_ptr<T> row = data->GetRow(i);
    std::map<std::string, std::string> args = {{"label", row->GetName()}};
    plt::plot(x, y, args);
  }
  plt::title(data->GetChartTitle(), {{"fontsize", PLOT_FONTSIZE_TITLE}});
  plt::xlabel(data->GetChartXLabel(), {{"fontsize", PLOT_FONTSIZE_LABEL}});
  plt::ylabel(data->GetChartYLabel(), {{"fontsize", PLOT_FONTSIZE_LABEL}});
  plt::tick_params({{"labelsize", PLOT_FONTSIZE_TICKS}});
  plt::legend({{"loc", PLOT_LEGEND_LOC}, {"fontsize", PLOT_FONTSIZE_LEGEND}});
}
