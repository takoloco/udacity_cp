#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <iostream>
#include <sstream>

#include "Client.h"

HttpClient::HttpClient(std::string host, int port): _host(host), _port(port), _client(host, port) {}

/**
 * Given a URI, queries it via GET and returns response body.
 * 
 * Sends a GET request against the URI specified by `uri` and returns the body
 * of HTTP response returned by the server.
 *
 * @param uri URI to be queried.
 * @return res-body Body of returned response by the server.
 * @throws std::runtime_error if the returned status code is not 200 (success).
 */
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
