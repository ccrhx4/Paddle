#pragma once

#include "dpcpp.h"

namespace paddle {
namespace platform {
    std::vector<dpcpp::device> GetAvailableDevices();
    int GetIntelGPUDeviceCount();
    std::vector<int> GetIntelSelectedDevices();
    void SetIntelGPUDeviceId(int device_id);
}
}
