#ifndef KV_READER_H
#define KV_READER_H

#include <Arduino.h>
#include "Base/3_StaticString.h"

// TODO: rename
// Example $progkey:PUBLIC%
#define CMD_INPUT_INIT_CHAR '$'
#define CMD_INPUT_SEP_CHAR ':'
#define CMD_INPUT_END_CHAR '%'

#define CMD_PRINT_START_MARKER "+++"
#define CMD_PRINT_END_MARKER "---"

class KVReader{

    private:
        bool init_found;
        bool sep_found;
        StaticString key_buffer;
        StaticString val_buffer;

    public:
        boolean valid_input;
        
        KVReader();

        /**
			get the current key as String.
		*/
		String getKey();

		/**
			get the current val as String.
		*/
		String getVal();

        void reset();

        boolean parseChar(char c);

        String kvString();

        unsigned int hash(unsigned int crc);
        unsigned int hash();

};



#endif // KV_READER_H