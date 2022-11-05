#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <array>
#include <memory>
#include <rwLog.h>
namespace rw
{

class Input
{
public:
    explicit Input() = default;

    int getKeyState(int key) const
    {
      assert((key > -1 && key < GLFW_KEY_LAST) && "Unknow key");
        return mKeys.at(static_cast<size_t>(key));
    }

    void setKey(const int& key, int value)
    {
      assert(!(key > -1 && key < GLFW_KEY_LAST) && "Unknow key");
      LOG("Key {} has been {}", key, value);
      mKeys[key] = value;
    }

private:
    std::array<int, GLFW_KEY_LAST> mKeys;
};
}

#endif // INPUT_H
