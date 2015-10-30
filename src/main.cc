#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

//Checks if command is "exit"
bool is_exit(char* c)
{
	if(c[0] == 'e' && c[1] == 'x' && c[2] == 'i' && c[3] == 't') return true;
	else return false;
}

//Checks if conditions are right for execution
bool should_run(bool fs, string c)
{
	if(c == "" || c == ";" || (c == "&&" && fs) || (c == "||" && !fs)) return true;
	else return false;
}

//Forks and executes command and returns success state
bool run_comm(char** a)
{
	pid_t pid = fork();
			
	if(pid == 0)
	{
		if(execvp(a[0],a) != 0) 
		perror("execvp");
		exit(1);
	}
	else if(pid > 0)
	{	
		int i;
		waitpid(pid,&i,0);
		if(i == 0) return true;
		else return false; 
	}
	else
	{
		cout << "Fork failed" << endl;
		exit(1);
	}			
}

//Constructs command from tokens and returns connector
string make_comm(queue<char*> &q, char** cm)
{
	bool again = false;
	string cond = "";
	int size = 0;

	//Adds tokens to command
	do
	{
		char* a = q.front();
		q.pop();
		
		//Ignores everything after '#'
		if(a[0] == '#')	
		{
			while(!q.empty()) q.pop();
			again = false;
		}
		
		//Checks for connectors
		else if(a[0] == '|' && a[1] == '|')
		{
			cond = "||";
			again = false;
		}
		else if(a[0] == '&' && a[1] == '&')
		{
			cond = "&&";
			again = false;
		}
		else if(a[0] == ';')
		{
			cond = ";";
			again = false;
		}
		
		//Adds tokens to command being constructed
		else
		{
			cm[size] = a;
			size++;
			again = true;
		}

		if(q.empty()) again = false;
	
	}while(again);
	
	//Terminates command with NULL
	cm[size] = NULL;

	return cond;
}	

//Main shell function
void run()
{
	//Runs until "exit"
	while(true)
	{
		char line[100];
		char* word;
		queue<char*> q;		
		bool prev_succ = true;
	
		//Prints command line
		cout << "$ ";
		
		//Puts input into array
		cin.getline(line,100);	
		
		//Seperates array into tokens
		word = strtok(line," ");
		while(word != NULL)
		{
			//Puts all tokens into a queue
			q.push(word);
			word = strtok(NULL, " ");
		}

		//Runs through all tokens in queue		
		while(!q.empty())	
		{	
			//Constructs command from tokens
			char* comm[100];
			string cond = make_comm(q,comm);
			
			//Executes commands if conditions met
			if(should_run(prev_succ, cond))
			{
				if(is_exit(comm[0]))			
				{
					exit(0);
				}		
				else
				{
					prev_succ = run_comm(comm);
				}
			}
		}
	}
}	

int main()
{
	run();

	return 0;
}

