#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "CommandBlock.cpp"
#include "CommandLine.h"

using namespace std;

//Checks if is a connector
bool is_conn(string s)
{
    if(s == ";" || s == "||" || s == "&&") return true;
    else return false;
}

//Checks if command is "exit"
bool is_exit(char* c)
{
    if (c[0] == 'e' && c[1] == 'x' && c[2] == 'i' && c[3] == 't') return true;
    else return false;
}

//Checks if conditions are right for execution
bool should_run(bool fs, string c)
{
    if (c == "" || c == ";" || (c == "&&" && fs) || (c == "||" && !fs)) return true;
    else return false;
}

//Forks and executes command and returns success state
bool run_comm(char** a)
{
    //Forks
    pid_t pid = fork();
            
    //Child process executes command
    if (pid == 0)
    {
        if (execvp(a[0], a) != 0) 
        perror("execvp");
        exit(1);
    }
    
    //Parent process waits for child process then returns success state
    else if (pid > 0)
    {    
        int i;
        waitpid(pid, &i, 0);
        if (i == 0) return true;
        else return false; 
    }
    
    //Failure
    else
    {
        cout << "Fork failed" << endl;
        exit(1);
    }            
}

//Adds spaces to facilitate seperation of tokens
void seperate(char* a)
{
    char n[100];
    int i, j;
    
    //Loops through original array and copies elements to new array
    for (i = 0, j = 0; a[i] != '\0'; i++)
    {
        //If element requires spaces
        if (a[i] == ';' || a[i] == '(' || a[i] == ')')
        {
            //Adds space before if not first element
            if(i != 0)
            {
                n[j] = ' ';
                j++;
            }
            
            //Adds element
            n[j] = a[i];
            j++;
            
            //Adds space after if not last element
            if(a[i + 1] != '\0')
            {
                n[j] = ' ';
                j++;
            }
        }
        
        //If element doesn't need spaces
        else
        {
            n[j] = a[i];
            j++;
        }
    }
    
    //Ends new array with null character
    n[j] = '\0';
    
    //Removes extra spaces at the end
    while(n[j - 1] == ' ')
    {
        j--;
        n[j] = '\0';
    }
    
    //Copies elements from new array back into original array
    for (i = 0; n[i] != '\0'; i++)
    {
        a[i] = n[i];
    }    
    
    //Ends original array with null character
    a[i] = '\0';    
   
    return;
}
    
//Main run function        
void run()
{
    while(true)
    {
        //Gets input
        char input[100];
        cout << "$ ";
        cin.getline(input, 100);
        
        //Constructs command line from input and runs it
        CommandLine cl(input);
        cl.run();
    }
}

int main()
{
    run();
    return 0;
}
