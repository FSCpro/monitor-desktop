#include "memory_monitor.h"
#include <QPainter>
#include <QTimer>
#include "utils.h"

MemoryMonitor::MemoryMonitor(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer();
    percent = 0;

    timer->start(1000);

    connect(timer, &QTimer::timeout, this, [=]{
        Utils::getMemoryPercent(percent);
        repaint();
    });

    setFixedWidth(52);
}

void MemoryMonitor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRect(rect());

    painter.setBrush(QColor("#2CA7F8"));
    painter.drawRect(QRect(0, 50 - percent / 2, width(), percent / 2));

    painter.setPen(QColor("#000000"));
    painter.drawText(rect(), Qt::AlignCenter, QString::number(percent) + "%");
}
