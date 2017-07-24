#include <jni.h>
#include <string>
#include <GLES2/gl2.h>

void on_surface_created();
void on_surface_changed();
void on_draw_frame();

extern "C" JNIEXPORT void JNICALL Java_app_electrobox_com_electrobox_GLJNIWrapper_on_1surface_1created(JNIEnv * env, jclass cls) {
    on_surface_created();
}

extern "C" JNIEXPORT void JNICALL Java_app_electrobox_com_electrobox_GLJNIWrapper_on_1surface_1changed(JNIEnv * env, jclass cls, jint width, jint height) {
    on_surface_changed();
}

extern "C" JNIEXPORT void JNICALL Java_app_electrobox_com_electrobox_GLJNIWrapper_on_1draw_1frame(JNIEnv * env, jclass cls) {
    on_draw_frame();
}

extern "C" JNIEXPORT void JNICALL Java_app_electrobox_com_electrobox_GLJNIWrapper_on_1pause(JNIEnv * env, jclass cls) {

}

extern "C" JNIEXPORT void JNICALL Java_app_electrobox_com_electrobox_GLJNIWrapper_on_1resume(JNIEnv * env, jclass cls) {

}

void on_surface_created() {

}

void on_surface_changed() {

}

void on_draw_frame() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}