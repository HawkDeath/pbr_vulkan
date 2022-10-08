#include <rwVulkanInstance.h>
#include <rwPhysicalDevice.h>
#include <rwLog.h>
#include <cstring>
#include <functional>
#include <algorithm>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace rw
{

  namespace
  {
    bool enable_extension(const char* requiredExtensionName, const std::vector<VkExtensionProperties>& availableExts, std::vector<const char*>& enabledExtesions)
    {
      for (auto& availableExtesion : availableExts)
      {
        if (strcmp(availableExtesion.extensionName, requiredExtensionName) == 0)
        {
          auto it = std::find_if(enabledExtesions.begin(), enabledExtesions.end(),
            [requiredExtensionName](const char* enabledExtName) {
              return strcmp(enabledExtName, requiredExtensionName) == 0;
            });
          if (it != enabledExtesions.end())
          {
            LOG("{} - extension is already enabled.", requiredExtensionName);
          }
          else
          {
            LOG("Extension {} found, enabling it.", requiredExtensionName);
            
          }
        // enabledExtesions.push_back(requiredExtensionName);
          return true;
        }
      }

      WLOG("Extension {} not found.", requiredExtensionName);
      return false;
    }
  }

  VulkanInstance::VulkanInstance(const std::string& appName, const std::unordered_map<const char*, bool>& requiredExtensions, uint32_t vulkanVersion)
  {
    uint32_t instanceExtCount;
    VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtCount, nullptr), "Failed to check instance extesnion properties");

    std::vector<VkExtensionProperties> availableInstanceExtensions(instanceExtCount);
    VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtCount, availableInstanceExtensions.data()), "Failed to check instance extesnion properties");

    // mEnabledExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

    uint32_t glfwExtCount = 0U;
    const char** glfwExt = glfwGetRequiredInstanceExtensions(&glfwExtCount);

    mEnabledExtensions = std::vector<const char*>(glfwExt, glfwExt + glfwExtCount);

    enable_extension(VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME, availableInstanceExtensions, mEnabledExtensions);

    LOG("Enabled extensions:");
    for (auto& ext : mEnabledExtensions)
    {
      LOG("\t{}", ext);
    }

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = std::string(appName + "_engine").c_str();
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = vulkanVersion;
    appInfo.pNext = nullptr;

    VkInstanceCreateInfo instanceInfo;
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(mEnabledExtensions.size());
    instanceInfo.ppEnabledExtensionNames = mEnabledExtensions.data();
    instanceInfo.enabledLayerCount = 0U;
    instanceInfo.ppEnabledLayerNames = nullptr;
    instanceInfo.pNext = nullptr;
    instanceInfo.flags = VkInstanceCreateFlags(0);

    VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &mInstance), "Failed to create Vulkan instance");

    query_gpus();
  }

  VulkanInstance::~VulkanInstance()
  {
    vkDestroyInstance(mInstance, nullptr);
  }

  void VulkanInstance::query_gpus()
  {
    uint32_t physicalDeviceCount = { 0 };
    VK_CHECK(vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, nullptr), "Cannot get number of physical devices");
    if (physicalDeviceCount < 1)
    {
      RT_THROW("Couldn't find a phisical device that support Vulkan API.");
    }

    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    VK_CHECK(vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, physicalDevices.data()), "Cannot get information about physical devices");

    for (auto& phyDevice : physicalDevices)
    {
      mGpus.push_back(std::make_unique<PhysicalDevice>(*this, phyDevice));
    }
  }

  PhysicalDevice& VulkanInstance::getFirstPhysicalDevice()
  {
    if (mGpus.empty()) RT_THROW("Physical device is not available");
    return *mGpus[0].get();
  }

  PhysicalDevice& VulkanInstance::getSuitablePhysicalDevice(VkSurfaceKHR surface)
  {
    return getFirstPhysicalDevice();
  }

  bool VulkanInstance::isEnabledExtension(const char* extensionsName) const
  {
    return std::find_if(mEnabledExtensions.begin(), mEnabledExtensions.end(),
      [extensionsName](const char* enabledExtension) { return strcmp(extensionsName, enabledExtension) == 0; }) != mEnabledExtensions.end();
  }

  const std::vector<const char*>& VulkanInstance::getExtensions()
  {
    return mEnabledExtensions;
  }

}