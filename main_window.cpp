#include "main_window.h"
#include "utils.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget();
    layout = new QHBoxLayout();
    networkLayout = new QVBoxLayout();
    memoryMonitor = new MemoryMonitor();
    downloadLabel = new QLabel("↓0.0K");
    uploadLabel = new QLabel("↑0.0K");
    timer = new QTimer(this);

    QAction *quitAction = new QAction("退出", this);
    menu = new QMenu;
    menu->addAction(quitAction);

    downloadLabel->setStyleSheet("QLabel { font-size: 13px; color: #FFFFFF; }");
    uploadLabel->setStyleSheet("QLabel { font-size: 13px; color: #FFFFFF; }");

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);

    networkLayout->setMargin(0);
    networkLayout->setSpacing(0);
    networkLayout->addStretch();
    networkLayout->addWidget(uploadLabel);
    networkLayout->addWidget(downloadLabel);
    networkLayout->addStretch();

    layout->setMargin(0);
    layout->addWidget(memoryMonitor);
    layout->addLayout(networkLayout);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    timer->start(500);

    connect(timer, &QTimer::timeout, this, &MainWindow::timeout);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#343639"));
    painter.drawRect(rect());
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
        move(e->globalPos() - p);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        p = e->globalPos() - frameGeometry().topLeft();
    }else if (e->button() == Qt::RightButton)
        menu->exec(QCursor::pos());
}

void MainWindow::timeout()
{
    unsigned long long int prevRecv = 0, prevSend = 0;
    unsigned long long int recv = 0, send = 0;

    Utils::getNetworkBandWidth(prevRecv, prevSend);
    Utils::sleep(1000);
    Utils::getNetworkBandWidth(recv, send);


    downloadLabel->setText("↓" + Utils::networkConversion(recv - prevRecv));
    uploadLabel->setText("↑" + Utils::networkConversion(send - prevSend));
}
