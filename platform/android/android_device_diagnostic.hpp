#pragma once

#include <string>

namespace Toollibs::Android {

struct DeviceInfo {
    // Device
    std::string manufacturer;
    std::string brand;
    std::string model;
    std::string product;
    std::string device;

    // Android
    std::string android_version;
    std::string api_level;
    std::string build_id;
    std::string fingerprint;
    std::string security_patch;

    // Hardware
    std::string architecture;
    std::string abi;
    std::string cpu_abi;
    std::string hardware;
    std::string soc;

    // Kernel
    std::string kernel_version;

    // Memory
    std::string ram_total;
    std::string ram_available;

    // Display
    std::string display_resolution;
    std::string display_density;

    // Battery
    std::string battery_level;
    std::string battery_status;
};

// Collect device information.
DeviceInfo get_device_info();

// Print collected device information.
void print_device_info(const DeviceInfo& info);

// Run the complete diagnostic.
void run_diagnostics();

} // namespace Toollibs::Android