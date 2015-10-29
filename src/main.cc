#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int main()
{
	while(true)
	{
		char str[100];
		char* point;
		queue<char*> q;		
	
		cout << "$ ";
		cin.getline(str,100);	
		point = strtok(str,".");

		while(point != NULL)
		{
			q.push(point);
			point = strtok(NULL, " ");
		}
		
	}
	return 0;
}
