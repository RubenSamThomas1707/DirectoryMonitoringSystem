/*
 * Filename:	directoryStatus.cc
 * Date:	May 6, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	CS 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains the function called in main to check if the .versions
 * 	directory exists. If it exists then the updated files would be stored in
 * 	existing directory. If the directory does not exists, then a new directory
 * 	will be created
 */

#include "program6header.h"
#include <sys/stat.h>

void directoryStatus()
{
    // Creating the directory to store the updated files in
  string versionsDirectoryPath = parsedInformationMap[WatchDir]+"/.versions";
  struct stat buffer;
  int existVal = stat(versionsDirectoryPath.c_str(), &buffer);

    // Creating the directory if it does not exist
  if(existVal == -1)
  {
    system(("mkdir "+versionsDirectoryPath).c_str());
    logFile << "Created the .versions directory to store the updated files" << endl;
  }  // End of if statement to create the directory

  else
  {
    logFile << "Using the already existing .versions directory to store the updated files" << endl;
  }  // End of else statement to log if the directory already exists
}  // End of function directory status
