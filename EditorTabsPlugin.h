#ifndef EDITORTABSPLUGIN_H
#define EDITORTABSPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace JieXin{
namespace EditorTabs {

class EditorTabsPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
public:
    EditorTabsPlugin();
    ~EditorTabsPlugin();

    void extensionsInitialized();
    bool initialize(const QStringList &arguments, QString *errorString);

};

} // namespace EditorTabs
} // namespace JieXin
#endif // EDITORTABSPLUGIN_H
