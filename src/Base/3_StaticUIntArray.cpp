#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_StaticUIntArray.h"

// ----------------------------------------------------
// CONSTRUCTOR
StaticUIntArray::StaticUIntArray() {
    this->reset();
}

// ----------------------------------------------------
// BUFFERED STRING INTERFACE
void StaticUIntArray::reset(){
    this->buffer[0] = STATIC_UINT_ARRAY_NULL_TOKEN;
    this->buffer[STATIC_UINT_ARRAY_BUFFER_LEN - 1] = STATIC_UINT_ARRAY_NULL_TOKEN;
    this->idx = 0;
}

boolean StaticUIntArray::push(unsigned int n){
    if (this->isFull()) {
        Serial.println("BUFFER IS FULL");
        return false;
    }
    this->buffer[this->idx] = n;
    this->idx++;
    this->buffer[this->idx] = STATIC_UINT_ARRAY_NULL_TOKEN; // keep it closed
    return true;
}

unsigned int StaticUIntArray::length() {
    unsigned int l = 0;
    for (int i = 0; i < STATIC_UINT_ARRAY_BUFFER_LEN; i++){
        if (this->buffer[i] == STATIC_UINT_ARRAY_NULL_TOKEN) { break; }
        l++;
    }
    return l;
}

boolean StaticUIntArray::isEmpty(){
    return this->idx == 0;
}

boolean StaticUIntArray::isFull(){
    return (this->idx == STATIC_UINT_ARRAY_BUFFER_LEN - 1);
}

unsigned int StaticUIntArray::hash(unsigned int crc){
    for (int i = 0; i < STATIC_UINT_ARRAY_BUFFER_LEN; i++){
        if (this->buffer[i] == STATIC_UINT_ARRAY_NULL_TOKEN) { break; }
        crc = Utils::crc16_hash(crc, (unsigned int)this->buffer[i]);
    }
    return crc;
}
unsigned int StaticUIntArray::hash(){
    return this->hash(0);
}