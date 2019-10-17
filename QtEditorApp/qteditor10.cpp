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
#include <QMdiArea>
#include <QMdiSubWindow>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), SLOT(setFontWidget( )));
    setCentralWidget(mdiArea);

#if 0				// Edit 메뉴를 수정한 후 0으로 변경
    QTextEdit *textedit = new QTextEdit(this);
//    setCentralWidget(textedit);
    mdiArea->addSubWindow(textedit);
#else
    newFile( );
#endif

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
    QAction *openAct = makeAction(":/images/open.png", "&Open", "Ctrl+O", \
                                  "Open a file", this, SLOT(openFile( )));
    QAction *saveAct = makeAction(":/images/save.png", "&Save", "Ctrl+S", \
                                  "Save this file", this, SLOT(saveFile( )));
    QAction *saveAsAct = makeAction(":/images/saveas.png", "&Save &as...", "Ctrl+Shift+S", \
                                  "Save this file as a new name", this, SLOT(saveAsFile( )));
    QAction *printAct = makeAction(":/images/print.png", "&Print", "Ctrl+P", \
                                   "Print this file", this, SLOT(print( )));
    QAction *quitAct = makeAction(":/images/quit.png", "&Quit", "Ctrl+Q", \
                                  "Quit this program", qApp, SLOT(quit( )));

    /* Edit Menu */
    QAction *undoAct = makeAction(":/images/undo.png", "&Undo", "Ctrl+Z", \
                                  "Undo", this, SLOT(undo( )));
    QAction *redoAct = makeAction(":/images/redo.png", "&Redo", "Ctrl+Shift+Z", \
                                  "Redo", this, SLOT(redo( )));
    QAction *copyAct = makeAction(":/images/copy.png", "&Copy", "Ctrl+C", \
                                  "Copy", this, SLOT(copy( )));
    QAction *cutAct = makeAction(":/images/cut.png", "C&ut", "Ctrl+X", \
                                  "Cut", this, SLOT(cut( )));
    QAction *pasteAct = makeAction(":/images/paste.png", "&Paste", "Ctrl+V", \
                                  "Paste", this, SLOT(paste( )));
    QAction *zoomInAct = makeAction(":/images/zoomIn.png", "Zoom &in", "Ctrl+=", \
                                  "Zoom In", this, SLOT(zoomIn( )));
    QAction *zoomOutAct = makeAction(":/images/zoomOut.png", "Zoon &out", "Ctrl+-", \
                                  "Zoom Out", this, SLOT(zoomOut( )));

    /* Format Menu */
    QAction *fontAct = makeAction(":/images/font.png", "&Font", "Ctrl+F", \
                                  "Font", this, SLOT(setFont( )));
    QAction *colorAct = makeAction(":/images/color.png", "C&olor", "Ctrl+G", \
                                  "Color", this, SLOT(setColor( )));
    QAction *alignLeftAct = makeAction(":/images/left.png", "&Left", "Ctrl+1", \
                                  "Left", this, SLOT(alignText( )));
    QAction *alignCenterAct = makeAction(":/images/center.png", "&Center", "Ctrl+2", \
                                  "Center", this, SLOT(alignText( )));
    QAction *alignRightAct = makeAction(":/images/right.png", "&Right", "Ctrl+3", \
                                  "Right", this, SLOT(alignText( )));
    QAction *alignJustifyAct = makeAction(":/images/justify.png", "&Justify", "Ctrl+4", \
                                  "Justify", this, SLOT(alignText( )));

    /* Window Menu */
    QAction *cascadeAct = makeAction(":/images/cascade.png", "&Cascade", "Ctrl+9", \
                                  "Cascade", mdiArea, SLOT(cascadeSubWindows( )));
    QAction *tileAct = makeAction(":/images/tile.png", "&Tile", "Ctrl+0", \
                                  "Tile", mdiArea, SLOT(tileSubWindows( )));
    QAction *prevWindowAct = makeAction(":/images/left.png", "&Left", "Ctrl+1", \
                                  "Left", mdiArea, SLOT(activatePreviousSubWindow( )));
    QAction *nextWindowAct = makeAction(":/images/center.png", "&Center", "Ctrl+2", \
                                  "Center", mdiArea, SLOT(activateNextSubWindow( )));

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

    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)),
                 this, SLOT(setCurrentFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)),
                 this, SLOT(setFontPointSize(qreal)));

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
    windowMenu->addAction(cascadeAct);
    windowMenu->addAction(tileAct);
    windowMenu->addSeparator( );
    windowMenu->addAction(prevWindowAct);
    windowMenu->addAction(nextWindowAct);
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
    QTextEdit *textedit = new QTextEdit;
    connect(textedit, SIGNAL(cursorPositionChanged( )), SLOT(setFontWidget( )));
    mdiArea->addSubWindow(textedit);
    textedit->show( );
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
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
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
}

void QtEditor::undo( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->undo( );
    }
}

void QtEditor::redo( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->redo( );
    }
}

void QtEditor::copy( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->copy( );
    }
}

void QtEditor::cut( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->cut( );
    }
}

void QtEditor::paste( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->paste( );
    }
}

void QtEditor::zoomIn( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->zoomIn( );
    }
}

void QtEditor::zoomOut( )
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->zoomOut( );
    }
}

void QtEditor::setCurrentFont(const QFont &f)
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        textedit->setCurrentFont(f);
    }
}

void QtEditor::setFontPointSize(qreal s)
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow( );
    if(subWindow != nullptr) {
        QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget( ));
        QFont font = textedit->currentFont( );
        font.setPointSizeF(s);
        textedit->setCurrentFont(font);
    }
}

void QtEditor::setFontWidget( )   /* QFontComboBox와 QDoubleSpinBox 설정 */
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow( )->widget( );
    QFont font = textedit->currentFont( );
    fontComboBox->setCurrentFont(font);    /* QFontComboBox와 QSpinBox를 */
    sizeSpinBox->setValue(font.pointSizeF( ));             /* 클래스의 멤버로 변경 */
}


