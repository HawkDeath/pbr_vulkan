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
    mProperties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    mProperties2.pNext = VK_NULL_HANDLE;
    vkGetPhysicalDeviceProperties2(mPhysicalDevice, &mProperties2);

    vkGetPhysicalDeviceFeatures(mPhysicalDevice, &mFeatures);
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemoryProperties);

    DriverVersion driverVersion;
    switch (mProperties2.properties.vendorID)
    {
    case 0x10DE:
      driverVersion.major = (mProperties2.properties.driverVersion >> 22) & 0x3ff;
      driverVersion.minor = (mProperties2.properties.driverVersion >> 14) & 0x0ff;
      driverVersion.patch = (mProperties2.properties.driverVersion >> 6) & 0x0ff;
      break;
    case 0x8086:
      driverVersion.major = (mProperties2.properties.driverVersion >> 14) & 0x3ffff;
      driverVersion.minor = mProperties2.properties.driverVersion & 0x3ffff;
      break;
    default:
      driverVersion.major = VK_VERSION_MAJOR(mProperties2.properties.driverVersion);
      driverVersion.minor = VK_VERSION_MINOR(mProperties2.properties.driverVersion);
      driverVersion.patch = VK_VERSION_PATCH(mProperties2.properties.driverVersion);
      break;
    }

    LOG("Found GPU: {}", mProperties2.properties.deviceName);
    LOG("\tDriverVersion: {}.{}.{}, Supported Vulkan Version: {}.{}.{}",
                                                                        driverVersion.major,
                                                                        driverVersion.minor,
                                                                        driverVersion.patch,
                                                                        VK_VERSION_MAJOR(mProperties2.properties.apiVersion),
                                                                        VK_VERSION_MINOR(mProperties2.properties.apiVersion),
                                                                        VK_VERSION_PATCH(mProperties2.properties.apiVersion));

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