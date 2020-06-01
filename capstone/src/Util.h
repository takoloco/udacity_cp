#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

/**
 * Utility class.
 *
 * Utility class which implements utility methods used across different classes
 * throughout the application.
 */
class Util
{
  public:
    static void Tokenize(const std::string& str,
                  std::vector<std::string>& tokens,
                  const std::string& delimiters);
};

#endif
