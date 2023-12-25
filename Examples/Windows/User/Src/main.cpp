
#include <windows.h>
#include <stdlib.h>
#include <graphics.h>
#include "miniui.h"
#include "test.xml.cpp"

#include "miniui_font_list.h"

using namespace std;

static void ScreenDriver(const RgbColor *rgbBuff, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    uint32_t sz = imagesize(x, y, x + width - 1, y + height - 1);
    int32_t *image = (int32_t *)malloc(sz);
    getimage(x, y, x + width - 1, y + height - 1, image);
    for(uint32_t i = 6; i < (sz / 4); i++)
        image[i] = *(int32_t *)&rgbBuff[i - 6] & 0xFFFFFF;
    putimage(x, y, image, COPY_PUT);
    free(image);
}

int main(void) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    Window::ScreenDriver = ScreenDriver;

    MainWindowDesign mainWindow;
    mainWindow.Update();

    getch();
    closegraph();

    return 0;
}
