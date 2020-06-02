# COVID-19 Tracker

## Overview

This application retrieves latest COVID-19 confirmed cases and deaths timeseries data published by John Hopkins
University and plots them using
[Matplotlib](https://github.com/lava/matplotlib-cpp).

## Design



## Installation

The following steps have been verified with Ubuntu 16.04.

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
### Execution

From the `build` directory, run the following command

```
./covid-tracker
```

You should see 4 charts in total as below:

![Charts](https://raw.githubusercontent.com/takoloco/udacity_cp/master/images/20200602_scr_covid-tracker_01.png)

### Troubleshooting

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
