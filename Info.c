/* Created by Alessandro Bigiotti */

// Include c library
#include <stdio.h>
#include <stdlib.h>

// Include OpenCL library
#include "CL/cl.h"
#include "CL/opencl.h"

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

#define CL_CHECK(_expr)    \
  do {                    \
    cl_int _err = _expr;  \
    if(_err == CL_SUCCESS)\
      break;\
    fprintf(stderr, "OpenCL Error: '%s' returned %d!\n", #_expr, (int)_err);\
    abort();\
  } while (0)

int main(int argc, char** argv){
  // The number of Platforms and its id
  cl_uint Num_Platform = 0;
  cl_platform_id Platform_id[10];

  // The number of Devices and its id
  cl_device_id Devices_id[10];
  cl_uint Num_Device = 0;


  CL_CHECK(clGetPlatformIDs(10,Platform_id, &Num_Platform));
  char buffer[10240];
  /* Show informations about the available Platforms */
  printf("== %d OpenCL Platform(s) found: ==\n", Num_Platform);
  for(int i=0; i<Num_Platform; i++){
    // for each Platform show some informations
    printf(" Platform id -- %d -- \n", i);
    CL_CHECK(clGetPlatformInfo(Platform_id[i], CL_PLATFORM_PROFILE, 1024, buffer, NULL));
    printf("  PROFILE - %s\n", buffer);
    CL_CHECK(clGetPlatformInfo(Platform_id[i], CL_PLATFORM_VERSION, 1024, buffer, NULL));
    printf("  VERSION - %s\n", buffer);
    CL_CHECK(clGetPlatformInfo(Platform_id[i], CL_PLATFORM_NAME, 1024, buffer, NULL));
    printf("  NAME - %s\n", buffer);
    CL_CHECK(clGetPlatformInfo(Platform_id[i], CL_PLATFORM_VENDOR, 1024, buffer, NULL));
    printf("  VENDOR - %s\n", buffer);
    CL_CHECK(clGetPlatformInfo(Platform_id[i], CL_PLATFORM_EXTENSIONS, 1024, buffer, NULL));
    printf("  EXTENSIONS - %s\n", buffer);


  }
  /* Show Informations about devices */
  CL_CHECK(clGetDeviceIDs(Platform_id[1], CL_DEVICE_TYPE_GPU, 10, Devices_id, &Num_Device));
  for(int k=0; k<Num_Device; k++){
    // for each device show some informations
    cl_uint buff_uint;
    cl_ulong buff_ulong;
    printf(" Device id -- %d --\n", k);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DEVICE_NAME, 1024, buffer, NULL));
    printf("  DEVICE_NAME = %s\n", buffer);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DEVICE_VENDOR, 1024, buffer, NULL));
    printf("  DEVICE_VENDOR = %s\n", buffer);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DEVICE_VERSION, 1024, buffer, NULL));
    printf("  DEVICE_VERSION = %s\n", buffer);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DRIVER_VERSION, 1024, buffer, NULL));
    printf("  DRIVER_VERSION = %s\n", buffer);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buff_uint), &buff_uint, NULL));
    printf("  MAX_COMPUTE = %u\n", (unsigned int)buff_uint);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(buff_uint), &buff_uint, NULL));
    printf("  MAX_CLOCK = %u\n", (unsigned int)buff_uint);
    CL_CHECK(clGetDeviceInfo(Devices_id[0], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(buff_ulong), &buff_ulong, NULL));
    printf("  GLOBAL_MEM = %u\n", (unsigned int)buff_ulong);
  }
return 0;
}
