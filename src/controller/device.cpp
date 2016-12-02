
#include "device.hpp"
#include <iostream>
#include "../easylogging++.h"

Device::Device() 
{
	init();
}

Device::~Device()
{
	if(context != NULL)
	{
		delete context;
	}
	if(queue != NULL) 
	{
		delete queue;
	}
}

void
Device::init()
{
	LOG(INFO) << "Queue wird erstellt";
	cl::Platform platform = get_platform();

	device = get_device(platform);

	context = new cl::Context({device});

	// Kernel calculates for each element C=A+B
	std::string kernel_code = 
		"	void kernel simple_add(global const int* A, global const int* B, global int* C){"
		"C[get_global_id(0)] = A[get_global_id(0)] + B[get_global_id(0)];"
		"}";
	sources.push_back({kernel_code.c_str(), kernel_code.length()});

	cl::Program program(*context, sources);
	if(program.build({device}) != CL_SUCCESS) {
		LOG(INFO) 
			<< "Error building: " 
			<< program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << "\n";
		exit(1);
	}

	// Size of array
	int array_size = 1000*1000*1;

	cl::Buffer buffer_A(*context, CL_MEM_READ_WRITE, sizeof(int)*array_size);
	cl::Buffer buffer_B(*context, CL_MEM_READ_WRITE, sizeof(int)*array_size);
	cl::Buffer buffer_C(*context, CL_MEM_READ_WRITE, sizeof(int)*array_size);

	int* A = new int[array_size];
	int* B = new int[array_size];
	for(int i = 0; i < array_size; i++)
	{
		A[i] = i;
		B[i] = i % 5;
	}
	//int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	//int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

	queue = new cl::CommandQueue(*context, device);
}

cl::Platform
Device::get_platform()
{
	// Get all Platforms
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);

	if(all_platforms.size()==0){
		LOG(INFO) << "No platforms found. Check OpenCL installation!\n";
		exit(1);
	}

	LOG(INFO) 
		<< "Using platform: " 
		<< all_platforms[0].getInfo<CL_PLATFORM_NAME>() << "\n";

	return all_platforms[0];
}

cl::Device 
Device::get_device(cl::Platform platform)
{
	// Get default device of the default platform
	std::vector<cl::Device> all_devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);

	if(all_devices.size()==0){
		LOG(INFO) << "No devices found. Check OpenCL installation!\n";
		exit(1);
	}

	LOG(INFO) 
		<< "Using device: " 
		<< all_devices[0].getInfo<CL_DEVICE_NAME>() << "\n";

	return all_devices[0];
}
