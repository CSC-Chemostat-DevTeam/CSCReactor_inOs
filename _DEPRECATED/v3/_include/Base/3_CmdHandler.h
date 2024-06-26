#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#include <SD.h>
#include "Base/2_utils.h"
#include "Base/3_AbsHandler.h"
#include "Base/3_KVReader.h"
#include "Base/3_SerialHandler.h"
#include "Base/3_Chemostat.h"

#define CMD_INPUT_TIMEOUT 300 // ms

// A subsystem for reciving and executing commands from a PC
class CmdHandler :
    public AbsHandler
{       
	private:
		KVReader kvreader;
		unsigned long respcount;

	public:

		// ----------------------------------------------------
        // CONSTRUCTOR
		CmdHandler(Chemostat* Ch);

		// ----------------------------------------------------
        // SKETCH INTERFACE
		void onsetup();
		
		void onloop();

		// ----------------------------------------------------
        // CMD INTERFACE
		virtual boolean execCmd();

		// ----------------------------------------------------
        // CMD INTERFACE 2
		/**
			Will try to read a key pair from serial.
			[BLOKING] This will block till tout or msg is received.

			\param[in] tout Waiting time in millisecunds

			\return void
		*/
		void tryReadCmd(unsigned long tout);
		void reset();

		unsigned int cmdhash();

		// TODO: implement a full recieve responce cmd system
		// Serial.print the responce of the commands
		// Responce ex. HASH reponse...
		// The current Akw message is just a responce

		/**
			get the current key as String.
		*/
		String getCmdKey();

		/**
			get the current val as String.
		*/
		String getCmdVal();
		String getCmdVal0();
		String getCmdVal1();
		String getCmdVal2();

		boolean hasValidCmd();
		unsigned int cmdHash();
		String cmdKvString();

		boolean hasKey(const String& str);
		boolean hasKeyPrefix(const String& prefix);
		boolean hasKeySuffix(const String& suffix);

		// ----------------------------------------------------
		// RESPONSE INTERFACE
		template <typename T0, typename... Ts>
		void response(T0 arg0, Ts... args) {
			this->Ch->pSERIAL->println(this->respcount, " | ", arg0, args...);
			this->respcount++;
		};
		void open_response();
		void close_response();

		// ----------------------------------------------------
		// REQUEST INTERFACE
		boolean request(String req);
};

#endif // CMD_HANDLER_H