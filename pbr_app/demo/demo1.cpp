#include <rwWindow.h>
#include <rwLog.h>
#include <memory>

class Demo1
{
  const uint32_t WIDTH = 1280;
  const uint32_t HEIGHT = 720;
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