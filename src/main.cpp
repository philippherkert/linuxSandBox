#include <iostream>

#include <CL/cl.hpp>

#include "ui.hpp"
#include "main.hpp"


#include "easylogging++.h"

// This initializes the logger. This is only 
// done once for all files
INITIALIZE_EASYLOGGINGPP

int test(int r);
void noTest(int k);
int main(int argc, char *argv[]) {

	el::Configurations conf("logger.conf");
	// Reconfigure single logger
	//el::Loggers::reconfigureLogger("default", conf);
	// Reconfigure all loggers
	el::Loggers::reconfigureAllLoggers(conf);

	START_EASYLOGGINGPP(argc, argv);

	LOG(INFO) << "Logger Test";
	std::cout << "OpenCL Test - Setting Git" << std::endl;

	// Get all Platforms
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if(all_platforms.size()==0){
		std::cout << "No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	// Get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if(all_devices.size()==0){
		std::cout << "No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device=all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

	cl::Context context({default_device});
	cl::Program::Sources sources;

	// Kernel calculates for each element C=A+B
	std::string kernel_code = 
		"	void kernel simple_add(global const int* A, global const int* B, global int* C){"
		"C[get_global_id(0)] = A[get_global_id(0)] + B[get_global_id(0)];"
		"}";
	sources.push_back({kernel_code.c_str(), kernel_code.length()});

	cl::Program program(context, sources);
	if(program.build({default_device}) != CL_SUCCESS) {
		std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
		exit(1);
	}
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int)*10);
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int)*10);
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int)*10);

	int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

	cl::CommandQueue queue(context, default_device);

	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int)*10, A);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int)*10, B);

	cl::Kernel simple_add(program, "simple_add");
	simple_add.setArg(0, buffer_A);
	simple_add.setArg(1, buffer_B);
	simple_add.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(simple_add, cl::NullRange, cl::NDRange(10), cl::NullRange);

	int C[10];

	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*10, C);

	std::cout << "Result: \n";
	for(int i = 0; i < 10; i++) {
		std::cout << C[i] << " ";
	}
	std::cout << std::endl;



	// Show window
	auto app = Gtk::Application::create(argc, argv, "org.ai.ai");

	Ui ui;
	return app->run(ui);
}

