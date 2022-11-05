#include <rwDevice.h>

namespace rw
{

  Device::Device(VulkanInstance& instance, VkSurfaceKHR surface, std::unordered_map<const char*, bool> requiredExtensions) : mInstance{instance}, mSurface{surface}
  {
  }

  Device::~Device()
  {
  }
}