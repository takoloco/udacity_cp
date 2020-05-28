#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

class Util
{
  public:
    static void Tokenize(const std::string& str,
                  std::vector<std::string>& tokens,
                  const std::string& delimiters);
};

#endif
