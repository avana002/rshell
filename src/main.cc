#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
#include <sys/wait.h>

using namespace std;

bool is_exit(char* c)
{
	if(c[0] == 'e' && c[1] == 'x' && c[2] == 'i' && c[3] == 't') return true;
	else return false;
}

int main()
{
	while(true)
	{
		char str[100];
		char* point;
		queue<char*> q;		
		bool prev_succ = true;
	
		cout << "$ ";
		cin.getline(str,100);	
		point = strtok(str," ");

		while(point != NULL)
		{
			q.push(point);
			point = strtok(NULL, " ");
		}
		while(!q.empty())	
		{
			char* comm[100];
			int size = 0;
			bool again = true;
			string cond = "";
			while(again)
			{
				char* a = q.front();
				q.pop();
				if(a[0] == '#')	
				{
					again = false;
				}
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
				else
				{
					comm[size] = a;
					size++;
				}

				if(q.empty()) again = false;
				
			}
			comm[size] = NULL;
			if(is_exit(comm[0])) exit(0);
			pid_t pid = fork();
			
			if(pid == 0)
			{
				if(cond == "" || cond == ";" || (cond == "&&" && prev_succ) || (cond == "||" && !prev_succ))
				{
					if(execvp(comm[0],comm) != 0) 
					perror("execvp");
					exit(1);
				}
				else exit(2);
			}
			else if(pid > 0)
			{	
				int i;

				waitpid(pid,&i,0);
				if(i == 1) prev_succ = false;
				else if(i == 0) prev_succ = true;
				else{} 
			}
			else
			{
				cout << "Fork failed" << endl;
				exit(1);
			}
		}
		
	}
	return 0;
}












