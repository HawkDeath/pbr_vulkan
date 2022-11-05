#ifndef RWVULKANINSTANCE_H
#define RWVULKANINSTNACE_H

#include <vulkan/vulkan.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace rw
{
  class PhysicalDevice;

  class VulkanInstance
  {
  public:
    VulkanInstance(const std::string& appName, const std::unordered_map<const char*, bool>& requiredExtensions = {}, uint32_t vulkanVersion = VK_MAKE_VERSION(1, 1, 0));
    ~VulkanInstance();

    VulkanInstance(const VulkanInstance&) = delete;
    VulkanInstance& operator=(const VulkanInstance&) = delete;
    VulkanInstance(VulkanInstance&&) = delete;
    VulkanInstance& operator=(VulkanInstance&&) = delete;

    PhysicalDevice& getFirstPhysicalDevice();
    PhysicalDevice& getSuitablePhysicalDevice(VkSurfaceKHR surface);

    VkInstance getHandler() const { return mInstance; }

    bool isEnabledExtension(const char* extensionsName) const;
    const std::vector<const char*>& getExtensions();

  private:
    void query_gpus();

  private:
    VkInstance mInstance = {VK_NULL_HANDLE};
    std::vector<const char*> mEnabledExtensions;

    std::vector<std::unique_ptr<PhysicalDevice>> mGpus;
  };

}

#endif // !RWVULKANINSTANCE_H
