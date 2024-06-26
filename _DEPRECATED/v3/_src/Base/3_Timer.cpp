#include "Base/1_config.h"
#include "Base/1_constants.h"
#include "Base/3_Timer.h"

Timer::Timer(unsigned long period, byte mode) { 
    this->mode = mode;
    this->event_count = 0;
    this->period = period;
    this->next_event = millis() + this->period;
}

Timer::Timer() { Timer(INFTY_LONG, TIMER_FIXED_MODE); }

void Timer::set_mode(byte mode) {this->mode = mode; }

void Timer::set_next(byte mode) {
	if (mode == TIMER_ROLLING_MODE) {
		this->next_event = millis() + this->period;
		return;
	} 
	if (mode == TIMER_FIXED_MODE) {
		this->next_event = this->next_event + this->period;
		return;
	} 
}
void Timer::set_next() { set_next(this->mode); }

unsigned long Timer::get_next() { return this->next_event; }

// Set a new period and recompute next event
void Timer::set_period(unsigned long new_period, byte mode) {
	if (this->period == new_period) { return; }
	this->period = new_period;
	set_next(mode);
}
void Timer::set_period(unsigned long new_period) {
	set_period(new_period, this->mode) ;
}

unsigned long Timer::get_period() { return this->period; }

unsigned long Timer::time_to_event() { return this->next_event - millis(); }

unsigned long Timer::get_event_count() { return this->event_count; }

// check if it is time for the event to occur and advance to next_event
bool Timer::istime(byte mode) {
	if (millis() > get_next()) {
		set_next(mode); 
		this->event_count++;
		return true;
	}
	return false;
}
bool Timer::istime() { return istime(this->mode);}

bool Timer::notyet(byte mode) { return !istime(mode); }
bool Timer::notyet() { return !istime(); }

// check if it is time for the event but do not advance the Timer
bool Timer::dry_istime() {
	return millis() > this->next_event;
}

bool Timer::dry_notyet() { return !dry_istime(); }

void Timer::wait() { while (dry_notyet()) {;}}