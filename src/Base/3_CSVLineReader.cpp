#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"

// TODO: use variable number of val buffers (use an array)
CSVLineReader::CSVLineReader(){
    // Serial.println(">>> At CSVLineReader::CSVLineReader <<<");
    
    // parser state
    this->init_found = false;
    this->sep_found = 0;
    this->valid_input = false;
    
    // buffers
    for (byte i = 0; i < CSV_LINE_READER_VALS_NUMBER; i++) {
        _CSV_LINE_VALS[i] = StaticString();
    }
}

String CSVLineReader::getValString(byte i) {
    return this->_CSV_LINE_VALS[i].toString();
}

void CSVLineReader::reset(){
    // parser state
    this->init_found = false;
    this->valid_input = false;
    this->sep_found = 0;

    // buffers
    for (byte i = 0; i < CSV_LINE_READER_VALS_NUMBER; i++) {
        _CSV_LINE_VALS[i].reset();
    }
}

String CSVLineReader::csvLineString(){
    String kvs = "";
    kvs += CSV_LINE_INIT_CHAR;
    for (byte i = 0; i < CSV_LINE_READER_VALS_NUMBER; i++) {
        kvs += this->getValString(i);
        kvs += CSV_LINE_SEP_CHAR;
    }
    kvs += CSV_LINE_END_CHAR;
    return kvs;
}

// ----------------------------------------------------
// Parser

// return true if char is valid
int CSVLineReader::parseChar(char c){

    // INIT CHAR
    if (c == CSV_LINE_INIT_CHAR) { 
        if (this->init_found) { return false; } // invalid (multiple init chars)
        this->init_found = true; 
        return PARSER_READY_FOR_NEXT; 
    }
    // HERE init_found should be true
    if (!init_found) { return PARSER_ERROR; }

    // DETECT SEP CHAR
    if (c == CSV_LINE_SEP_CHAR) { 
        // if (this->sep_found == CSV_LINE_READER_VALS_NUMBER) { return false; } // invalid
        this->sep_found++; 
        return PARSER_READY_FOR_NEXT;
    }

    // DETECT END CHAR
    if (c == CSV_LINE_END_CHAR) { 
        this->valid_input = true; // validate input
        return PARSER_MSG_COMPLETED;
    }

    // STORE CHAR
    if (sep_found < CSV_LINE_READER_VALS_NUMBER) {
        this->_CSV_LINE_VALS[sep_found].push(c);   
    } else { // to many vals
        return PARSER_ERROR; 
    }

    // FULL BUFFER
    for (byte i = 0; i < CSV_LINE_READER_VALS_NUMBER; i++) {
        if (_CSV_LINE_VALS[i].isFull()) { return PARSER_ERROR; }
    }

    return PARSER_READY_FOR_NEXT;
}

int CSVLineReader::parseChar(String str) {
    for (unsigned int i = 0; i < str.length(); i++) {
        int flag = parseChar(str[i]);
        if (flag == PARSER_READY_FOR_NEXT) { continue; }
        if (flag == PARSER_ERROR) { return PARSER_ERROR; }
        if (flag == PARSER_MSG_COMPLETED) { return PARSER_MSG_COMPLETED; }
    }
    return PARSER_ERROR;
}


// ----------------------------------------------------
// HASH 
unsigned int CSVLineReader::hash(unsigned int crc) {
    for (byte i = 0; i < CSV_LINE_READER_VALS_NUMBER; i++) {
        crc = this->_CSV_LINE_VALS[i].hash(crc);
    }
    return crc;
}
unsigned int CSVLineReader::hash(){ return this->hash(0); }