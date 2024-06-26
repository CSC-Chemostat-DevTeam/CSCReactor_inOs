#include "Base/2_Utils.h"
#include "Base/3_StaticString.h"

// ----------------------------------------------------
// CONSTRUCTOR
StaticString::StaticString() {
    this->reset();
}

StaticString::StaticString(String& str) {
    this->reset();
    for (unsigned int i = 0; i < str.length(); i++) {
        this->push(str.charAt(i));
    }
}

// ----------------------------------------------------
// BUFFERED STRING INTERFACE
void StaticString::reset(){
    this->buffer[0] = STATIC_STRING_NULL_TOKEN;
    this->buffer[STATIC_STRING_BUFFER_LEN - 1] = STATIC_STRING_NULL_TOKEN;
    this->idx = 0;
}

String StaticString::toString(){
    return String(this->buffer);
}

boolean StaticString::push(char c){
    if (this->isFull()) {
        Serial.println("BUFFER IS FULL");
        return false;
    }
    this->buffer[this->idx] = c;
    this->idx++;
    this->buffer[this->idx] = STATIC_STRING_NULL_TOKEN; // keep it closed
    return true;
}

boolean StaticString::push(String str){
    for (unsigned int i = 0; i < str.length(); i++) {
        if (!this->push(str.charAt(i))) { return false; }
    }
    return true;
}

unsigned int StaticString::length() {
    unsigned int l = 0;
    for (int i = 0; i < STATIC_STRING_BUFFER_LEN; i++){
        if (this->buffer[i] == STATIC_STRING_NULL_TOKEN) { break; }
        l++;
    }
    return l;
}

boolean StaticString::isEmpty(){
    return this->idx == 0;
}

boolean StaticString::isFull(){
    return (this->idx == STATIC_STRING_BUFFER_LEN - 1);
}

unsigned int StaticString::hash(unsigned int crc){
    for (int i = 0; i < STATIC_STRING_BUFFER_LEN; i++){
        if (this->buffer[i] == STATIC_STRING_NULL_TOKEN) { break; }
        crc = Utils::crc16_hash(crc, this->buffer[i]);
    }
    return crc;
}
unsigned int StaticString::hash(){
    return this->hash(0);
}