# ModifyImage_OpenCL_c
## Introduction
This Program allow to modify an image (.bmp format) using punctual and local operations. 
It take in input a path to an image.bmp. If the path exists the image will be loaded using [DevIL](http://openil.sourceforge.net/) library. The pixels of the image will be converted into float and 
will be processed on the GPU using OpenCL library. 

## How it functions
1. Take an image.bmp as input;
2. Specify how many filters to apply (single or combined)
3. Select the filters for the appropriate modification
4. Save the output in the folder _/Image_

## Requirements
To Compile and Run the program you need to install and configure all necessary libraries:
* The gcc compiler, generally it is installed by default; if you haven't it, open the terminal and type the command (Debian/Ubuntu):
  * $_sudo apt-get install gcc_
* See this guide to install CUDA: [link to   instruction](http://docs.nvidia.com/cuda/cuda-installation-guide-linux/#axzz4KKVroazE)
* Here there is CUDA-TOOLKIT: [link to download](https://developer.nvidia.com/cuda-downloads)
* Note: If you have a propertie drivers, i reccomend to use bumblebee ([Debian](https://wiki.debian.org/it/Bumblebee) / [Ubuntu](https://wiki.ubuntu.com/Bumblebee)) instead of nouveau Nvidia driver.
* The [DevIL](http://openil.sourceforge.net/) library to load the image: [donwload](http://openil.sourceforge.net/download.php)
* The OpenCL library ([NVIDIA](https://developer.nvidia.com/opencl) / [AMD](http://developer.amd.com/tools-and-sdks/opencl-zone/)) library 
* To run the compiled program, i use optirun, it will be installed automatically with the bumblebee installation.

## The Program
The program is composed by some files:
* Program.c: Contains the main function, is here the kernel functions.
* dataStruct.c: Contains all necessary dataStructures
* filter_kernel.cl: Contains the .cl code functions
* initKernel.c: Contains a function to create the kernels
* setKernelSngle.c: Contains a function to set the Kernel's parameters for independent executions
* setKernelCombined.c: Contains a function to set the kernel's parameters for conditionated executions
* setOpenCLAmbient.c: Contains a function to set the Platform, Device, Context... for OpenCL (i.e. CPU or GPU or toghether)
Other files:
* Info.c: A Program to show some informations about GPU Devices
* Image: A folder to save the output images

## Compile and Run Info.c
Open the Terminal, move to the folder where is the program and type:
* $ _gcc -std=c99 -I /usr/include/CL -L /usr/lib/x86_64-linux-gnu/libOpenCL.so Info.c -o Info -lOpenCL_
* $ _optirun ./Info_

## Compile and Run the Program
Open the Terminal, move to the folder where is the program and type:
* $ _gcc -std=c99 -I /usr/include/CL -L /usr/lib/x86_64-linux-gnu/libOpenCL.so  -lIL -lILU -lILUT Program.c -o Main -lOpenCL_
* $ _optirun ./Main_

