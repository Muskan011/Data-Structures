#include "teamdata.h"

int TeamData::numPlayers() const
{
    return numPlayers_; // returns the number of players.
}

TeamData::TeamData(std::string filename)
{
    json jInFile;      // json objects to store input json file and the updated file created by this program respectively.
    ifstream jsonFile; // ifstream object

    jsonFile.open(filename); // open input file in jsonFile
    if (!jsonFile.is_open())
    {                                               // if jsonFile doesn't open
        cout << "Cannot open " << filename << '\n'; // then print error message
    }
    jsonFile >> jInFile; // store jsonFile in json object jInFile.
    jsonFile.close();    // close the ifstream object.

    numPlayers_ = jInFile["metadata"]["numPlayers"];    // numPlayer is the the number of player given in the metadata.
    winPercentages_.resize(numPlayers_, vector<float>(numPlayers_));    // winPercentage_ is resized to have numPlayer_ elements that are intialized to the vector of type float 
                                                                        // containing values of numPlayers.

    for (auto &itr : jInFile["teamStats"])
    {               // iterates through the team statistics
        int first, second;      //defining variables needed.
        float percentage;

        first = itr["playerOne"];       // playerOne's Statistics are stored in first
        second = itr["playerTwo"];      // playerTwo's Statistics are stored in second
        percentage = itr["winPercentage"];  // Both the players calculated wining percentage is stored in percentage
        winPercentages_[first][second] = percentage, winPercentages_[second][first] = percentage; // then percentage is assigned to each player's statistic.
    }
}
