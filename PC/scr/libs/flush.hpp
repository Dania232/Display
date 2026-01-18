#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>


int write_to_display(std::vector<uint8_t> &buf)
{
    const char *port = "/dev/ttyUSB0";
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0)
        return 1;

    termios t{};
    tcgetattr(fd, &t);

    cfsetispeed(&t, B9600);
    cfsetospeed(&t, B9600);

    t.c_cflag |= (CLOCAL | CREAD);
    t.c_cflag &= ~PARENB;
    t.c_cflag &= ~CSTOPB;
    t.c_cflag &= ~CSIZE;
    t.c_cflag &= ~HUPCL;
    t.c_cflag |= CS8;

    t.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    t.c_iflag &= ~(IXON | IXOFF | IXANY);
    t.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &t);

    int flags;
    ioctl(fd, TIOCMGET, &flags);
    flags |= TIOCM_DTR | TIOCM_RTS;
    ioctl(fd, TIOCMSET, &flags);

    write(fd, buf.data(), buf.size());
    tcdrain(fd); // wait until transmitted

    close(fd);
    return 0;
}

int read_fr_display(std::vector<uint8_t> &buf){
    const char *port = "/dev/ttyUSB0";
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0)
        return 1;

    termios t{};
    tcgetattr(fd, &t);

    cfsetispeed(&t, B9600);
    cfsetospeed(&t, B9600);

    t.c_cflag |= (CLOCAL | CREAD);
    t.c_cflag &= ~PARENB;
    t.c_cflag &= ~CSTOPB;
    t.c_cflag &= ~CSIZE;
    t.c_cflag &= ~HUPCL;
    t.c_cflag |= CS8;

    t.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    t.c_iflag &= ~(IXON | IXOFF | IXANY);
    t.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &t);

    int flags;
    ioctl(fd, TIOCMGET, &flags);
    flags |= TIOCM_DTR | TIOCM_RTS;
    ioctl(fd, TIOCMSET, &flags);

    read(fd, buf.data(), buf.size());
    tcdrain(fd); // wait until transmitted

    close(fd);
    return 0;
}