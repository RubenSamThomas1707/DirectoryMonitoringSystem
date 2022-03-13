/*
 * Filename:	parseConfFile.cc
 * Date:	May 2, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	CS 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains the helper function parseConfFileToMap which is called in
 * 	the main function. This function parses the conf file using rudeConfig and
 * 	stores the information retrieved into a map. The function prototype for this
 * 	function is defined in the program6header.h file.
 */

#include "program6header.h"

void parseConfFileToMap()
{
   // Creating a config object
  rude::Config config;

   // Loading the .conf file else and checking if the file was opened successfully
 if(config.load(parsedInformationMap[CONFfile].c_str()))
 {
     // Retrieving information from the conf file
   if(config.setSection("Parameters"))
   {
     string verboseSetting = config.getStringValue("Verbose");
     string logFile = config.getStringValue("LogFile");
     string password = config.getStringValue("Password");
     string versionsNum = config.getStringValue("NumVersions");
     string watchDirPath = config.getStringValue("WatchDir");
  
       // Entering information retrieved from the conf file into a map
     parsedInformationMap.insert(pair<int,string>(Verbose, verboseSetting));
     parsedInformationMap.insert(pair<int,string>(LogFile, logFile));
     parsedInformationMap.insert(pair<int,string>(Password, password));
     parsedInformationMap.insert(pair<int,string>(NumVersions, versionsNum));
     parsedInformationMap.insert(pair<int,string>(WatchDir, watchDirPath));
  }

   else
   {
     cerr << "The Parameters section in the conf file is not properly defined." << endl;
   }
 }  // end of if statement

 else
 {
    cerr << "The conf file could not be opened" << endl;
 }

} // End of function parseConfFileToMap
