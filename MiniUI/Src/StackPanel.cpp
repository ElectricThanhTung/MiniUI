
#include "StackPanel.hpp"

StackPanel::StackPanel() : Content(this), Padding(0, 0, 0, 0), BackgroundColor(0), Orientation(Vertical) {

}

void StackPanel::OnDraw(Graphics &g) {
    if(this->BackgroundColor.A)
        g.FullRectangle(this->BackgroundColor, Rect(0, 0, this->ActualWidth, this->ActualHeight));
    if(Content.Count() == 0)
        return;
    if(Orientation == Horizontal)
        this->DrawHorizontal(g);
    else
        this->DrawVertical(g);
}

void StackPanel::DrawHorizontal(Graphics &g) {
    unsigned short contentCount = Content.Count();
    signed short flexibleWidth = this->ActualWidth;
    unsigned char flexibleCount = contentCount;
    signed short m = Padding.Left;
    signed short x = 0;
    if(this->Padding.Right < Content[contentCount - 1]->Margin.Right)
        flexibleWidth -= Content[contentCount - 1]->Margin.Right;
    else
        flexibleWidth -= this->Padding.Right;
    for(unsigned short i = 0; i < contentCount; i++) {
        UI *obj = Content[i];
        if(obj->Width > 0) {
            flexibleWidth -= obj->Width;
            flexibleCount--;
        }
        if(i)
            m = Content[i - 1]->Margin.Right;
        if(m < obj->Margin.Left)
            m = obj->Margin.Left;
        flexibleWidth -= m;
    }
    if(flexibleCount)
        flexibleWidth = (flexibleWidth < 0) ? 0 : flexibleWidth / flexibleCount;
    m = Padding.Left;
    for(unsigned short i = 0; i < contentCount; i++) {
        UI *obj = Content[i];
        if(obj->Width >= 0)
            *(signed short *)&obj->ActualWidth = obj->Width;
        else
            *(signed short *)&obj->ActualWidth = flexibleWidth;

        if(obj->Height >= 0)
            *(signed short *)&obj->ActualHeight = obj->Height;
        else {
            signed short h = this->ActualHeight - obj->Margin.Top - obj->Margin.Bottom;
            *(signed short *)&obj->ActualHeight = (h < 0) ? 0 : h;
        }
        
        if(i)
            m = Content[i - 1]->Margin.Right;
        if(m < obj->Margin.Left)
            m = obj->Margin.Left;
        x += m;
        if(i && (m < Content[i - 1]->Margin.Right))
            m = Content[i - 1]->Margin.Right;
        obj->Draw(g, x, (Padding.Top > obj->Margin.Top) ? Padding.Top : obj->Margin.Top);
        x += obj->ActualWidth;
    }
}

void StackPanel::DrawVertical(Graphics &g) {
    unsigned short contentCount = Content.Count();
    signed short flexibleHeight = this->ActualHeight;
    unsigned char flexibleCount = contentCount;
    signed short m = Padding.Top;
    signed short y = 0;
    if(this->Padding.Bottom < Content[contentCount - 1]->Margin.Bottom)
        flexibleHeight -= Content[contentCount - 1]->Margin.Bottom;
    else
        flexibleHeight -= this->Padding.Bottom;
    for(unsigned short i = 0; i < contentCount; i++) {
        UI *obj = Content[i];
        if(obj->Height > 0) {
            flexibleHeight -= obj->Height;
            flexibleCount--;
        }
        if(i)
            m = Content[i - 1]->Margin.Bottom;
        if(m < obj->Margin.Top)
            m = obj->Margin.Top;
        flexibleHeight -= m;
    }
    if(flexibleCount)
        flexibleHeight = (flexibleHeight < 0) ? 0 : flexibleHeight / flexibleCount;
    m = Padding.Top;
    for(unsigned short i = 0; i < contentCount; i++) {
        UI *obj = Content[i];
        if(obj->Height >= 0)
            *(signed short *)&obj->ActualHeight = obj->Height;
        else
            *(signed short *)&obj->ActualHeight = flexibleHeight;

        if(obj->Width >= 0)
            *(signed short *)&obj->ActualWidth = obj->Width;
        else {
            signed short w = this->ActualWidth - obj->Margin.Left - obj->Margin.Right;
            *(signed short *)&obj->ActualWidth = (w < 0) ? 0 : w;
        }

        if(i)
            m = Content[i - 1]->Margin.Bottom;
        if(m < obj->Margin.Top)
            m = obj->Margin.Top;
        y += m;
        if(i && (m < Content[i - 1]->Margin.Bottom))
            m = Content[i - 1]->Margin.Bottom;
        obj->Draw(g, (Padding.Left > obj->Margin.Left) ? Padding.Left : obj->Margin.Left, y);
        y += obj->ActualHeight;
    }
}
