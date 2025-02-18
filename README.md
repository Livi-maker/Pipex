Pipex reproduce the behaviour of the terminal regarding the pipe (|) command. 

It takes as input a file, at least two command and an outpul file -> ./pipex file1 cmd1 cm2 file2

It reads from the first file and write on the second one, redirecting the standard input and output

It works exactly like this command line: < file1 cmd1 | cmd2 > file2

It is able to handle more than two instructions as well as the here_doc function. 

In this case, the input format will be -> here_doc "delimiter" cmd1 cmd2 file

It will read from the standard input untill a delimiter word is used and write on the file provided.

Exactly as the command line cmd1 << delimiter | cmd2 >> file
