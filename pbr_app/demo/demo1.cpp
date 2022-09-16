#include <Window.h>


int main()
{
  rw::Window window = { "pbr", 1280, 720 };

  while (!window.isClose())
  {
    glfwPollEvents();
  }

  return 0;
}