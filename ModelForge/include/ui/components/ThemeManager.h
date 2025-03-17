#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#define DARK_SECTION_BG     0x21252A
#define DARK_WIDGET_BG      0x292C34
#define DARK_TEXT           0xffffff
#define DARK_ASSOCIATION    0xffffff

#define LIGHT_SECTION_BG    0xffffff
#define LIGHT_WIDGET_BG     0xffffff
#define LIGHT_TEXT          0x000000
#define LIGHT_ASSOCIATION   0x000000

class ThemeManager{
private:
    static bool theme;

public:
    static void toogleTheme();
    static bool getTheme();

    static int getSectionBackgroundColor();
    static int getWidgetBackgroundColor();
    static int getTextColor();
    static int getAssociationColor();

};

#endif // THEMEMANAGER_H
