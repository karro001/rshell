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
bool balancedPrecedence(string line);
void findDelim(string &cpy, string &delim);
void cmd(const string &line,string delim, int &success);
int exec(const string &line);
int Test(const string line);

int main()
{
  string delim;
  int success = 0;
  while (1)
  {
    input:
    cout << getcwd(NULL, 0) << " $ " << flush; //couts the current working directory
    
    string line;
    string temp;
    getline(cin, line);
    findDelim(line,delim);
    // delim.clear();
  
    
    begin:
    if(line.find("#") != string::npos)
    {
      if(line.find("#") == 0){
        goto input;
      }
      else{
        line = line.substr(0,line.find("#"));
      }
    }
    if(line == "exit")
      return 0;
    
    if(delim == "("){
      if(!balancedPrecedence(line)) 
        goto input;
      if(balancedPrecedence(line)){
        temp = line.substr(line.find_last_of("(") + 1, line.find(")") - 1);
        findDelim(temp,delim);
        // cout << "TEMP: " << temp << endl;
        if(delim.size() == 0)
          exec(temp);
        else{
          cmd(temp,delim,success);
        }
        
        
        // temp = line.substr(line.find(")") + 1, line.size());
        temp = line.erase(line.find_last_of("("), line.find(")")+1);
        line = temp;
        // cout << "TEMP2: " << temp << endl; //&& echo hi
        again: 
        findDelim(line,delim);
        if(delim.size() != 0)
        {
          // cout << success << endl;
          temp = line.substr(line.find(delim) + delim.size(), line.size());
          line = temp; //echo hi, with delim = &&, success != 0
          // cout << "TEMP: " << temp << endl;
          if(delim == "&&" && success == 0)
            goto begin;
          else if(delim == "&&" && success != 0)
            goto again;
          else if(delim == "||" && success == 0)
            goto again;
          else if(delim == "||" && success != 0)
            goto begin;
          else
            goto begin;
        }
        else{
          goto input;
        }
      }
    }
    else{
      if(delim.size() != 0)
        cmd(line,delim,success);
      else if(line.size() != 0){
        // cout << "TEMP: " << temp << endl;
        // cout << "Entered exec" << endl << "Delim: " << delim << endl;
        exec(line);
      }
    }
  }
  return 0;
}
void cmd(const string &line,string delim, int& success){
    //cout << "LINE: " << line << endl;
    string cpy = line;
    string tempDelim = delim;
    string copyDelim = delim;
    
    findDelim(cpy,copyDelim);
    if(copyDelim.size() == 0){
      exec(line);
      return;
    }
    copyDelim = delim;
    string temp = cpy.substr(0,cpy.find(delim));
    while(1){
      
      tempDelim = copyDelim;
      success = exec(temp);
      if(temp == cpy)
        return;
      if(cpy.find(tempDelim) != string::npos){
        temp = cpy.substr(cpy.find(tempDelim)+tempDelim.size(),cpy.size());
        cpy = temp;
        temp.clear();                              
      }
      if(tempDelim == "&&" && success == 0){
        findDelim(cpy,copyDelim);
        if(cpy.find(copyDelim) != string::npos && copyDelim.size() != 0){
          temp = cpy.substr(0,cpy.find(copyDelim));
        }
        else{
          temp = cpy;
        }
      }
      else if(tempDelim == "&&" && success == -1){
        copyDelim = tempDelim;
        while(copyDelim == "&&" && copyDelim.size() != 0){
          findDelim(cpy,copyDelim);
          temp = cpy.substr(cpy.find(copyDelim) + copyDelim.size(),cpy.size());
          cpy = temp;
        }
        if(copyDelim.size() == 0){
          return;
        }
      }
      if(tempDelim == ";"){
        findDelim(cpy,copyDelim);
        if(cpy.find(copyDelim) != string::npos && copyDelim.size() != 0){
          temp = cpy.substr(0,cpy.find(copyDelim));
        }
        else{
          temp = cpy;
        }
      }
      if(tempDelim == "||" && success == 0){
        findDelim(cpy,copyDelim);
        if(cpy.find(copyDelim) != string::npos && copyDelim.size() != 0){
          temp = cpy.substr(cpy.find(copyDelim) + copyDelim.size(),cpy.size());
          cpy = temp;
        }
        else{
          return;
        }
      }
      else if(tempDelim == "||" && success == -1){
        findDelim(cpy,copyDelim);
        // cout << "CPY: " << cpy << endl;
        if(cpy.find(copyDelim) != string::npos && copyDelim.size() != 0){
          temp = cpy.substr(0,cpy.find(copyDelim));
        }
        else{
          temp = cpy;
        }
      }
      if(tempDelim == "("){
        
        temp = cpy.substr(cpy.find_last_of("(")+1, cpy.find(")") - 1);
        
        
        
        
  
        findDelim(cpy,copyDelim);
        if(cpy.find(copyDelim) != string::npos && copyDelim.size() != 0){
          temp = cpy.substr(0,cpy.find(copyDelim));
        }
      }
    }
}
int exec(const string &line){
    //cout << "Line: " << line << endl;
    if((line.find("test") == 0 || line.find("[") == 0) || (line.find("test") == 1 || line.find("[") == 1))
    {
      if((line.find("test") != string::npos || line.find("[ ") != string::npos) && line.find("/") != string::npos){
          // brackets = true;
          // if(balancedPrecedence(line))
          //   return -1;
          if(Test(line) == 0)
            return 0;
          else
            return -1;
      }
      else if((line.find("test") != string::npos && line.find("/") == string::npos) || (line.find("[") != string::npos && line.find("/") == string::npos)){
        cout << "Failed to execute: No such file or directory" << endl;
        return -1;
      }
    }
    const char* temp = line.c_str();
    char* lineCopy = (char*)temp;
    vector<char*> args;
    char* prog = strtok(lineCopy, " " );
    string test = prog;
    // cout << "TEST: " << test << endl;
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
          perror("Failed to execute");
          exit(1);
  
      }
      else{
        exit(2);
      }
    }
    else{
        int status;
        waitpid(child, &status, WUNTRACED|WCONTINUED);
        
        if(WEXITSTATUS(status) == 0){
          return 0;
        }
        else{
          kill(child,SIGUSR1);
          return -1;
        }
    }
    exit(1);
    return 0;
}
void findDelim(string &cpy, string &delim){
      unsigned pos = 4096;
      // cout << cpy << endl;
      delim.clear();
      if(cpy.find("&&") != string::npos){
        // cout << "ENTERED: &&" << endl;
        delim = "&&";
        pos = cpy.find("&&");
      }
      if(cpy.find("||") != string::npos && cpy.find("||") < pos){
        // cout << "ENTERED: ||" << endl;
        delim = "||";
        pos = cpy.find("||");
        // cout << pos << endl;
      }
      if(cpy.find(";") != string::npos && cpy.find(";") < pos){
        // cout << "ENTERED: ;" << endl;
        delim = ";";
        pos = cpy.find(";");
      }
      if(cpy.find("(") != string::npos && cpy.find("(") < pos){
        // cout << "ENTERED: ;" << endl;
        //if(balancedPrecedence(cpy)){
          delim = "(";
          pos = cpy.find("(");
        //}
      }
}
bool balancedPrecedence(string line)
{
    int par_count = 0;
    int brac_count = 0;
    for(unsigned i = 0; i < line.size(); ++i)
    {
        if(line.at(i) == '(')
            ++par_count;
        else if(line.at(i) == ')')
            --par_count;
        else if(line.at(i) == '[')
            ++brac_count;
        else if(line.at(i) == ']')
            --brac_count;
    }
    if(par_count == 0 && brac_count == 0)
        return true;
    else{
      if(par_count != 0 && brac_count != 0){
        cout << "Unbalanced number of parentheses or brackets" << endl;
        return false;
      }
      else if(par_count != 0){
        cout << "Unbalanced number of parentheses" << endl;
        return false;
      }
      else{
        cout << "Unbalanced number of brackets" << endl;
        return false;
      }
    }
}

int Test(const string line)
{
    string copy = line;
    string flag;
    string temp;
    string delim;
    int success;
    int flagtype = 1; // 1 = -e, 2 = -d, 3 = -f
        
    if(copy.find("test") != string::npos){
        // cout << "COPY1: " << copy << endl; 
        // cout << "COPY1: " << copy << endl;
        if(copy.find('-') != string::npos)
          flag = copy.substr(copy.find("-"),copy.find("-") +1);
        // cout << "FLAG: " << flag << endl;
        if(copy.find("/") != string::npos)
          copy = copy.substr(copy.find("/") + 1,copy.size());
        if(copy.find(' ')){
          copy = copy.substr(0,copy.find(' '));
          // cout << "COPY1: " << copy << endl;
          // temp = copy.substr(0, copy.find(' '));
          // copy = copy.substr(copy.find(' ') + 1, copy.size());
          // findDelim(copy,delim);
          // cout << "COPY2: " << copy << endl;
          // if(delim.size() != 0)
          //   copy = copy.substr(copy.find(delim) + delim.size(), copy.size());
          // cout << "COPY3: " << copy << endl;
        }
    }
    else if(copy.find("[ ") != string::npos){
        if(copy.find('-') != string::npos)
          flag = copy.substr(copy.find("-"),copy.find("-") +1);
        if(copy.find("/") != string::npos){
          copy = copy.substr(copy.find('/') + 1);
          copy.erase(copy.find(" ]"));
        }
        else
          return -1;
    }

    if(flag.find("-d") != string::npos)
        flagtype = 2;
    else if (flag.find("-f") != string::npos)
        flagtype = 3;
        
    struct stat buffer;
    vector<const char*> path;
    path.push_back(copy.c_str());
    
    if(stat(const_cast<char*>(path[0]), &buffer) < 0 && flagtype == 1){
        perror("Stat");
        cout << "(False)" << endl;
        success = -1;
        if(delim == "||" || delim == ";")
          cmd(copy,delim,success);
        return 0;
    }
      if(flagtype == 1){
          cout << "(True)" << endl;
          if(delim == "&&" || delim == ";")
            cmd(copy,delim,success);
          return 0;
      }   
      else if(flagtype == 3){//check if path leads to a file
          if(S_ISREG(buffer.st_mode))
              cout << "(TRUE)" << endl;
          else
              cout << "(FALSE)" << endl;
          return 0;
      }   
      else if(flagtype == 2){ // check if path leads to a directory
          if(S_ISDIR(buffer.st_mode))
              cout << "(TRUE)" << endl;
          else
              cout << "(FALSE)" << endl;
          return 0;
      }
      else{
          perror("Incorrect input for test");
          return -1;
      }
    
}