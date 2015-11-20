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
const char code_prod[] = "__kernel void prod(__global float *inout, \
	__global float *in) { \
		const uint index = get_global_id(0); \
		inout[index] = inout[index] * in[index]; \
	}";

int main(int argc, char** argv) {
	cl_platform_id platform;
        cl_device_id devices[1];

	clGetPlatformIDs(1, &platform, NULL);
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, devices, NULL);
	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0};
	cl_context context = clCreateContext(properties, 1, devices, NULL, NULL, NULL);
	cl_command_queue cq1 = clCreateCommandQueue(context, devices[0], 0, NULL);
	
	size_t buffSizeInBytes = global*sizeof(float);
	float buf[global];
	cl_mem device_buf1 = clCreateBuffer(context, CL_MEM_READ_WRITE, buffSizeInBytes, NULL, NULL);
	cl_mem device_buf2 = clCreateBuffer(context, CL_MEM_READ_WRITE, buffSizeInBytes, NULL, NULL);

	size_t initsrcsize = strlen(code_init);
	const char *initsrcptr[] = {code_init};
	size_t prodsrcsize = strlen(code_prod);
	const char *prodsrcptr[] = {code_prod};

	cl_program initprog=clCreateProgramWithSource(context, 1, initsrcptr, &initsrcsize, NULL);
	clBuildProgram(initprog, 0, NULL, "", NULL, NULL);
	cl_program prodprog=clCreateProgramWithSource(context, 1, prodsrcptr, &prodsrcsize, NULL);
	clBuildProgram(prodprog, 0, NULL, "", NULL, NULL);
	cl_kernel initK = clCreateKernel(initprog, "init", NULL);
	cl_kernel prodK = clCreateKernel(prodprog, "prod", NULL);

	clSetKernelArg(initK, 0, sizeof(cl_mem), &device_buf1);
	clEnqueueNDRangeKernel(cq1, initK, 1, NULL, &global, &local, 0, NULL, NULL);
	clSetKernelArg(initK, 0, sizeof(cl_mem), &device_buf2);
	clEnqueueNDRangeKernel(cq1, initK, 1, NULL, &global, &local, 0, NULL, NULL);
	printf("Initializing buffers...\n");
	clFinish(cq1); 

	clSetKernelArg(prodK, 0, sizeof(cl_mem), &device_buf1);
	clSetKernelArg(prodK, 1, sizeof(cl_mem), &device_buf2);
	clEnqueueNDRangeKernel(cq1, prodK, 1, NULL, &global, &local, 0, NULL, NULL);
	clEnqueueReadBuffer(cq1, device_buf1, CL_FALSE, 0, buffSizeInBytes, buf, 0, NULL, NULL);
	printf("Calculating pairwise product...\n");
	clFinish(cq1);

	float result = 0;
	for (int i = 0; i < global; ++i) {
		result += buf[i];
	}
	printf("Dot product: %f\n", result);

	return 0;
}

