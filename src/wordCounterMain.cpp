#include "wordCounter.h"
using namespace std;

int main(){
    WordCounter wc = WordCounter();
    wc.forkMaps();
    wc.forkReduce();
    return 0;
}