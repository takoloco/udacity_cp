# COVID-19 Tracker

## Overview

COVID-19 Tracker is a C++ application that retrieves latest COVID-19 confirmed cases and deaths timeseries data published by [John Hopkins University](https://github.com/CSSEGISandData/COVID-19) and plots them using [Matplotlib](https://github.com/lava/matplotlib-cpp).

## Design

### Class Diagram

COVID-19 Tracker consists of 6 main entities and 1 Utility class.

* Tracker - Main class that kicks off the application
* EntityData - Data class that contains data for an geographical entity (i.e. country for Global, county for USA) represeted as a single row in JHU CSV files.
* EntityDataCsv - Class that represents an entire CSV JHU file that has a vector of corresponding `EntityData` instances which represent rows of the CSV file.
* EntityDataFactory - Factory class that produces instances of `EntityData`.
* HttpClient - Wrapper class around [cpp-httplib](https://github.com/yhirose/cpp-httplib) used to communicate with HTTP servers.
* Plotter - Class that implements plotting logic using C++ adaptation of [matplotlib-cpp](https://github.com/lava/matplotlib-cpp).
* Utility - Utility class that implements utility methods used across different classes in COVID-19 Tracker.

![Diagram](https://raw.githubusercontent.com/takoloco/udacity_cp/master/images/capstone/20200602_diagram_class_covid-tracker_01.png)

### Execution Flow

COVID-19 Tracker consists of 6 main entities and 1 Utility class. The main class `Tracker` kicks off its data ingestion class by sending HTTP requests to JHU's GitHub repo via `HttpClient` class. The returned data is then processed into `EntityDataCsv` objects each of which has an vector of pointers to `EntityData` objects instantiated by the `EntityDataFactory` Singleton instance. Finally, the `Plotter` class instance plots the data stored in the `EntityCsvData` objects.

![Diagram](https://raw.githubusercontent.com/takoloco/udacity_cp/master/images/capstone/20200602_diagram_sequence_covid-tracker_01.png)

## Installation

The following steps have been tested and verified with Ubuntu 16.04.

### Clone repos 

Get the main project codebase.

```
git clone https://github.com/takoloco/udacity_cp.git
```

This project also use the following libraries so please clone their repos as
well:

* [cpp-httplib](https://github.com/yhirose/cpp-httplib)
* [matplotlib-cpp](https://github.com/lava/matplotlib-cpp)

```
git clone https://github.com/yhirose/cpp-httplib.git
git clone https://github.com/lava/matplotlib-cpp.git
```

### Install packages

```
sudo apt install python
sudo apt install python-numpy
sudo apt-get install libssl-dev
Sudo apt-get install python-matplotlib
sudo apt-get install libpthread-stubs0-dev
```
### Check cmake version

You need `cmake` version **3.14** or later to compile this project. Check the
version of `cmake` installed in your environment by running the below
command:

```
cmake -version
```

If the version is lower than 3.14, please follow the following steps to
reinstall `cmake`.

Please download the latest version of `cmake` from [https://cmake.org/download/].

Untar the file
```
tar xzf cmake-3.X.Y.tar.gz
```
Move into the cmake directory
```
cd cmake-3.X.Y
```
Install `cmake` (this will take a while)
```
./bootstrap && make && sudo make install
```
Check your `cmake` version again to confirm that you now have the latest version
of `cmake`.
```
cmake -version
```
### Compilation

You should now be ready to compile the code!

From your working directory, create a directory called `build` under `capstone`.
```
mkdir -pv udacity_cp/capstone/build
```
Move into the `build` directory just created.
```
cd udacity_cp/capstone/build
```
Run `cmake`
```
cmake ..
```
Build the project!
```
make
```

See the Troubleshooting section below if you run into issues at the `cmake` or `make` steps.

### Execution

From the `build` directory, run the following command

```
./covid-tracker
```

You should see 4 charts in total as below:

![Charts](https://raw.githubusercontent.com/takoloco/udacity_cp/master/images/capstone/20200602_scr_covid-tracker_01.png)

### Troubleshooting

#### numpy error

If the system tells you that you already have `numpy` installed but `cmake`
fails to recognize it, you may need to remove `numpy` and try installing again
as below (obviously be careful before removing in case you have other
application dependent on numpy).

```
sudo apt-get remove python-numpy
sudo apt-get autoremove
```

Once the pakcages have been removed, try installing again.

```
sudo apt install python-numpy
```

#### Compilation error

You may encounter below compilation errors at `static_assert` checks in `matplotlibcpp.h`.

```
/home/tako/matplotlib-cpp/matplotlibcpp.h:305:37: error: expected ‘,’ before ‘)’ token
 static_assert(sizeof(long long) == 8);                                  ^
/home/tako/matplotlib-cpp/matplotlibcpp.h:305:37: error: expected string-literal before ‘)’ token
/home/tako/matplotlib-cpp/matplotlibcpp.h:307:46: error: expected ‘,’ before ‘)’ token
 static_assert(sizeof(unsigned long long) == 8);
```

If this happens, comment out lines 305 and 307 in matplotlib-cpp/matplotlibcpp.h or modify the lines as below.


```
static_assert(sizeof(long long) == 8, “”);
--
static_assert(sizeof(unsigned long long) == 8, “”);
```

## Rubric Points

### Required rubric points

|Criteria|Requirement|
|--------|-----------|
|A README with instructions is included with the project|This file satisfies this requirement.|
|The README indicates which project is chosen.|The Overview, Design and Installation sections of this file describes the project as required.|
|The README includes information about each rubric point addressed.|This section discusses each rubric point addressed.|
|The submission must compile and run.|Confirmed in my own GCP environment as well as Udacity workspace that the code compiles and runs.|

### Optional rubric points

|Criteria|Requirement|
|--------|-----------|
|The project demonstrates an understanding of C++ functions and control structures.|Various control structures such as if statements, switch statements and for/while loops are used throughout the project.|
|The project uses Object Oriented Programming techniques.|The project consists of 7 class entities as seen in the above entity relationship diagram.|
|Classes use appropriate access specifiers for class members.|The methods and variables defined in the classes in the project are assigned appropriate access specifiers.|
|All class members that are set to argument values are initialized through member initialization lists.|Classes such as `HttpClient`, `EntityData` and `EntityDataCsv` use member initialization lists in initializing their variables.|
|Classes encapsulate behavior.|Classes are designed around data entities such as `EntityDataCsv` which represents a CSV file published by JHU and `EntityData` which represents a row in a CSV file. Classes implements getters/setters for users to use in accsssing state.
|At least two variables are defined as references, or two functions use pass-by-reference in the project code.|`Plotter::Plot` and `Tracker::PlotData` use pass-by-reference.|
|The project uses smart pointers instead of raw pointers.|Classes such as `Tracker` and `EntityDataCsv` use shared pointers.|
|The project uses multithreading.|The Tracker classes uses `std::async` in kicking off CSV data downloads in concurrent fashion.|
