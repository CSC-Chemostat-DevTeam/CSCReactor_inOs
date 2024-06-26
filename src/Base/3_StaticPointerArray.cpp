#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_StaticPointerArray.h"

// ----------------------------------------------------
// CONSTRUCTOR
StaticPointerArray::StaticPointerArray() {
    this->reset();
}

// ----------------------------------------------------
// BUFFERED STRING INTERFACE
void StaticPointerArray::reset(){
    this->buffer[0] = STATIC_POINTER_ARRAY_NULL_TOKEN;
    this->buffer[STATIC_POINTER_ARRAY_BUFFER_LEN - 1] = STATIC_POINTER_ARRAY_NULL_TOKEN;
    this->idx = 0;
}

boolean StaticPointerArray::push(void* n){
    if (this->idx == STATIC_POINTER_ARRAY_BUFFER_LEN - 1) {
        Serial.println("BUFFER IS FULL");
        return false;
    }
    this->buffer[this->idx] = n;
    this->idx++;
    this->buffer[this->idx] = STATIC_POINTER_ARRAY_NULL_TOKEN; // keep it closed
    return true;
}
boolean StaticPointerArray::push(const void* n){
    return StaticPointerArray::push((void*)n);
}

unsigned int StaticPointerArray::length() {
    unsigned int l = 0;
    for (int i = 0; i < STATIC_POINTER_ARRAY_BUFFER_LEN; i++){
        if (this->buffer[i] == STATIC_POINTER_ARRAY_NULL_TOKEN) { break; }
        l++;
    }
    return l;
}

boolean StaticPointerArray::isEmpty(){
    return this->idx == 0;
}

boolean StaticPointerArray::isFull(){
    return (this->idx == STATIC_POINTER_ARRAY_BUFFER_LEN - 1);
}

//  getters
// NOTE: Do no check for inbound
// NOTE: Do no check for anything
void* StaticPointerArray::getPointer(int i){
    return this->buffer[i];
}
unsigned int StaticPointerArray::getUInt(int i){
    return *((unsigned int*)this->buffer[i]);
}
int StaticPointerArray::getInt(int i){
    return *((int*)this->buffer[i]);
}
char StaticPointerArray::getChar(int i){
    return *((char*)this->buffer[i]);
}