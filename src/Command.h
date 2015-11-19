#ifndef COMMAND
#define COMMAND

#include "CommandBlock.h"

class Command : public CommandBlock
{
    public:
    Command()
    {
        r = "";
        con = ";";
        iscom = true;
    }
};

#endif