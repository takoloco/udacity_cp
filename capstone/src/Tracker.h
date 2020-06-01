#ifndef TRACKER_H
#define TRACKER_H

#include <memory>

#include "Client.h"
#include "EntityData.h"
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
  template <typename T>
  std::shared_ptr<EntityDataCsv<T>> GetData(CsvType csv_type);
  template <typename T2>
  void PlotData(CsvType csv_type, std::vector<int> display_rows,
  int row_num, int column_num, int index);
  void Run();
private:
  HttpClient _client;
  std::unique_ptr<Plotter> _plotter;
};

#include "Tracker.tpp"

#endif
