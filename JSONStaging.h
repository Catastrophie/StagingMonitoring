#pragma once
#include <map>

/*
	The purpose of this class is to take the data Premetheous is retrieving and compile it in a cleaner fashion for unreal to breakdown.
*/

// MAYBE ADD LATER FOR SLIMMING DOWN DATA INTO SYSTEM FILES INSTEAD OF ONE FILE. 
//		At this time this isn't needed
//typedef struct {
//	std::pair<std::string, float> comp1;
//	std::pair<std::string, float> comp2;
//	std::pair<std::string, float> comp3;
//	std::pair<std::string, float> comp4;
//	std::pair<std::string, float> comp5;
//};

int currentTime = 0;
std::vector<std::string> timestampVect;
std::vector<std::pair<std::string, std::string>> statBySystem;
std::string holdString;

//Separate the file data into individual lists for later calculation
int systemCount = 5;
std::streampos endOfFileRead;