# rshell
Atticus VanArsdale

rshell is a command-line driven user interface based on bash. rshell works with most commands not explicitly built into bash. rshell functions as expected: it takes in a command line, formats the input into individual commands, then runs said commands using forking depending on conditionality. 

Design:
Command-line input is treated as a single object, which is then parsed into "Command blocks" based on precedence operators or connectors where applicable. These blocks are further parsed into either component commands or more command blocks. When the command line is run, it runs each of its component blocks based on the success of the previous one. Command blocks similarly run their component commands or blocks based on previous success. Special commands such as "exit" and "test" are identified when the command object is run, and treated differently than normal commands.

Known bugs:
-cannot handle certain connectors not seperated by spaces
-cannot handle comments without '#' padded by spaces
-cannot perform test with more than one space between brackets

 
