#include "utils.h"
#include <QTime>
#include <QApplication>

void Utils::getMemoryPercent(float &percent)
{
    FILE *fp = fopen("/proc/meminfo", "r");
    unsigned long memTotal;
    unsigned long memAvailable;
    char str[256];
    char *temp;

    while(fgets(str, sizeof(str) , fp) != NULL) {
        temp = strtok(str, ": ");

        if(strcmp(temp, "MemTotal") == 0)
            memTotal = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "MemAvailable") == 0)
            memAvailable = (unsigned long)atof(strtok (NULL, ": "));
    }

    percent = (memTotal - memAvailable) * 100.0 / memTotal;

    fclose(fp);
}

void Utils::getNetworkBandWidth(unsigned long long int &receiveBytes, unsigned long long int &sendBytes)
{
    char buffer[255];
    FILE *fp = fopen("/proc/net/dev", "r");

    // Ignore the first two lines of the file.
    fgets(buffer, 255, fp);
    fgets(buffer, 255, fp);

    receiveBytes = 0;
    sendBytes = 0;

    while (fgets(buffer, 255, fp)) {
        unsigned long long int rBytes, sBytes;
        char *line = strdup(buffer);

        char *dev;
        dev = strtok(line, ":");

        // Filter lo (virtual network device).
        if (QString::fromStdString(dev).trimmed() != "lo") {
            sscanf(buffer + strlen(dev) + 2, "%llu %*d %*d %*d %*d %*d %*d %*d %llu", &rBytes, &sBytes);

            receiveBytes += rBytes;
            sendBytes += sBytes;
        }

        free(line);
    }

    fclose(fp);
}

void Utils::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < reachTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

QString Utils::networkConversion(long bytes)
{
    if (bytes < 1024)
        return QString::number(bytes) + "B";

    if (bytes / 1024 < 1024)
        return QString::number(bytes / 1024, 'r', 1) + "K";

    if (bytes / 1024 / 1024 < 1024)
        return QString::number(bytes / 1024 / 1024, 'r', 1) + "M";
}
