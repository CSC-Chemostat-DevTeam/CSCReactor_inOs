#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_Collection.h"

// ----------------------------------------------------
// CONSTRUCTOR
Collection::Collection()
{
    this->stackReset();
}

Collection::Collection(int *arr, unsigned int size)
{
    this->stackReset();
    if (size > COLLECTION_BUFFER_LEN - 1U)
    {
        Serial.println("size > COLLECTION_BUFFER_LEN - 1");
        size = COLLECTION_BUFFER_LEN - 1U;
    }
    for (unsigned int i = 0U; i < size; i++)
    {
        this->push(arr[i]);
    }
}

Collection::Collection(String &str)
{
    unsigned int size = str.length();
    char *char_arr = const_cast<char *>(str.c_str());
    int *int_arr = reinterpret_cast<int *>(char_arr);
    Collection(int_arr, size);
}

// ----------------------------------------------------
// ARRAY INTERFACE
boolean Collection::set(int c, unsigned int i)
{
    this->buffer[i] = c;
    return true;
}
boolean Collection::set(char c, unsigned int i)
{
    return this->set(static_cast<int>(c), i);
}

int Collection::get(unsigned int i)
{
    return this->buffer[i];
}
int Collection::getInt(unsigned int i)
{
    return this->get(i);
}
unsigned int Collection::getUInt(unsigned int i)
{
    return static_cast<unsigned int>(this->get(i));
}
char Collection::getChar(unsigned int i)
{
    return static_cast<char>(this->get(i));
}

boolean Collection::isEmpty(unsigned int i)
{
    return this->get(i) == this->nullval();
}

unsigned int Collection::length()
{
    return COLLECTION_BUFFER_LEN;
}

int Collection::nullval()
{
    return COLLECTION_NULL_TOKEN;
}

// ----------------------------------------------------
// STACK INTERFACE
void Collection::stackReset()
{
    for (unsigned int i = 0U; i < this->length(); i++)
    {
        this->set(this->nullval(), i);
    }
    this->idx = 0U;
}

boolean Collection::push(int n)
{
    if (this->isStackFull())
    {
        Serial.println("BUFFER IS FULL");
        return false;
    }
    this->set(n, this->idx);
    this->idx++;
    this->set(this->nullval(), this->idx); // keep it closed
    return true;
}

boolean Collection::push(char n)
{
    return this->push(static_cast<int>(n));
}

boolean Collection::push(int *arr, unsigned int size)
{
    for (unsigned int i = 0U; i < size; i++)
    {
        if (!this->push(arr[i]))
        {
            return false;
        }
    }
    return true;
}

boolean Collection::push(const String &str)
{
    unsigned int size = str.length();
    for (unsigned int i = 0U; i < size; i++)
    {
        if (!this->push(str.charAt(i)))
        {
            return false;
        }
    }
    return true;
}

boolean Collection::isStackEmpty()
{
    return this->stackEndPos() == 0U;
}

boolean Collection::isStackFull()
{
    return (this->idx == this->length() - 1U);
}

unsigned int Collection::stackEndPos()
{
    return this->idx;
}

unsigned int Collection::stackLength()
{
    unsigned int l = 0U;
    for (unsigned int i = 0U; i < this->length(); i++)
    {
        if (this->isEmpty(i))
        {
            break;
        }
        l++;
    }
    return l;
}

// ----------------------------------------------------
// UTILS INTERFACE
unsigned int Collection::hash(unsigned int crc)
{
    for (unsigned int i = 0U; i < this->length(); i++)
    {
        if (this->isEmpty(i))
        {
            break;
        }
        crc = Utils::crc16_hash(this->getUInt(i), crc);
    }
    return crc;
}
unsigned int Collection::hash()
{
    return this->hash(0U);
}

String Collection::toString()
{
    String str = "";
    for (unsigned int i = 0U; i < this->length(); i++)
    {
        if (this->isEmpty(i))
        {
            break;
        }
        str += this->getChar(i);
    }
    return str;
}