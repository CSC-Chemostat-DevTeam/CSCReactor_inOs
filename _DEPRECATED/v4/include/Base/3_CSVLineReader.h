#ifndef KV_READER_H
#define KV_READER_H

#include <Arduino.h>
#include "Base/3_StaticString.h"

class CSVLineReader{

    private:
        bool init_found;
        byte sep_found;
        
        StaticString _CSV_LINE_VALS[CSV_LINE_READER_VALS_NUMBER];

    public:
        boolean valid_input;
        
        CSVLineReader();

		/**
			get the current val as String.
		*/
		String getValString(byte i);

        // reset the reader
        void reset();

        boolean parseChar(char c);
        boolean parseChar(String str);

        String csvLineString();
        // return all vals joined without separators
        String joinVals();


        unsigned int hash(unsigned int crc);
        unsigned int hash();

};



#endif // KV_READER_H