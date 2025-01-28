// Pre-requirement     : Installing Intel oneAPI (one of SYCL implementations)
//
// On Windows option 1 : icpx -fsycl  file_name.cpp (see notes on the next page)
//
// On Windows option 2 : Visual Studio 
//                       Create “DPC++ Console” type project then in the 
//                       Solution Explorer, right click on the project and in the 
//                       "Project Properties | Configuration | VC++ Directories” 
//                       Add C:\Program Files(x86)\Intel\oneAPI\2025.0\include
//				  	 to "Include Directors" and
//                       Add C:\Program Files(x86)\Intel\oneAPI\2025.0\lib
//					 to "Library Directors"
//

#include <sycl/sycl.hpp>
#include <iostream>

int main()
{
	auto cpus = sycl::platform(sycl::cpu_selector_v).get_devices();
	auto gpus = sycl::platform(sycl::gpu_selector_v).get_devices();


	std::cout << "List of CPUs:" << std::endl;
	for (auto cpu : cpus) {
	    sycl::queue qCPU(cpu);
	    std::cout<<"\t"<<qCPU.get_device().get_info<sycl::info::device::name>();
	    std::cout << std::endl;
	}

	std::cout << std::endl << "List of GPUs:" << std::endl;
	for (auto gpu : gpus) {
	    sycl::queue qGPU(gpu);
	    std::cout<<"\t"<<qGPU.get_device().get_info<sycl::info::device::name>();
	    std::cout << std::endl;
	}
}
