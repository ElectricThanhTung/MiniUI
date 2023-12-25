
#include "miniui_window.h"
#include "miniui_collections.h"

static RgbColor RgbColorBuff[MINIUI_GRAPHIC_W * MINIUI_GRAPHIC_H];

Window::Window(void) : Control(Size::None) {
    this->content = 0;
}

const char *Window::GetType(void) {
    return "Window";
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

Control &Window::GetContent(void) const {
    return *this->content;
}

void Window::Update(void) {
    this->UpdateActualSize();
    const Size &actualSize = this->GetActualSize();

    if(this->content != 0) {
        for(int16_t y = 0; y < actualSize.Height; y += MINIUI_GRAPHIC_H) {
            uint16_t h = actualSize.Height - y;
            if(h > MINIUI_GRAPHIC_H)
                h = MINIUI_GRAPHIC_H;
            for(int16_t x = 0; x < actualSize.Width; x += MINIUI_GRAPHIC_W) {
                int16_t w = actualSize.Width - x;
                if(w > MINIUI_GRAPHIC_W)
                    w = MINIUI_GRAPHIC_W;
                Graphics g(Rect(x, y, w, h), RgbColorBuff);
                g.Clear();
                this->OnDraw(g);
                if(Window::ScreenDriver)
                    Window::ScreenDriver(RgbColorBuff, x, y, w, h);
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

void Window::UpdateActualSize(void) {
    this->UpdateActualWidth(MINIUI_WINDOWS_W);
    this->UpdateActualHeight(MINIUI_WINDOWS_H);
}

void Window::OnDraw(Graphics &g) {
    if(this->content && this->content->GetVisible()) {
        const Size &actualSize = this->GetActualSize();
        const Thickness &objMargin = this->content->GetMargin();
        const Size &objSize = this->content->GetActualSize();
        const HorizontalAlignment objHorizAlign = this->content->GetHorizontalAlignment();
        const VerticalAlignment objVertAlign = this->content->GetVerticalAlignment();
        int16_t graphX2 = actualSize.Width - objMargin.Right;
        int16_t graphY2 = actualSize.Height - objMargin.Bottom;
        int16_t objX, objY;

        if(objHorizAlign == HorizontalAlignment::Left)
            objX = 0;
        else if(objHorizAlign == HorizontalAlignment::Center)
            objX = (actualSize.Width - objSize.Width) / 2 - objMargin.Right;
        else
            objX = (actualSize.Width - objSize.Width) - objMargin.Right;

        if(objVertAlign == VerticalAlignment::Top)
            objY = 0;
        else if(objVertAlign == VerticalAlignment::Center)
            objY = (actualSize.Height - objSize.Height) / 2 - objMargin.Bottom;
        else
            objY = (actualSize.Height - objSize.Height) - objMargin.Bottom;

        Graphics objGraph = g.SubGraphics(objMargin.Left, objMargin.Top, graphX2, graphY2).SubGraphics(objX, objY);
        this->content->OnDraw(objGraph);
    }
}

void (*Window::ScreenDriver)(const RgbColor *rgbBuff, uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;
