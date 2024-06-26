#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

#define TIMER_ROLLING_MODE 0
#define TIMER_FIXED_MODE 1

// TODO: move out implementation

// A class to handle time intervals trigered actions
class Timer {
	private:
		byte mode;
		unsigned long period;
		unsigned long next_event;
		unsigned long event_count;

	public:
		Timer(unsigned long period, byte mode);
		
        Timer();

		void set_mode(byte mode);

		void set_next(byte mode); 
		
		void set_next();

		unsigned long get_next();

		// Set a new period and recompute next event
		void set_period(unsigned long new_period, byte mode);
		void set_period(unsigned long new_period);

		unsigned long get_period();

		unsigned long time_to_event();

		unsigned long get_event_count();

		// check if it is time for the event to occur and advance to next_event
		bool istime(byte mode);
		bool istime();

		bool notyet(byte mode);
		bool notyet();

		// check if it is time for the event but do not advance the Timer
		bool dry_istime();

		bool dry_notyet();

		void wait();
};

#endif // TIMER_H