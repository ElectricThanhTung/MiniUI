

#include "UIs.hpp"

class MainWindow : public Window {
public:
    MainWindow(Size &size) {
        this->Width = size.Width;
        this->Height = size.Height;

        MainPanel.BackgroundColor = Color::Red;
        MainPanel.Orientation = Vertical;

        Panel1.BackgroundColor = Color::Green;
        Panel1.Height = 150;
        Panel1.Margin = Thickness(5, 5, 5, 5);

        Panel2.BackgroundColor = Color::Yellow;
        Panel2.Orientation = Horizontal;
        Panel2.Margin = Thickness(5, 5, 5, 5);

        Panel3.BackgroundColor = Color::Pink;
        Panel3.Margin = Thickness(5, 5, 5, 5);

        Panel4.BackgroundColor = Color::Orange;
        Panel4.Margin = Thickness(5, 5, 5, 5);

        Panel5.BackgroundColor = Color::Purple;
        Panel5.Margin = Thickness(5, 5, 5, 5);

        Panel2.Content.Add(Panel3);
        Panel2.Content.Add(Panel4);
        Panel2.Content.Add(Panel5);

        MainPanel.Content.Add(Panel1);
        MainPanel.Content.Add(Panel2);

        this->SetContent(MainPanel);
    }
private:
    StackPanel Panel1 = StackPanel();
    StackPanel Panel2 = StackPanel();
    StackPanel Panel3 = StackPanel();
    StackPanel Panel4 = StackPanel();
    StackPanel Panel5 = StackPanel();
    StackPanel MainPanel = StackPanel();
};
