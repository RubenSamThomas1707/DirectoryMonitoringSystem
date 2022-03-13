/*
 * Filename:	parseCmd.cc
 * Date:	April 27, 2021
 * Author:	Ruben Sam Thomas
 * Email:	rst180005@utdallas.edu
 * Course:	CS 3377.0W5, Spring 2021
 * Version:	1.0
 * Copyright:	2021, All Rights Reserved
 *
 * Description:
 * 	This file contains the subfunction called in the program6main.cc file to parse
 * 	the command line arguments and place it into a map. The prototype 
 * 	for the function defined in this file is in the program6header.h file.
 */

#include "program6header.h"

  // This is the function to parse the commmand line arguments and place it into the map.
void parseCmdToMap(int argc, char *argv[])
{
  TCLAP::CmdLine cmd("CS 3377.0W5 Program6 - Directory Monitor Daemon", ' ', "1.0");
  TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon)", cmd, false);
  TCLAP::UnlabeledValueArg<string> confFileArg("CONFfile", "The name of the configuration file. Defaults to cs3377dirmond.conf", false, "cs3377dirmond.conf", "config filename", false);

    // Adding the UnlabeledValueArg for the CONF file to the cmd
  cmd.add(confFileArg);

    // Parsing the command line arguments to cmd
  cmd.parse(argc, argv);

    // Adding the CONF file name to the map
  parsedInformationMap.insert(pair<int, string>(CONFfile, confFileArg.getValue()));

    // Checking if the daemon switch is enabled in the command line argument
  if(daemonSwitch.getValue() == 1)
  {
    parsedInformationMap.insert(pair<int,string>(Daemon, "true"));
  }

  else
  {
    parsedInformationMap.insert(pair<int,string>(Daemon, "false"));
  }
}

