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

QPalette ThemeManager::darkPalette = QPalette();//QColor(0x21252A));

QPalette ThemeManager::lightPalette = QPalette();//QColor(0xffffff));

const QPalette& ThemeManager::getLightPalette(){
    return lightPalette;
}

const QPalette& ThemeManager::getDarkPalette(){
    return darkPalette;
}

void ThemeManager::createPalettes(const QPalette& systemPalette){
    darkPalette = QPalette(QColor(0x21252A));
    lightPalette = QPalette(systemPalette);

    lightPalette.setColor(QPalette::WindowText, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::Button, QColor(220, 220, 220));
    lightPalette.setColor(QPalette::Light, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::Midlight, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::Dark, QColor(127, 127, 127));
    lightPalette.setColor(QPalette::Mid, QColor(170, 170, 170));
    lightPalette.setColor(QPalette::Text, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::BrightText, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::Shadow, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::AlternateBase, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
    lightPalette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::PlaceholderText, QColor(0, 0, 0, 127));
    lightPalette.setColor(QPalette::Accent, QColor(255, 255, 255));

}
