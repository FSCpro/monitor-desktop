#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QWidget *mainWidget;
    QHBoxLayout *layout;
    QVBoxLayout *networkLayout;
    QLabel *downloadLabel;
    QLabel *uploadLabel;
    QTimer *timer;
    QPoint p;

    void sleep(unsigned int msec);

private slots:
    void timeout();
};

#endif // MAIN_WINDOW_H
