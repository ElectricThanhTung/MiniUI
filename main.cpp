
#include <stdlib.h>
#include <graphics.h>
#include "miniui.h"

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

Window mainWindow;
StackPanel mainPanel;
StackPanel panel1;
StackPanel panel2;

int main(void) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    Window::ScreenDriver = ScreenDriver;

    mainPanel.SetBackColor(Color::White);
    mainPanel.SetOrientation(Orientation::Vertical);

    panel1.SetSize(Size(100, 100));
    panel1.SetMargin(Thickness(1));
    panel1.SetBackColor(Color::Red);
    
    panel2.SetSize(Size(100, 100));
    panel2.SetMargin(Thickness(0));
    panel2.SetBackColor(Color(64, 0, 0, 0));

    Label label1 = Label("Bùi Viết Minh Trí", Color::Black, Font(TimesNewRoman));

    Label label2 = Label("OK", Color::Black, Font(TimesNewRoman, 20));
    label2.SetMargin(Thickness(10, 5, 10, 5));

    Button button1;
    button1.SetContent(label2);
    button1.SetMargin(Thickness(10));

    mainPanel.Children.Add(panel1);
    mainPanel.Children.Add(panel2);
    mainPanel.Children.Add(label1);
    mainPanel.Children.Add(button1);

    mainWindow.SetContent(mainPanel);

    mainWindow.Update();

    getch();
    closegraph();

    return 0;
}
