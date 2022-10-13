#include <string>
#include "reduceProcess.h"
using namespace std;

int main(int argc, char const *argv[]){
    string pipeName = argv[2];
    ReduceProcess reduceProcess(atoi(argv[1]), pipeName);
    reduceProcess.readMapData();
    reduceProcess.reduceMapData();
    reduceProcess.encodeResult();
    reduceProcess.sendResultToMainProcess();
    return 0;
}