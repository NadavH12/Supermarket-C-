/*
Nadav Horowitz Assignment #6 TwoHashTable 11/27/2022

Position.h
This file includes a simple position class that functions like the Point class. Includes fields for indexInTable and
indexInbin, which take default values of -1. File includes constructor to initialize fields to wanted values. 
*/

struct Position{
    public:
        int indexInTable = -1; //position in the table.
        int indexInBin = -1;   // position in the linked list.

        Position(int _indexInTable, int _indexInBin){
            indexInTable = _indexInTable;
            indexInBin = _indexInBin;
        }
};