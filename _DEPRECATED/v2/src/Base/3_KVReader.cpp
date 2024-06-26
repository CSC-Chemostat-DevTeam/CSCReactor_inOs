#include "Base/2_utils.h"
#include "Base/3_KVReader.h"

KVReader::KVReader(){
    // parser state
    this->init_found = false;
    this->sep_found = false;
    this->valid_input = false;
    
    // buffers
    this->key_buffer = StaticString();
    this->val_buffer = StaticString();
}

String KVReader::getKey() {
    return this->key_buffer.toString();
}

String KVReader::getVal() {
    return this->val_buffer.toString();
}

void KVReader::reset(){
    // parser state
    this->init_found = false;
    this->sep_found = false;
    this->valid_input = false;

    // buffers
    this->key_buffer.reset();
    this->val_buffer.reset();
}

String KVReader::kvString(){
    String kvs = "";
    kvs += CMD_INPUT_INIT_CHAR;
    kvs += this->getKey();
    kvs += CMD_INPUT_SEP_CHAR;
    kvs += this->getVal();
    kvs += CMD_INPUT_END_CHAR;
    return kvs;
}

boolean KVReader::parseChar(char c){

    // INIT CHAR
    if (c == CMD_INPUT_INIT_CHAR) { 
        if (this->init_found) { return false; } // invalid (multiple init chars)
        this->init_found = true; 
        return true; 
    }
    // HERE init_found should be true
    if (!init_found) { return false; }

    // DETECT SEP CHAR
    if (c == CMD_INPUT_SEP_CHAR) { 
        if (this->sep_found) { return false; } // invalid
        this->sep_found = true; 
        return true;
    }

    // DETECT END CHAR
    if (c == CMD_INPUT_END_CHAR) { 
        this->valid_input = true; // validate input
        return true;
    }

    // STORE CHAR
    if (this->sep_found) {
        // VAL CHAR
        this->val_buffer.push(c);
    } else {
        // KEY CHAR
        this->key_buffer.push(c);
    }

    // FULL BUFFER
    if (this->key_buffer.isFull() || this->val_buffer.isFull()) { 
        return false; 
    }

    return true;
}

unsigned int KVReader::hash(unsigned int crc) {
    crc = this->key_buffer.hash(crc);
    return this->val_buffer.hash(crc);
}

unsigned int KVReader::hash(){
    return this->hash(0);
}