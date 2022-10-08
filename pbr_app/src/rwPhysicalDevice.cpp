#include <rwPhysicalDevice.h>
#include <rwLog.h>

namespace rw
{

  struct DriverVersion
  {
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
  };

  PhysicalDevice::PhysicalDevice(VulkanInstance& instance, VkPhysicalDevice physicalDevice) : mInstance{ instance }, mPhysicalDevice{ physicalDevice }
  {
    vkGetPhysicalDeviceProperties(mPhysicalDevice, &mProperties);
    vkGetPhysicalDeviceFeatures(mPhysicalDevice, &mFeatures);
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemoryProperties);

    DriverVersion driverVersion = {
      ((mProperties.driverVersion) >> 22),
      (((mProperties.driverVersion) >> 12) & 0x3ff),
      ((mProperties.driverVersion) & 0xfff)
    };

    LOG("Found GPU: {}", mProperties.deviceName);
    LOG("\tDriverVersion: {}.{}.{}, Supported Vulkan Version: {}.{}.{}", driverVersion.major, driverVersion.minor, driverVersion.patch,
                                                                   VK_VERSION_MAJOR(mProperties.apiVersion),
                                                                   VK_VERSION_MINOR(mProperties.apiVersion),
                                                                   VK_VERSION_PATCH(mProperties.apiVersion));

    uint32_t queueFamilyPropertyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertyCount, nullptr);
    mQueueFamilyProperties = std::vector<VkQueueFamilyProperties>(queueFamilyPropertyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyPropertyCount, mQueueFamilyProperties.data());
  }

  PhysicalDevice::~PhysicalDevice()
  {
  }

  bool PhysicalDevice::isPresentSupported(VkSurfaceKHR surface, uint32_t queueIdx)
  {
    VkBool32 presentSupported = { VK_FALSE };
    if (surface != VK_NULL_HANDLE)
    {
      VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(mPhysicalDevice, queueIdx, surface, &presentSupported), "Failed to get information about surface");
    }
    return presentSupported;
  }
}