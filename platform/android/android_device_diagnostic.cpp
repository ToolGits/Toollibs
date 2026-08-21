#include "android_device_diagnostic.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Toollibs::Android {

namespace {

// ============================================================
// STRING HELPERS
// ============================================================

std::string trim(const std::string& value)
{
    std::size_t start = 0;
    std::size_t end = value.size();

    while (start < end &&
           (value[start] == ' ' ||
            value[start] == '\t' ||
            value[start] == '\n' ||
            value[start] == '\r')) {
        ++start;
    }

    while (end > start &&
           (value[end - 1] == ' ' ||
            value[end - 1] == '\t' ||
            value[end - 1] == '\n' ||
            value[end - 1] == '\r')) {
        --end;
    }

    return value.substr(start, end - start);
}

// ============================================================
// ANDROID PROPERTY
// ============================================================

std::string get_property(const char* property)
{
    std::string command = "getprop ";
    command += property;

    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe)
        return "Unknown";

    char buffer[512];

    if (!fgets(buffer, sizeof(buffer), pipe)) {
        pclose(pipe);
        return "Unknown";
    }

    pclose(pipe);

    std::string result = trim(buffer);

    if (result.empty())
        return "Unknown";

    return result;
}

// ============================================================
// FILE READER
// ============================================================

std::string read_file(const char* path)
{
    std::ifstream file(path);

    if (!file)
        return "Unknown";

    std::stringstream buffer;
    buffer << file.rdbuf();

    const std::string result = trim(buffer.str());

    if (result.empty())
        return "Unknown";

    return result;
}

// ============================================================
// /PROC VALUE READER
// ============================================================

std::string read_proc_value(
    const char* path,
    const std::string& key)
{
    std::ifstream file(path);

    if (!file)
        return "Unknown";

    std::string line;

    while (std::getline(file, line)) {
        if (line.rfind(key, 0) != 0)
            continue;

        const std::size_t separator = line.find(':');

        if (separator == std::string::npos)
            continue;

        return trim(line.substr(separator + 1));
    }

    return "Unknown";
}

// ============================================================
// ARCHITECTURE DETECTION
// ============================================================

std::string detect_architecture()
{
#if defined(__aarch64__)
    return "aarch64";
#elif defined(__arm__)
    return "arm";
#elif defined(__x86_64__)
    return "x86_64";
#elif defined(__i386__)
    return "x86";
#else
    return "unknown";
#endif
}

// ============================================================
// DISPLAY PROPERTY FALLBACK
// ============================================================

std::string get_display_size()
{
    std::string result =
        get_property("vendor.display-size");

    if (result != "Unknown")
        return result;

    result =
        get_property("persist.sys.display-size");

    if (result != "Unknown")
        return result;

    result =
        get_property("ro.vendor.display-size");

    if (result != "Unknown")
        return result;

    return "Unknown";
}

} // namespace

// ============================================================
// DEVICE INFORMATION
// ============================================================

DeviceInfo get_device_info()
{
    DeviceInfo info;

    // --------------------------------------------------------
    // DEVICE
    // --------------------------------------------------------

    info.manufacturer =
        get_property("ro.product.manufacturer");

    info.brand =
        get_property("ro.product.brand");

    info.model =
        get_property("ro.product.model");

    info.product =
        get_property("ro.product.name");

    info.device =
        get_property("ro.product.device");

    // --------------------------------------------------------
    // ANDROID
    // --------------------------------------------------------

    info.android_version =
        get_property("ro.build.version.release");

    info.api_level =
        get_property("ro.build.version.sdk");

    info.build_id =
        get_property("ro.build.id");

    info.fingerprint =
        get_property("ro.build.fingerprint");

    info.security_patch =
        get_property("ro.build.version.security_patch");

    // --------------------------------------------------------
    // HARDWARE
    // --------------------------------------------------------

    info.architecture =
        detect_architecture();

    info.abi =
        get_property("ro.product.cpu.abilist");

    info.cpu_abi =
        get_property("ro.product.cpu.abi");

    info.hardware =
        get_property("ro.hardware");

    info.soc =
        get_property("ro.soc.model");

    if (info.soc == "Unknown") {
        info.soc =
            get_property("ro.board.platform");
    }

    // --------------------------------------------------------
    // KERNEL
    // --------------------------------------------------------

    info.kernel_version =
        read_file("/proc/version");

    // --------------------------------------------------------
    // MEMORY
    // --------------------------------------------------------

    info.ram_total =
        read_proc_value(
            "/proc/meminfo",
            "MemTotal");

    info.ram_available =
        read_proc_value(
            "/proc/meminfo",
            "MemAvailable");

    // --------------------------------------------------------
    // DISPLAY
    // --------------------------------------------------------

    info.display_resolution =
        get_display_size();

    info.display_density =
        get_property("ro.sf.lcd_density");

    // --------------------------------------------------------
    // BATTERY
    // --------------------------------------------------------

    info.battery_level =
        read_file(
            "/sys/class/power_supply/battery/capacity");

    info.battery_status =
        read_file(
            "/sys/class/power_supply/battery/status");

    return info;
}

// ============================================================
// OUTPUT
// ============================================================

void print_device_info(const DeviceInfo& info)
{
    std::cout
        << "========================================\n"
        << " Toollibs Android Device Diagnostic\n"
        << "========================================\n\n";

    std::cout << "[ Device ]\n";
    std::cout
        << "Manufacturer : " << info.manufacturer << '\n'
        << "Brand        : " << info.brand << '\n'
        << "Model        : " << info.model << '\n'
        << "Product      : " << info.product << '\n'
        << "Device       : " << info.device << '\n';

    std::cout << "\n[ Android ]\n";
    std::cout
        << "Version      : " << info.android_version << '\n'
        << "API Level    : " << info.api_level << '\n'
        << "Build ID     : " << info.build_id << '\n'
        << "Security     : " << info.security_patch << '\n'
        << "Fingerprint  : " << info.fingerprint << '\n';

    std::cout << "\n[ Hardware ]\n";
    std::cout
        << "Architecture : " << info.architecture << '\n'
        << "ABI          : " << info.abi << '\n'
        << "CPU ABI      : " << info.cpu_abi << '\n'
        << "Hardware     : " << info.hardware << '\n'
        << "SoC          : " << info.soc << '\n';

    std::cout << "\n[ Kernel ]\n";
    std::cout
        << "Version      : "
        << info.kernel_version
        << '\n';

    std::cout << "\n[ Memory ]\n";
    std::cout
        << "RAM Total    : " << info.ram_total << '\n'
        << "RAM Available: " << info.ram_available << '\n';

    std::cout << "\n[ Display ]\n";
    std::cout
        << "Resolution   : " << info.display_resolution << '\n'
        << "Density      : " << info.display_density << '\n';

    std::cout << "\n[ Battery ]\n";
    std::cout
        << "Level        : " << info.battery_level << '\n'
        << "Status       : " << info.battery_status << '\n';

    std::cout << "\n[ Diagnostic ]\n";
    std::cout
        << "Status       : OK\n";

    std::cout
        << "\n========================================\n";
}

// ============================================================
// DIAGNOSTIC ENTRY POINT
// ============================================================

void run_diagnostics()
{
    const DeviceInfo info = get_device_info();

    print_device_info(info);
}

} // namespace Toollibs::Android