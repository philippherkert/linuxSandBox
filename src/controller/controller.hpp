
/**
 * Controlls the Modell
 */

#pragma once

#include <boost/lockfree/queue.hpp>

#include "action/action.hpp"
#include "state.hpp"

class Action;
class State;

class Controller
{
	public:
		Controller();
		~Controller();

		void run();
		void action_push(Action* action);
		State* current_state;
		Action* message_pop();
		void stop_thread();

	protected:
		boost::lockfree::queue<Action*>* queue;

	private:
		bool controller_loop;
};
