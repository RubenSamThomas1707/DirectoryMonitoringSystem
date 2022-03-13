/*
 * Filename:	program6main.cc
 * Date:	April 27, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	CS 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains all the function calls and tclap function information
 * 	to parse the command line and take the appropriate actions based on the
 * 	user input.
 */

#include "program6header.h"
#include <sys/stat.h>

  // Defining a global variable to store the value from the signal function
map<int, string> parsedInformationMap;
ofstream logFile;
ofstream pidFile;
string pidFileName = "cs3377dirmond.pid";

int main(int argc, char* argv[])
{
    // Calling a subfunction to parse the command line arguments using TCLAP
  parseCmdToMap(argc, argv);

    // Calling a subfunction to parse the conf file using rudeconfig
  parseConfFileToMap();

    // Creating a fstream object for the log file
  logFile.open(parsedInformationMap[LogFile].c_str());

    // Checking if the pid file already exists
  ifstream pidCheckStream;
  pidCheckStream.open(pidFileName.c_str());

  if(pidCheckStream)
  {
      // Printing an error message saying that id already exists
    cout << "A pid file already exists. Logging message and exiting..." << endl;
    pidCheckStream.close();
    exit(0);
  }

    // Calling the function to create the directory
  directoryStatus();

    // Condition statement to check if the daemon flag is present to run accordingly
  if(parsedInformationMap[Daemon] == "true")
  {
       // Opening the file object for the pid file
     pidFile.open(pidFileName.c_str());
     
     cout << "Running in daemon mode..." << endl;
       
       // Running as a deaemon
     pid_t childPid = fork();

     if(childPid < 0)
     {
       cerr << "Error while creating the daemon" << endl;
       return 1;
     }
     
     else if(childPid == 0)
     {
     	 // Registering signals
       signal(SIGINT, signalHandler);
       signal(SIGTERM, signalHandler);
       signal(SIGHUP, signalHandler);
       
         // Calling the function to watch the directory
       directoryMonitor(pidFileName);

     }  // End of else if statement 
     
     else
     {
       cout << "Entering the child's pid into the pid file" << endl;
       pidFile << childPid << endl;
       
       cout << "Parent exiting" << endl;
       return 0;
     }  // End of code for parent process

  }    // End of if condition to run as daemon

  else
  {
     cout << "Running from the command line" << endl;
     
       // Registering the signals
     signal(SIGHUP, signalHandler);
     signal(SIGINT, signalHandler);
     signal(SIGTERM, signalHandler);

       // Calling the function to watch the directory
     directoryMonitor(pidFileName);

  }  // End of else statement to run in command line

  return 0;
}
