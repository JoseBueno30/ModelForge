#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QPalette>
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
    static QPalette darkPalette;
    static QPalette lightPalette;

public:
    static void toogleTheme();
    static bool getTheme();
    static void getInitialTheme();

    const static QPalette& getLightPalette();
    const static QPalette& getDarkPalette();

    static int getSectionBackgroundColor();
    static int getWidgetBackgroundColor();
    static int getTextColor();
    static int getAssociationColor();

    static void createPalettes(const QPalette& systemPalette);



};

#endif // THEMEMANAGER_H
