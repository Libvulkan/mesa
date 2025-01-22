#include "wrapper_private.h"

// Fake Vulkan function to enumerate device extensions
VkResult fake_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char *layerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties) {
    *pPropertyCount = 2; // Fake two extensions
    pProperties[0] = (VkExtensionProperties){"VK_KHR_swapchain", VK_MAKE_VERSION(1, 0, 0)};
    pProperties[1] = (VkExtensionProperties){"VK_KHR_ray_tracing_pipeline", VK_MAKE_VERSION(1, 1, 0)};
    return VK_SUCCESS;
}

// Initialize fake Vulkan dispatch table
void fake_vk_dispatch_table_init(struct fake_vk_dispatch_table *table) {
    table->vkEnumerateDeviceExtensionProperties = fake_vkEnumerateDeviceExtensionProperties;
}

// Wrapper function to initialize the fake Vulkan instance
void wrapper_fake_vk_instance_init(struct wrapper_instance *instance) {
    instance->vk.api_version = VK_API_VERSION_1_3;  // Set Vulkan version to 1.3
    fake_vk_dispatch_table_init(&instance->fake_dispatch_table);  // Initialize fake Vulkan dispatch table
}

// Wrapper function to initialize the wrapper instance
void wrapper_instance_init(struct wrapper_instance *instance) {
    // Initialize the real Vulkan instance if necessary
    // ...

    // Initialize fake Vulkan dispatch table if needed
    wrapper_fake_vk_instance_init(instance);

    // Set the dispatch table to use the fake Vulkan function
    instance->dispatch_table.vkEnumerateDeviceExtensionProperties = instance->fake_dispatch_table.vkEnumerateDeviceExtensionProperties;
    // Add more fake Vulkan functions if needed
}

// Example of using the wrapper instance with fake Vulkan extension
VkResult wrapper_enumerate_device_extension_properties(struct wrapper_instance *instance, VkPhysicalDevice physicalDevice, const char *layerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties) {
    return instance->dispatch_table.vkEnumerateDeviceExtensionProperties(physicalDevice, layerName, pPropertyCount, pProperties);
}
