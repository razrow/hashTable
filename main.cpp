//p12 HashTable
//Rowan Briggs
//May 23, 2018
/* Description:
Type up and get the Hash table on pages 19 - 22 to work.
Show your sample test run at the bottom of your code using a multiline comment
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>  //for random numbers
#include <ctime>    //for random numbers
using namespace std;

//Hash Table
//hash.cpp
//demonstrates hash table with linear probing

class DataItem{//(could have more data)
public:
    int data; //data item (key)
    //-------------------------
    DataItem(int newData){
        data = newData;
    }//constructor {}
    //-------------------------
};//end class DataItem

class HashTable{
private:
    vector<DataItem*> hashArray; //vector holds hash table
    int arraySize;
    DataItem* pNonItem; //for deleted items

public:
    //-------------------------
    HashTable(int size) {//constructor
        arraySize = size;
        hashArray.resize(arraySize); //size the vector
        for(int j=0; j<arraySize; j++){//initialize elements
            hashArray[j] = NULL;
        }
        pNonItem = new DataItem(-1); //deleted item key is -1
    }
    //-------------------------
    void displayTable(){
        cout << "Table: ";
        for(int j=0; j<arraySize; j++){
            if(hashArray[j] != NULL){
                cout << hashArray[j]->data << " ";
            }
            else {
                cout << "** ";
            }
        }
        cout << endl;
    }
    //-------------------------
    int hashFunc(int key){
        return key % arraySize; //hash function
    }
    //-------------------------
    void insert(DataItem* pItem){//insert a DataItem
        //assumes table not full
        int key = pItem->data; //extract key
        int hashVal = hashFunc(key);//hash the key
                                    //until empty cell or -1
        while(hashArray[hashVal] != NULL &&
                hashArray[hashVal]->data != -1){
            ++hashVal; //go to next cell
            hashVal %= arraySize; //wraparound if necessary
        }
        hashArray[hashVal] = pItem; //insert item
    } //end of insert
    //-------------------------
    DataItem* remove(int key) {//remove a DataItem
        int hashVal = hashFunc(key);
        while(hashArray[hashVal] != NULL){
            if(hashArray[hashVal]->data == key) { //found the key?
                DataItem* pTemp = hashArray[hashVal]; //save item
                hashArray[hashVal] = pNonItem; //delete item
                return pTemp;   //return item
            }
            ++hashVal;  //go to next cell
            hashVal %= arraySize;   //wraparound if necessary
        }
        return NULL;
    }//end remove()
    //-------------------------
    DataItem* find(int key) {//find item with key
        int hashVal = hashFunc(key);    //hash the key
        while(hashArray[hashVal] != NULL){  //until empty cell
            if(hashArray[hashVal]->data == key) {//found the key?
                return hashArray[hashVal]; //yes return item
            }
            ++hashVal; //go to next cell
            hashVal %= arraySize; //wraparound if necessary
        }
        return NULL;
    }
};

int main() {
    DataItem* pDataItem;
    int aKey, size, n, keysPerCell;
    time_t aTime;
    char choice = 'b';
    //get sizes
    cout << "Enter size of hash table: ";
    cin >> size;
    cout << "Enter initial number of items: ";
    cin >> n;
    keysPerCell = 10;

    HashTable theHashTable(size); //make table
    srand(static_cast<unsigned>(time(&aTime)) ); //make a random list of numbers
    for(int j=0; j<n; j++){//insert data
        aKey = rand() % (keysPerCell*size); //r
        pDataItem = new DataItem(aKey);
        theHashTable.insert(pDataItem);
    }
    while(choice != 'x'){//interacts with user
        cout << "Enter first letter of " << "show, insert, delete, or find: ";
        char choice;
        cin >> choice;
        switch(choice){
            case 's':
                theHashTable.displayTable();
                break;
            case 'i':
                cout << "Enter key value to insert: ";
                cin >> aKey;
                pDataItem = new DataItem(aKey);
                theHashTable.insert(pDataItem);
                break;
            case 'd':
                cout << "Enter key value to delete: ";
                cin >> aKey;
                theHashTable.remove(aKey);
                break;
            case 'f':
                cout << "Entere key value to find: ";
                cin >> aKey;
                pDataItem = theHashTable.find(aKey);
                if(pDataItem != NULL){
                    cout << "Found " << aKey << endl;
                }
                else {
                    cout << "Could not find " << aKey << endl;
                }
                break;
            default:
                cout << "Invalid entry\n";
        }//end switch
    }//end while
}//end main()

/* Output:
Enter size of hash table: 12
Enter initial number of items: 8
Enter first letter of show, insert, delete, or find: s
Table: 72 ** 2 ** 16 113 114 ** 80 44 ** 71
Enter first letter of show, insert, delete, or find: f
Entere key value to find: 66
Could not find 66
Enter first letter of show, insert, delete, or find: f
Entere key value to find: 113
Found 113
Enter first letter of show, insert, delete, or find: i
Enter key value to insert: 1
Enter first letter of show, insert, delete, or find: s
Table: 72 1 2 ** 16 113 114 ** 80 44 ** 71
Enter first letter of show, insert, delete, or find: d
Enter key value to delete: 16
Enter first letter of show, insert, delete, or find: s
Table: 72 1 2 ** -1 113 114 ** 80 44 ** 71
Enter first letter of show, insert, delete, or find:
Process finished with exit code 15
 */