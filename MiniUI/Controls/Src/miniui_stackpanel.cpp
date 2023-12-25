
#include "miniui_stackpanel.h"

StackPanel::StackPanel(void) :
Control(Size::None), orientation(Orientation::Horizontal),
backColor(Color::Transparent), Children(*this) {

}

const char *StackPanel::GetType(void) {
    return "StackPanel";
}

void StackPanel::SetOrientation(const Orientation &value) {
    this->orientation = value;
}

const Orientation &StackPanel::GetOrientation(void) const {
    return this->orientation;
}

void StackPanel::SetBackColor(const Color &color) {
    this->backColor = color;
}

const Color &StackPanel::GetBackColor(void) const {
    return this->backColor;
}

void StackPanel::UpdateActualWidth(int16_t referWidth) {
    int16_t sumWidth = 0;
    int16_t maxWidth = 0;
    int16_t noneCount = 0;
    int16_t temp;
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        Control &child = this->Children[i];
        int16_t childWidth = child.GetSize().Width;
        const Thickness &childMargin = this->Children[i].GetMargin();
        if(childWidth >= 0) {
            temp = childWidth + childMargin.Left + childMargin.Right;
            child.UpdateActualWidth(Size::None);
        }
        else if(childWidth == Size::Auto) {
            child.UpdateActualWidth(Size::None);
            temp = child.GetActualSize().Width + childMargin.Left + childMargin.Right;
        }
        else {
            noneCount++;
            temp = 0;
        }
        sumWidth += temp;
        temp = MiniUI_MAX(temp, 0);
        if(maxWidth < temp)
            maxWidth = temp;
    }
    int16_t width = this->GetSize().Width;
    int16_t contentWidth = (this->orientation == Orientation::Horizontal) ? sumWidth : maxWidth;
    if(width == Size::None) {
        const Thickness &margin = this->GetMargin();
        width = referWidth - margin.Left - margin.Right;
    }
    else if(width == Size::Auto)
        width = contentWidth;
    this->SetActualWidth(width);
    if(noneCount) {
        int16_t noneWidth = (this->orientation == Orientation::Horizontal) ? ((width - contentWidth) / noneCount) : width;
        for(uint16_t i = 0; i < this->Children.Count; i++) {
            Control &child = this->Children[i];
            if(child.GetSize().Width == Size::None)
                child.UpdateActualWidth(noneWidth);
        }
    }
}

void StackPanel::UpdateActualHeight(int16_t referHeight) {
    int16_t sumHeight = 0;
    int16_t maxHeight = 0;
    int16_t noneCount = 0;
    int16_t temp;
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        Control &child = this->Children[i];
        int16_t childHeight = child.GetSize().Height;
        const Thickness &childMargin = this->Children[i].GetMargin();
        if(childHeight >= 0) {
            temp = childHeight + childMargin.Left + childMargin.Right;
            child.UpdateActualHeight(Size::None);
        }
        else if(childHeight == Size::Auto) {
            child.UpdateActualHeight(Size::None);
            temp = child.GetActualSize().Height + childMargin.Top + childMargin.Bottom;
        }
        else {
            noneCount++;
            temp = 0;
        }
        sumHeight += temp;
        temp = MiniUI_MAX(temp, 0);
        if(maxHeight < temp)
            maxHeight = temp;
    }
    int16_t height = this->GetSize().Height;
    int16_t contentHeight = (this->orientation == Orientation::Vertical) ? sumHeight : maxHeight;
    if(height == Size::None) {
        const Thickness &margin = this->GetMargin();
        height = referHeight - margin.Top - margin.Bottom;
    }
    else if(height == Size::Auto)
        height = contentHeight;
    this->SetActualHeight(height);
    if(noneCount) {
        int16_t noneHeight = (this->orientation == Orientation::Vertical) ? ((height - contentHeight) / noneCount) : height;
        for(uint16_t i = 0; i < this->Children.Count; i++) {
            Control &child = this->Children[i];
            if(child.GetSize().Height == Size::None)
                child.UpdateActualHeight(noneHeight);
        }
    }
}

void StackPanel::OnDraw(Graphics &g) {
    if(this->backColor.A != 0x00) {
        const Size &actualSize = this->GetActualSize();
        g.FillRectangle(this->backColor, Rect(0, 0, actualSize.Width, actualSize.Height));
    }

    if(this->orientation == Orientation::Horizontal)
        this->DrawHorizontal(g);
    else if(this->orientation == Orientation::Vertical)
        this->DrawVertical(g);
    else
        this->DrawNone(g);
}

void StackPanel::DrawHorizontal(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    int16_t graphLeft = 0;
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        Control &obj = this->Children[i];
        const Size &objSize = obj.GetActualSize();
        const Thickness &objMargin = obj.GetMargin();

        graphLeft += objMargin.Left;

        if(obj.GetVisible()) {
            const VerticalAlignment objVertAlign = obj.GetVerticalAlignment();
            int16_t graphX2 = actualSize.Width - objMargin.Right;
            int16_t graphY2 = actualSize.Height - objMargin.Bottom;
            int16_t objY;

            if(objVertAlign == VerticalAlignment::Top)
                objY = 0;
            else if(objVertAlign == VerticalAlignment::Center)
                objY = (actualSize.Height - objSize.Height) / 2 - objMargin.Bottom;
            else
                objY = (actualSize.Height - objSize.Height) - objMargin.Bottom;

            Graphics objGraph = g.SubGraphics(graphLeft, objMargin.Top, graphX2, graphY2).SubGraphics(0, objY);
            obj.OnDraw(objGraph);
        }
        graphLeft += objSize.Width + objMargin.Right;
    }
}

void StackPanel::DrawVertical(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    int16_t graphTop = 0;
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        Control &obj = this->Children[i];
        const Size &objSize = obj.GetActualSize();
        const Thickness &objMargin = obj.GetMargin();

        graphTop += objMargin.Top;

        if(obj.GetVisible() && graphTop < actualSize.Height) {
            const HorizontalAlignment objHorizAlign = obj.GetHorizontalAlignment();
            int16_t graphX2 = actualSize.Width - objMargin.Right;
            int16_t graphY2 = actualSize.Height - objMargin.Bottom;
            int16_t objX;

            if(objHorizAlign == HorizontalAlignment::Left)
                objX = 0;
            else if(objHorizAlign == HorizontalAlignment::Center)
                objX = (actualSize.Width - objSize.Width) / 2 - objMargin.Right;
            else
                objX = (actualSize.Width - objSize.Width) - objMargin.Right;

            Graphics objGraph = g.SubGraphics(objMargin.Left, graphTop, graphX2, graphY2).SubGraphics(objX, 0);
            obj.OnDraw(objGraph);
        }
        graphTop += objSize.Height + objMargin.Bottom;
    }
}

void StackPanel::DrawNone(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        Control &obj = this->Children[i];
        const Thickness &objMargin = obj.GetMargin();

        if(obj.GetVisible()) {
            const Size &objSize = obj.GetActualSize();
            const HorizontalAlignment objHorizAlign = obj.GetHorizontalAlignment();
            const VerticalAlignment objVertAlign = obj.GetVerticalAlignment();
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
            obj.OnDraw(objGraph);
        }
    }
}
