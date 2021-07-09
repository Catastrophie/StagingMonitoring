#include <iostream>  
#include <fstream> 
#include <vector>
#include "JSONStaging.h"


//Main
int main()
{

    while (true)
    {
        if (timeStampMonitorStats.fail()) {

            //Create listening loop for change to size or sleep
            break; //may not need exactly like this
        }

        endOfFileRead = timeStampMonitorStats.tellp();
        timeStampMonitorStats >> holdString;

        holdString.erase(0, holdString.find("defaultdict(<class 'dict'>, {"));
        holdString.erase(holdString.find("})"), holdString.length());

        //contain timestamp of readings
        std::string timestamp = holdString.substr(0, holdString.find(": {'"));
        holdString.erase(0, timestamp.length() + 5);
        timestampVect.push_back(timestamp);

        //loop through each system and create vector for the current timestamp
        for (int i = 0; i < systemCount; i++) {
            std::pair<std::string, std::string> sysValue;
            std::string compName = holdString.substr(0, holdString.find("': '"));
            holdString.erase(0, compName.length() + 4);
            sysValue.first = compName;
            std::string currentValue = holdString.substr(0, holdString.find("', '"));
            holdString.erase(0, currentValue.length() + 4);
            sysValue.second = currentValue;

            statBySystem.push_back(sysValue);
        }

        int last = timestampVect.size();
        // Open the file for Temperature data and save the most recent stats 
        //      NEEDS ADJUSTED TO RETRIEVE THE LAST DATA VALUES???
        std::ofstream dataFile;
        dataFile.open("unrealStageTemp.txt");
        dataFile << timestampVect.at(last) << "\n";

        //
        if (last > 0) {
            for (int i = ((last * 5) + 1) - 5; i < ((last * 5) + 1); i++) { //May break
                dataFile << statBySystem.at(i).first << " : ";
                dataFile << statBySystem.at(i).second << "\n";
            }
            dataFile.close();
        }
    }
}
    /*
    defaultdict(<class 'dict'>, {
        1623427831
        : {'
        ddc-infra-pdu-h9-1.redhorn
        ': '
        44
        ', '
        ddc-infra-pdu-q5-1.redhorn
        ': '
        43
        ', '
        ddc-infra-pdu-s11-1.redhorn
        ': '
        39
        ', '
        ddc-infra-pdu-u11-1.redhorn
        ': '
        45
        ', '
        ddc-infra-pdu-u7-1.redhorn
        ': '
        46
        '}, 
        1623428431: {'ddc-infra-pdu-h9-1.redhorn': '42', 'ddc-infra-pdu-q5-1.redhorn': '40', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '42', 'ddc-infra-pdu-u7-1.redhorn': '44'}, 
        1623429031: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '37', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623429631: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '35', 'ddc-infra-pdu-s11-1.redhorn': '36', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623430231: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '39', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623430831: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '37', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623431431: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '36', 'ddc-infra-pdu-s11-1.redhorn': '37', 'ddc-infra-pdu-u11-1.redhorn': '35', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623432031: {'ddc-infra-pdu-h9-1.redhorn': '41', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623432631: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623433231: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623433831: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623434431: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623435031: {'ddc-infra-pdu-h9-1.redhorn': '41', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623435631: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623436231: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '35', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623436831: {'ddc-infra-pdu-h9-1.redhorn': '37', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623437431: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623438031: {'ddc-infra-pdu-h9-1.redhorn': '41', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '39'}, 
        1623438631: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '40', 'ddc-infra-pdu-s11-1.redhorn': '40', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623439231: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '35'}, 
        1623439831: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623440431: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623441031: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623441631: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '40', 'ddc-infra-pdu-u11-1.redhorn': '39', 'ddc-infra-pdu-u7-1.redhorn': '39'}, 
        1623442231: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623442831: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '39'}, 
        1623443431: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623444031: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '39', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623444631: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '37', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623445231: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '37', 'ddc-infra-pdu-u11-1.redhorn': '36', 'ddc-infra-pdu-u7-1.redhorn': '35'}, 
        1623445831: {'ddc-infra-pdu-h9-1.redhorn': '40', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '35', 'ddc-infra-pdu-u7-1.redhorn': '36'}, 
        1623446431: {'ddc-infra-pdu-h9-1.redhorn': '39', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '38', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '37'}, 
        1623447031: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '37', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623447631: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '38', 'ddc-infra-pdu-s11-1.redhorn': '40', 'ddc-infra-pdu-u11-1.redhorn': '37', 'ddc-infra-pdu-u7-1.redhorn': '38'}, 
        1623448231: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '40', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '40'}, 
        1623448831: {'ddc-infra-pdu-h9-1.redhorn': '38', 'ddc-infra-pdu-q5-1.redhorn': '39', 'ddc-infra-pdu-s11-1.redhorn': '39', 'ddc-infra-pdu-u11-1.redhorn': '38', 'ddc-infra-pdu-u7-1.redhorn': '37'},
        ...
        }})

    */
