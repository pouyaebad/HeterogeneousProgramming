// Pre-requirement     : Installing CUDA and integrating it to Visual Studio
//
// On Windows          : Visual Studio,
//                       Create CUDA type project or add CUDA to project:
//                       Right Click on Project in the Solution Explorer then
//                       Built Dependencies | Built Customizations... | check CUDA 
// Note                : file name should have .cu extension

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>

__global__ void thread_in_GPU (int* nums_in_GPU, int *subTot_in_GPU)
{
    int threadNo = threadIdx.x;
    subTot_in_GPU[threadNo] = nums_in_GPU[threadNo*2]+nums_in_GPU[threadNo*2 + 1];
}

int main()
{
    int nums[] = { 33, 12, -5, 15 }, subTot[2], *nums_in_GPU, *subTot_in_GPU;
    int sNums{std::size(nums)*sizeof(int)}, sSubTot{std::size(subTot)*sizeof(int)};


    if (cudaSuccess != cudaSetDevice(0)) return -1;//Select a GPU to run code on it
    if (cudaSuccess != cudaMalloc((void**)&nums_in_GPU, sNums)) return -2;
    if (cudaSuccess != cudaMalloc((void**)&subTot_in_GPU, sSubTot)) return -3;

    if (cudaSuccess != cudaMemcpy(nums_in_GPU, nums, sNums,cudaMemcpyHostToDevice))
        return -4;

    thread_in_GPU <<<1, 2 >>> (nums_in_GPU, subTot_in_GPU);//Creates 1*2= 2 THREADS

    if (cudaSuccess != cudaDeviceSynchronize()) return -5; // Wait threads finish

  if (cudaSuccess!=cudaMemcpy(subTot,subTot_in_GPU,sSubTot,cudaMemcpyDeviceToHost))
        return -6;

    cudaFree(nums_in_GPU);
    cudaFree(subTot_in_GPU);

    cudaDeviceReset();

    int grand_total{ subTot[0] + subTot[1] };

    std::cout << "Sum of all numbers is: " << grand_total << std::endl;
}

// Printed Result: 55
