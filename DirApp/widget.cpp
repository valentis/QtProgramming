#include "widget.h"

#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProcess>
#include <QTextEdit>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir(".");
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    QPushButton *makeDir = new QPushButton("Make Directory", this);
    QPushButton* removeDir = new QPushButton("Remove Directory", this);
    QPushButton *renameDir = new QPushButton("Rename Directory", this);
    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(makeDir);
    layout->addWidget(removeDir);
    layout->addWidget(renameDir);
    layout->addWidget(outputEdit);

    connect(dirListWidget, SIGNAL(itemClicked(QListWidgetItem *)), \
                                     SLOT( selectItem(QListWidgetItem*) ));
    connect(dirListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), \
                                     SLOT( changeDir() ));
    connect(makeDir, SIGNAL(clicked()), SLOT( makeDir()) );
    connect(renameDir, SIGNAL(clicked()), SLOT( renameDir()));
    connect(removeDir, SIGNAL(clicked()), SLOT( removeDir()));

    refreshDir();
}

Widget::~Widget()
{
}

void Widget::refreshDir()
{
    dirListWidget->clear();
    for(int index = 0; index < directory->entryList().count(); index++) {
        dirListWidget->addItem(directory->entryList().at(index));
    };
}

void Widget::selectItem(QListWidgetItem* item)
{
    filenameLineEdit->setText(item->text());
}

void Widget::changeDir()
{
    QString file = directory->absoluteFilePath(dirListWidget->currentItem()->text());

    QFileInfo checkDir(file);
    if(checkDir.isDir()) {
        directory->cd(file);
        refreshDir();
    } else if(checkDir.isExecutable()) {
        QProcess cmd;
        QStringList arguments;
        cmd.start(file, arguments);
        qDebug() << file;

        outputEdit->clear();
        if (!cmd.waitForStarted()) return;
        QByteArray result = cmd.readAllStandardOutput();
        outputEdit->append(result);
        if (!cmd.waitForFinished()) return;
        result = cmd.readAllStandardOutput();
        outputEdit->append(result);
    }
}

void Widget::makeDir()
{
    if(filenameLineEdit->text().length()) {
        directory->mkdir(filenameLineEdit->text());
        directory->refresh();         /* QDir 클래스는 현재의 디렉터리 정보를 캐싱 */
        refreshDir();
    }
}

void Widget::removeDir()
{
    if(filenameLineEdit->text().length()) {
        directory->rmdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

void Widget::renameDir()
{
    if(filenameLineEdit->text().length()) {
        directory->rename(dirListWidget->currentItem()->text(), \
                                    filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}
