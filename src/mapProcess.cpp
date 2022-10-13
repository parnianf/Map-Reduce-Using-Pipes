#include "mapProcess.h"
#include <algorithm>
#include <sstream>
#include <dirent.h>
#include <string.h>
using namespace std;

#define TESTCASES_PATH "./testcases/"

MapProcess :: MapProcess (int pipeFd, string namePipe){
  namedPipeName = namePipe;
  char buff[PIPE_BUFFER_SIZE];
  if(read(pipeFd, buff, PIPE_BUFFER_SIZE)<0){
    cout<<"READ ERROR"<<endl;
  }
  close(pipeFd);
  fileName = buff;
}

void MapProcess::getFileContents(){
  string lineOfFile;
  string filePath = TESTCASES_PATH +fileName;
  ifstream file(filePath);
  getline(file, lineOfFile);
  replace(lineOfFile.begin(), lineOfFile.end(), ',', ' ');
  stringstream ss(lineOfFile);
  string word;
  while(getline(ss, word, ' ')){
    if(word != "")
      wordsInFile.push_back(word);
  }
}

void MapProcess::processMap(){
  for(int i=0; i < wordsInFile.size(); i++){
    wordCountMap.insert(pair<string, int>(wordsInFile[i], 0));
  }
  for(int i=0; i < wordsInFile.size(); i++){
    wordCountMap[wordsInFile[i]]++;
  }
}

void MapProcess::sendMapToReduce(){
  string sendString = "";
  for(auto word : wordCountMap){
    sendString += word.first;
    sendString += ":";
    sendString += to_string(word.second);
    sendString += "|";
  }
  string x = strtok((char*)fileName.c_str(),".");
  string namedPipeNameToOpen = namedPipeName + x;
  pid_t namedPipeFd = open(namedPipeNameToOpen.c_str(), O_WRONLY);
  if(write(namedPipeFd, sendString.c_str(), sendString.size()+1)<0){
      cout<<"error on writing in named pipe"<<endl;
  }

}
