#ifndef EDITORTABSVIEW_H
#define EDITORTABSVIEW_H

#include "EditorTabsPlugin.h"

#include <coreplugin/editormanager/ieditor.h>


#include <QtGui>

namespace JieXin{
namespace EditorTabs {
enum Tabs {
    Tab_1   = 0x0,
    Tab_2   = 0x1,
    Tab_3   = 0x2,
    Tab_4   = 0x3,
    Tab_5   = 0x4,
    Tab_6   = 0x5,
    Tab_7   = 0x6,
    Tab_8   = 0x7,
    Tab_9   = 0x8,
    Tab_10  = 0x9
};

class EditorTabsWidget : public QWidget
{
    Q_OBJECT

public:
    EditorTabsWidget();
    ~EditorTabsWidget();

    QWidget *getTabWidget();
    Core::IEditor *getEditor(QWidget *tab);
    QWidget *getTab(Core::IEditor *editor);


    bool eventFilter(QObject *obj, QEvent *event);
    bool isEditorWdiget(QObject *obj);

private slots:
//    void handleClicked(const QModelIndex &);
//    void handlePressed(const QModelIndex &);
    void updateCurrentTab(Core::IEditor* editor);
//    void contextMenuRequested(QPoint pos);
    void handleCurrentChanged(int index);
    void handleEditorOpened(Core::IEditor* editor);
    void handlerEditorClosed(QList<Core::IEditor*> editors);

    void handleTabCloseRequested(int index);

/*
private:
    void activateEditor(const QModelIndex &index);
    void closeEditor(const QModelIndex &index);
*/


private:
    QTabWidget *m_tabWidget;
    QMap<QWidget*, Core::IEditor*> m_tabsEtiors;
};

} // namespace EditorTabs
} // namespace JieXin

#endif // EDITORTABSVIEW_H
