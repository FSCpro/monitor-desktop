#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <QWidget>

class MemoryMonitor : public QWidget
{
    Q_OBJECT

public:
    MemoryMonitor(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

private:
    int percent;
};

#endif // MEMORYMONITOR_H
