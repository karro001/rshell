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
1. Rshell cannot utilize the command "cd"

2. Rshell does not support precedence operators

3. The command echo will be treated as a valid command even with no accompanying message i.e.
  ```
  $ echo
  ```
  * this will print out a blank into the terminal

4. While you can chain commands using connectors, you cannot mix different connectors in the same command line i.e.
  ```
  $ echo hello && echo world || echo !!!
  ```
  * this command will execute but will print "hello" then " world || echo !!!" to the terminal
  
  
#How to run
```
$ git clone https://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw2
$ make
$ bin/rshell
```
