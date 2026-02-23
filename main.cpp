#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 The entry makes up a single hash table slot, containining a key(string), 
 value(int), and the isOccupied and isDeleted booleans. isOccupied indicates
 if the slot has ever been used, and isDeleted is used for lazy deletion.
*/
struct Entry {
    string key;
    int value;
    bool isOccupied = false;
    bool isDeleted = false;
};

class HashTable {
public:
vector<Entry> table; // underlying storage
bool debug;
    /*
     Creates a hash table with a default capacity of 17
    */
    HashTable(size_t cap = 17, bool debugToggle = false) {
    table.resize(cap);
    count = 0;
    debug = debugToggle;
}

    /*
     Used to insert or update a key and value pairing
    */
    void placeDaKey(const string& key, int value) {

        // This resizes the table if it's over 75% full
        if ((double)count / table.size() >= 0.75) {
            resizeDaTable();
        }

        // Find the starting index using the hash function
        size_t index = hashFunction(key);

        // Continues moving forward til it finds and empty slot
        while (table[index].isOccupied && !table[index].isDeleted) {
            
            if (debug == true) {
        cout << "Collision at index " << index << ", viewing next data slot..." << endl;
    }

            // If the key already exists, update its value
            if (table[index].key == key) {
                table[index].value = value;
                
                if (debug == true) {
            cout << "Updated existing key at the index: " << index << endl;
        }
                return;
            }

            // Move to the next slot
            index = (index + 1) % table.size();
        }

        // Insert the new key-value pair
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;

        count++;
        
        // Displays the insertion step if the debug mode is toggled on
        if (debug) {
    cout << "Inserting key: " << key << endl;
}
    }

    /*
     Searches for a key in the table.
     Will return true if the key is found, and stores it in the reference variable, and will return
     false if no key is found.
    */
    bool getDaKey(const string& key, int& value) const {
        size_t index = hashFunction(key);
        size_t start = index;
        
        if (debug == true) {
    cout << "PUT operation for key: " << key << endl;
    }

        // Continue probing until we hit an unused slot
        while (table[index].isOccupied) {
            
            if (debug == true) {
        cout << "Collision at index " << index << ", probing next slot..." << endl;
    }

            if (!table[index].isDeleted && table[index].key == key) {
                value = table[index].value;
                return true;
            }
            
            if (debug == true) {
            cout << "Updated existing key at index " << index << endl;
        }
    

            index = (index + 1) % table.size();

            // Stop if we've looped back to the starting point
            if (index == start)
                break;
        }

        return false;
    }

    /*
     This removes the key from the table by using lazy deletion, without actually fully
     deleting it to ensure the search functions properly
    */
    bool removeDaKey(const string& key) {
        size_t index = hashFunction(key);
        size_t start = index;

        while (table[index].isOccupied) {

            if (!table[index].isDeleted && table[index].key == key) {
                table[index].isDeleted = true;
                count--;
                return true;
            }

            index = (index + 1) % table.size();

            if (index == start)
                break;
        }

        return false;
    }

    /*
     This prints all the contents of the hash Table
     
    */
    void printDaTable() const {
        cout << "\nBehold the hash table:\n";

        for (size_t i = 0; i < table.size(); i++) {
            cout << i << ": ";

            if (table[i].isOccupied && !table[i].isDeleted) {
                cout << table[i].key << " -> " << table[i].value;
            } else {
                cout << "I'm empty...";
            }

            cout << endl;
        }
    }
    
    void toggleDebug() {
    debug = !debug;
    cout << "Debug mode is now " << (debug ? "ON" : "OFF") << endl;
}

private:
    
    size_t count;        // the number of total data points active in the table

    /*
     The hash function to convert the strings into a index in the table
    */
    size_t hashFunction(const string& key) const {
        size_t hashValue = 0;

        for (char c : key) {
            hashValue = hashValue * 31 + c;
        }

        return hashValue % table.size();
    }

    /*
     The function to resize the table when the load becomes too large, will double the old size
     of the table and re-insert the table elements
    */
    void resizeDaTable() {
        size_t newCap = table.size() * 2;
        vector<Entry> oldTable = table;

        table.clear();
        table.resize(newCap);
        count = 0;
        
        if (debug == true) {
    cout << "Resizing table from " << table.size()
         << " to " << table.size() * 2 << endl;
}

        // Reinsert the old entries into the new table
        for (const auto& entry : oldTable) {
            if (entry.isOccupied && !entry.isDeleted) {
                placeDaKey(entry.key, entry.value);
            }
        }
    }
};

/*
 Used to demonstrate the functionality of the hash table
*/
int main() {
    HashTable ht;
    int choice;
    string key;
    int value;
    

    while (true) {
    cout << "\n===== Hash Table Menu =====\n";
    cout << "1. Insert (PUT)\n";
    cout << "2. Search (GET)\n";
    cout << "3. Remove\n";
    cout << "4. Print Table\n";
    cout << "5. Exit\n";
    cout << "6. Toggle Debug Mode\n";
    cout << "Enter choice: ";

    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number.\n";
        continue;
    }

    if (choice < 1 || choice > 6) {
        cout << "Invalid option. Choose 1-6.\n";
        continue;
    }

    if (choice == 1) {
        cout << "Enter key: ";
        cin >> key;
        cout << "Enter value: ";
        cin >> value;
        ht.placeDaKey(key, value);
    }
    else if (choice == 2) {
        cout << "Enter key: ";
        cin >> key;

        if (ht.getDaKey(key, value))
            cout << "Value found: " << value << endl;
        else
            cout << "Key not found.\n";
    }
    else if (choice == 3) {
        cout << "Enter key to remove: ";
        cin >> key;

        if (ht.removeDaKey(key))
            cout << "Key removed.\n";
        else
            cout << "Key not found.\n";
    }
    else if (choice == 4) {
        ht.printDaTable();
    }
    else if (choice == 5) {
        cout << "Exiting the program, bye bye...\n";
        break;
    }
    else if (choice == 6) {
        ht.toggleDebug();
    }
}

    return 0;
}
    }

    return 0;
}
