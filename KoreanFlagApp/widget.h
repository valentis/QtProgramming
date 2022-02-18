#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QTimer* drawTimer;
    int clipWidth;

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);

private slots:
    void setDrawRect();
};

#endif // WIDGET_H
