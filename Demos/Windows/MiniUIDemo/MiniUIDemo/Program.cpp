
#include <windows.h>
#include "graphics.h"
#include "MainWindow.cpp"

#define SCREEN_W        600
#define SCREEN_H        400

static void DrawToCreen(short x, short y, short width, short height, int* colors) {
    int *buf = new int[width * height + 6];
    getimage(0, 0, 0, 0, buf);
    buf[1] = width;
    buf[2] = height;
    buf[3] = width * 4;
    memcpy(&buf[6], colors, width * height * sizeof(int));
    putimage(x, y, buf, COPY_PUT);
    delete[] buf;
}

static void SystemSleep(unsigned int ms) {
    Sleep(ms);
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    initwindow(SCREEN_W + 10, SCREEN_H + 10, "MiniUI");

    Window::SetDriver(DrawToCreen);
    Window::SetSleepFunc(SystemSleep);

    MainWindow *mainWindows = new MainWindow(Size(SCREEN_W, SCREEN_H));
    mainWindows->Show();

    while (!kbhit()) {
        delay(200);
    }
    return 0;
}
