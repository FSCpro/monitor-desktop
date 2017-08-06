#include "memory_monitor.h"
#include <QPainter>
#include <QDebug>
#include "utils.h"

MemoryMonitor::MemoryMonitor(QWidget *parent)
    : QWidget(parent)
{
    setFixedWidth(50);

}

void MemoryMonitor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F7BCB8"));
    painter.drawRect(rect());
}
