#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QDir;
class QListWidget;
class QListWidgetItem;
class QLineEdit;
class QTextEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QDir *directory;
    QListWidget *dirListWidget;
    QLineEdit *filenameLineEdit;
    QTextEdit *outputEdit;
    void refreshDir();

public slots:
    void selectItem(QListWidgetItem*);            /* QListWidget의 클릭 */
    void changeDir();                                     /* QListWidget의 더블 클릭 */
    void makeDir();
    void removeDir();
    void renameDir();
};
#endif // WIDGET_H
