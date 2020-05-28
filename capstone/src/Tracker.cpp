#include <iostream>
#include <memory>
#include <vector>

#include "Client.h"
#include "EntityDataFactory.h"
#include "Tracker.h"

#define HOSTNAME_DST "raw.githubusercontent.com"
#define PORT_DST 443
#define URI_GLOBAL_DST "/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_global.csv"
#define URI_US_DST "/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_US.csv"
#define DATE_GLOBAL_START "1/22/20"
#define DATE_US_START "3/10/20"

Tracker::Tracker() : _client(HOSTNAME_DST, PORT_DST) {}

void Tracker::GetData()
{
  std::vector<std::shared_ptr<JHUGlobalConfirmedData>> lines;
  std::string line;

  // Get Data from John Hopkins Website
  std::string response = _client.Get(URI_GLOBAL_DST);
  std::stringstream csv(response);

  // Process response
  std::unique_ptr<EntityDataFactory> factory;
  factory->getInstance();
  while(std::getline(csv, line, '\n')) {
    auto data = factory->CreateData<JHUGlobalConfirmedData>(DataSourceType::JHUGlobalConfirmed, line);
    lines.push_back(data);
  }
  _csv = std::make_shared<EntityDataCsv<JHUGlobalConfirmedData>>(lines,
  CsvType::JHU_GLOBAL_CONFIRMED);
}

void Tracker::PlotData()
{
  _plotter->plot(_csv);
}

void Tracker::Run()
{
  GetData();
  std::cout << "Plot data!" << std::endl;
  PlotData();
  std::cout << std::endl;
  std::vector<std::shared_ptr<JHUGlobalConfirmedData>> lines = _csv->GetLines();
  for(std::shared_ptr<JHUGlobalConfirmedData> line: lines) {
    //std::cout << line->GetData() << std::endl;
  }
  std::cout << "That is all!" << std::endl;
}

int main(int argc, const char **argv)
{
  Tracker tracker;
  tracker.Run();
}
