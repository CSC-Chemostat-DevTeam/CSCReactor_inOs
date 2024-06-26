#include "Base/2_utils.h"
#include "Base/3_KVReader.h"

// TODO: use variable number of val buffers (use an array)
KVReader::KVReader(){
    // Serial.println(">>> At KVReader::KVReader <<<");
    
    // parser state
    this->init_found = false;
    this->sep_found = 0;
    this->valid_input = false;
    
    // buffers
    this->key_buffer = StaticString();
    this->val_buffer0 = StaticString();
    this->val_buffer1 = StaticString();
    this->val_buffer2 = StaticString();
}

String KVReader::getKey() {
    return this->key_buffer.toString();
}

String KVReader::getVal() {
    return this->val_buffer0.toString();
}
String KVReader::getVal0() {
    return this->val_buffer0.toString();
}
String KVReader::getVal1() {
    return this->val_buffer1.toString();
}
String KVReader::getVal2() {
    return this->val_buffer2.toString();
}

void KVReader::reset(){
    // parser state
    this->init_found = false;
    this->valid_input = false;
    this->sep_found = 0;

    // buffers
    this->key_buffer.reset();
    this->val_buffer0.reset();
    this->val_buffer1.reset();
    this->val_buffer2.reset();
}

String KVReader::kvString(){
    String kvs = "";
    kvs += KV_STR_INIT_CHAR;
    kvs += this->getKey();
    kvs += KV_STR_SEP_CHAR;
    kvs += this->getVal0();
    kvs += KV_STR_SEP_CHAR;
    kvs += this->getVal1();
    kvs += KV_STR_SEP_CHAR;
    kvs += this->getVal2();
    kvs += KV_STR_END_CHAR;
    return kvs;
}

// return true if char is valid
boolean KVReader::parseChar(char c){

    // INIT CHAR
    if (c == KV_STR_INIT_CHAR) { 
        if (this->init_found) { return false; } // invalid (multiple init chars)
        this->init_found = true; 
        return true; 
    }
    // HERE init_found should be true
    if (!init_found) { return false; }

    // DETECT SEP CHAR
    if (c == KV_STR_SEP_CHAR) { 
        if (this->sep_found > 2) { return false; } // invalid
        this->sep_found++; 
        return true;
    }

    // DETECT END CHAR
    if (c == KV_STR_END_CHAR) { 
        this->valid_input = true; // validate input
        return true;
    }

    // STORE CHAR
    if (this->sep_found == 0) { // KEY CHAR
        this->key_buffer.push(c);
    } else if (this->sep_found == 1) { // VAL0 CHAR
        this->val_buffer0.push(c);
    } else if (this->sep_found == 2) { // VAL1 CHAR
        this->val_buffer1.push(c);
    } else if (this->sep_found == 3) { // VAL2 CHAR
        this->val_buffer2.push(c);
    } else { // should never happend ;)
        return false; 
    }

    // FULL BUFFER
    if (this->key_buffer.isFull() || this->val_buffer0.isFull() || this->val_buffer1.isFull() || this->val_buffer2.isFull()) { 
        return false; 
    }

    return true;
}

boolean KVReader::parseChar(String str) {
    for (unsigned int i = 0; i < str.length(); i++) {
        if (!parseChar(str[i])) { return false; }
    }
    return true;
}

unsigned int KVReader::hash(unsigned int crc) {
    crc = this->key_buffer.hash(crc);
    crc = this->val_buffer0.hash(crc);
    crc = this->val_buffer1.hash(crc);
    return this->val_buffer2.hash(crc);
}

unsigned int KVReader::hash(){
    return this->hash(0);
}