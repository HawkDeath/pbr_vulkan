#ifndef RWPHYSICALDEVICE_H
#define RWPHYSICALDEVICE_H


#include <vulkan/vulkan.h>

namespace rw
{
  class VulkanInstance;
  class PhysicalDevice
  {
  public:
	PhysicalDevice(VulkanInstance& instance, VkPhysicalDevice physicalDevice);
	~PhysicalDevice();


	VulkanInstance& getInstance() const { return mInstance; }

  private:
	VulkanInstance& mInstance;

	VkPhysicalDevice mPhysicalDevice;

  };

}

#endif // !RWPHYSICALDEVICE_H
