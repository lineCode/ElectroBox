package app.electrobox.com.electrobox;

public class GLJNIWrapper {
    static {
        System.loadLibrary("native-lib");
    }

    public static native void on_surface_created();

    public static native void on_surface_changed(int width, int height);

    public static native void on_draw_frame();

    public static native void on_pause();

    public static native void on_resume();
}
