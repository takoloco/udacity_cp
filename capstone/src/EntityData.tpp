#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "Util.h"

template <class T>
EntityDataCsv<T>::EntityDataCsv(CsvType type) : _type(type)
{
  SetStartDate(_type);
}

template <class T>
EntityDataCsv<T>::EntityDataCsv(std::vector<std::shared_ptr<T>> lines,
CsvType type) : _lines(lines), _type(type)
{
  SetStartDate(_type);
  SetXOffset();
}

template <class T>
void EntityDataCsv<T>::SetStartDate(CsvType type)
{
  switch(_type)
  {
    case CsvType::JHU_GLOBAL_CONFIRMED:
    case CsvType::JHU_GLOBAL_DEATHS:
      _startDate = "1/22/20";
      break;
    case CsvType::JHU_USA_CONFIRMED:
    case CsvType::JHU_USA_DEATHS:
      _startDate = "3/10/20";
      break;
    default:
      _startDate = "1/22/20";
  }
}

template <typename T>
void EntityDataCsv<T>::SetXOffset()
{
  std::vector<std::string> line;
  std::string raw_line = _lines[_ROW_NUMBER_X]->GetData();
  Util::Tokenize(raw_line, line, ",");
  auto it = std::find (line.begin(), line.end(), std::string(_startDate));
  if (it == line.end())
    throw std::runtime_error("Start Date " + std::string(_startDate,
    sizeof(_startDate)) + " not found in CSV file!");
  _xOffset = std::distance(line.begin(), it);
}

template <typename T>
template <typename T2>
std::vector<T2> EntityDataCsv<T>::GetX()
{ 
  if(!_xOffset)
  {
    SetXOffset();
  }
  std::vector<std::string> line;
  std::string raw_line = _lines[_ROW_NUMBER_X]->GetData();
  Util::Tokenize(raw_line, line, ",");
  return std::vector<T2>(line.begin() + _xOffset, line.end());
}

template <typename T>
template <typename T2>
std::vector<T2> EntityDataCsv<T>::GetY(int index)
{
  std::vector<std::string> line;
  std::vector<T2> y;

  if(!_xOffset)
  {
    SetXOffset();
  }

  if(index  == _ROW_NUMBER_X) 
    return y;

  std::string raw_line = _lines[index]->GetData();
  Util::Tokenize(raw_line, line, ",");
  std::transform(line.begin() + _xOffset, line.end(),
  std::back_inserter(y), [](const std::string& str)
  { return std::stoi(str); });
  return y;
}

template <typename T>
std::vector<std::string> EntityDataCsv<T>::GetY(int index)
{
  std::vector<std::string> line;

  if(!_xOffset)
  {
    SetXOffset();
  }

  if(index  == _ROW_NUMBER_X) 
    return GetX<std::string>();

  std::string raw_line = _lines[index]->GetData();
  Util::Tokenize(raw_line, line, ",");
  return std::vector<std::string>(line.begin() + _xOffset, line.end());
}
