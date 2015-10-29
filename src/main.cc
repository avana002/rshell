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
	
		cout << "$ ";
		cin.getline(str,100);	
		point = strtok(str," ");

		while(point != NULL)			//fills queue with every word entered
		{
			q.push(point);
			point = strtok(NULL, " ");
		}
		//cout << "command recieved" << endl;
		while(!q.empty())			//seperates words into commands
		{
			char* comm[100];
			int size = 0;
			bool again = true;
			string cond = "";
			while(again)			//gets one word at a time
			{
				char* a = q.front();
				q.pop();
				if(a[0] == '#')		//if word is #, ignores rest
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
			//cout << "command constructed" << endl;
			pid_t pid = fork();
			
			if(pid == 0)					//child executes command
			{
				execvp(comm[0],comm);
			//	cout << "child runs" << endl;
			//	cout << comm[0] << endl;
				return 0;
			}
			else if(pid > 0)				//parent waits for child
			{	
			//	cout << "parent waits" << endl;
				wait(0);
			//	cout << "returned to parent" << endl;
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












