
#include "load_action.hpp"
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
}
