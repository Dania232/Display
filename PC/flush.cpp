#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdint>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int main()
{
    const char* port = "/dev/ttyUSB0";
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0) return 1;



    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    // read all bytes from stdin
    size_t total_read = 0;
    while (total_read < buffer.size())
    {
        ssize_t n = read(0, buffer.data() + total_read, buffer.size() - total_read);
        if (n <= 0)
            break; // EOF or error
        total_read += n;
    }

    if (total_read != buffer.size())
    {
        std::cerr << "Not enough data!\n";
        return 1;
    }

    



    // termios tty{};
    // cfsetospeed(&tty, B9600);
    // cfsetispeed(&tty, B9600);
    // tty.c_cflag = CS8 | CLOCAL | CREAD;
    // tty.c_lflag = 0;
    // tty.c_iflag = 0;
    // tty.c_oflag = 0;
    // tcsetattr(fd, TCSANOW, &tty);

    // int status;
    // ioctl(fd, TIOCMGET, &status);
    // status |= TIOCM_DTR;
    // ioctl(fd, TIOCMSET, &status);

    

    write(fd, buffer.data(), buffer.size());
    close(fd);


    return 0;
}
