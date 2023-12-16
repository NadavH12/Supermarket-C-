/*
Nadav Horowitz Assignment #6 TwoHashTable 11/27/2022

UPCEntry.h
This file includes the functions and fields required for UPCEntry objects. UPCEntry objects function like Nodes in linkedlists.
UPCEntry contains a long long field for upc code, a string for description, and a UPCEntry* pointer to point to the next
UPCEntry in the list. The file also contains hash functions 1 & 2 which are used when implementing the TwoHashTable.
*/

#ifndef UPC_ENTRY
#define UPC_ENTRY
#include <string>
using namespace std;

struct UPCEntry {
    long long upc;
    string desc;
    UPCEntry* next;

    //Default constructor
    UPCEntry(){}
    
    //1 string parameter constructor, extracts necessary data from parameter and constructs UPCEntry object
    UPCEntry(string line){
        int commaLocation = line.find(',');
        string upcLine = line.substr(0,commaLocation);
        upc = stoll(upcLine);
        desc = line.substr(commaLocation+1);
        next = NULL;
    }

    //Constructor without data extraction
    UPCEntry(long long upcNumber, string line){
        upc = upcNumber;
        desc = line;
        next = NULL;
    }

    //hash function 1
    int hash1(int tableSize){
        return upc % tableSize;
    }

    //hash function 2
    int hash2(int tableSize){
        return abs(desc[0] + 27 * desc[1] + 729 * desc[2]) % tableSize;
    }
};
#endif