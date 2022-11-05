#ifndef RWPHYSICALDEVICE_H
#define RWPHYSICALDEVICE_H

#include <vulkan/vulkan.h>
#include <vector>

namespace rw
{
  class VulkanInstance;

  class PhysicalDevice
  {
  public:
	explicit PhysicalDevice(VulkanInstance& instance, VkPhysicalDevice physicalDevice);
	~PhysicalDevice();

	PhysicalDevice(const PhysicalDevice&) = delete;
	PhysicalDevice(PhysicalDevice&&) = delete;
	PhysicalDevice& operator=(const PhysicalDevice&) = delete;
	PhysicalDevice& operator=(PhysicalDevice&&) = delete;

	const VkPhysicalDeviceFeatures getFeatures() const { return mFeatures; }
	const VkPhysicalDeviceProperties2 getProperties() const { return mProperties2; }
	const VkPhysicalDeviceMemoryProperties getMemoryProperties() const { return mMemoryProperties; }

	const std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const { return mQueueFamilyProperties; }

	VulkanInstance& getInstance() const { return mInstance; }
	VkPhysicalDevice getHandler() const { return mPhysicalDevice; }

	bool isPresentSupported(VkSurfaceKHR surface, uint32_t queueIdx);

  private:
	VulkanInstance& mInstance;

	VkPhysicalDevice mPhysicalDevice;

	VkPhysicalDeviceFeatures mFeatures;
	VkPhysicalDeviceMemoryProperties mMemoryProperties;
	VkPhysicalDeviceProperties2 mProperties2;

	std::vector<VkQueueFamilyProperties> mQueueFamilyProperties;

  };

}

#endif // !RWPHYSICALDEVICE_H
