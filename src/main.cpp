#include <iostream>

#include <boost/thread/thread.hpp>
#include <CL/cl.hpp>

#include "ui.hpp"
#include "multi_thread.hpp"
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

	MT* mt = new MTD();
	mt->test1();
	delete mt;

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

	// Size of array
	int array_size = 1000*1000*100;

	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int)*array_size);
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int)*array_size);
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int)*array_size);

	int* A = new int[array_size];
	int* B = new int[array_size];
	for(int i = 0; i < array_size; i++)
	{
		A[i] = i;
		B[i] = i % 5;
	}
	//int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	//int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

	cl::CommandQueue queue(context, default_device);

	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int)*array_size, A);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int)*array_size, B);

	delete[] A;
	delete[] B;

	cl::Kernel simple_add(program, "simple_add");
	simple_add.setArg(0, buffer_A);
	simple_add.setArg(1, buffer_B);
	simple_add.setArg(2, buffer_C);

	// el::base::PerformanceTracker track_1;
	 TIMED_SCOPE(track_1, "track");
	PERFORMANCE_CHECKPOINT(track_1);
	int number_of_runs = 50;
	for(int i = 0; i < number_of_runs; i++)
	{
		queue.enqueueNDRangeKernel(simple_add, cl::NullRange, cl::NDRange(array_size), cl::NullRange);

	}

	// simple_add.setArg(0, buffer_C);
	// queue.enqueueNDRangeKernel(simple_add, cl::NullRange, cl::NDRange(10), cl::NullRange);


	int* C = new int[array_size];

	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*array_size, C);
	PERFORMANCE_CHECKPOINT(track_1);

	// std::cout << "Result: \n";
	// for(int i = 0; i < 10; i++) {
	//   std::cout << C[i] << " ";
	// }
	// std::cout << std::endl;

	delete[] C;

	// Show window
	// auto app = Gtk::Application::create(argc, argv, "org.ai.ai");
//
	// Ui ui;
	// return app->run(ui);
	return 0;
}

