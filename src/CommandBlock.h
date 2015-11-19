#ifndef COMMANDBLOCK
#define COMMANDBLOCK

#include <string>
#include <queue>
#include <sstream>
#include <vector>

#include "Command.h"

using namespace std;

class CommandBlock
{
    private:
    vector<CommandBlock*> c;
    bool prev_succ;
    
    protected:
    string r;
    string con;
    bool iscom;
    
    public:
    CommandBlock();
    ~CommandBlock();
    void add(string);
    void mod_con(string);
    string get_conn();
    void parse();
    bool is_com();
    void printself();
    void printch();
    bool run();
};

#endif