#ifndef KV_READER_H
#define KV_READER_H

#include <Arduino.h>
#include "Base/3_StaticString.h"

// Example $key:VAL0:VAL1%
#define KV_STR_INIT_CHAR '$'
#define KV_STR_SEP_CHAR ':'
#define KV_STR_END_CHAR '%'




class KVReader{

    private:
        bool init_found;
        byte sep_found;
        
        StaticString key_buffer;
        StaticString val_buffer0;
        StaticString val_buffer1;
        StaticString val_buffer2;

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
		String getVal0();
		String getVal1();
		String getVal2();

        void reset();

        boolean parseChar(char c);
        boolean parseChar(String str);

        String kvString();

        unsigned int hash(unsigned int crc);
        unsigned int hash();

};



#endif // KV_READER_H