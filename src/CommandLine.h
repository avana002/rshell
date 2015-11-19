#ifndef COMMANDLINE
#define COMMANDLINE

#include "CommandBlock.h"

void seperate(char* a);
bool should_run(bool fs, string c);

class CommandLine
{
    private:
    string r;  
    vector<CommandBlock*> c;
    bool prev_succ;
    
    public:
    CommandLine()
    :r(""), prev_succ(true){}
    
    CommandLine(char* array)
    :r(""), prev_succ(true)
    {
        //Removes characters after '#'
        for (unsigned i = 0; array[i] != '\0'; i++)
        {
            if (array[i] == '#')
            {
                array[i] = '\0';
                array[i + 1] = '\0';
            }
        }
        
        //Adds spaces around parentheses and connectors
        seperate(array);
        
        //Stores array as string in object
        r = string(array);
        
        //If no input, skips parsing
        if (r == "") return;
        
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
                //Creates new command block with correct connector
                CommandBlock* n = new CommandBlock();
                n->mod_con(q.front());
                q.pop();
                
                //If command block is enclosed in parentheses
                if(q.front() == "(")
                {
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
                
                //If not
                else
                {
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
        for(unsigned i = 0; i < c.size(); i++) { c.at(i)->parse(); }
    }
    
    //Prints command line
    void printself() { cout << "Command Line: " << r << endl; }
    
    //Prints child command blocks
    void printcb()
    {
        cout << "Command Blocks: ";
        for (unsigned i = 0; i < c.size(); i++) c.at(i)->printself();
        cout << endl;
    }
    
    //Prints child commands of child command blocks
    void printc()
    {
        cout << "Commands: ";
        for (unsigned i = 0; i < c.size(); i++) c.at(i)->printch();
        cout << endl;
    }
    
    //Runs child command blocks is applicable
    void run()
    {
        for (unsigned i = 0; i < c.size(); i++)
        {
            if (should_run(prev_succ, c.at(i)->get_conn()))
            {
                prev_succ = c.at(i)->run();
            }
        }
    }
    
    ~CommandLine() 
    { 
        for (unsigned i = 0; i < c.size(); i++) delete c.at(i); 
    }
};

#endif