#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class HelloTriangleApplication
{
public:
void run()
{
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

private:
GLFWwindow *window;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

VkInstance instance;

void initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void initVulkan()
{
	createInstance();
}

void mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void cleanup()
{
	vkDestroyInstance(instance, nullptr);
	
	glfwDestroyWindow(window);

	glfwTerminate();
}

void createInstance()
{
	// Optional first struct
	// Defines information of the application created by the user, passing it into a struct that is then passed to the GPU driver
	VkApplicationInfo appInfo{};         // has a null pnext pointer
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// Required second struct
	// Contains global state of the application, such as layers and extensions. Applies to the whole program.
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char **glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);         // gets the extensions required by glfw

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;         // Contains global extensions that are required by glfw

	createInfo.enabledLayerCount = 0;         // Determine the global validation layers to enable

	// Now we can create the instance
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance!");
	}

	checkExtensions();
}

void checkExtensions(){
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "available extensions:" << std::endl;

	for (const auto &extension : extensions)
	{
		std::cout << '\t' << extension.extensionName << std::endl;
	}
}
};

int main()
{
	HelloTriangleApplication app;

	try
	{
		app.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}