#ifndef STATIC_INT_ARRAY
#define STATIC_INT_ARRAY

#include <Arduino.h>
#include "1_config.h"

// ----------------------------------------------------

// #include <iostream>

// int main() {
//     int bla[] = {1, 2, 3, 4};
//     int* intPtr = bla;

//     // Reinterpret cast da int* a char*
//     char* charPtr = reinterpret_cast<char*>(intPtr);

//     // Stampa i byte dei primi due interi
//     for (size_t i = 0; i < 2 * sizeof(int); ++i) {
//         std::cout << static_cast<int>(charPtr[i]) << " ";
//     }

//     std::cout << std::endl;

//     return 0;
// }

// ----------------------------------------------------

class Collection{
    private:
        unsigned int idx;
        int buffer[COLLECTION_BUFFER_LEN];

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        Collection();
        Collection(int* arr, unsigned int size);
        Collection(String& str);

        // ----------------------------------------------------
        // ARRAY INTERFACE
        boolean set(int c, unsigned int i);
        boolean set(char c, unsigned int i);
        int get(unsigned int i);
        int getInt(unsigned int i);
        unsigned int getUInt(unsigned int i);
        char getChar(unsigned int i);
        boolean isEmpty(unsigned int i);
        unsigned int length();
        int nullval();

        // ----------------------------------------------------
        // STACK INTERFACE
        void stackReset();
        boolean push(int n);
        boolean push(char n);
        boolean push(int* arr, unsigned int size);
        boolean push(String& str);
        boolean isStackEmpty();
        boolean isStackFull();
        unsigned int stackEndPos();
        unsigned int stackLength();

        // ----------------------------------------------------
        // HASH INTERFACE
        String toString();
        unsigned int hash(unsigned int crc);
        unsigned int hash();
};


#endif // STATIC_INT_ARRAY