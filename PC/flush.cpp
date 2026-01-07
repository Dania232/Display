#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdint>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int main()
{
    const char *port = "/dev/ttyUSB0";
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0)
        return 1;

    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));
    std::vector<uint8_t> buffer_out(H * (W / 8));

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

    for (int col_ind = 0; col_ind < W; col_ind++)
    {
        for (int row_ind = 0; row_ind < H; row_ind++)
        {
            bool val;
            val = buffer[col_ind / 8 + row_ind*W/8] & (1 << (col_ind % 8));
            std::cout << val;
            buffer_out[row_ind / 8 + col_ind*H/8] |= (val << (row_ind % 8));
        }
    }

    // for (int col = 0; col < W; col++)
    // {
    //     for (int row = 0; row < H; row++)
    //     {
    //         // extract pixel from row-major input
    //         bool val = (buffer[row * (W / 8) + col / 8] >> (col % 8)) & 1;

    //         // place pixel in correct byte of column-major output
    //         buffer_out[col * (H / 8) + row / 8] |= (val << (row % 8));
    //     }
    // }

    // for (int col = 0; col < W; col++)
    // {
    //     for (int page = 0; page < H / 8; page++)
    //     {
    //         uint8_t byte = 0;
    //         for (int bit = 0; bit < 8; bit++)
    //         {
    //             int row = page * 8 + bit;
    //             bool val = (buffer[row * (W / 8) + col / 8] >> (col % 8)) & 1;
    //             byte |= (val << bit);
    //         }
    //         buffer_out[col * (H / 8) + page] = byte; // assign full byte
    //     }
    // }

    termios t{};
    tcgetattr(fd, &t);

    cfsetispeed(&t, B9600);
    cfsetospeed(&t, B9600);

    t.c_cflag |= (CLOCAL | CREAD);
    t.c_cflag &= ~PARENB;
    t.c_cflag &= ~CSTOPB;
    t.c_cflag &= ~CSIZE;
    t.c_cflag |= CS8;

    t.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    t.c_iflag &= ~(IXON | IXOFF | IXANY);
    t.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &t);

    int flags;
    ioctl(fd, TIOCMGET, &flags);
    flags |= TIOCM_DTR | TIOCM_RTS;
    ioctl(fd, TIOCMSET, &flags);

    write(fd, buffer_out.data(), buffer.size());
    tcdrain(fd); // wait until transmitted

    close(fd);

    return 0;
}
