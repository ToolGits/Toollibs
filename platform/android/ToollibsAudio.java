package com.toollibs.audio;

public final class ToollibsAudio {

    static {
        System.loadLibrary("toollibs_audio");
    }

    private ToollibsAudio() {}

    public static native boolean init();
    public static native void load(String path);
    public static native void play(String path);
    public static native void pause();
    public static native void stop();
    public static native void shutdown();
}
