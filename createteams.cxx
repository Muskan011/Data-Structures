#include <set>
#include "json.hpp"
#include "priorityqueue.h"
#include "teamdata.h"

#define NUM_ARGS 2 // hash define created for 2 input arguments
#define DUMP_READ_OUT 2 // hash define created to use in the dump() function to avoid using number 2.
#define FAIR_PERCENT 50 // as given in the instructions defined to 50 percent

int main(int argc, char **argv)
{
    if (argc > NUM_ARGS || argc < NUM_ARGS)
    {                                          // if there are more or less than 2 arguments
        cout << "Wrong number of arguments\n"; // then print error message
        return 0;                              // and exit gracefully
    }
    TeamData originalData(argv[1]); // store json file and store it in object of TeamData

    size_t heapMaxValue = originalData.numPlayers() * originalData.numPlayers(); // max heap size is numplayer^2 as there are that many possible teams.
    PriorityQueue priorityQ(heapMaxValue);                                       // make priority queue with max heap size of heapMaxValue

    json updatedData;   // defining json object
    int i, j;           // defining iterators
    for (i = 0; i < originalData.numPlayers(); i++)
    {                                                                               // i goes from 0 to numPlayers - 1
        for (j = i + 1; j < originalData.numPlayers(); j++)
        {                                                                           // j goes from i+1 to numPlayers - 1 as we don't want 2 teams that are the same.
            float key = fabs(originalData.winPercentages(i, j) - FAIR_PERCENT);               // keys stores how close to 50 the win percentage of the team is. Therefore absolute value is used.
            pair<float, pair<int, int>> toInsert = make_pair(key, make_pair(i, j)); // toInsert stores the key and the index of the first and second player.
            priorityQ.insert(toInsert);                                             // priority queue is inserted with the players and how close their win percentage is to 50.
        }
    }

    vector<pair<int, int>> groups; // group stores the informations of the teammates.
    set<int> popped;               // popped stored the elements that are popped out of the priority queue

    while (!priorityQ.isEmpty())
    {                                                    // until the priority queue is empty
        KeyValuePair removedMin = priorityQ.removeMin(); // keep removing the min and storing the min removed in removedMin.
        if (!popped.count(removedMin.second.first) && !popped.count(removedMin.second.second))
        {                                           // if both the removed key and value are not already present in the set popped.
            Value val = removedMin.second;
            groups.push_back(val);    // then add the both the values of the key value pair to groups
            popped.insert(val.first); // and then store the values in popped one by one.
            popped.insert(val.second);
        }
    }

    updatedData["teams"] = groups;                   // storing the vector pair of ints into a json object with the heading "teams".
    cout << updatedData.dump(DUMP_READ_OUT) << '\n'; // then print the output in a readable format.
    return 1;                                        // exit gracefully
}