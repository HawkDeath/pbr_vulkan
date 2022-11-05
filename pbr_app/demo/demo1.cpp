#include <rwWindow.h>
#include <rwLog.h>
#include <memory>

#include <rwVulkanInstance.h>

class Demo1
{
  const uint32_t WIDTH = 1920U;
  const uint32_t HEIGHT = 1080U;

public:
  Demo1()
  {
  }

  ~Demo1()
  {
  }

  void run()
  {
    while (!window.isClose())
    {
      glfwPollEvents();
    }
  }

private:
  rw::Window window = { "demo1", WIDTH, HEIGHT };
  rw::VulkanInstance mInstance = { "demoApp1" };
};


int main()
{
  try
  {
    std::unique_ptr<Demo1> demoApp = std::make_unique<Demo1>();
    demoApp->run();

  }
  catch (std::exception& e)
  {
    ELOG(e.what());
    return -1;
  }

  return 0;
}