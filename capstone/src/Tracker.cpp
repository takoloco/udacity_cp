#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
 
#include "Client.h"
#include "EntityDataFactory.h"
#include "Plotter.h"
#include "Tracker.h"

#define HOSTNAME_DST "raw.githubusercontent.com"
#define PORT_DST 443
#define URI_GLOBAL_CONFIRMED_DST "/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_global.csv"
#define URI_GLOBAL_DEATHS_DST "/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_deaths_global.csv"
#define URI_US_CONFIRMED_DST "/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_US.csv"
#define URI_US_DEATHS_DST "/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_deaths_US.csv"
#define CHART_SUPER_TITLE "COVID-19 Daily Confirmed Cases/Deaths"
#define CHART_ROW_NUM 2
#define CHART_COLUMN_NUM 2

// Specifies which rows in global JHU CSV files to be displayed.
const std::vector<int> GLOBAL_ROWS{29, 138, 140, 188, 224, 226};
// Specifies which rows in USA JHU CSV files to be displayed.
const std::vector<int> USA_ROWS{210, 229, 234, 1318, 1864, 2975};

Tracker::Tracker() : _client(HOSTNAME_DST, PORT_DST) {}

/**
 * Retrieves CSV data from JHU and returns as an EntityDataCsv instance.
 *
 * Retrieves necessary CSV data from JHU's GitHub repo
 * (https://github.com/CSSEGISandData/COVID-19/tree/master/csse_covid_19_data/csse_covid_19_time_series)
 * and encapsulates it in EntityCsvData instance and returns it.
 * 
 * @param CsvType CsvType of the file to be retrieved.
 * @return data shared_ptr to EntityDataCsv instance containing data from
 * downloaded/processed CSV file.
 */
std::shared_ptr<EntityDataCsv> Tracker::GetData(const CsvType csv_type)
{
  std::vector<std::shared_ptr<EntityData>> lines;
  std::string line;
  std::string uri;

  switch(csv_type)
  {
    case CsvType::JHU_GLOBAL_CONFIRMED:
      uri = URI_GLOBAL_CONFIRMED_DST;
      break;
    case CsvType::JHU_GLOBAL_DEATHS:
      uri = URI_GLOBAL_DEATHS_DST;
      break;
    case CsvType::JHU_USA_CONFIRMED:
      uri = URI_US_CONFIRMED_DST;
      break;
    case CsvType::JHU_USA_DEATHS:
      uri = URI_US_DEATHS_DST;
      break;
    default: 
      uri = URI_GLOBAL_CONFIRMED_DST;
  }

  // Get Data from John Hopkins Website
  std::string response = _client.Get(uri);
  std::stringstream csv(response);

  // Process response
  std::unique_ptr<EntityDataFactory> factory;
  factory->getInstance();
  while(std::getline(csv, line, '\n')) {
    auto data = factory->CreateData(csv_type, line);
    lines.push_back(data);
  }

  return std::make_shared<EntityDataCsv>(lines, csv_type);
}

/**
 * Plots a vector of CSV data as Matplotlib plot.
 *
 * Given a vector of CSV data, feed it to Plotter instance for plotting.
 *
 * @param csvs CSV data to be plotted..
 * @param display_rows Vector of int specifying which rows in CSV to be plotted.
 * @param row_num Number of total rows of subplots to be plotted.
 * @param column_num Number of total columns of subplots to be plotted.
 */
void Tracker::PlotData(std::vector<std::shared_ptr<EntityDataCsv>> csvs,
std::vector<std::vector<int>> display_rows, int row_num, int column_num)
{
  _plotter->Plot(csvs, display_rows, row_num, column_num);
}

/**
 * Executes Tracker.
 * 
 * Executes COVID-19 tracker.
 */
void Tracker::Run()
{
  _plotter->SetSuperTitle(CHART_SUPER_TITLE);
  std::cout << "Start plotting data..." << std::endl;
  auto a1 = std::async(&Tracker::GetData, this,
  CsvType::JHU_GLOBAL_CONFIRMED);
  auto a2 = std::async(&Tracker::GetData, this,
  CsvType::JHU_GLOBAL_DEATHS);
  auto a3 = std::async(&Tracker::GetData, this,
  CsvType::JHU_USA_CONFIRMED);
  auto a4 = std::async(&Tracker::GetData, this,
  CsvType::JHU_USA_DEATHS);

  a1.wait();
  a2.wait();
  a3.wait();
  a4.wait();
  _csvs.push_back(a1.get());
  _csvs.push_back(a2.get());
  _csvs.push_back(a3.get());
  _csvs.push_back(a4.get());

  PlotData(_csvs, {GLOBAL_ROWS, GLOBAL_ROWS, USA_ROWS, USA_ROWS},
  CHART_ROW_NUM, CHART_COLUMN_NUM);

  std::cout << "Plotting complete!" << std::endl;
}

int main(int argc, const char **argv)
{
  Tracker tracker;
  tracker.Run();
}
