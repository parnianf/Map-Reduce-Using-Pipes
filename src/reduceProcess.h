#include <vector>
#include <string>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <map>

class ReduceProcess{
  public:
    ReduceProcess(int pipeWriteFd, std::string pipeName);
    void readMapData();
    void getTestcasesFiles();
    void reduceMapData();
    void encodeResult();
    void sendResultToMainProcess();
  private:
    int pipeWriteEndFd;
    std::string namedPipeName;
    std::vector< std::string > files;
    std::map<std::string, int> wordCountMap;
    std::multimap<std::string, int> umap;
    std::string result;
};