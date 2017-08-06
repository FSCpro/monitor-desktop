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
    painter.setBrush(QColor("#4A4A4A"));
    painter.drawRect(rect());

    if (percent <= 30)
        painter.setBrush(QColor("#63C1FF"));
    else if (percent <= 50)
        painter.setBrush(QColor("#2CA7F8"));
    else if (percent <= 60)
        painter.setBrush(QColor("#0078C8"));
    else if (percent <= 70)
        painter.setBrush(QColor("#FFA54C"));
    else if (percent <= 80)
        painter.setBrush(QColor("#FF7E00"));
    else if (percent <= 100)
        painter.setBrush(QColor("#FF4B4B"));

    painter.drawRect(QRect(0, 51 - percent / 2, width(), percent / 2));

    if (percent <= 30)
        painter.setPen(QColor("#FFFFFF"));
    else if (percent <= 50)
        painter.setPen(QColor("#FFFFFF"));
    else if (percent <= 60)
        painter.setPen(QColor("#FFFFFF"));
    else if (percent <= 70)
        painter.setPen(QColor("#000000"));
    else if (percent <= 80)
        painter.setPen(QColor("#000000"));
    else if (percent <= 100)
        painter.setPen(QColor("#FFFFFF"));

    painter.drawText(rect(), Qt::AlignCenter, QString::number(percent, 'r', 0) + "%");
}
