// Pre-requirement     : Installing Intel oneAPI
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

#include <oneapi/dpl/execution>
#include <oneapi/dpl/algorithm>
#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>

int main()
{
	bool run_on_cpu{ false }; // "true" to run on CPU, "false" to run on GPU

	sycl::queue queue_device;

	if (true == run_on_cpu) // Choosing 1st CPU to Run Algorithms on it
	{
		auto cpus = sycl::platform(sycl::cpu_selector_v).get_devices();
		if (cpus.size() < 0) {
			std::cout << "no CPUs Found to Run on" << std::endl;
			return -1;
		}
		sycl::queue queue_CPU(cpus[0]); // 1st CPU
		queue_device = queue_CPU;
	}
	else // Choosing 1st GPU to Run Algorithms on it
	{
		auto gpus = sycl::platform(sycl::gpu_selector_v).get_devices();
		if (gpus.size() < 0) {
			std::cout << "no GPUs Found to Run on" << std::endl;
			return -2;
		}
		sycl::queue queue_GPU(gpus[0]); // 1st GPU
		queue_device = queue_GPU;
	}

	std::vector<int> nums{ 9, 4, 0, 3, 1, 6, -4, 7 };

	oneapi::dpl::sort(oneapi::dpl::execution::make_device_policy(queue_device),
                         nums.begin(), nums.end());

	for (auto n : nums)
		std::cout << " " << n;
	std::cout << std::endl;
}
// Printed Result: -4 0 1 3 4 6 7 9
