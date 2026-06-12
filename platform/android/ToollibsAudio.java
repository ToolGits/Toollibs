package com.toollibs.audio;

public class ToollibsAudio {

    static {
        System.loadLibrary("toollibs_audio");
    }

    // JNI bridge
    public static native boolean init();
    public static native void load(String path);
    public static native void play();
    public static native void pause();
    public static native void stop();
    public static native void shutdown();
}