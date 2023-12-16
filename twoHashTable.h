/*
Nadav Horowitz Assignment #6 TwoHashTable 11/27/2022

TwoHashTable.h
This file includes the function prototypes and fields required to implement the TwoHashTable class.
The fields contain the hashTableSize, and a double pointer for the array of UPCEntry pointers
Functionality includes insert & search.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "UPCEntry.h"
#include "position.h"
using namespace std;

class TwoHashTable{
    public:
        UPCEntry** hashTable;
        int hashTableSize;

    //Constructor takes name of input file and tableSize as input. Constructs twoHashTable and fills with data
    //extracted from input file.
    TwoHashTable(string filename, int tableSize){
        hashTableSize = tableSize;
        hashTable = new UPCEntry* [tableSize];
        for(int i = 0; i < tableSize; i++){
            hashTable[i] = NULL;
        }
        fstream fileStream (filename);
        string fileLine;
        if(fileStream.is_open()){
            getline(fileStream,fileLine);
            while(getline(fileStream,fileLine)){
                istringstream lineStream(fileLine);
                long long upcNumber;
                string upcName;
                lineStream >> upcNumber;
                getline(lineStream, upcName);
                upcName = upcName.substr(1);
                if(upcName[upcName.size() - 1] == '\r')
                    upcName.erase(upcName.size() - 1);
                UPCEntry* item = new UPCEntry(upcNumber,upcName);
                insert(*item);
            }
        }
    }

    //Insert method uses 2 hash functions and inserts parameter item into the shorter bucket
    //If buckets are the same length, defaults to hash value from function 1
    bool insert(UPCEntry &item){
        int hash1Value = item.hash1(hashTableSize);
        UPCEntry* entry = hashTable[hash1Value];
        int bucket1Elements = 0;
        while(entry != NULL){
            entry = entry->next;
            bucket1Elements++;
        }
        int hash2Value = item.hash2(hashTableSize);
        entry = hashTable[hash2Value];
        int bucket2Elements = 0;
        while(entry != NULL){
            entry = entry->next;
            bucket2Elements++;
        }

        int shortestBucket;
        int hashValue;
        if(bucket1Elements <= bucket2Elements){
            shortestBucket = bucket1Elements;
            hashValue = hash1Value;
        } else {
            shortestBucket = bucket2Elements;
            hashValue = hash2Value;
        }

        UPCEntry* frontEntry = hashTable[hashValue];
        UPCEntry* newEntry = &item;
        if(frontEntry == NULL){
            hashTable[hashValue] = newEntry;
        } else {
            newEntry->next = frontEntry; 
            hashTable[hashValue] = newEntry;
            
        }
        return false;
    }

    //Search function uses both hash functions trying to find parameter item
    //if not found, return the default position with both indices set as -1
    Position search(UPCEntry &item){
        long long wantedUPC = item.upc;
        string wantedDesc = item.desc;
        int hashValue = item.hash1(hashTableSize);
        UPCEntry* searchPtr = hashTable[hashValue];
        int positionInBin = 0;
        while(searchPtr != NULL){
            if(searchPtr->desc == wantedDesc && searchPtr->upc == wantedUPC){
                return Position(hashValue, positionInBin);
            } else {
                searchPtr = searchPtr->next;
                positionInBin++;
            }
        }
        hashValue = item.hash2(hashTableSize);
        searchPtr = hashTable[hashValue];
        positionInBin = 0;
        while(searchPtr != NULL){
            if(searchPtr->desc == wantedDesc && searchPtr->upc == wantedUPC){
                return Position(hashValue, positionInBin);
            } else {
                searchPtr = searchPtr->next;
                positionInBin++;
            }
        }
        return Position(-1,-1);//Item not found
    }

    //getStdDev() function finds lengths of all individual bins and puts them in array then calls instructor's getStdDev() function
    float getStdDev(){
        int* binLengths = new int[hashTableSize];
        for(int i = 0; i < hashTableSize; i ++){
            UPCEntry* entry = hashTable[i];        
            int binLength = 0;
            while(entry != NULL){
                entry = entry->next;
                binLength++;
            }
            binLengths[i] = binLength;
        }
        return getStdDev(binLengths, hashTableSize);
    }

    private:
    //Instructor implemented getStdDev function
    float getStdDev(int* binLengths, int tableSize){
        float sum = 0;
        for (int i = 0; i < tableSize; i++)
            sum += binLengths[i];

        float avarage = sum / tableSize;
        float dev_sum = 0;
        for (int i = 0; i < tableSize; i++)
        {
            dev_sum = dev_sum + (binLengths[i] - avarage) * (binLengths[i] - avarage);
        }
        float variance = dev_sum / tableSize;
        return sqrt(variance);
    }
};