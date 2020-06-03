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

#define CHART_TITLE_GLOBAL_CONFIRMED "Daily Confirmed Cases by Country - Global"
#define CHART_TITLE_GLOBAL_DEATHS "Daily Deaths by Country - Global"
#define CHART_TITLE_USA_CONFIRMED "Daily Confirmed Cases by County - USA"
#define CHART_TITLE_USA_DEATHS "Daily Deaths by County - USA"
#define CHART_X_LABEL_GLOBAL_CONFIRMED "Number of Days Since February 1 2020"
#define CHART_X_LABEL_GLOBAL_DEATHS CHART_X_LABEL_GLOBAL_CONFIRMED
#define CHART_X_LABEL_USA_CONFIRMED "Number of Days Since March 1 2020"
#define CHART_X_LABEL_USA_DEATHS CHART_X_LABEL_USA_CONFIRMED
#define CHART_Y_LABEL_GLOBAL_CONFIRMED "Number of Confirmed Cases"
#define CHART_Y_LABEL_GLOBAL_DEATHS "Number of Deaths"
#define CHART_Y_LABEL_USA_CONFIRMED CHART_Y_LABEL_GLOBAL_CONFIRMED
#define CHART_Y_LABEL_USA_DEATHS CHART_Y_LABEL_GLOBAL_DEATHS
#define START_DATE_DEFAULT "2/1/20"
#define START_DATE_USA "3/1/20"

/**
 * Represents different types of COVID-19 CSV files JHU publishes.
 *
 * Represents different types of COVID-19 time series CSV files John Hopkins
 * University publishes through GitHub
 * (https://github.com/CSSEGISandData/COVID-19/tree/master/csse_covid_19_data/csse_covid_19_time_series).
 */
enum CsvType
{
  /// Global confirmed cases
  JHU_GLOBAL_CONFIRMED,
  /// Global deaths
  JHU_GLOBAL_DEATHS,
  /// USA confirmed cases,
  JHU_USA_CONFIRMED,
  /// USA deaths
  JHU_USA_DEATHS
};

/**
 * Contains data from a single line in a CSV file which represents an entity.
 *
 * Contains data extracted from a single line in a given JHU CSV file which
 * represents an entity (varies depending on the source CSV file) in both raw
 * and parsed formats.
 */
class EntityData
{
  public:
    EntityData(const CsvType type, const std::string &data);
    std::string GetRawData() { return _raw_data; }
    std::string GetName() { return _name; }
    std::vector<std::string> GetData() { return _data; }
  protected:
    std::vector<std::string> _data;
    std::string _name;
    std::string _raw_data;
    CsvType _type;
};

/**
 * Contains data extracted from an entire JHU CSV file.
 *
 * Contains data extracted from an entire JHU CSV file in a form of a vector of
 * EntityData objects as well as additional meta data used in plotting.
 */
class EntityDataCsv
{
  public:
    constexpr static int _ROW_NUMBER_X = 0;
    EntityDataCsv() {}
    EntityDataCsv(CsvType type = CsvType::JHU_GLOBAL_CONFIRMED);
    EntityDataCsv(std::vector<std::shared_ptr<EntityData>> rows, CsvType type =
    CsvType::JHU_GLOBAL_CONFIRMED);

    // Getters
    std::string GetChartTitle() { return _chartTitle; }
    std::string GetChartXLabel() { return _chartXLabel; }
    std::string GetChartYLabel() { return _chartYLabel; }
    int GetNumRows() { return _numRows; }
    std::shared_ptr<EntityData> GetRow(const int rowNum) { return _rows[rowNum]; }
    std::vector<std::shared_ptr<EntityData>> GetRows() { return _rows; }
    std::string GetStartDate() { return _startDate; }
    CsvType GetType() { return _type; }

    // Setters
    void SetChartParameters(const CsvType type);
    void SetNumRows(const int numRows) { _numRows = numRows; }
    void SetXOffset();

    // CSV Data Output
    std::vector<int> GetX();
    std::vector<std::string> GetXAsString();
    std::vector<int> GetY(const int index);
    std::vector<std::string> GetYAsString(const int index);
  protected:
    std::string _chartTitle;
    std::string _chartXLabel;
    std::string _chartYLabel;
    int _numRows = 0;
    std::vector<std::shared_ptr<EntityData>> _rows;
    std::string _startDate;
    CsvType _type;
    int _xOffset = 0;
};

#endif
