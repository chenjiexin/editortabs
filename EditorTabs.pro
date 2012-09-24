QTC_SOURCE = /your/qtcreator/src/dir
QTC_BUILD = /your/qtcreator/build/dir
TEMPLATE = lib
TARGET = EditorTabs
IDE_SOURCE_TREE = $$QTC_SOURCE
IDE_BUILD_TREE     = $$QTC_BUILD
PROVIDER = JieXin
DESTDIR = $$QTC_BUILD/JieXin
LIBS += -L$$QTC_BUILD/lib/qtcreator/plugins/Nokia
LIBS += -L$$QTC_BUILD/lib/qtcreator
include($$QTC_SOURCE/src/qtcreatorplugin.pri)
include($$QTC_SOURCE/src/plugins/coreplugin/coreplugin.pri)

HEADERS += \
    EditorTabsView.h \
    EditorTabsPlugin.h

SOURCES += \
    EditorTabsView.cpp \
    EditorTabsPlugin.cpp

OTHER_FILES += \
    EditorTabs.pluginspec
