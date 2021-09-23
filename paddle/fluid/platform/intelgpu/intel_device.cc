#include "intel_device.h"
#include <mutex>

namespace paddle {
namespace platform {
    static thread_local int current_gpu_id = 0;
    std::mutex mutex;

    std::vector<dpcpp::device> GetAvailableDevices() {
	std::vector<dpcpp::device> root_devices;
        auto plaform_list = dpcpp::platform::get_platforms();
	for (const auto& platform : plaform_list) {
	    auto device_list = platform.get_devices();
	    for (const auto& device : device_list) {
                if (device.is_gpu()) {
                    root_devices.push_back(device);
                }
            }
	}
        
	std::vector<dpcpp::device> devices;

	for (const auto& root_device : root_devices) {
             std::vector<dpcpp::device> sub_devices;
             try {
                sub_devices = root_device.create_sub_devices<dpcpp::info::partition_property::partition_by_affinity_domain>(
                    dpcpp::info::partition_affinity_domain::next_partitionable);
                devices.insert(devices.end(), sub_devices.begin(), sub_devices.end());
             } catch (dpcpp::feature_not_supported& e) {
                devices.push_back(root_device);
             }
        }

	return devices;
    }

    int GetDeviceCount() {
        std::vector<dpcpp::device> all_gpus = GetAvailableDevices();
	return all_gpus.size();
    }

    std::vector<int> GetIntelSelectedDevices() {
	std::vector<int> devices;
	int count = GetDeviceCount();
        
	for (int i = 0; i < count; ++i) {
             devices.push_back(i);
        }
	return devices;
    }

    void SetIntelGPUDeviceId(int device_id) {
        std::lock_guard<std::mutex> lock(mutex);
	current_gpu_id = device_id;
    }
  }
}
