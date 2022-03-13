/*
 * Filename:	program6header.h
 * Date:	April 27, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	Cs 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains all the function prototypes of the functions defined in the other files.
 * 	This file also contains an enumerated list for all the terms to be stored in the map
 */

#ifndef PROGRAM6HEADER_H
#define PROGRAM6HEADER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <tclap/SwitchArg.h>
#include <tclap/UnlabeledValueArg.h>
#include <tclap/CmdLine.h>
#include <rude/config.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

using namespace std;

  // Defining a global variable to store the value that is returned from the signal handler
extern map<int, string> parsedInformationMap;
extern ofstream logFile;
extern ofstream pidFile;
extern int fileDescriptor;
extern int watchDescriptor;
extern string pidFileName;

#define BUFFER_SIZE 1024

// Function prototypes
int main(int argc, char* argv[]);
void parseCmdToMap(int argc, char *argv[]);
void parseConfFileToMap();
void signalHandler(int signalNum);
void updateConfElements();
void directoryStatus();
void directoryMonitor(string pidFileName);
void uploadToVersionsDirectory(string fileName);
void getDateFromPipe(char *inputbuffer, FILE *dateArgOutput, string &date);
void checkFileNameChange();

 // Enums for the map
enum ParseComponents{Daemon, CONFfile, Verbose, LogFile, Password, NumVersions, WatchDir};

#endif			//	End of header guard for program6header.h file
