#include "main_window.h"
#include "utils.h"
#include <QTime>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget();
    layout = new QHBoxLayout();
    downloadLabel = new QLabel("↓0.0 KB/s");
    uploadLabel = new QLabel("↑0.0 KB/s");
    timer = new QTimer(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    layout->addWidget(downloadLabel);
    layout->addWidget(uploadLabel);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    timer->start(500);

    connect(timer, &QTimer::timeout, this, &MainWindow::timeout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < reachTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::timeout()
{
    unsigned long long int prevRecv = 0, prevSend = 0;
    unsigned long long int recv = 0, send = 0;

    Utils::getNetworkBandWidth(prevRecv, prevSend);

    sleep(1000);

    Utils::getNetworkBandWidth(recv, send);

    downloadLabel->setText("↓" + QString::number((recv - prevRecv) / 1024.0, 'f', 1) + " KB/s");
    uploadLabel->setText("↑" + QString::number((send - prevSend) / 1024.0, 'f', 1) + " KB/s");
}
