#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

// A state container for tracking progress of a concurrent task
class ConcurrentTask {
	private:
		long todo;
		long state;

	public:
		ConcurrentTask();

		bool is_todo();

		void at_init();

		void reset();

		void at_exit();

		bool is_running();

};

#endif // CONCURRENT_TASK_H