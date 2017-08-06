#include "memory_monitor.h"
#include <QPainter>
#include <QDebug>
#include "utils.h"

MemoryMonitor::MemoryMonitor(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(52);

    int i;
    Utils::getMemoryPercent(i);
}

void MemoryMonitor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#EBEBEB"));
    painter.drawRect(rect());
}
