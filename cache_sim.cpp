#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure for a cache line
struct CacheLine {
    bool valid;
    int tag;
};

class Cache {
private:
    int numSets;
    int associativity;
    vector<vector<CacheLine>> sets;

public:
// Constructor
    Cache(int numEntries, int assoc) {
        associativity = assoc;
        numSets = numEntries / assoc;

// Initialize cache with invalid entries
        sets.resize(numSets, vector<CacheLine>(associativity, {false, -1}));
    }

    // Access function: returns true if HIT, false if MISS
    bool access(int address) {
        int index = address % numSets;
        int tag = address / numSets;

        // Check for HIT
        for (int i = 0; i < associativity; i++) {
            if (sets[index][i].valid && sets[index][i].tag == tag) {
                return true;
            }
        }

        // MISS: find empty slot
        for (int i = 0; i < associativity; i++) {
            if (!sets[index][i].valid) {
                sets[index][i].valid = true;
                sets[index][i].tag = tag;
                return false;
            }
        }

        // MISS: replace first entry (simple policy)
        sets[index][0].tag = tag;
        sets[index][0].valid = true;

        return false;
    }
};

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 4) {
        cout << "Usage: ./cache_sim num_entries associativity file" << endl;
        return 1;
    }

    // Read command-line arguments
    int numEntries = stoi(argv[1]);
    int associativity = stoi(argv[2]);
    string filename = argv[3];

    // Create cache
    Cache cache(numEntries, associativity);

    // Open input file
    ifstream infile(filename);
    if (!infile) {
        cout << "Error: Cannot open input file." << endl;
        return 1;
    }

    // Open output file
    ofstream outfile("cache_sim_output");

    int address;

    // Process each memory reference
    while (infile >> address) {
        bool hit = cache.access(address);

        if (hit)
            outfile << address << " : HIT" << endl;
        else
            outfile << address << " : MISS" << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
