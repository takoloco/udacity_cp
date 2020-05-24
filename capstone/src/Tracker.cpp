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

Tracker::Tracker() : _client(HOSTNAME_DST, PORT_DST) {}

void Tracker::Run()
{
  std::vector<std::shared_ptr<EntityData>> lines;
  std::string line;

  // Get Data from John Hopkins Website
  std::string response = _client.Get(URI_GLOBAL_DST);
  std::stringstream csv(response);

  // Process response
  EntityDataFactory * raw_factory;
  raw_factory->getInstance();
  std::unique_ptr<EntityDataFactory> factory(raw_factory);
  while(std::getline(csv, line, '\n')) {
    auto data = factory->CreateData<JHUGlobalConfirmedData>(DataSourceType::JHUGlobalConfirmed, line);
    lines.push_back(data);
  }
  std::cout << "Print data!" << std::endl;
  for(std::shared_ptr<EntityData> line: lines) {
    line->getData();
  }
  std::cout << "That is all!" << std::endl;
}

int main(int argc, const char **argv)
{
  Tracker tracker;
  tracker.Run();
}
