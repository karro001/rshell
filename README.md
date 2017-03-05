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
$ echo Hello; echo world!

$ ls && mkdir Test_Folder && echo made folder && ls

$ mkdir || cat nonexistantfile || echo First two commands failed
```

#Bugs & Limitations
1. When using the test command, paths must start with a backslash i.e.
  ```
  $ test -e /test/file/path
  ```
  will work but,
  ```
  $ test -e test/file/path
  ```
  will not execute

2. When using the test command, there is an issue with concatenating its string i.e.
  ```
  $ test -e /bin echo hi && echo hello
  $ [ -e /bin ] echo hi && echo hello
  ```
  * both of these commands will run normally since our user implemented test truncates
      1. anything after the space after the end of the path up til the next connector when using "test"
      2. anything after the ending bracket up til the next connector when using brackets

3. Connecters must be written correctly such as: "&&", "||", ";" otherwise is will be treated as an input into aa command i.e
  ```
  $ echo hi & ls && echo hello
  ```
  * this will print out "hi & ls" then the next correct connector is reached and the command proceeds as normal
  ```
  $ ls & echo hi && echo hello
  ```
  * here ls will try to display the contents of directories with the names "&", "echo", and "hi" up until the next correct connector where the command proceeds normally again
  
4. Precedence operators will only work when at the very front of the command, of if it encapsulates the entire command however nested parentheses will cause an error i.e
  ```
  $ (echo hi && failcommand) || echo hello
  $ (echo yes && ls || echo no && echo hello)
  ```
  * these commands will run normally, however
  
  ```
  $ failcommand || (echo hello && ls)
  $ (echo hi && echo hello) || (echo yes && echo no)
  $ ((echo hi && echo hello) || ls) && ls
  ```
  * these commands will produce an error or the wrong output
  * In addition the parentheses cannot be used anywhere but for declaring precedence i.e.
  ```
  $ echo (); echo (hello); echo hello(); echo )(
  ```
      * these commands will produce errors
  
#How to run
```
$ git clone https://github.com/yourusername/rshell.git
$ cd rshell
$ git checkout hw3
$ make
$ bin/rshell
```
