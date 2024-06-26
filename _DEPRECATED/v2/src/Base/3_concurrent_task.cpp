#include "Base/1_config.h"
#include "Base/3_concurrent_task.h"

ConcurrentTask::ConcurrentTask() { 
	reset();
}

bool ConcurrentTask::is_todo() { this->state++; return this->state == this->todo; }

void ConcurrentTask::at_init() { this->state = 0; this->todo++;}

void ConcurrentTask::reset() { this->state = 0; this->todo = 0; }

void ConcurrentTask::at_exit() { reset(); }

bool ConcurrentTask::is_running() { return this->todo > 0; }