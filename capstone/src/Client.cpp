#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <iostream>
#include <sstream>

#include "Client.h"

HttpClient::HttpClient(std::string host, int port): _host(host), _port(port), _client(host, port) {}

std::string HttpClient::Get(std::string uri)
{
  auto res = _client.Get(uri.c_str());

  if (res && res->status == 200) {
    return res->body;
  }
  std::ostringstream error;
  error << "HTTP request to " << _host << ":" << _port << " failed with code: " << res->status;
  throw std::runtime_error(error.str());
}
