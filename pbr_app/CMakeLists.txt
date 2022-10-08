set(APP_SOURCE
    src/rwPhysicalDevice.cpp
    src/rwVulkanInstance.cpp
    src/rwWindow.cpp)

set(APP_HEADERS
    include/rwPhysicalDevice.h
    include/rwVulkanInstance.h
    include/rwInput.h
    include/rwLog.h
    include/rwWindow.h)


set(PBR_APP_SOURCE demo/demo1.cpp ${APP_SOURCE} ${APP_HEADERS} )
include_directories(include)
add_executable(${PROJECT_NAME} ${PBR_APP_SOURCE})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw Vulkan::Vulkan glm spdlog::spdlog assimp::assimp)
target_link_directories(${PROJECT_NAME} PRIVATE ./include)