#include "mapProcess.h"
using namespace std;

int main(int argc, char const *argv[]){
    string pipeName = argv[2];
    MapProcess MapProcess(atoi(argv[1]), pipeName);
    MapProcess.getFileContents();
    MapProcess.processMap();
    MapProcess.sendMapToReduce();
    return 0;
}