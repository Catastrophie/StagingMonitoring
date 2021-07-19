#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "JSONStaging.h"


//Main
int main()
{
    std::string holdString;
    std::ifstream timeStampMonitorStats("testingTempdata.txt");
    std::stringstream buffer;
    buffer << timeStampMonitorStats.rdbuf();
    holdString = buffer.str();
    timeStampMonitorStats.close();

    std::string opening = "defaultdict(<class 'dict'>, {";

    holdString.erase(0, opening.length());
    holdString.erase(holdString.find("})"), holdString.length());

    //endOfFileRead = timeStampMonitorStats.tellp();

    while (holdString.length() > 0)
        holdString = constructData(holdString);

    createFile();

    return 0;
}

void createFile() {

    int last = timestampVect.size() - 1;
    // Open the file for Temperature data and save the most recent stats
    //      NEEDS ADJUSTED TO RETRIEVE THE LAST DATA VALUES???
    std::ofstream dataFile;
    dataFile.open("unrealStageTemp.txt");
    dataFile << timestampVect.at(last) << "\n";

    //
    if (last > 0) {
        for (int i = (last * 5) - 1; i < ((last + 1) * 5) - 1; i++) { //May break
            dataFile << statBySystem.at(i).first << " : ";
            dataFile << statBySystem.at(i).second << "\n";
        }
        dataFile.close();
    }
}

std::string constructData(std::string holdString) {
    //contain timestamp of readings
    std::string timestamp = holdString.substr(0, holdString.find(": {'"));
    holdString.erase(0, timestamp.length() + 4);
    timestampVect.push_back(timestamp);

    //loop through each system and create vector for the current timestamp
    for (int i = 0; i < systemCount; i++) {
        std::pair<std::string, std::string> sysValue;
        std::string compName = holdString.substr(0, holdString.find("': '"));
        holdString.erase(0, compName.length() + 4);
        sysValue.first = compName;

        if (holdString.find("', '") > holdString.find("'}, ")) {
            std::string currentValue = holdString.substr(0, holdString.find("'}, "));
            holdString.erase(0, currentValue.length() + 4);
            sysValue.second = currentValue;
        }
        else {
            std::string currentValue = holdString.substr(0, holdString.find("', '"));
            holdString.erase(0, currentValue.length() + 4);
            sysValue.second = currentValue;
        }
        statBySystem.push_back(sysValue);
    }
    return holdString;
}