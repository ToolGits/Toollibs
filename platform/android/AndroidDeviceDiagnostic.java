package com.toolgits.androiddiagnostic;

public final class AndroidDeviceDiagnostic {

    static {
        System.loadLibrary("android_device_diagnostic");
    }

    private AndroidDeviceDiagnostic() {
    }

    public static native String getDiagnosticReport();
}