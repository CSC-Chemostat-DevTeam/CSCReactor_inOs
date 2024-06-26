#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#include <SD.h>
#include "Base/2_utils.h"
#include "Base/4_AbsHandler.h"
#include "Base/3_CSVLineReader.h"
#include "Base/4_SerialHandler.h"
#include "Base/4_Chemostat.h"

// ----------------------------------------------------
// All parseble msgs between the PC and the board must be 
// handle by this class
// ----------------------------------------------------

class MsgHandler :
    public AbsHandler
{       
	private:
		CSVLineReader csvline;

		// Response
		unsigned long respcount;
		unsigned int hash;

	public:

		// ----------------------------------------------------
        // CONSTRUCTOR
		MsgHandler(Chemostat* Ch);

		// ----------------------------------------------------
        // SKETCH INTERFACE
		void onsetup();
		
		void onloop();

		// ----------------------------------------------------
        // _DEV INTERFACE
        String getClassName();

		// ----------------------------------------------------
        // MSG INTERFACE
		virtual boolean handleMsg();

		// ----------------------------------------------------
        // MSG INTERFACE 2
		/**
			Will try to read a key pair from serial.
			[BLOKING] This will block till tout or msg is received.

			\param[in] tout Waiting time in millisecunds

			\return void
		*/
		void tryReadMsg(unsigned long tout);
		void tryReadMsg(const String& msg);
		void reset();

		// unsigned int cmdhash();

		String getValString(byte i);

		boolean hasValidMsg();
		unsigned int msgHash();
		String msgCsvLineString();

		// ----------------------------------------------------
		// MSG VAL STRING QUERIES
		boolean hasValString(byte i, const String& str);
		boolean hasValStringPrefix(byte i, const String& prefix);
		boolean hasValStringSuffix(byte i, const String& suffix);

		// ----------------------------------------------------
		// SEND MSG
		template <typename Arg>
		void sendMsg(Arg arg0) {
			this->Ch->pSERIAL->println(CSV_LINE_INIT_CHAR, arg0, CSV_LINE_END_CHAR);
		}
		template <typename T0, typename... Ts>
		void sendMsg(T0 arg0, Ts... args) {
			this->Ch->pSERIAL->print(CSV_LINE_INIT_CHAR);
			_printCSVVals(arg0, args...);
			this->Ch->pSERIAL->println(CSV_LINE_END_CHAR);
		};

		// utils
		template <typename Arg>
		void _printCSVVals(Arg arg) { this->Ch->pSERIAL->print(arg);}
		// variadic template with one or more arguments.
		template <typename First, typename... Args>
		void _printCSVVals(First first, Args... args) {
			this->Ch->pSERIAL->print(first); 
			this->Ch->pSERIAL->print(CSV_LINE_SEP_CHAR); 
			_printCSVVals(args...);
		}

		// ----------------------------------------------------
		// RESPONSE INTERFACE
		// Example $AKW:MSG-HASH:TIMETAG:RECIEVED%
		// Example $RES:MSG-HASH:RES_COUNT:BLA:BLE:BLI%
		// Example $AKW:MSG-HASH:TIMETAG:DONE%
		template <typename T0, typename... Ts>
		void sendMsgResponse(T0 arg0, Ts... args) {
			this->sendMsg("RES", this->hash, this->respcount, arg0, args...);
			this->respcount++;
		};
		void sendMsgResponse() { this->respcount++; } // empty response
		void openMsgResponse();
		void closeMsgResponse();

		// ----------------------------------------------------
		template <typename T0, typename... Ts>
		void sendMsgAcknowladge(T0 arg0, Ts... args) {
			this->Ch->pMSG->sendMsg(
				MSG_ACKNOWLADGE_TOKEN,
				this->Ch->pMSG->hash, 
				this->Ch->nowTimeTag(),
				arg0, args...
			);
		}
};

#endif // CMD_HANDLER_H