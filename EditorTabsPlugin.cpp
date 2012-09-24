#include "EditorTabsPlugin.h"
#include "EditorTabsView.h"

#include <coreplugin/editormanager/editormanager.h>

#include <QtPlugin>


using namespace JieXin;
using namespace EditorTabs;

EditorTabsPlugin::EditorTabsPlugin()
{
}

EditorTabsPlugin::~EditorTabsPlugin()
{
}

void EditorTabsPlugin::extensionsInitialized()
{
}

bool EditorTabsPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);
    Core::EditorManagerPlaceHolder* emph =  Core::EditorManagerPlaceHolder::current();
    EditorTabsWidget *etw = new EditorTabsWidget();
    emph->layout()->addWidget(etw->getTabWidget());
    addAutoReleasedObject(etw);
    return true;
}

Q_EXPORT_PLUGIN(EditorTabsPlugin)
