#ifndef CLIENT_H
#define CLIENT_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
#include <iostream>

class HttpClient
{
public:
    HttpClient(std::string host, int port);
    std::string Get(std::string uri);
private:
    std::string _host;
    int _port;
    httplib::SSLClient _client;
};

#endif
