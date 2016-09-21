# ModifyImage_OpenCL_c
## Introduction
This Program allow to modify an image (.bmp format) using punctual and local operations. 
It take in input a path to an image.bmp. If the path exists the image will be loaded using [DevIL](http://openil.sourceforge.net/) library. The pixels of the image will be converted into float and 
will be processed into GPU using OpenCL library.

## Requests
To Compile and Run the program you need to install and configure all necessary library:
* The gcc compiler, generally it is installed by default; if you haven't it, open the terminal and type the command(Debian/Ubuntu):
  * $_sudo apt-get install gcc_
* See this guide to install CUDA: [link to instruction](http://docs.nvidia.com/cuda/cuda-installation-guide-linux/#axzz4KKVroazE)
* Here there is CUDA-TOOLKIT: [link to download](https://developer.nvidia.com/cuda-downloads)
* Note: If you have a propertie drivers, i reccomend to use bumblebee ([Debian](https://wiki.debian.org/it/Bumblebee) / [Ubuntu](https://wiki.ubuntu.com/Bumblebee)) instead of nouveau Nvidia driver.
* The [DevIL](http://openil.sourceforge.net/) library to load the image: [donwload](http://openil.sourceforge.net/download.php)
* The OpenCL library ([NVIDIA](https://developer.nvidia.com/opencl)/[AMD](http://developer.amd.com/tools-and-sdks/opencl-zone/)) library 
* To run the compiled program, i use optirun, it will install automatically with the bumblebee installation.

## The Program
The program is composed by some files:
* Program.c: Contains the main function, is here that will run the kernels.
* dataStruct.c: Contains all necessary dataStructures
* filter_kernel.cl: Contains the .cl code functions
* initKernel.c: Contains a function to create the kernels
* setKernel.c: Contains a function to set the Kernels parameters
* setOpenCLAmbient.c: Contains a function to set the Platform, Device, Context... for OpenCL
