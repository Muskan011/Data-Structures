#include <iostream>
#include <fstream>
#include "priorityqueue.h"

#define NUM_ARGS 2 // hash define created for 2 input arguments
#define DUMP_READ_OUT 2 // hash define created to use in the dump() function to avoid using number 2.

using namespace std;        // namespaces being used are std and nlohmann.
using namespace nlohmann;   // namespaces being used are std and nlohmann.

int main(int argc, char **argv)
{

    if (argc > NUM_ARGS || argc < NUM_ARGS)
    {                                          // if there are more or less than 2 arguments
        cout << "Wrong number of arguments\n"; // then print error message
        return 0;                              // and exit gracefully
    }

    json jInFile, updatedData; // json objects to store input json file and the updated file created by this program respectively.
    ifstream jsonFile;         // ifstream object
    jsonFile.open(argv[1]);    // open input file in jsonFile

    if (!jsonFile.is_open())
    {                                              // if jsonFile doesn't open
        cout << "Cannot open " << argv[1] << '\n'; // then print error message
        return 0;                                  // and exit gracefully
    }
    jsonFile >> jInFile; // store jsonFile in json object jInFile.
    jsonFile.close();    // close the ifstream object.

    int numOperations;                                        // counter to count number of operations
    string operation, key;                                    // operation stores the operation that needs to be performed on the priority queue
    KeyValuePair removed, minimum;                            // variable to store the removed element and the minimum value of PriorityQueue.
    size_t heapMaxValue = jInFile["metadata"]["maxHeapSize"]; // variable to store the max heap size.
    numOperations = 0;
    PriorityQueue priorityQ(heapMaxValue); // make a priority queue object with max heap size given in the metadata.

    for (auto itr = jInFile.begin(); itr != jInFile.end(); itr++)
    {                    // iterator to iterate through the input json object.
        key = itr.key(); // key stores whether data is metadata or an operation.
        if (key == "metadata")
        {                       // if the data is metadata.
            updatedData = priorityQ.JSON();                                  // print metadata
            updatedData["metadata"]["numOperations"] = numOperations;        // added numOperations to the metadata of the out json object.
            updatedData["metadata"]["maxHeapSize"] = priorityQ.getMaxSize(); // added maxHeapSize to the metadata of the out json object.
        }
        else
        {
            numOperations++;                 // if the key is not metadata it is an operation so add an counter numOperations.
            operation = (*itr)["operation"]; // store the name of the operations in operation

            if (operation == "removeMin")        // if the operation in removeMin
                removed = priorityQ.removeMin(); // then store the popped element of the heap in removed

            else if (operation == "min")   // if the operation in min
                minimum = priorityQ.min(); // then store the minimum element of the heap in minimum

            else if (operation == "size") // if the operation in size
                priorityQ.size();         // call size on priority queue.

            else if (operation == "isEmpty") // if the operation in isEmpty
                priorityQ.isEmpty();         // call isEmpty on priority queue.

            else if (operation == "insert")
            {                                // if the operation in min
                double index = jInFile[key]["key"]; // store the key that needs to be inserted into to PQ in index
                priorityQ.insert(index);     // insert index into the Priority Queue.
            }
        }
    }
    cout << updatedData.dump(DUMP_READ_OUT) << '\n'; // print readable output of the json object.
    return 1;                                        // exit gracefully.
}