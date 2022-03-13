/*
 * Filename:	inotifyFunctions.cc
 * Date:	May 7, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	CS 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains the inotify file monitoring functions which are called in main.
 * 	The functions in this file will monitor the watch directory and log any changes
 * 	that occur. This file also contains the function to create new time stamped copies
 * 	of the file that was modified.
 */

#include "program6header.h"
#include <sys/inotify.h>
#include <sstream>
#define PATH_MAX 4096

int fileDescriptor;
int watchDescriptor;

void directoryMonitor(string pidFileName)
{
    // Defining variables and registering signals
  fileDescriptor = inotify_init();
  size_t bufsiz = sizeof(struct inotify_event) + PATH_MAX + 1;
  struct inotify_event *event = (struct inotify_event *) malloc(bufsiz);

    // Checking if the file descriptior was opened successfully
  if(fileDescriptor < 0)
  {
      // Logging that the file descriptor could not be created and exiting the program
    logFile << "The file descriptor could not be created. Exiting..." << endl;
    
      // Closing the pid file
    pidFile.close();

      // Closing the log file
    logFile.close();

      // Removing the pid file
    remove(pidFileName.c_str());

    exit(0);
  }

    // Adding the watch to the desired directory
  watchDescriptor = inotify_add_watch(fileDescriptor, parsedInformationMap[WatchDir].c_str(), IN_CLOSE_WRITE);

    // Looping till a signal is received
  while(true)
  {
      // Monitoring and logging information to the logfile
    read(fileDescriptor, event, bufsiz);

    if(event->len > 0)
    {
        // Not logging that file names that are hidden files
      if(event->name[0] != '.' && event->name[0] != '~')
      {
          // Logging that the directory has been updated
        logFile << "The file " << event->name << " has been modified in the watch directory" << endl;
      
          // Uploading a timestamped version to the .versions subfolder
        uploadToVersionsDirectory(event->name);
      }   // Ignoring all the hidden files

    }  // Checking if buffer contains any value

  }   // End of while statement

}   // End of function to monitor the directory


  // Function to upload a version of the file to the .versions directory
void uploadToVersionsDirectory(string fileName)
{
   // Uploading a version of the document to the .versions directory
  logFile << "Uploading a timestamped version of the file " << fileName << " to the .versions directory."<< endl;

   // Getting the date and time using the date command
  string date = "";
  string dateCommand = "date +%Y.%m.%d-%H:%M:%S";
  FILE *dateArgOutput;
  char inputbuffer[BUFFER_SIZE];
  string fileVersionName;

   // Getting the output of the date command using pipe
  dateArgOutput = popen(dateCommand.c_str(), "r");
  
    // Getting the date string from the pipe
  getDateFromPipe(inputbuffer, dateArgOutput, date);
  
    // Defining variables for the version name, path to copy form and the path to copy the version to
  fileVersionName = fileName + "." + date;
  string sourcePath = parsedInformationMap[WatchDir]+"/"+fileName;
  string destinationPath = parsedInformationMap[WatchDir]+"/.versions/"+fileVersionName;
    
    // System call to copy file to destination
  system(("cp " + sourcePath + " " + destinationPath).c_str());
    
    // Closing the pipe
  pclose(dateArgOutput);

}   // End of function to upload updated versions to the .versions directory

  // Function to get the date string
void getDateFromPipe(char *inputbuffer, FILE *dateArgOutput, string &date)
{
  char *inputLine;
  
  inputLine = fgets(inputbuffer, BUFFER_SIZE, dateArgOutput);

  while(inputLine != NULL)
  {
    string inLine = inputLine;
    date = date + inLine;

    inputLine = fgets(inputbuffer, BUFFER_SIZE, dateArgOutput);
  }  // End of while statement
}   // End of function to get date information from pipe
