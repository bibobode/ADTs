#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>
#include <cassert>

using namespace std;

class HashTable {
public:
	HashTable() {}
	virtual ~HashTable() {}
	virtual int insert(int uw_id, string const info) = 0;
	virtual int remove(int uw_id) = 0;
	virtual string& operator[](int uw_id) = 0;
	virtual void print() const = 0;
protected:
	static const int defaultSize = 100;
	int hash(int key, int buckets) const { return key % buckets; }
};

class HashTableClosed : public HashTable {
    
    // for use in HashTableClosed
    struct Student {
        Student() : uw_id(0), valid(false), name("") {}
        int uw_id;
        string name;
        bool valid;
    };
    
    public:
    
    HashTableClosed();
    HashTableClosed(int buckets);
    virtual int insert(int uw_id, string const info);
    virtual int remove(int uw_id);
    virtual string& operator[](int uw_id);
    virtual void print () const;
    
    vector<Student> bucketList;
    
};

HashTableClosed::HashTableClosed() {
    for (int i = 0; i < defaultSize; i++) {
        Student newStudent;
        bucketList.push_back(newStudent);
    }
}

HashTableClosed::HashTableClosed(int buckets) {
    if (buckets < 1) {
        for (int i = 0; i < defaultSize; i++) {
            Student newStudent;
            bucketList.push_back(newStudent);
        }
    }
    else {
        for (int i = 0; i < buckets; i++) {
            Student newStudent;
            bucketList.push_back(newStudent);
        }
    }
}


int HashTableClosed::insert(int uw_id, string const info) {
    
    int slot = hash(uw_id, bucketList.size());
    
    for (int i = 0; i < bucketList.size(); i++) {
        if (bucketList[i].uw_id == uw_id && bucketList[i].valid == true) {
            return 0;
        }
    }
    
    bool loopedOnce = false;
    int j = bucketList.size();
    for (int i = slot; i < j; i++) {
        if (bucketList[i].valid == false) {
            bucketList[i].uw_id = uw_id;
            bucketList[i].name = info;
            bucketList[i].valid = true;
            return 1;
        }
        
        if (i == bucketList.size()-1 && loopedOnce == false) {
            i = -1;
            j = slot;
            loopedOnce = true;
        }
    }

    return 0;
    
    
}

int HashTableClosed::remove(int uw_id) {
    
    for (int i = 0; i < bucketList.size(); i++) {
        if (bucketList[i].uw_id == uw_id && bucketList[i].valid) {
            bucketList[i].valid = false;
            return 1;
        }
    }
    return 0;
}

string& HashTableClosed::operator[](int uw_id) {
    
    for (int i = 0; i < bucketList.size(); i++) {
        if (bucketList[i].uw_id == uw_id && bucketList[i].valid == true) {
            return bucketList[i].name;
        }
    }
    
    int k = insert(uw_id, "");
    
    if (k == 1) {
        for (int i = 0; i < bucketList.size(); i++) {
            if (bucketList[i].uw_id == uw_id && bucketList[i].valid == true) {
                return bucketList[i].name;
            }
        } 
    }
    else {
        throw string ("table full");
    }
    
}

void HashTableClosed::print() const {
    
    bool printedItem = false;
    for (int i = 0; i < bucketList.size(); i++) {
        if (bucketList[i].valid && bucketList[i].uw_id != 0) {
            
            if (printedItem) {
                cout << " ";
            }
            
            cout << "(" << bucketList[i].uw_id << ", " << bucketList[i].name << ")";
            //cout << "(" << bucketList[i].uw_id << ", " << bucketList[i].name << ", " << i << ")";
            
            printedItem = true;
        }
    }
    
    cout << endl;
}

int main (int argc, char* argv[]) {
	HashTable* table;
	for(int i=0; i<1; i++) {
		switch(i) {
			case 0: table = new HashTableClosed(4); break;
                //case 1: table = new HashTableOpen(4); break;
		}
        
        table->insert(0, "Gia");
		// This next line works because operator[] inserts a new
		// uw_id if it doesn't find a given uw_id, and returns a 
		// reference to a string, which we can then modify.
		(*table)[0] = "Rin";
		cout << "uw_ids[" << 4444 << "] = " << (*table)[4444] << endl;
		try {
			(*table)[1111] = "Uri";
		} catch(string e) {
			cout << e << endl;
		}
		table->print();
		cout << endl;
        
		delete table;
	}
    
}