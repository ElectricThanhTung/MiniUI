
#include "miniui_stackpanel.h"

StackPanel::StackPanel(void) :
Control(Size::NoneSize), Children(*this), orientation(Orientation::Horizontal),
backColor(Color::Transparent) {

}

StackPanel::StackPanel(const StackPanel &&stackPanel) :
Control(Size::NoneSize), Children(*this), orientation(Orientation::Horizontal),
backColor(Color::Transparent) {

}

void StackPanel::SetOrientation(const Orientation &value) {
    if(this->orientation != value) {
        this->orientation = value;
        this->RequestUpdate();
    }
}

const Orientation &StackPanel::GetOrientation(void) {
    return this->orientation;
}

void StackPanel::SetBackColor(const Color &color) {
    if(this->backColor != color) {
        this->backColor = color;
        this->RequestUpdate();
    }
}

const Color &StackPanel::GetBackColor(void) {
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
        temp = MAX(temp, 0);
        if(maxWidth < temp)
            maxWidth = temp;
    }
    int16_t width = this->GetSize().Width;
    Control &parent = this->GetParent();
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
            const Thickness &childMargin = this->Children[i].GetMargin();
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
        temp = MAX(temp, 0);
        if(maxHeight < temp)
            maxHeight = temp;
    }
    int16_t height = this->GetSize().Height;
    Control &parent = this->GetParent();
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
            const Thickness &childMargin = this->Children[i].GetMargin();
            if(child.GetSize().Height == Size::None)
                child.UpdateActualHeight(noneHeight);
        }
    }
}

void StackPanel::UpdateLocation(void) {
    if(this->orientation == Orientation::Horizontal) {
        int16_t x = this->GetLoaction().X;
        int16_t y = this->GetLoaction().Y;
        for(uint16_t i = 0; i < this->Children.Count; i++) {
            Control &obj = this->Children[i];
            const Size &objSize = obj.GetActualSize();
            const Thickness &objMargin = obj.GetMargin();
            x += objMargin.Left;
            obj.SetLocation(x, y + objMargin.Top);
            obj.UpdateLocation();
            x += objMargin.Right + objSize.Width;
        }
    }
    else if(this->orientation == Orientation::Vertical) {
        int16_t x = this->GetLoaction().X;
        int16_t y = this->GetLoaction().Y;
        for(uint16_t i = 0; i < this->Children.Count; i++) {
            Control &obj = this->Children[i];
            const Size &objSize = obj.GetActualSize();
            const Thickness &objMargin = obj.GetMargin();
            y += objMargin.Top;
            obj.SetLocation(x + objMargin.Left, y);
            obj.UpdateLocation();
            y += objMargin.Bottom + objSize.Height;
        }
    }
    else {
        int16_t x = this->GetLoaction().X;
        int16_t y = this->GetLoaction().Y;
        for(uint16_t i = 0; i < this->Children.Count; i++) {
            Control &obj = this->Children[i];
            const Thickness &objMargin = obj.GetMargin();
            obj.SetLocation(x + objMargin.Left, y + objMargin.Top);
            obj.UpdateLocation();
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
    int16_t g_left = 0;
    int16_t remainWidth = actualSize.Width;
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        if(remainWidth <= 0)
            return;
        Control &obj = this->Children[i];
        const Size &objSize = obj.GetActualSize();
        const Thickness &objMargin = obj.GetMargin();

        if(obj.GetVisible()) {
            int16_t g_width = remainWidth - objMargin.Left - objMargin.Right;
            int16_t g_height = actualSize.Height - objMargin.Top - objMargin.Bottom;
            Graphics objGraph = g.SubGraphics(g_left + objMargin.Left, objMargin.Top, g_width, g_height);
            obj.OnDraw(objGraph);
        }
        int16_t temp = objSize.Width + objMargin.Left + objMargin.Right;
        remainWidth -= temp;
        g_left += temp;
    }
}

void StackPanel::DrawVertical(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    int16_t g_top = 0;
    int16_t remainHeight = actualSize.Height;
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        if(remainHeight <= 0)
            return;
        Control &obj = this->Children[i];
        const Size &objSize = obj.GetActualSize();
        const Thickness &objMargin = obj.GetMargin();

        if(obj.GetVisible()) {
            int16_t g_width = actualSize.Width - objMargin.Left - objMargin.Right;
            int16_t g_height = remainHeight - objMargin.Top - objMargin.Bottom;
            Graphics objGraph = g.SubGraphics(objMargin.Left, g_top + objMargin.Top, g_width, g_height);
            obj.OnDraw(objGraph);
        }
        int16_t temp = objSize.Height + objMargin.Top + objMargin.Bottom;
        remainHeight -= temp;
        g_top += temp;
    }
}

void StackPanel::DrawNone(Graphics &g) {
    const Size &actualSize = this->GetActualSize();
    for(uint16_t i = 0; i < this->Children.Count; i++) {
        Control &obj = this->Children[i];
        const Size &objSize = obj.GetActualSize();
        const Thickness &objMargin = obj.GetMargin();

        if(obj.GetVisible()) {
            int16_t g_width = actualSize.Width - objMargin.Left - objMargin.Right;
            int16_t g_height = actualSize.Height - objMargin.Top - objMargin.Bottom;
            Graphics objGraph = g.SubGraphics(objMargin.Left, objMargin.Top, g_width, g_height);
            obj.OnDraw(objGraph);
        }
    }
}
