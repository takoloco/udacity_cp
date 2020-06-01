#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "Util.h"

template <class T>
EntityDataCsv<T>::EntityDataCsv(const CsvType type) : _type(type)
{
  SetChartParameters(_type);
}

template <class T>
EntityDataCsv<T>::EntityDataCsv(std::vector<std::shared_ptr<T>> rows,
CsvType type) : _rows(rows), _type(type)
{
  SetChartParameters(_type);
  SetXOffset();
  SetNumRows(rows.size());
}

/**
 * Initializes various chart parameter variable values for EntityDataCsv.
 *
 * Initializes chart parameter variables values such as start date, title, X and
 * Y labels.
 *
 * @param type CsvType of the current JHU CSV file.
 */
template <class T>
void EntityDataCsv<T>::SetChartParameters(CsvType type)
{
  switch(_type)
  {
    case CsvType::JHU_GLOBAL_CONFIRMED:
      _chartTitle = CHART_TITLE_GLOBAL_CONFIRMED;
      _chartXLabel = CHART_X_LABEL_GLOBAL_CONFIRMED;
      _chartYLabel = CHART_Y_LABEL_GLOBAL_CONFIRMED;
      _startDate = START_DATE_DEFAULT;
      break;
    case CsvType::JHU_GLOBAL_DEATHS:
      _chartTitle = CHART_TITLE_GLOBAL_DEATHS;
      _chartXLabel = CHART_X_LABEL_GLOBAL_DEATHS;
      _chartYLabel = CHART_Y_LABEL_GLOBAL_DEATHS;
      _startDate = START_DATE_DEFAULT;
      break;
    case CsvType::JHU_USA_CONFIRMED:
      _chartTitle = CHART_TITLE_USA_CONFIRMED;
      _chartXLabel = CHART_X_LABEL_USA_CONFIRMED;
      _chartYLabel = CHART_Y_LABEL_USA_CONFIRMED;
      _startDate = START_DATE_USA;
      break;
    case CsvType::JHU_USA_DEATHS:
      _chartTitle = CHART_TITLE_USA_DEATHS;
      _chartXLabel = CHART_X_LABEL_USA_DEATHS;
      _chartYLabel = CHART_Y_LABEL_USA_DEATHS;
      _startDate = START_DATE_USA;
      break;
    default:
      _chartTitle = CHART_TITLE_GLOBAL_CONFIRMED;
      _chartXLabel = CHART_X_LABEL_GLOBAL_CONFIRMED;
      _chartYLabel = CHART_Y_LABEL_GLOBAL_CONFIRMED;
      _startDate = START_DATE_DEFAULT;
  }
}

/**
 * Initializes offset of X label for plotting.
 *
 * Uses _startDate in determining the offset of X label and stores the offset in
 * _xOffset.
 * 
 * @throws std::runtime_error Thrown when _startDate is not found in
 * _ROW_NUMBER_X of the CSV file.
 */
template <class T>
void EntityDataCsv<T>::SetXOffset()
{
  std::vector<std::string> row = _rows[_ROW_NUMBER_X]->GetData();
  auto it = std::find (row.begin(), row.end(), std::string(_startDate));
  if (it == row.end())
    throw std::runtime_error("Start Date " + std::string(_startDate,
    sizeof(_startDate)) + " not found in CSV file!");
  _xOffset = std::distance(row.begin(), it);
}

/**
 * Returns X values for plotting..
 *
 * Returns a vector of <T2> to be used as X values in plotting.
 *
 * @return x Vector of <T2> to be used as X values in plotting.
 */
template <class T>
template <typename T2>
std::vector<T2> EntityDataCsv<T>::GetX()
{ 
  if(!_xOffset)
  {
    SetXOffset();
  }
  std::vector<T2> row = _rows[_ROW_NUMBER_X]->GetData();
  return std::vector<T2>(row.begin() + _xOffset, row.end());
}

/**
 * Returns Y values for plotting.
 *
 * Returns a vector of <T2> to be used as Y values in plotting.
 * 
 * @tparam T The type of EntityData class stored in EntityDataCsv.
 * @tparam T2 The type of data in which y is to be returned.
 * @param index Row index used in retrieving applicable row data.
 * @return y Vector of <T2> to be used as Y values in plotting.
 */
template <class T>
template <typename T2>
std::vector<T2> EntityDataCsv<T>::GetY(int index)
{
  std::vector<T2> y;

  if(!_xOffset)
  {
    SetXOffset();
  }

  if(index  == _ROW_NUMBER_X) 
    return y;

  std::vector<std::string> row = _rows[index]->GetData();
  std::transform(row.begin() + _xOffset, row.end(),
  std::back_inserter(y), [](const std::string& str)
  { return std::stoi(str); });
  return y;
}

/**
 * Returns Y values for plotting as std::string.
 *
 * Returns a vector of std::string to be used as Y values in plotting.
 * 
 * @tparam T The type of EntityData class stored in EntityDataCsv.
 * @param index Row index used in retrieving applicable row data.
 * @return y Vector of <T2> to be used as Y values in plotting.
 */
template <class T>
std::vector<std::string> EntityDataCsv<T>::GetY(int index)
{
  if(!_xOffset)
  {
    SetXOffset();
  }

  if(index  == _ROW_NUMBER_X) 
    return GetX<std::string>();

  std::vector<std::string> row = _rows[index]->GetData();
  return std::vector<std::string>(row.begin() + _xOffset, row.end());
}
