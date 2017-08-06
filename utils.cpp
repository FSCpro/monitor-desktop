#include "utils.h"
#include <QTime>
#include <QApplication>
#include <QFile>

void Utils::getMemoryPercent(int &percent)
{
    FILE *file = fopen("/proc/meminfo", "r");
    unsigned long memTotal;
    unsigned long memAvailable;
    unsigned long memFree;
    unsigned long buffers;
    unsigned long cached;
    unsigned long swapTotal;
    unsigned long swapFree;
    char str[256];
    char *temp;

    while(fgets(str, sizeof(str) , file) != NULL) {
        temp = strtok(str, ": ");

        if(strcmp(temp, "MemTotal") == 0)
            memTotal = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "MemAvailable") == 0)
            memAvailable = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "MemFree") == 0)
            memFree = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "Buffers") == 0)
            buffers = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "Cached") == 0)
            cached = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "SwapTotal") == 0)
            swapTotal = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "SwapFree") == 0)
            swapFree = (unsigned long)atof(strtok (NULL, ": "));
    }

    percent = (memTotal - memAvailable) * 100.0 / memTotal;
}

void Utils::getNetworkBandWidth(unsigned long long int &receiveBytes, unsigned long long int &sendBytes)
{
    char *buf;
    static int bufsize;
    FILE *devfd;

    buf = (char *) calloc(255, 1);
    bufsize = 255;
    devfd = fopen("/proc/net/dev", "r");

    // Ignore the first two lines of the file.
    fgets(buf, bufsize, devfd);
    fgets(buf, bufsize, devfd);

    receiveBytes = 0;
    sendBytes = 0;

    while (fgets(buf, bufsize, devfd)) {
        unsigned long long int rBytes, sBytes;
        char *line = strdup(buf);

        char *dev;
        dev = strtok(line, ":");

        // Filter lo (virtual network device).
        if (QString::fromStdString(dev).trimmed() != "lo") {
            sscanf(buf + strlen(dev) + 2, "%llu %*d %*d %*d %*d %*d %*d %*d %llu", &rBytes, &sBytes);

            receiveBytes += rBytes;
            sendBytes += sBytes;
        }

        free(line);
    }

    fclose(devfd);
    free(buf);
}

void Utils::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < reachTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
