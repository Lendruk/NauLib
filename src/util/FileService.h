#include <iostream>
using namespace std;

namespace NauLib {
  class FileService {
    public:
      string getCurrentWorkingDirectory();
      static string readFile(string fileName);
  };
}