#include "EditorTabsView.h"

#include <coreplugin/editormanager/editormanager.h>
/*
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/icore.h>
#include <coreplugin/coreconstants.h>
*/

#include <QList>
#include <QMap>
#include <QListIterator>
#include <QAction>

using namespace JieXin;
using namespace EditorTabs;

EditorTabsWidget::EditorTabsWidget()
{
    Core::EditorManager *em = Core::EditorManager::instance();
    // init TabWidget
    m_tabWidget = new QTabWidget();
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_tabWidget->sizePolicy().hasHeightForWidth());
    m_tabWidget->setSizePolicy(sizePolicy);
    m_tabWidget->setUsesScrollButtons(true);
    m_tabWidget->setTabsClosable(true);
    m_tabWidget->setMovable(true);

    QList<Core::IEditor*> editors = em->openedEditors();
    QListIterator<Core::IEditor*> editorsItr(editors);
    while (editorsItr.hasNext())
    {
        QWidget *tab = new QWidget();
        Core::IEditor *editor = editorsItr.next();
        // init the Tabs
        m_tabWidget->addTab(tab, editor->displayName());
        // init the Map of Tabs and Editors
        m_tabsEtiors.insert(tab, editor);
    }

    // init the signals and slots
    connect(em, SIGNAL(currentEditorChanged(Core::IEditor*)),
            this, SLOT(updateCurrentTab(Core::IEditor*)));

    connect(m_tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(handleCurrentChanged(int)));

    connect(em, SIGNAL(editorOpened(Core::IEditor*)),
            this, SLOT(handleEditorOpened(Core::IEditor*)));

    connect(em, SIGNAL(editorsClosed(QList<Core::IEditor*>)),
            this, SLOT(handlerEditorClosed(QList<Core::IEditor*>)));

    connect(m_tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(handleTabCloseRequested(int)));
}

EditorTabsWidget::~EditorTabsWidget() {}

void EditorTabsWidget::updateCurrentTab(Core::IEditor *editor)
{
    m_tabWidget->setCurrentWidget(this->getTab(editor));
}

void EditorTabsWidget::handleCurrentChanged(int index)
{
    if (index != -1)
    {
        QWidget *tab = m_tabWidget->widget(index);
        if (m_tabsEtiors.contains(tab))
            Core::EditorManager::instance()->activateEditor(this->getEditor(tab));
    }
}

void EditorTabsWidget::handleEditorOpened(Core::IEditor *editor)
{
    QWidget *tab = new QWidget();
    m_tabWidget->addTab(tab, editor->displayName());
    m_tabsEtiors.insert(tab, editor);
    // jx_add: for trigger event
    editor->widget()->installEventFilter(this);
}

void EditorTabsWidget::handlerEditorClosed(QList<Core::IEditor *> editors)
{
    QListIterator<Core::IEditor*> editorsItr(editors);
    while (editorsItr.hasNext())
    {
        Core::IEditor *editor = editorsItr.next();
        QWidget *tab = getTab(editor);
        if (m_tabsEtiors.contains(tab))
            m_tabsEtiors.remove(tab);
        if (-1 < m_tabWidget->indexOf(tab))
            m_tabWidget->removeTab( m_tabWidget->indexOf(tab) );
    }
}

void EditorTabsWidget::handleTabCloseRequested(int index)
{
    if (-1 < index) {
        QWidget *tab = m_tabWidget->widget(index);
        QList<Core::IEditor*> editorsToClose;
        editorsToClose.clear();
        if (m_tabsEtiors.contains(tab)) {
            editorsToClose.append(this->getEditor(tab));
            // notice: closeEditors will emit the SIGNAL(editorsClosed(QList<Core::IEditor*>))
            Core::EditorManager::instance()->closeEditors(editorsToClose);
            if (m_tabsEtiors.contains(tab))
                m_tabsEtiors.remove(tab);
            if (-1 < m_tabWidget->indexOf(tab))
                m_tabWidget->removeTab(m_tabWidget->indexOf(tab));
        }
    }
}

QWidget *EditorTabsWidget::getTabWidget()
{
    return this->m_tabWidget;
}

Core::IEditor *EditorTabsWidget::getEditor(QWidget *tab)
{
    return m_tabsEtiors.value(tab);
}

QWidget *EditorTabsWidget::getTab(Core::IEditor *editor)
{
    return m_tabsEtiors.key(editor);
}

bool EditorTabsWidget::eventFilter(QObject *obj, QEvent *event)
{
    //qWarning("event = %x", event->type());
    if (event->type() == QEvent::KeyPress && isEditorWdiget(obj)) {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        //qWarning("key = %x", ke->key());
        if ( ke->modifiers() == Qt::AltModifier ) {
            switch (ke->key()) {
            case Qt::Key_1:
                m_tabWidget->setCurrentIndex(Tab_1);
                break;
            case Qt::Key_2:
                m_tabWidget->setCurrentIndex(Tab_2);
                break;
            case Qt::Key_3:
                m_tabWidget->setCurrentIndex(Tab_3);
                break;
            case Qt::Key_4:
                m_tabWidget->setCurrentIndex(Tab_4);
                break;
            case Qt::Key_5:
                m_tabWidget->setCurrentIndex(Tab_5);
                break;
            case Qt::Key_6:
                m_tabWidget->setCurrentIndex(Tab_6);
                break;
            case Qt::Key_7:
                m_tabWidget->setCurrentIndex(Tab_7);
                break;
            case Qt::Key_8:
                m_tabWidget->setCurrentIndex(Tab_8);
                break;
            case Qt::Key_9:
                m_tabWidget->setCurrentIndex(Tab_9);
                break;
            case Qt::Key_0:
                m_tabWidget->setCurrentIndex(Tab_10);
                break;
            default:
                break;
            }
            return true;
        }
    }
    return false;
}

bool EditorTabsWidget::isEditorWdiget(QObject *obj)
{
    QMapIterator<QWidget*, Core::IEditor*> i(m_tabsEtiors);
    while (i.hasNext()) {
        i.next();
        if (obj == i.value()->widget())
            return true;
    }
    return false;
}


