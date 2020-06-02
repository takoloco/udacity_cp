#ifndef TRACKER_H
#define TRACKER_H

#include <memory>

#include "Client.h"
#include "Plotter.h"

/**
 * COVID-19 Tracker main class.
 * 
 * Main COVID-19 Tracker class which kicks off retrieval of CSV data from JHU
 * GitHub repo and plots the processed data.
 */
class Tracker
{
public:
  Tracker();
  std::shared_ptr<EntityDataCsv> GetData(const CsvType csv_type);
  void PlotData(std::vector<std::shared_ptr<EntityDataCsv>> csvs, 
  std::vector<std::vector<int>> display_rows, int row_num,
  int column_num);
  void Run();
private:
  HttpClient _client;
  std::vector<std::shared_ptr<EntityDataCsv>> _csvs;
  std::unique_ptr<Plotter> _plotter;
};

#endif
