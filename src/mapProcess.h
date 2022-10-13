#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>
#include <map>

#define PIPE_BUFFER_SIZE 8192

class MapProcess{
  public:
    MapProcess(int pipeFd, std::string namePipe);
    void getFileContents();
    void processMap();
    void sendMapToReduce();

  private:
    std::vector<std::string> files;
    std::vector<std::string> wordsInFile;
    std::map<std::string, int> wordCountMap;
    std::string fileName;
    std::string namedPipeName;    
};
