#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStatusBar>
#include <QDockWidget>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    /* File Menu */
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

    /* Edit Menu */
    QAction *undoAct = makeAction("undo.png", "&Undo", "Ctrl+Z", \
                                  "Undo", textedit, SLOT(undo( )));
    QAction *redoAct = makeAction("redo.png", "&Redo", "Ctrl+Shift+Z", \
                                  "Redo", textedit, SLOT(redo( )));
    QAction *copyAct = makeAction("copy.png", "&Copy", "Ctrl+C", \
                                  "Copy", textedit, SLOT(copy( )));
    QAction *cutAct = makeAction("cut.png", "C&ut", "Ctrl+X", \
                                  "Cut", textedit, SLOT(cut( )));
    QAction *pasteAct = makeAction("paste.png", "&Paste", "Ctrl+V", \
                                  "Paste", textedit, SLOT(paste( )));
    QAction *zoomInAct = makeAction("zoomIn.png", "Zoom &in", "Ctrl+=", \
                                  "Zoom In", textedit, SLOT(zoomIn( )));
    QAction *zoomOutAct = makeAction("zoomOut.png", "Zoon &out", "Ctrl+-", \
                                  "Zoom Out", textedit, SLOT(zoomOut( )));

    /* Format Menu */
    QAction *fontAct = makeAction("font.png", "&Font", "Ctrl+F", \
                                  "Font", this, SLOT(setFont( )));
    QAction *colorAct = makeAction("color.png", "C&olor", "Ctrl+G", \
                                  "Color", this, SLOT(setColor( )));
    QAction *alignLeftAct = makeAction("left.png", "&Left", "Ctrl+1", \
                                  "Left", this, SLOT(alignText( )));
    QAction *alignCenterAct = makeAction("center.png", "&Center", "Ctrl+2", \
                                  "Center", this, SLOT(alignText( )));
    QAction *alignRightAct = makeAction("right.png", "&Right", "Ctrl+3", \
                                  "Right", this, SLOT(alignText( )));
    QAction *alignJustifyAct = makeAction("justify.png", "&Justify", "Ctrl+4", \
                                  "Justify", this, SLOT(alignText( )));

    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    QMenu *editMenu = menubar->addMenu("&Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);

    QToolBar *fileToolBar = addToolBar("&File");
//    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QToolBar *editToolBar = addToolBar("&Edit");
//    editToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();
    editToolBar->addAction(copyAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addSeparator();
    editToolBar->addAction(zoomInAct);
    editToolBar->addAction(zoomOutAct);

    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)),
                 textedit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)),
                 textedit, SLOT(setFontPointSize(qreal)));

    addToolBarBreak( );      /* 다음 툴바는 아랫 줄로 위치 */

    QToolBar *formatToolbar = addToolBar("&Format");
    formatToolbar->addAction(fontAct);
    formatToolbar->addAction(colorAct);
    formatToolbar->addSeparator( );
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);
    formatToolbar->addSeparator( );
    formatToolbar->addAction(alignLeftAct);
    formatToolbar->addAction(alignCenterAct);
    formatToolbar->addAction(alignRightAct);
    formatToolbar->addAction(alignJustifyAct);

    QMenu *formatMenu = menubar->addMenu("&Format");
    formatMenu->addAction(fontAct);
    formatMenu->addAction(colorAct);
    QMenu *alignMenu = formatMenu->addMenu("&Align");
    alignMenu->setIcon(QIcon("align.png"));
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);

    QLabel* label = new QLabel("Dock Widget", this);
    QDockWidget *dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(label);

    QMenu *windowMenu = menubar->addMenu("&Window");
    windowMenu->addSeparator( );
    QMenu *toolbarMenu = windowMenu->addMenu("&Toolbar");
    toolbarMenu->addAction(fileToolBar->toggleViewAction( ));
    toolbarMenu->addAction(formatToolbar->toggleViewAction( ));
    toolbarMenu->addAction(editToolBar->toggleViewAction( ));
    windowMenu->addAction(dock->toggleViewAction( ));

    QStatusBar* statusbar = statusBar( );
    QLabel* statusLabel = new QLabel("Qt Editor", statusbar);
    statusLabel->setObjectName("StautsLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started", 1500);
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile( )
{
    statusBar()->showMessage("Make New File");
}

void QtEditor::openFile( )
{
    statusBar()->showMessage("Open a File");
}

void QtEditor::saveFile( )
{
    statusBar()->showMessage("Save this File");
}

void QtEditor::saveAsFile( )
{
    statusBar()->showMessage("Save this File as a new name");
}

void QtEditor::print( )
{
    statusBar()->showMessage("Print this File");
}

void QtEditor::setFont( )
{
    statusBar()->showMessage("Set Font");
}

void QtEditor::setColor( )
{
    statusBar()->showMessage("Set Color");
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

void QtEditor::alignText( )
{
    QAction *action = static_cast<QAction*>(sender( ));
    if(action->text( ) == "&Left")
        textedit->setAlignment(Qt::AlignLeft);
    else if(action->text( ) == "&Center")
        textedit->setAlignment(Qt::AlignCenter);
    else if(action->text( ) == "&Right")
        textedit->setAlignment(Qt::AlignRight);
    else if(action->text( ).contains("Justify", Qt::CaseInsensitive))
        textedit->setAlignment(Qt::AlignJustify);
}

