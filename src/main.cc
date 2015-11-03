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

void seperate(char* a)
{
	char n[100];
	int i, j;
	for(i = 0, j = 0; a[i] != '\0'; i++,j++)
	{
		if(a[i] == ';')
		{
			n[j] = ' ';
			j++;
			n[j] = ';';
			j++;
			n[j] = ' ';
		}
		else
		{
			n[j] = a[i];
		}
	}
	n[j] = '\0';
	for(i = 0; n[i] != '\0'; i++)
	{
		a[i] = n[i];
	}	
	a[i] = '\0';	
	return;
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
		
		seperate(line);

		//Seperates array into tokens
		word = strtok(line," ");
		while(word != NULL)
		{
			//Puts all tokens into a queue
			q.push(word);
			word = strtok(NULL, " ");
		}

		queue<string> conn;
		int num = 1;

		//Runs through all tokens in queue		
		while(!q.empty())	
		{	
			//Constructs command from tokens
			char* comm[100];
			//string cond = make_comm(q,comm);
			conn.push(make_comm(q,comm));		

			//int num = 1;
	
			//Executes commands if conditions met
			if(num == 1 || should_run(prev_succ, conn.front()))
			{
				if(is_exit(comm[0]))			
				{
					exit(0);
				}		
				else
				{
					prev_succ = run_comm(comm);
				}
				//num++;
			}
			if(num != 1)conn.pop();
			num++;
		}
	}
}	

int main()
{
	run();
//	char a[100];
//	a[0] = 'l';
//	a[1] = ';';
//	a[2] = 's';
//	a[3] = '\0';
//	cout << a << endl;
//	seperate(a);
//	cout << a << endl;

	return 0;
}










