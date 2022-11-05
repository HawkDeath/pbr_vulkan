#ifndef RWDEVICE_H
#define RWDEVICE_H

#include <vulkan/vulkan.h>
#include <rwVulkanInstance.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace rw
{
  // temporary
  class Buffer;
  class ImageBuffer;
  class CommandBuffer;
  class CommandPool;
  class QueueFamily;

  class Device
  {
  public:
	explicit Device(VulkanInstance& instance, VkSurfaceKHR surface, std::unordered_map<const char*, bool> requiredExtensions = {});
	~Device();

	Device(const Device&) = delete;
	Device(Device&&) = delete;
	Device& operator=(const Device&) = delete;
	Device& operator=(Device&&) = delete;

	VkDevice getHandler() const { return mDevice; }
	VkSurfaceKHR getSurface() const { return mSurface; }

	// const QueueFamily* getGraphicsQueue() const { return mGraphicsQueue.get(); }
	// const QueueFamily* getPresentQueue() const { return mPresentQueue.get(); }

	//CommandBuffer beginSingleCommandBuffer();
	//void endSignleCommandBuffer(CommandBuffer& command);

	//const CommandPool* getCommandPool() { return mCommandPool.get(); };

  private:
	const VulkanInstance& mInstance;

	VkDevice mDevice;
	VkSurfaceKHR mSurface;

	std::vector<const char*> mEnabledExtensions;


	// std::unique_ptr<CommandPool> mCommandPool;

	//std::unique_ptr<QueueFamily> mGraphicsQueue;
	//std::unique_ptr<QueueFamily> mPresentQueue;

  };

}

#endif // !RWDEVICE_H
