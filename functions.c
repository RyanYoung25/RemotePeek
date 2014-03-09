/* 
 * This file will have all of the functions that call system commands and return strings.
 * Each function will return 0 on success and -1 on error and take a string, res, to 
 * return the result in. 
 */


 void getTop(char** res)
 {
    //Get the header from the top command and put it in res
 }

 void getNetwork(char** res)
 {
    //Get the network info from the command ss -s 
 }

 void getKernelName(char** res)
 {
    //Get the kernel name and info from uname -a
 }

 void getDate(char** res)
 {
    //Get the Date from the command echo `date`
 }

 void getDiskSpace(char** res)
 {
    //Get disk space used from command df
 }

 void getLoggedInUsers(char** res)
 {
    //Get all of the logged in users using command who -a
 }