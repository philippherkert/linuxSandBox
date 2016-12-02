

#include "idle_state.hpp"
#include "controller.hpp"
#include "../easylogging++.h"

Controller::Controller()
{
	this->queue = new boost::lockfree::queue<Action*>(128);
	this->current_state = new Idle_State(this);
	controller_loop = true;
}

Controller::~Controller()
{
	delete queue;
	delete current_state;
	if(device != NULL) 
	{
		delete device;
	}
}

void
Controller::run()
{
	LOG(INFO) << "Run Method Started!";
	while(controller_loop)
	{
		current_state->act();
	}
}

void
Controller::action_push(Action* action)
{
	queue->push(action);
}

Action* 
Controller::message_pop()
{
	Action* tmp_action = NULL;
	queue->pop(tmp_action);
	return tmp_action;
}

void
Controller::stop_thread()
{
	controller_loop = false;
}
