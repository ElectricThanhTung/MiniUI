
#include "Window.hpp"

#define FPS             60
#define BUFFER_W        128
#define BUFFER_H        128

Window::Window() : BackgroundColor(Color::Transparent), Padding(0, 0, 0, 0) {
    this->Width = 200;
    this->Height = 100;
}

void Window::OnDraw(Graphics &g) {
    if(this->BackgroundColor.A)
        g.FullRectangle(this->BackgroundColor, Rect(0, 0, this->ActualWidth, this->ActualHeight));
    signed short left = this->Padding.Left > Content->Margin.Left ? this->Padding.Left : Content->Margin.Left;
    signed short top = this->Padding.Top > Content->Margin.Top ? this->Padding.Top : Content->Margin.Top;
    signed short right = this->Padding.Right > Content->Margin.Right ? this->Padding.Right : Content->Margin.Right;
    signed short bottom = this->Padding.Bottom > Content->Margin.Bottom ? this->Padding.Bottom : Content->Margin.Bottom;
    signed short w = this->ActualWidth - left - right;
    signed short h = this->ActualHeight - top - bottom;
    if(w <= 0 || h <= 0)
        return;
    *(signed short *)&Content->ActualWidth = w;
    *(signed short *)&Content->ActualHeight = h;
    Content->Draw(g, left, top, w, h);
}

void Window::SetContent(UI &content) {
    if(content.Parent == 0) {
        this->Content = &content;
        SetParent(content, *this);
    }
}

void Window::Show() {
    while(1) {
        if(&Content != 0) {
            unsigned char buffer[(BUFFER_W * BUFFER_H) * sizeof(Color) + sizeof(Bitmap::Width) + sizeof(Bitmap::Height)];
            ((unsigned short *)buffer)[0] = BUFFER_W;
            ((unsigned short *)buffer)[1] = BUFFER_H;
            Bitmap bm = Bitmap(*(Image *)buffer);
            Graphics g = Graphics(bm);
            *(signed short *)&this->ActualWidth = this->Width;
            *(signed short *)&this->ActualHeight = this->Height;
            signed short w = BUFFER_W;
            signed short h = BUFFER_H;
            signed short X = this->Width / w + ((this->Width % w) ? 1 : 0);
            signed short Y = this->Height / h + ((this->Height % h) ? 1 : 0);
            for(signed short x = 0; x < X; x++) {
                for(signed short y = 0; y < Y; y++) {
                    *(signed short *)&g.Left = x * w;
                    *(signed short *)&g.Top = y * h;
                    *(signed short *)&g.Right = g.Left + ((x != (X - 1)) ? w : (this->Width % w)) - 1;
                    *(signed short *)&g.Bottom = g.Top + ((y != (Y - 1)) ? h : (this->Height % h)) - 1;
                    g.Clear(Color::Transparent);
                    this->Draw(g, 0, 0);
                    if(ScreenDriver != 0)
                        ((void (*)(short, short, short, short, int *))ScreenDriver)(g.Left, g.Top, w, h, (int *)g.BitmapBuffer.Data);
                }
            }
        }
        if(SleepFunc != 0)
            ((void (*)(unsigned int))SleepFunc)(1000 / FPS);
    }
}

void Window::SetParent(UI &obj, UI &parent) {
    *(UI **)&obj.Parent = &parent;
}

void Window::SetDriver(void (*driver)(short, short, short, short, int *)) {
    Window::ScreenDriver = (void *)driver;
}

void Window::SetSleepFunc(void (*sleepFunc)(unsigned int ms)) {
    Window::SleepFunc = (void *)sleepFunc;
}

void *Window::ScreenDriver = 0;
void *Window::SleepFunc = 0;
