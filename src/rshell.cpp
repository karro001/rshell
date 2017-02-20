#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void cmd(const string &line,string delim);
int exec(const string &line);

int main()
{

  
  while (1)
  {
    cout << getcwd(NULL, 0) << " $ " << flush; //couts the current working directory
    
    string line;
    string temp;
    getline(cin, line);
    
    if(line.find("#") != string::npos)
    {
      if(line.find("#") != 0){
        line = line.substr(0,line.find("#"));
      }
      else{
        line.clear();
      }
    }
    if(line == "exit")
      return 0;
      
    else if(line.find("&&") != string::npos){
      cmd(line,"&&");
    }
    else if(line.find("||") != string::npos){
      cmd(line,"||");
    }
    else if(line.find(";") != string::npos){
      cmd(line,";");
    }
    else if(line.size() != 0)
      exec(line);
        
  }
  return 0;
}

void cmd(const string &line,string delim){
  
    // const char *line1 = line.c_str();
    int success = 0;
    int counter = 0;
    string cpy = line;
    string temp = cpy.substr(0,cpy.find(delim));
    while(cpy.find(delim) != string::npos || counter < 2){
      // int child = fork();
      // if(child < 0){
      //   perror("Fork failed");
      //   exit(1);
      // }
      // else if(child == 0){
      success = exec(temp);
      // cout << "SUCCESS" << success << endl;
      //   exit(0);
      // }
      // else{
      //   if ( waitpid( child, 0, 0 ) < 0 ){
      //     perror("Parent wait failed");
      //     exit(1);
      //   }
      // }
      if(cpy.find(delim) != string::npos){
        temp = cpy.substr(cpy.find(delim)+delim.size(),cpy.size());
        cpy = temp;
        temp.clear();
      }
      if(delim == "&&" && success == 0){
        if(cpy.find(delim) != string::npos){
          temp = cpy.substr(0,cpy.find(delim));
        }
        else{
          temp = cpy.substr(0,cpy.size());
          counter++;
        }
      }
      else if(delim == "&&" && success == -1){
        return;
      }
      if(delim == ";"){
        if(cpy.find(delim) != string::npos){
          temp = cpy.substr(0,cpy.find(delim));
        }
        else{
          temp = cpy.substr(0,cpy.size());
          counter++;
        }
      }
      if(delim == "||" && success == -1){
        if(cpy.find(delim) != string::npos){
          temp = cpy.substr(0,cpy.find(delim));
        }
        else{
          temp = cpy.substr(0,cpy.size());
          counter++;
        }
      }
      else if(delim == "||" && success != -1){
        temp.clear();
        return;
      }
      // else if(delim == ";"){
      //   if(cpy.find(delim) != string::npos)
      //     temp = cpy.substr(0,cpy.find(delim));
        // else
        //   temp = cpy.substr(0,cpy.size());
      // }
  }
      
}
int exec(const string &line){
    

    const char* temp = line.c_str();
    char* lineCopy = (char*)temp;
    vector<char*> args;
    char* prog = strtok(lineCopy, " " );
    string test = prog;
    if(test == "exit"){
      exit(0);
    }
    char* tmp = prog;
    pid_t child = fork();
    if(child < 0){
      perror("FORK FAILED");
      exit(1);
    }
    else if(child == 0){
      while ( tmp != NULL )
      {
          args.push_back( tmp );
          tmp = strtok( NULL, " " );
      }
      char** argv = new char*[args.size()+1];
      
      for ( unsigned k = 0; k < args.size(); k++ )
        argv[k] = args[k];
      
      argv[args.size()] = NULL;
      if (execvp(prog, argv) < 0){
          // kill(child, SIGKILL);
          // kill(child, SIGTERM);
          perror("Failed to execute");
          exit(1);
  
      }
      else{
        // kill(child, SIGKILL);
        // kill(child, SIGTERM);
        exit(2);
      }
    }
    else{
        // if ( waitpid( child, 0, 0 ) < 0 ){
          // perror("Parent wait failed");
        //   exit(1);
        // }
        int status;
        waitpid(child, &status, WUNTRACED|WCONTINUED);
        
        // cout << WEXITSTATUS(status) << endl;
        if(WEXITSTATUS(status) == 0){
          return 0;
        }
        else{
           kill(child,SIGUSR1);
          return -1;
        }
        // if(status != 0)
        //   return 0;
        // else
        //   return -1;
        // if ( WIFEXITED(status) == 0)
        //   return 0;
        // else
        //   return -1;
    }
    return 0;
}
