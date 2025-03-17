#include <ui/components/ThemeManager.h>

bool ThemeManager::theme = false;

void ThemeManager::toogleTheme(){
    theme = !theme;
}

bool ThemeManager::getTheme(){
    return theme;
}

int ThemeManager::getAssociationColor(){
    return theme ? LIGHT_ASSOCIATION : DARK_ASSOCIATION;
}

int ThemeManager::getSectionBackgroundColor(){
    return theme ? LIGHT_SECTION_BG : DARK_SECTION_BG;
}

int ThemeManager::getTextColor(){
    return theme ? LIGHT_TEXT : DARK_TEXT;
}

int ThemeManager::getWidgetBackgroundColor(){
    return theme ? LIGHT_WIDGET_BG : DARK_WIDGET_BG;
}
