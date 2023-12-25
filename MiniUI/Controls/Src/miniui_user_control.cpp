
#include "miniui_collections.h"
#include "miniui_thickness.h"
#include "miniui_user_control.h"

UserControl::UserControl(void) : Control(Size::Auto), backColor(Color::Transparent) {
    this->content = 0;
}

const char *UserControl::GetType(void) {
    return "UserControl";
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

Control &UserControl::GetContent(void) const {
    return *this->content;
}

void UserControl::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &UserControl::GetBackColor(void) const {
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
        width = MiniUI_MAX(referWidth - margin.Left - margin.Right, 0);
        this->SetActualWidth(width);
        if(this->content)
            this->content->UpdateActualWidth(width);
    }
    else {
        if(this->content)
            this->content->UpdateActualWidth(Size::None);
        if(this->content) {
            const Thickness &contentMargin = this->content->GetMargin();
            this->SetActualWidth(MiniUI_MAX(this->content->GetActualSize().Width + contentMargin.Left + contentMargin.Right, 0));
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
        height = MiniUI_MAX(referHeight - margin.Top - margin.Bottom, 0);
        this->SetActualHeight(height);
        if(this->content)
            this->content->UpdateActualHeight(height);
    }
    else {
        if(this->content)
            this->content->UpdateActualHeight(Size::None);
        if(this->content) {
            const Thickness &contentMargin = this->content->GetMargin();
            this->SetActualHeight(MiniUI_MAX(this->content->GetActualSize().Height + contentMargin.Top + contentMargin.Bottom, 0));
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
