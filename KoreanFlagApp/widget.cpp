/*
    Copyright (c) 2007. 6. 20, YoungJin Suh(valentis@gmail.com)

    This source code is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or (at
    your option) any later version.

    This library is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
    General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this library; if not, write to the Free Software Foundation,
    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <QtMath>
#include <QTimer>

#define DEGREE  56.31           // 건곤감리를 위한 각도

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), clipWidth(1)
{
    setWindowTitle("Korean Flag!");
    resize(300, 200);           // 기본창의 크기는 3:2으로 고정한다.

    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), SLOT(setDrawRect()));
    drawTimer->start(10);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *e)
{
    QRect clipRect(0, 0, clipWidth%width()+1, height());

    QPainter painter(this);
    painter.setClipping(true);
    painter.setClipRect(clipRect);

    // 대각선의 길이
    qreal diagonalLength = qSqrt(qPow(width(), 2)+qPow(height(), 2));
    qint16 start;
    // 반지름과 중앙 점 구하기
    qint16 radius = width()/3.;
    qint16 xPoint = (width()-radius)/2., yPoint = (height()-radius)/2.;

    // 외각선 그리기
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    // 태극 무늬의 외각선은 투명색으로
    painter.setPen(Qt::transparent);

    // 윗쪽 빨간색 반원
    QPainterPath pathBigRed;
    pathBigRed.arcMoveTo(xPoint, yPoint, radius, radius, -DEGREE/2);
    pathBigRed.arcTo(xPoint, yPoint, radius, radius, -DEGREE/2, 180);
    painter.setBrush(Qt::red);
    painter.drawPath(pathBigRed);

    // 아랫쪽 파랑색 반원
    QPainterPath pathBigBlue;
    pathBigBlue.arcMoveTo(xPoint, yPoint, radius, radius, 180-DEGREE/2);
    pathBigBlue.arcTo(xPoint, yPoint, radius, radius, 180-DEGREE/2, 180);
    painter.setBrush(Qt::blue);
    painter.drawPath(pathBigBlue);

    // 중간의 작은 빨간색 반원
    painter.setBrush(Qt::red);
    painter.resetTransform();
    painter.translate(width()/2, height()/2);
    painter.rotate(-DEGREE);
    painter.drawEllipse(-radius/4, -radius/2, radius/2., radius/2.);

    // 중간의 작은 파란색 반원
    painter.setBrush(Qt::blue);
    painter.resetTransform();
    painter.translate(width()/2, height()/2);
    painter.rotate(-DEGREE);
    painter.drawEllipse(-radius/4, 0, radius/2., radius/2.);

    // 건
    start = -radius*(0.5+0.25+1/3.);
    painter.resetTransform();
    painter.translate(width()/2, height()/2);
    painter.rotate(-DEGREE);
    painter.setBrush(Qt::black);
    for(int i = 0; i < 3; i++)
        painter.drawRect(-radius/4, start+(radius/24+radius/12)*i, radius/2, radius/12);

    // 곤
    start = diagonalLength/2-(radius*(0.5+0.25+1/3.))+radius/24;
    painter.setBrush(Qt::black);
    for(int i = 0; i < 3; i++) {
        painter.drawRect(-radius/4, start+(radius/24+radius/12)*i, radius/4-radius/48, radius/12);
        painter.drawRect(radius/48, start+(radius/24+radius/12)*i, radius/4-radius/48, radius/12);
    }

    // 감
    start = -radius*(0.5+0.25+1/3.);
    painter.resetTransform();
    painter.translate(width()/2, height()/2);
    painter.rotate(DEGREE);
    painter.setBrush(Qt::black);
    for(int i = 0; i < 3; i++) {
        if(i%2) {
            painter.drawRect(-radius/4, start+(radius/24+radius/12)*i, radius/2, radius/12);
        } else {
            painter.drawRect(-radius/4, start+(radius/24+radius/12)*i, radius/4-radius/48, radius/12);
            painter.drawRect(radius/48, start+(radius/24+radius/12)*i, radius/4-radius/48, radius/12);
        }
    }

    // 리
    start = diagonalLength/2-(radius*(0.5+0.25+1/3.))+radius/24;
    painter.resetTransform();
    painter.translate(width()/2, height()/2);
    painter.rotate(DEGREE);
    painter.setBrush(Qt::black);
    for(int i = 0; i < 3; i++) {
        if(i%2) {
            painter.drawRect(-radius/4, start+(radius/24+radius/12)*i, radius/4-radius/48, radius/12);
            painter.drawRect(radius/48, start+(radius/24+radius/12)*i, radius/4-radius/48, radius/12);
        } else {
            painter.drawRect(-radius/4, start+(radius/24+radius/12)*i, radius/2, radius/12);
        }
    }

    QWidget::paintEvent(e);
}

void Widget::resizeEvent(QResizeEvent* e)
{
    // 크기 변화시 3:2을 유지하도록 고정
    resize(e->size().width(), e->size().width()*2/3);
}

void Widget::setDrawRect()
{
    clipWidth++;
    update();
}
