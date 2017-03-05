# RShell 
A user implemented shell program for CS100

#Introduction
This program called Rshell is a command shell written in C++. It functions as a terminal that will take in simple commands from the user and run them. A command prompt will be printed first then the user is able to enter their command. The command will be read in one line and be executed.

#Examples of Program Usage
The program is able to excute most commands available in a terminal such as:
```
ls -l

echo Hello World!

ps

cal

date

mkdir Directory_Name

rm -r Directory_Name
```
In addition commands can be chained together using connectors:
* &&
* ||
* ;
* #
```
echo Hello; echo world!

ls && mkdir Test_Folder && echo made folder && ls

mkdir || cat nonexistantfile || echo First two commands failed
```

#Bugs & Limitations
1. When using the test command, paths must start with a backslash i.e.
  ```
  test -e /test/file/path
  ```
  will work but,
  ```
  test -e test/file/path
  ```
  will not execute

2. The command echo will be treated as a valid command even with no accompanying message i.e.
  ```
  $ echo
  ```
  * this will print out a blank into the terminal
  
3. Precedence operators will only work when at the very front of the command, of if it encapsulates the entire command i.e
  ```
  (echo hi && failcommand) || echo hello
  (echo yes && ls || echo no && echo hello)
  ```
  * these command will run normally however,
  
  '''
  failcommand || (echo hello && ls)
  (echo hi && echo hello) || (echo yes && echo no)
  ```
  * thse command with produce and error or the wrong output
#How to run
```
$ git clone https://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw3
$ make
$ bin/rshell
```
