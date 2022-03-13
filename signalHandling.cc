/*
 * Filename:	signalHandling.cc
 * Date:	May 6, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	CS 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains the functions to elegantly handle the different
 * 	signals sent by the user to stop the daemon or to reread the conf
 * 	file. These signals can either be SIGINT, SIGTERM, or the SIGUP.
 */

#include "program6header.h"
#include <sys/inotify.h>

  // Function to determine which signal was entered by the user
void signalHandler(int signalNum)
{
    // Case statement to check the signal passed in
  switch(signalNum)
  {
     // Case statement for SIGINT signal
    case SIGINT:
        // Logging that the signal was received
      logFile << "\"SIGINT\" - INTERRUPT SIGNAL RECEIVED!" << endl;
      logFile << "Closing .log files." << endl;
      logFile << "Cleaning .pid file." << endl; 
      logFile << "Daemon Exited..." << endl;

        // Closing the pid file
      pidFile.close();

        // Closing the log file
      logFile.close();

        // Removing the pid file
      remove(pidFileName.c_str());

        // Removing the watch on the directory
      inotify_rm_watch(fileDescriptor, watchDescriptor);
      exit(0);

      break;

     // Case statement for SIGTERM signal
    case SIGTERM:
        // Logging that the SIGTERM signal was received
      logFile << "\"SIGTERM\" - TERMINATE SIGNAL RECEIVED!" << endl;
      logFile << "Closing .log files." << endl;
      logFile << "Cleaning .pid file." << endl;
      logFile << "Daemon Exited..." << endl;

        // Closing the pid file
      pidFile.close();

        // Closing the log file
      logFile.close();

        // Removing the pid file
      remove(pidFileName.c_str());

        // Removing the watch on the directory
      inotify_rm_watch(fileDescriptor, watchDescriptor);
      exit(0);

      break;

     // Case statement for SIGHUP signal
    case SIGHUP:
        // Logging that the SIGHUP signal was received.
      logFile << "\"SIGHUP\" - HANGUP SIGNAL RECEIVED!" << endl;
      logFile << "Rereading .conf file." << endl;
      
        // Checking if file name has changed after rereading conf file
      checkFileNameChange();

	// Logging that the map has been updated
      logFile << "The map has been updated with the new values." << endl;

      break;

    default:
    break;

  }  // End of switch statement

}  // End of signal handler function

  // Function to update the necessary elements in the map when SIGHUP is called
void updateConfElements()
{
    // Creating a config object
  rude::Config config;

    // Loading the .conf file and checking if the file was opened successfully
  if(config.load(parsedInformationMap[CONFfile].c_str()))
  {
      // Retrieving information from the conf file
    if(config.setSection("Parameters"))
    {
      string verboseSetting = config.getStringValue("Verbose");
      string logFileName = config.getStringValue("LogFile");
      string versionsNum = config.getStringValue("NumVersions");

        // Updating the information in the map
     parsedInformationMap[Verbose] = verboseSetting;
     parsedInformationMap[LogFile] = logFileName;
     parsedInformationMap[NumVersions] = versionsNum;

    }  // End of if statement to check if the parameters section was found successfully

    else
    {
      logFile << "The Parameters section in the conf file is not properly defined" << endl;
    }
  }  // End of if statement

  else
  {
     logFile << "The conf file could not be opened" << endl;
  }

}   // End of function to update conf file elements in the map


  // Function to check if the file elements were changed in the map
void checkFileNameChange()
{
    // Checking if the file name changed
  string oldFileName = parsedInformationMap[LogFile];
  updateConfElements();
  string newFileName = parsedInformationMap[LogFile];

  if(oldFileName != newFileName)
  {
    logFile << "The log file has changed.\nNow logging to " << newFileName << endl;
    logFile.close();
    logFile.open(newFileName.c_str());
    logFile << "Logging changed from " << oldFileName << endl;
 }   // End of if statement

}  // End of function to check if the file name changed
