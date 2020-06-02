#ifndef CLIENT_H
#define CLIENT_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
#include <iostream>

/**
 * A wrapper class around httplib.
 *
 * A wrapper class around cpp-httplib (https://github.com/yhirose/cpp-httplib)
 * used to communicate with HTTP servers.
 */
class HttpClient
{
public:
    HttpClient(std::string host, int port);
    std::string Get(const std::string uri);
private:
    std::string _host;
    int _port;
    httplib::SSLClient _client;
};

#endif
