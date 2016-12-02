
#include "load_action.hpp"
#include "../device.hpp"
#include "../../easylogging++.h"

Load_Action::Load_Action()
{

}

Load_Action::~Load_Action()
{

}

void
Load_Action::visit(State* state)
{
	LOG(INFO) << "Loading Ai.";
	// state->controller->stop_thread();
	state->controller->device = new Device();
}
