#include "utils.h"

namespace Utils
{
    void getNetworkBandWidth(unsigned long long int &receiveBytes, unsigned long long int &sendBytes)
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

}
