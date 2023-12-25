
#include "miniui_collections.h"
#include "miniui_thickness.h"
#include "miniui_user_control.h"

UserControl::UserControl(void) : Control(Size::AutoSize), backColor(Color::Transparent) {
    this->content = 0;
}

void UserControl::SetContent(Control &control) {
    Collections *objParentList = (Collections *)control.GetParentList();
    control.SetParent(*this);
    if(objParentList)
        objParentList->Remove(control);
    if(this->content)
        this->content->SetParent(NULL_CONTROL);
    this->content = &control;
}

Control &UserControl::GetContent(void) {
    return *this->content;
}

void UserControl::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &UserControl::GetBackColor(void) {
    return this->backColor;
}

void UserControl::UpdateActualWidth(int16_t referWidth) {
    int16_t width = this->GetSize().Width;
    if(width >= 0) {
        this->SetActualWidth(width);
        if(this->content)
            this->content->UpdateActualWidth(width);
    }
    else if((width == Size::None) && (referWidth >= 0)) {
        const Thickness &margin = this->GetMargin();
        width = MAX(referWidth - margin.Left - margin.Right, 0);
        this->SetActualWidth(width);
        if(this->content)
            this->content->UpdateActualWidth(width);
    }
    else {
        if(this->content)
            this->content->UpdateActualWidth(Size::None);
        if(this->content) {
            const Thickness &contentMargin = this->content->GetMargin();
            this->SetActualWidth(MAX(this->content->GetActualSize().Width + contentMargin.Left + contentMargin.Right, 0));
        }
        else
            this->SetActualWidth(0);
    }
}

void UserControl::UpdateActualHeight(int16_t referHeight) {
    int16_t height = this->GetSize().Height;
    if(height >= 0) {
        this->SetActualHeight(height);
        if(this->content)
            this->content->UpdateActualHeight(height);
    }
    else if((height == Size::None) && (referHeight >= 0)) {
        const Thickness &margin = this->GetMargin();
        height = MAX(referHeight - margin.Top - margin.Bottom, 0);
        this->SetActualHeight(height);
        if(this->content)
            this->content->UpdateActualHeight(height);
    }
    else {
        if(this->content)
            this->content->UpdateActualHeight(Size::None);
        if(this->content) {
            const Thickness &contentMargin = this->content->GetMargin();
            this->SetActualHeight(MAX(this->content->GetActualSize().Height + contentMargin.Top + contentMargin.Bottom, 0));
        }
        else
            this->SetActualHeight(0);
    }
}

void UserControl::OnDraw(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    if(this->backColor.A != 0x00)
        g.FillRectangle(this->backColor, Rect(0, 0, actualSize.Width, actualSize.Height));
    if(this->content && this->content->GetVisible()) {
        const Thickness &objMargin = this->content->GetMargin();
        if(objMargin != 0) {
            int16_t width = actualSize.Width - objMargin.Left - objMargin.Right;
            int16_t height = actualSize.Height - objMargin.Top - objMargin.Bottom;
            Graphics objGraph = g.SubGraphics(objMargin.Left, objMargin.Top, width, height);
            this->content->OnDraw(objGraph);
        }
        else
            this->content->OnDraw(g);
    }
}
