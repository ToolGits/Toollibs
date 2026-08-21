#include "android_device_diagnostic.hpp"

#include <jni.h>

#include <sstream>
#include <string>

namespace Toollibs::Android::JNI {

namespace {

std::string build_diagnostic_report()
{
    const DeviceInfo info = get_device_info();

    std::ostringstream report;

    report
        << "========================================\n"
        << " Toollibs Android Device Diagnostic\n"
        << "========================================\n\n";

    report << "[ Device ]\n";
    report
        << "Manufacturer : " << info.manufacturer << '\n'
        << "Brand        : " << info.brand << '\n'
        << "Model        : " << info.model << '\n'
        << "Product      : " << info.product << '\n'
        << "Device       : " << info.device << '\n';

    report << "\n[ Android ]\n";
    report
        << "Version      : " << info.android_version << '\n'
        << "API Level    : " << info.api_level << '\n'
        << "Build ID     : " << info.build_id << '\n'
        << "Security     : " << info.security_patch << '\n'
        << "Fingerprint  : " << info.fingerprint << '\n';

    report << "\n[ Hardware ]\n";
    report
        << "Architecture : " << info.architecture << '\n'
        << "ABI          : " << info.abi << '\n'
        << "CPU ABI      : " << info.cpu_abi << '\n'
        << "Hardware     : " << info.hardware << '\n'
        << "SoC          : " << info.soc << '\n';

    report << "\n[ Kernel ]\n";
    report
        << "Version      : " << info.kernel_version << '\n';

    report << "\n[ Memory ]\n";
    report
        << "RAM Total    : " << info.ram_total << '\n'
        << "RAM Available: " << info.ram_available << '\n';

    report << "\n[ Display ]\n";
    report
        << "Resolution   : " << info.display_resolution << '\n'
        << "Density      : " << info.display_density << '\n';

    report << "\n[ Battery ]\n";
    report
        << "Level        : " << info.battery_level << '\n'
        << "Status       : " << info.battery_status << '\n';

    report << "\n[ Diagnostic ]\n";
    report << "Status       : OK\n";

    return report.str();
}

jstring native_get_diagnostic_report(
    JNIEnv* env,
    jclass)
{
    const std::string report = build_diagnostic_report();

    return env->NewStringUTF(report.c_str());
}

} // namespace

} // namespace Toollibs::Android::JNI

// ============================================================
// JNI REGISTRATION
// ============================================================

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void*)
{
    JNIEnv* env = nullptr;

    if (vm->GetEnv(
            reinterpret_cast<void**>(&env),
            JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    constexpr const char* class_name =
        "com/toolgits/androiddiagnostic/AndroidDeviceDiagnostic";

    jclass local_class = env->FindClass(class_name);

    if (local_class == nullptr)
        return JNI_ERR;

    static const JNINativeMethod methods[] = {
        {
            "getDiagnosticReport",
            "()Ljava/lang/String;",
            reinterpret_cast<void*>(
                Toollibs::Android::JNI::
                    native_get_diagnostic_report)
        }
    };

    constexpr jint method_count =
        static_cast<jint>(
            sizeof(methods) / sizeof(methods[0]));

    const jint result =
        env->RegisterNatives(
            local_class,
            methods,
            method_count);

    env->DeleteLocalRef(local_class);

    if (result != JNI_OK)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}