#include "reduceProcess.h"
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <map>
#include <algorithm>
using namespace std;

#define PIPE_BUFFER_SIZE 8192
#define TESTCASES_PATH "./testcases"

ReduceProcess::ReduceProcess(int pipeWriteFd, string pipeName){
    pipeWriteEndFd = pipeWriteFd;
    namedPipeName = pipeName;
    result = "";
    getTestcasesFiles();
}

void ReduceProcess::getTestcasesFiles(){
    DIR *dir;
    struct dirent *diread;
    if((dir = opendir(TESTCASES_PATH)) != nullptr) {
        while((diread = readdir(dir)) != nullptr) {
            int pos = string(diread->d_name).find(".");
            string fileExtension = string(diread->d_name).substr(pos + 1);
            if(fileExtension == "csv"){
                string fname = diread->d_name;
                files.push_back(fname);
            }
        }
        closedir(dir);
    }
    else{
        perror ("opendir");
    }
}

void ReduceProcess::readMapData(){
    for(int i=0;i<files.size();i++){
        char buff[PIPE_BUFFER_SIZE];
        string x = strtok((char*)files[i].c_str(),".");
        string namedPipeNameToOpen = namedPipeName + x;
        pid_t namedPipeFd = open(namedPipeNameToOpen.c_str(), O_RDONLY);
        if(read(namedPipeFd, buff, PIPE_BUFFER_SIZE)<0){
            cout<<"error on reading from map in process reduce"<<endl;
            return;
        }
        string word, frequency, mapData = buff;
        stringstream ss(mapData);
        while(getline(ss, word, ':')){
            getline(ss, frequency, '|');
            umap.insert(pair<string, int>(word, atoi(frequency.c_str())));
        }
    }
}

void ReduceProcess::reduceMapData(){
    for(auto wordFreq: umap){
        if (wordCountMap.find(wordFreq.first) == wordCountMap.end()){
            wordCountMap.insert(pair<string, int> (wordFreq.first, wordFreq.second));
        }
        else{
            wordCountMap[wordFreq.first] += wordFreq.second;
        }
    }
}

void ReduceProcess::encodeResult(){
    for(auto mapReduced : wordCountMap){
        result += mapReduced.first;
        result += ",";
        result += to_string(mapReduced.second);
        result += "\n";
    }
}

void ReduceProcess::sendResultToMainProcess(){
    char* buff = (char*)result.c_str();
    if(write(pipeWriteEndFd, buff, strlen(buff)+1)<0){
        cout<<"error on writing in sending data to map in reduced"<<endl;
    }
    close(pipeWriteEndFd);
}
