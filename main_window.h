#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include "memory_monitor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QWidget *mainWidget;
    QHBoxLayout *layout;
    QVBoxLayout *networkLayout;
    MemoryMonitor *memoryMonitor;
    QLabel *downloadLabel;
    QLabel *uploadLabel;
    QTimer *timer;
    QPoint p;

private slots:
    void timeout();
};

#endif // MAIN_WINDOW_H
