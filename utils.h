#ifndef UTILS_H
#define UTILS_H

#include <QObject>

namespace Utils
{
    void getNetworkBandWidth(unsigned long long int &receiveBytes, unsigned long long int &sendBytes);
    void sleep(unsigned int msec);
}

#endif // UTILS_H
