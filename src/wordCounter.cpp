#include "wordCounter.h"
#include <iostream>
#include <string.h>
#include <string>
#include <wait.h>
#include <dirent.h>
const char* namedPipeFifo = "./namedPipe"; 

using namespace std;

#define PIPE_BUFFER_SIZE 8192
#define MAP_EXEC_PATH "./mapProcess"
#define REDUCE_EXEC_PATH "./reduceProcess"
#define OUTPUT_FILE_NAME "output.csv"
#define TESTCASES_PATH "./testcases"

WordCounter :: WordCounter(){
    getTestcasesFiles();
}

void WordCounter:: getTestcasesFiles(){
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

void WordCounter::forkReduce(){
    for(int i = 0; i < files.size(); i++){
        string x = strtok((char*)files[i].c_str(),".");
        string namedPipeName = namedPipeFifo + x;
        mkfifo(namedPipeName.c_str(), 0666);
    }

    pid_t pid = fork();
    if(pid < 0)
        cerr<<"unable to fork reduce process!"<<endl;
    else if(pid == 0){
        close(mapPipes[mapPipes.size()-1][READ]);
        char * argv[3];
        argv[0] = (char*) REDUCE_EXEC_PATH;
        argv[1] = (char*) to_string(mapPipes[mapPipes.size()-1][WRITE]).c_str();
        argv[2] = (char*) namedPipeFifo;
        argv[3] = NULL;
        execv(argv[0], argv);
    }
    else if(pid > 0){
        waitpid(pid, NULL, 0);
        close(mapPipes[mapPipes.size()-1][WRITE]);
        reducer = pid;
    }

    char buff[PIPE_BUFFER_SIZE];
    if(read(mapPipes[mapPipes.size()-1][READ], buff, PIPE_BUFFER_SIZE)<0){
        cout<<"read error from reduce in main process"<<endl;
    }
    int outputFileFd = open(OUTPUT_FILE_NAME, O_RDWR | O_CREAT, 0644);
    write(outputFileFd, buff, strlen(buff));
    close(outputFileFd);
}

void WordCounter::forkMaps(){

    for(int i = 0 ; i < files.size()+1 ; i++){
        int fd[2];
        if(pipe(fd) < 0){
            cerr << "create unnamed pipe of map failed"<<endl ;
            return;
        }
        vector<int> fds;
        fds.push_back(fd[0]);
        fds.push_back(fd[1]);
        mapPipes.push_back(fds);
    }

    for(int i = 0; i < files.size() ; i++){
        pid_t pid = fork();
        if(pid < 0){
            cerr << "error in forking map in main process" << endl;
        }
        else if(pid == 0){
            close(mapPipes[i][WRITE]);
            char * argv[3];
            argv[0] = (char*) MAP_EXEC_PATH;
            argv[1] = (char*) to_string(mapPipes[i][READ]).c_str();
            argv[2] = (char*) namedPipeFifo;
            argv[3] = NULL;
            execv(argv[0], argv);
        }
        else{
            close(mapPipes[i][READ]);
            char* buff = (char*) files[i].c_str();
            if(write(mapPipes[i][WRITE], buff, strlen(buff)+1)<0){
                cout<<"error on writing in fork map function"<<endl;
            }
            close(mapPipes[i][WRITE]);
        }
    }
}
