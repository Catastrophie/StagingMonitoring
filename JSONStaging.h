/*
 The purpose of this class is to take the data Premetheous is retrieving
 and compile it in a cleaner fashion for unreal to breakdown.
*/
#ifndef JSONSTAGING_H
#define JSONSTAGING_H

#include <map>

int currentTime;
std::vector<std::string> timestampVect;
std::vector<std::pair<std::string, std::string> > statBySystem;
std::string holdString;

//Separate the file data into individual lists for later calculation
int systemCount = 5;
void createFile();
std::string constructData(std::string);
#endif