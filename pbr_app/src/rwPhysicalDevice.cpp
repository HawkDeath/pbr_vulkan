#include <rwPhysicalDevice.h>

namespace rw
{

  PhysicalDevice::PhysicalDevice(VulkanInstance& instance, VkPhysicalDevice physicalDevice) : mInstance{ instance }, mPhysicalDevice{ physicalDevice }
  {
  }

  PhysicalDevice::~PhysicalDevice()
  {
  }
}