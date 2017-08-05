#include "memory_monitor.h"
#include <QPainter>

MemoryMonitor::MemoryMonitor(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(50);
}

void MemoryMonitor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRect(rect());
}
