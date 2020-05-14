#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <iostream>

int main(void)
{
  std::string host = "raw.githubusercontent.com";
  // IMPORTANT: 1st parameter must be a hostname or an IP adress string.
  httplib::SSLClient cli(host, 443);
  std::string body;

  auto res = cli.Get("/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_global.csv");
  if (res && res->status == 200) {
    std::cout << res->body << std::endl;
  }

  //assert(res->body.empty());
  /*if (res && res->status == 200) {
    std::cout << res->body << std::endl;
  }*/
}
