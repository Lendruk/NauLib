#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include "FileService.h"
using namespace std;
#include <fstream>

namespace NauLib {
  string FileService::getCurrentWorkingDirectory() {
    char buffer[FILENAME_MAX];
    GetCurrentDir(buffer, FILENAME_MAX);
    string currentWorkingDirectory(buffer);
    return currentWorkingDirectory;
  }

  string FileService::readFile(string fileName) {
    ifstream file;
    file.open(fileName);
    if(file.is_open()) {
      string output( (std::istreambuf_iterator<char>(file)),
                     (std::istreambuf_iterator<char>()  ));
      file.close();
      return output;
    }
    return "";
  }
}