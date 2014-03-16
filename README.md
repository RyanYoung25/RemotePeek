RemotePeek
==========

A C program that let's you take a look at the important information of the computer running it from any connected web browser. Displays
uname -a; date; ss -s; df; who -a; top -b

To compile it run:

gcc -o remotePeek socket.c

Then to run it: 

./remotePeek 

