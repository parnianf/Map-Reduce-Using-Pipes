#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

class WordCounter{

  public:
    WordCounter();
    void forkMaps();
    void getTestcasesFiles();
    void forkReduce();

  private:
    int processCount;
    std :: string filesDirectory; 
    std::vector< std::string > files;
    std::vector<std::vector<int> > mapPipes;
    pid_t reducer;
};