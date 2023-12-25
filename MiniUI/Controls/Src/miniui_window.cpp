
#include "miniui_window.h"
#include "miniui_collections.h"

static RgbColor RgbColorBuff[MINIUI_GRAPHIC_W * MINIUI_GRAPHIC_H];

Window::Window(void) : Control(Size::NoneSize) {
    this->content = 0;
}

Window::Window(const Window &&window) : Control(Size::NoneSize) {
    this->content = window.content;
}

void Window::SetContent(Control &control) {
    Collections *objParentList = (Collections *)control.GetParentList();
    control.SetParent(*this);
    if(objParentList)
        objParentList->Remove(control);
    if(this->content)
        this->content->SetParent(NULL_CONTROL);
    this->content = &control;
}

Control &Window::GetContent(void) {
    return *this->content;
}

void Window::Update(void) {
    this->UpdateActualWidth(MINIUI_WINDOWS_W);
    this->UpdateActualHeight(MINIUI_WINDOWS_H);
    const Size &actualSize = this->GetActualSize();

    if(this->GetVisible() && (this->content != 0)) {
        int16_t X = actualSize.Width / MINIUI_GRAPHIC_W;
        int16_t Y = actualSize.Height / MINIUI_GRAPHIC_H;
        for(int16_t y = 0; y < Y; y++) {
            for(int16_t x = 0; x < X; x++) {
                uint16_t left = x * MINIUI_GRAPHIC_W;
                uint16_t top = y * MINIUI_GRAPHIC_H;
                Graphics g(Rect(left, top, MINIUI_GRAPHIC_W, MINIUI_GRAPHIC_H), RgbColorBuff);
                g.Clear();
                this->OnDraw(g);
                if(Window::ScreenDriver)
                    Window::ScreenDriver(RgbColorBuff, left, top, MINIUI_GRAPHIC_W, MINIUI_GRAPHIC_H);
            }
        }
    }
}

void Window::UpdateActualWidth(int16_t referWidth) {
    this->SetActualWidth(referWidth);
    if(this->content)
        this->content->UpdateActualWidth(referWidth);
}

void Window::UpdateActualHeight(int16_t referHeight) {
    this->SetActualHeight(referHeight);
    if(this->content)
        this->content->UpdateActualHeight(referHeight);
}

void Window::OnDraw(Graphics &g) {
    if(this->content && this->content->GetVisible()) {
        const Thickness &objMargin = this->content->GetMargin();
        if(objMargin != 0) {
            const Size &actualSize = this->GetActualSize();
            int16_t width = actualSize.Width - objMargin.Left - objMargin.Right;
            int16_t height = actualSize.Height - objMargin.Top - objMargin.Bottom;
            Graphics objGraph = g.SubGraphics(objMargin.Left, objMargin.Top, width, height);
            this->content->OnDraw(objGraph);
        }
        else
            this->content->OnDraw(g);
    }
}

void (*Window::ScreenDriver)(const RgbColor *rgbBuff, uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;
