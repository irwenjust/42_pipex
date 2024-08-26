# 42_pipex   
Practice process and basic redirect project.   
Function introduces video: https://www.youtube.com/watch?v=EqndHT606Tw&t=1s    
One more video list recommend: https://www.youtube.com/watch?v=6xbLgZpOBi8&t=920s   
   
The grade is 125/100.   

## **Some parts of work**  
Mandatory part:  
1) Input check    
2) Initial data   
3) Pipe and fork   
4) Check path    
5) Execute command


Bonus part:   
1) Handle multiple pipe   
2) here_doc

## **Compilation** 
To compile this project you should run `make` in the terminal.  
To compile the bonus part need to run `make bonus`.  
To run the mandatory program needs to follow this:  
```sh  
$ ./pipex file1 cmd1 cmd2 file2
```  
For example: ` ./pipex infile "ls -l" "wc -l" outfile`   

For bonus program:  
If run it without here_doc:  
```sh  
$ ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2  
```  
For example: ` ./pipex infile "cat" "ls -l" "wc -l" outfile`  

If run it with here_doc:  
```sh  
$  ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file  
```  
For example: ` ./pipex here_doc "EOF" "cat" "ls -l" "wc -l" outfile`  

## **Some tips**   
A good test tool recommended: https://github.com/Jarnomer/pipex-error-tester?tab=readme-ov-file   
(This tester's message is based on bash, if you use zsh the program name's position will be different. That could be fine.)   

The evaluation stage could be a challenge. The boundary between A and B could be flexible as the subject didn't mention. So just discuss with your evaluator! (possible handle case: no path(redirect), special sign in command(like single quote in "" or sign with \ or $ sign etc). For example: ./pipex "grep 'Error:' logfile.txt" "awk '{print $2}'").
