
#pragma once
#include <CL/cl.hpp>


class Device{
	public:
		cl::Device device;
		cl::Context* context;
		cl::CommandQueue* queue;
		cl::Program::Sources sources;
		
		Device();
		virtual ~Device();

	private:
		void init();
		cl::Platform get_platform();
		cl::Device get_device(cl::Platform platform);
};
