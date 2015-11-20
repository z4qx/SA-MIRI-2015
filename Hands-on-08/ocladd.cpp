#include <CL/cl.h>
#include <stdio.h>
#include <string.h>

// Application constants
const size_t local = 1024;
const size_t global = local*128;

const char code_init[] = "__kernel void init(__global float *out) { \
		const uint index = get_global_id(0); \
		out[index] = 1.0f; \
	}";
const char code_add[] = "__kernel void add(__global float *inout, \
	__global float *in) { \
		const uint index = get_global_id(0); \
		inout[index] = inout[index] + in[index]; \
	}";

int main(int argc, char** argv) {
        cl_platform_id platform;
        cl_device_id devices[2];

	clGetPlatformIDs(1, &platform, NULL);
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, devices, NULL);
	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0};
	cl_context context = clCreateContext(properties, 1, devices, NULL, NULL, NULL);
	cl_command_queue cq1 = clCreateCommandQueue(context, devices[0], 0, NULL);
	
	uint buffSizeInBytes = global*sizeof(float);
	float buf[global];
	cl_mem device_buf1 = clCreateBuffer(context, CL_MEM_READ_WRITE, buffSizeInBytes, NULL, NULL);
	cl_mem device_buf2 = clCreateBuffer(context, CL_MEM_READ_WRITE, buffSizeInBytes, NULL, NULL);

	size_t initsrcsize = strlen(code_init);
	const char *initsrcptr[] = {code_init};
	size_t addsrcsize = strlen(code_add);
	const char *addsrcptr[] = {code_add};

	cl_program initprog=clCreateProgramWithSource(context, 1, initsrcptr, &initsrcsize, NULL);
	clBuildProgram(initprog, 0, NULL, "", NULL, NULL);
	cl_program addprog=clCreateProgramWithSource(context, 1, addsrcptr, &addsrcsize, NULL);
	clBuildProgram(addprog, 0, NULL, "", NULL, NULL);
	cl_kernel initK = clCreateKernel(initprog, "init", NULL);
	cl_kernel addK = clCreateKernel(addprog, "add", NULL);

	clSetKernelArg(initK, 0, buffSizeInBytes, &device_buf1);
	clEnqueueNDRangeKernel(cq1, initK, 1, NULL, &local, &global, 0, NULL, NULL);
	clSetKernelArg(initK, 0, buffSizeInBytes, &device_buf2);
	clEnqueueNDRangeKernel(cq1, initK, 1, NULL, &local, &global, 0, NULL, NULL);
	printf("Initializing buffers...\n");
	clFinish(cq1); 

	clSetKernelArg(addK, 0, buffSizeInBytes, &device_buf1);
	clSetKernelArg(addK, 1, buffSizeInBytes, &device_buf2);
	clEnqueueNDRangeKernel(cq1, addK, 1, NULL, &local, &global, 0, NULL, NULL);
	clEnqueueReadBuffer(cq1, device_buf1, CL_FALSE, 0, buffSizeInBytes, buf, 0, NULL, NULL);
	printf("Adding buffers...\n");
	clFinish(cq1);

	return 0;
}

