#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <climits>

using namespace std;

// Cache line structure
struct CacheLine {
    bool valid;
    int tag;
    int lastUsed; // for LRU
};

// Cache class
class Cache {
private:
    int numSets;
    int associativity;
    int time; // global time for LRU
    vector<vector<CacheLine>> sets;
    unordered_set<int> seen; // for miss classification

public:
    // Constructor
    Cache(int numEntries, int assoc) {
        associativity = assoc;
        numSets = numEntries / assoc;
        time = 0;

        sets.resize(numSets, vector<CacheLine>(associativity, {false, -1, 0}));
    }

    // Access function
    string access(int address) {
        int index = address % numSets;
        int tag = address / numSets;

        time++;

        int lruIndex = 0;
        int minTime = INT_MAX;

        // Check HIT
        for (int i = 0; i < associativity; i++) {
            if (sets[index][i].valid && sets[index][i].tag == tag) {
                sets[index][i].lastUsed = time;
                return "HIT";
            }
        }

        // MISS classification
        string result;
        if (seen.find(address) == seen.end()) {
            result = "MISS (Compulsory)";
        } else {
            result = "MISS (Conflict)";
        }
        seen.insert(address);

        // Find empty slot
        for (int i = 0; i < associativity; i++) {
            if (!sets[index][i].valid) {
                sets[index][i] = {true, tag, time};
                return result;
            }
        }

        // Replace LRU
        for (int i = 0; i < associativity; i++) {
            if (sets[index][i].lastUsed < minTime) {
                minTime = sets[index][i].lastUsed;
                lruIndex = i;
            }
        }

        sets[index][lruIndex] = {true, tag, time};

        return result;
    }
};

int main(int argc, char* argv[]) {
    // Check arguments
    if (argc != 4) {
        cout << "Usage: ./cache_sim num_entries associativity file" << endl;
        return 1;
    }

    int numEntries = stoi(argv[1]);
    int associativity = stoi(argv[2]);
    string filename = argv[3];

    Cache cache(numEntries, associativity);

    ifstream infile(filename);
    if (!infile) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }

    ofstream outfile("cache_sim_output");

    int address;

    while (infile >> address) {
        string result = cache.access(address);
        outfile << address << " : " << result << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
