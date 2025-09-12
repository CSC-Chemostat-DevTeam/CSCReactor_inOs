#ifndef KV_READER_H
#define KV_READER_H

#include <Arduino.h>
#include "Base/3_Collection.h"

class CSVLineReader
{

private:
    // PARSER
    bool init_found;
    unsigned int sep_found;
    boolean valid_input;

    // DATA
    Collection _CSV_LINE_VALS[CSV_LINE_READER_VALS_NUMBER];

public:
    // ----------------------------------------------------
    // CONSTRUCTOR
    CSVLineReader();

    // ----------------------------------------------------
    // ARRAY INTERFACE
    String getValString(unsigned int i);
    String getValString(unsigned int i, const String &dflt);
    int getValInt(unsigned int i);
    int getValInt(unsigned int i, int dflt);
    boolean isEmpty(unsigned int i);

    // ----------------------------------------------------
    // PARSER INTERFACE
    int parseChar(int c);
    int parseChar(byte c);
    int parseChar(char c);
    int parseChar(String str);
    boolean hasLine();
    void reset();

    // ----------------------------------------------------
    // CSV
    String csvLineString(boolean trim);
    // return all vals joined without separators
    // String joinVals();

    // ----------------------------------------------------
    // UTILS
    unsigned int hash(unsigned int crc);
    unsigned int hash();
};

#endif // KV_READER_H