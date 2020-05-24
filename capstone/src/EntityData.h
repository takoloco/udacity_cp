#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include <string>
#include <vector>

class EntityData
{
  public:
    EntityData(std::string data) : _raw_data(data) {}
    //EntityData(std::string data, std::vector<T> x, std::vector<int> y) : _raw_data(data), _x(x), _y(y) {}
    std::vector<int> getX() { return _x; }
    std::vector<int> getY() { return _y; }
    std::string getData() { return _raw_data; }
  protected:
    std::string _raw_data;
    std::vector<int> _x;
    std::vector<int> _y;
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

#endif
