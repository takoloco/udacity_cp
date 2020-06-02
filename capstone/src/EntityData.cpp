#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "EntityData.h"
#include "Util.h"

EntityDataCsv::EntityDataCsv(const CsvType type) : _type(type)
{
  SetChartParameters(_type);
}

EntityDataCsv::EntityDataCsv(std::vector<std::shared_ptr<EntityData>> rows,
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
void EntityDataCsv::SetChartParameters(const CsvType type)
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
void EntityDataCsv::SetXOffset()
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
 * Returns a vector of int to be used as X values in plotting.
 *
 * @return x Vector of <int> to be used as X values in plotting.
 */
std::vector<int> EntityDataCsv::GetX()
{ 
  std::vector<int> x;

  if(!_xOffset)
  {
    SetXOffset();
  }
  std::vector<std::string> row = _rows[_ROW_NUMBER_X]->GetData();
  std::transform(row.begin() + _xOffset, row.end(),
  std::back_inserter(x), [](const std::string& str)
  { return std::stoi(str); });
  return x;
}

/**
 * Returns X values for plotting..
 *
 * Returns a vector of int to be used as X values in plotting.
 *
 * @return x Vector of <int> to be used as X values in plotting.
 */
std::vector<std::string> EntityDataCsv::GetXAsString()
{ 
  if(!_xOffset)
  {
    SetXOffset();
  }
  std::vector<std::string> row = _rows[_ROW_NUMBER_X]->GetData();
  return std::vector<std::string>(row.begin() + _xOffset, row.end());
}

/**
 * Returns Y values for plotting.
 *
 * Returns a vector of int to be used as Y values in plotting.
 * 
 * @param index Row index used in retrieving applicable row data.
 * @return y Vector of int to be used as Y values in plotting.
 */
std::vector<int> EntityDataCsv::GetY(const int index)
{
  std::vector<int> y;

  if(!_xOffset)
  {
    SetXOffset();
  }

  if(index == _ROW_NUMBER_X) 
    return y;

  std::vector<std::string> row = _rows[index]->GetData();
  std::transform(row.begin() + _xOffset, row.end(),
  std::back_inserter(y), [](const std::string& str) { return std::stoi(str); });
  return y;
}
/**
 * Returns Y values for plotting as std::string.
 *
 * Returns a vector of std::string to be used as Y values in plotting.
 * 
 * @param index Row index used in retrieving applicable row data.
 * @return y Vector of <std::string> to be used as Y values in plotting.
 */
std::vector<std::string> EntityDataCsv::GetYAsString(const int index)
{
  if(!_xOffset)
  {
    SetXOffset();
  }

  if(index  == _ROW_NUMBER_X) 
    return GetXAsString();

  std::vector<std::string> row = _rows[index]->GetData();
  return std::vector<std::string>(row.begin() + _xOffset, row.end());
}
