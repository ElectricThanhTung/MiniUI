
#include "miniui_window.h"
#include "miniui_collections.h"

static RgbColor RgbColorBuff[MINIUI_GRAPHIC_W * MINIUI_GRAPHIC_H];

Window::Window(void) : Control(Size::NoneSize), requestRect(0, 0, 0, 0) {
    this->content = 0;
}

Window::Window(const Window &&window) : Control(Size::NoneSize), requestRect(0, 0, 0, 0) {
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
    this->SetRequestRect(Rect(0, 0, MINIUI_WINDOWS_W, MINIUI_WINDOWS_H));
}

Control &Window::GetContent(void) {
    return *this->content;
}

void Window::Update(void) {
    this->UpdateActualWidth(MINIUI_WINDOWS_W);
    this->UpdateActualHeight(MINIUI_WINDOWS_H);
    const Size &actualSize = this->GetActualSize();

    if((this->requestRect.Width >= 0) && (this->requestRect.Height >= 0)) {
        if(this->GetVisible() && (this->content != 0)) {
            int16_t X = this->requestRect.Width / MINIUI_GRAPHIC_W;
            int16_t Y = this->requestRect.Height / MINIUI_GRAPHIC_H;
            for(int16_t y = 0; y < Y; y++) {
                for(int16_t x = 0; x < X; x++) {
                    uint16_t left = x * MINIUI_GRAPHIC_W + this->requestRect.Left;
                    uint16_t top = y * MINIUI_GRAPHIC_H + this->requestRect.Top;
                    Graphics g(Rect(left, top, MINIUI_GRAPHIC_W, MINIUI_GRAPHIC_H), RgbColorBuff);
                    g.Clear();
                    this->OnDraw(g);
                    if(Window::ScreenDriver)
                        Window::ScreenDriver(RgbColorBuff, left, top, MINIUI_GRAPHIC_W, MINIUI_GRAPHIC_H);
                }
            }
            if((this->requestRect.Width % MINIUI_GRAPHIC_W) && (this->requestRect.Height % MINIUI_GRAPHIC_H)) {
                uint16_t left = X * MINIUI_GRAPHIC_W + this->requestRect.Left;
                uint16_t top = Y * MINIUI_GRAPHIC_H + this->requestRect.Top;
                int16_t w = this->requestRect.Width % MINIUI_GRAPHIC_W;
                int16_t h = this->requestRect.Height % MINIUI_GRAPHIC_H;
                Graphics g(Rect(left, top, w, h), RgbColorBuff);
                g.Clear();
                this->OnDraw(g);
                if(Window::ScreenDriver)
                    Window::ScreenDriver(RgbColorBuff, left, top, w, h);
            }
        }
        this->requestRect = Rect(0, 0, 0, 0);
    }
}

bool Window::RequestUpdate(bool isRecall) {
    this->UpdateActualWidth(MINIUI_WINDOWS_W);
    this->UpdateActualHeight(MINIUI_WINDOWS_H);
    this->UpdateLocation();
    return false;
}

void Window::SetRequestRect(const Rect &rect) {
    int16_t x = MAX(rect.Left, 0);
    int16_t y = MAX(rect.Top, 0);
    int16_t w = (rect.Left + rect.Width) - x;
    int16_t h = (rect.Top + rect.Height) - y;
    if((this->requestRect.Width == 0) || (this->requestRect.Height == 0))
        requestRect = Rect(x, y, w, h);
    else {
        int16_t left = MIN(x, this->requestRect.Left);
        int16_t top = MIN(y, this->requestRect.Top);
        int16_t width = MAX(x + w, this->requestRect.Left + this->requestRect.Width) - left;
        int16_t height = MAX(y + h, this->requestRect.Top + this->requestRect.Height) - top;
        requestRect = Rect(left, top, width, height);
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

void Window::UpdateLocation(void) {
    if(this->content)
        this->content->UpdateLocation();
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
