#include "Command.h"
#include "CommandBlock.h"

bool is_conn(string);
bool should_run(bool, string);
bool is_exit(char*);
bool run_comm(char**);

CommandBlock::CommandBlock()
:prev_succ(true), r(""), con(";"), iscom(false) {}

//Adds additional tokens to command block
void CommandBlock::add(string s)
{
	if (r != "") r.append(" ");
	r.append(s);
}

//Changes connector
void CommandBlock::mod_con(string n) { con = n; }

//Parses command block into commands and command blocks
void CommandBlock::parse()
{
    //Puts tokens in string into queue
    stringstream s;
    s.str(r);
    queue<string> q;
   
    q.push(";");
    while(!s.eof())
    {
        string t;
        s >> t;
        q.push(t);
    }
        
    //Constructs command blocks from queue
    while(!q.empty())
    {
        if(is_conn(q.front()))
        {
            string conn = q.front();
            q.pop();
            CommandBlock* n;
                
            //If a command block in parentheses 
            if(q.front() == "(")
            {
                n = new CommandBlock();
                n->mod_con(conn);
                    
                int open = 1;
                int closed = 0;
                q.pop();
                    
                while(!q.empty() && open != closed)
                {
                    if(q.front() == ")") closed++;
                    if(open != closed) n->add(q.front());
                    q.pop();
                }
            }
                
            //If a command
            else
            {
                n = new Command();
                n->mod_con(conn);
                while(!q.empty() && !is_conn(q.front()))
                {
                    n->add(q.front());
                    q.pop();
                }
            }
                
            //Adds command block to vector in object
            c.push_back(n);
        }
    }
    
    //Parses child command blocks
    for(unsigned i = 0; i < c.size(); i++)
    {
        if(!c.at(i)->is_com()) c.at(i)->parse();
    }
}
    
//Returns if is a command
bool CommandBlock::is_com() { return iscom; }

//Prints command block
void CommandBlock::printself()
{
    cout << con << ' ' << '(' <<  ' ' << r << ' ' << ')' << ' ';
}

//Prints child commands and command blocks
void CommandBlock::printch()
{
    cout << con << ' ' << '(' << ' ';
    for (unsigned i = 0; i < c.size(); i++)
    {
        if (c.at(i)->is_com()) c.at(i)->printself();
        else c.at(i)->printch();
    }
    cout << ')' << ' ';
}

//Returns connector
string CommandBlock::get_conn() { return con; }

//Returns if command is test
bool is_test(string c)
{
    if (c[0] == 't' && c[1] == 'e' && c[2] == 's' && c[3] == 't') return true;
    else return false;
}

//Runs the test command
bool test(string s)
{
    //Determines flag and filename
    string flag = "-e";
    stringstream ss;
    ss.str(s);
    string file = "";
    
    while(!ss.eof())
    {
        string t;
        ss >> t;
        if (t == "-e" || t == "-f" || t == "-d") flag = t;
        else file = t;
    }
    
    //Gets status of file
    struct stat buf;
    
    //If file doesn't exist
    if(stat(file.c_str(),&buf) == -1) return false;
    
    //If file does exist
    else
    {
        //If exists
        if(flag == "-e") return true;
        
        //If exists and is regular file
        else if(flag == "-f" && S_ISREG(buf.st_mode)) return true;
        
        //If exists and is directory
        else if(flag == "-d" && S_ISDIR(buf.st_mode)) return true;
        
        //If exists but is not desired type
        else return false;
    }
}

//Runs command block
bool CommandBlock::run()
{
    //If just a command
    if(iscom)
    {
        //If command is test
        if(r.at(0) == '[' && r.at(r.size() - 1) == ']')
        {
            r.erase(0,1);
            r.erase(r.size() - 1, 1);
            return test(r);
        }
        else if(is_test(r))
        {
            r.erase(0,4);
            return test(r);
        }
        
        //If not test
        else
        {
            //Creates 2D array from string
            stringstream s;
            s.str(r);
            char* a[100];
            int j = 0;
            
            while(!s.eof())
            {
                string t;
                s >> t;
                a[j] = new char[100];
                strcpy(a[j],t.c_str());
                j++;
            }
            
            //Ends array with NULL
            a[j] = NULL;
            
            //If command is exit
            if(is_exit(a[0])) exit(0);
            
            //If not, runs command and returns success state
            return run_comm(a);
        }
    }
    
    //If a command block
    else
    {
        //Runs child command blocks and commands if applicable
        for (unsigned i = 0; i < c.size(); i++)
        {
            if (should_run(prev_succ, c.at(i)->get_conn()))
            {
                prev_succ = c.at(i)->run();
            }
        }
    }
    
    //Returns success state of command block
    return prev_succ;
}

CommandBlock::~CommandBlock()
{
    for (unsigned i = 0; i < c.size(); i++) delete c.at(i);
}
