
#include <iostream>

#include "multi_thread.hpp"

#include "easylogging++.h"

using namespace std;

MT::MT()
{

}

MT::~MT()
{

}

void
MT::test1()
{
	cout << "MT Test!\n";
}

MTD::MTD()
{

}

MTD::~MTD()
{

}
void
MTD::test1()
{
	cout << "MTD Test!\n";
	LOG(INFO) << "MTD invoked.";
}


