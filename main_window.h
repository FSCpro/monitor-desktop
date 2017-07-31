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

private:
    QWidget *mainWidget;
    QHBoxLayout *layout;
    QLabel *downloadLabel;
    QLabel *uploadLabel;
    QTimer *timer;

    void sleep(unsigned int msec);

private slots:
    void timeout();
};

#endif // MAIN_WINDOW_H
