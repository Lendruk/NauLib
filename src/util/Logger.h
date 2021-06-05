#include <iostream>
using namespace std;

namespace NauLib {
  class Logger {
    private:
      static void logMessage(string message, string color);
      static const string RED;
      static const string GREEN;
      static const string YELLOW;
      static const string WHITE;
    public:
      static void info(string message);
      static void warn(string message);
      static void error(string message);
      static void fatal(string message);
  };
}

#define KNRM  "\x1B[0m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
