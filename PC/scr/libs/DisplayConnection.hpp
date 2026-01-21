#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "../../../Shared/ITransporLayer.hpp"

class DisplayConnection : public ITransporLayer
{

public:
    enum Eror
    {
        TIMEOUT,
    };

    DisplayConnection(std::string port = "/dev/ttyUSB0")
    {
        fd = open(port.c_str(), O_RDWR | O_NOCTTY);
        if (fd < 0)
            throw std::runtime_error("Failed to open serial port");

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

        t.c_cc[VMIN] = 0;
        t.c_cc[VTIME] = 10;

        tcsetattr(fd, TCSANOW, &t);

        int flags;
        ioctl(fd, TIOCMGET, &flags);
        flags |= TIOCM_DTR | TIOCM_RTS;
        ioctl(fd, TIOCMSET, &flags);

        
    }

    int send_byte(uint8_t byte) override
    {
        ssize_t written = write(fd, &byte, 1);
        if (written != 1)
            throw std::runtime_error("Failed to DisplayConnection::send_byte");
        tcdrain(fd); // wait until transmitted
        return 0;
    }

    int recive_byte(uint8_t &byte) override
    {
        ssize_t read_bytes = read(fd, &byte, 1);
        if (read_bytes == 0)
            throw std::runtime_error("DisplayConnection::recive_byte TIMEOUT");
        if (read_bytes != 1)
            throw std::runtime_error("Failed to DisplayConnection::recive_byte");
        return 0;
    }

    int sendBuffer(const std::vector<uint8_t> &buf)
    {
        ssize_t written = write(fd, buf.data(), buf.size());
        if (written != buf.size())
            throw std::runtime_error("Failed to DisplayConnection::sendBuffer");
        tcdrain(fd); // wait until transmitted
        return 0;
    }
    int receiveBuffer(std::vector<uint8_t> &buf)
    {
        ssize_t read_bytes = read(fd, buf.data(), buf.size());
        if (read_bytes == 0)
            throw std::runtime_error("DisplayConnection::receiveBuffer TIMEOUT");
        if (read_bytes != buf.size())
            throw std::runtime_error("Failed to DisplayConnection::receiveBuffer");
        return 0;
    }

    ~DisplayConnection()
    {
        close(fd);
    }

private:
    int fd;
};