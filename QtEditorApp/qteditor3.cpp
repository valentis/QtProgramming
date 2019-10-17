#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QApplication>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit *textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

#if 0
    QAction *newAct = new QAction(QIcon("new.png"), "&New", this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("make new file"));
    connect(newAct, SIGNAL(triggered( )), SLOT(newFile( )));
#else
    QAction *newAct = makeAction("new.png", "&New", "Ctrl+N", \
                                 "make new file", this, SLOT(newFile( )));
#endif
    QAction *openAct = makeAction("open.png", "&Open", "Ctrl+O", \
                                  "Open a file", this, SLOT(openFile( )));

    QAction *saveAct = makeAction("save.png", "&Save", "Ctrl+S", \
                                  "Save this file", this, SLOT(saveFile( )));

    QAction *saveAsAct = makeAction("saveas.png", "&Save &as...", "Ctrl+Shift+S", \
                                  "Save this file as a new name", this, SLOT(saveAsFile( )));

    QAction *printAct = makeAction("print.png", "&Print", "Ctrl+P", \
                                  "Print this file", this, SLOT(print( )));

    QAction *quitAct = makeAction("quit.png", "&Quit", "Ctrl+Q", \
                                  "Quit this program", qApp, SLOT(quit( )));

    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu *formatMenu = menubar->addMenu("&Format");
    formatMenu->addAction(fileToolBar->toggleViewAction( ));
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile( )
{
    qDebug("Make New File");
}

void QtEditor::openFile( )
{
    qDebug("Open a File");
}

void QtEditor::saveFile( )
{
    qDebug("Save this File");
}

void QtEditor::saveAsFile( )
{
    qDebug("Save this File as a new name");
}

void QtEditor::print( )
{
    qDebug("print this File");
}

QAction *QtEditor::makeAction(QString icon, QString name, \
                              QString shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(name, this);
    if(icon.length( ))
         act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

