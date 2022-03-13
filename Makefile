#
# Filename:	Makefile
# Date:		April 27, 2021
# Author:	Ruben Sam Thomas
# Email:	rst180005@utdallas.edu
# Course:	CS 3377.0W5, Spring 2021
# Version:	1.0
# Copyright:	2021, All Rights Reserved
#
# Description:
# 	This is the make file to automate the creation of object files from the source files.
# 	It then links all the object files and creates the final executable.
#

# Initializing the variables
CXX = g++
CXXFLAGS = -Wall -Werror
CPPFLAGS = -I/home/010/r/rs/rst180005/include

# Linker Flags
LDFLAGS = -static -L/home/010/r/rs/rst180005/lib/rude
LDLIBS = -lrudeconfig

# Naming the final executable
EXECUTABLE = program6

OBJS = program6main.o parseCmd.o parseConfFile.o signalHandling.o directoryStatus.o inotifyFunctions.o

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *o
