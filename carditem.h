#pragma once
#include <QString>

struct CardItem {
    enum class AccessType { Free, Unlocked, Locked };
    int         moduleIndex;
    QString     moduleName;
    QString     imagePath;
    QString     name;
    QString     comment;   // tam metin
    QString     detail;    // detay sayfası uzun metin
    bool        hasAdvancedSettings = false;
    AccessType  accessType = AccessType::Free;
    QString     url= "";
};
