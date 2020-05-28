#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "Util.h"

#define START_DATE_DEFAULT "1/22/20"

class EntityData
{
  public:
    EntityData(std::string data) : _raw_data(data) {}
    //EntityData(std::string data, std::vector<T> x, std::vector<int> y) : _raw_data(data), _x(x), _y(y) {}
    std::string GetData() { return _raw_data; }
  protected:
    std::string _raw_data;
};

class JHUGlobalConfirmedData : public EntityData
{
  public:
    JHUGlobalConfirmedData(std::string data) : EntityData(data) {}
};

class JHUGlobalDeathsData : public EntityData
{
  public:
    JHUGlobalDeathsData(std::string data) : EntityData(data) {}
};

class JHUUSAConfirmedData : public EntityData
{
  public:
    JHUUSAConfirmedData(std::string data) : EntityData(data) {}
};

class JHUUSADeathsData : public EntityData
{
  public:
    JHUUSADeathsData(std::string data) : EntityData(data) {}
};

enum CsvType
{
  JHU_GLOBAL_CONFIRMED,
  JHU_GLOBAL_DEATHS,
  JHU_USA_CONFIRMED,
  JHU_USA_DEATHS
};

template <class T>
class EntityDataCsv
{
  public:
    constexpr static int _ROW_NUMBER_X = 0;
    EntityDataCsv() {}
    EntityDataCsv(CsvType type = CsvType::JHU_GLOBAL_CONFIRMED);
    EntityDataCsv(std::vector<std::shared_ptr<T>> lines, CsvType type =
    CsvType::JHU_GLOBAL_CONFIRMED);
    std::vector<std::shared_ptr<T>> GetLines() { return _lines; }
    CsvType GetType() { return _type; }
    std::string GetStartDate() { return _startDate; }
    void SetStartDate(CsvType type);
    void SetXOffset();
    template <typename T2>
    std::vector<T2> GetX();
    template <typename T3>
    std::vector<T3> GetY(int index);
    std::vector<std::string> GetY(int index);
  protected:
    std::vector<std::shared_ptr<T>> _lines;
    CsvType _type;
    std::string _startDate = START_DATE_DEFAULT;
    int _xOffset = 0;
};

#include "EntityData.tpp"

#endif
