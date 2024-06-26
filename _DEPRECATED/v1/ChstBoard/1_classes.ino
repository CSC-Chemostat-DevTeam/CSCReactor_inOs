#define TIMER_INF 1000000000
class Timer {
	private:
		long period;
		long next_event;
		long event_count;

	public:
		Timer(long period) { 
			this->event_count = 0;
			this->period = period;
			set_next();
		}

		Timer() { Timer(TIMER_INF); }

		void set_next(long event) { this->next_event = event; }

		void set_next() { set_next(millis() + this->period); }

		long get_next() { return this->next_event; }

		void set_period(long new_period) {
			if (this->period == new_period) { return; }
			this->period = new_period;
			set_next();
		}

		long get_period() { return this->period; }

		long time_to_event() { return this->next_event - millis(); }

		long get_event_count() { return this->event_count; }

		bool istime() {
			if (millis() > this->next_event) {
				set_next(); 
				this->event_count++;
				return true;
			}
			return false;
		}

		bool notyet() { return !istime(); }
};

class Concurrent {
	private:
		long todo;
		long state;

	public:
		Concurrent() { 
			reset();
		}

		bool is_todo() { this->state++; return this->state == this->todo; }

		void at_init() { this->state = 0; this->todo++;}

		void reset() { this->state = 0; this->todo = 0; }

		void at_exit() { reset(); }

		bool is_running() { return this->todo > 0; }

};