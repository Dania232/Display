#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdint>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int read_stdin(std::vector<uint8_t> &buf);
int remap_display_bits(std::vector<uint8_t> &vec, int H, int W);
int write_serial(std::vector<uint8_t> &buf);

int main()
{

    const int W = 128;
    const int H = 64;
    std::vector<uint8_t> buffer(H * (W / 8));

    if (read_stdin(buffer) != 0)
    {
        std::cerr << "Not enough data!\n";
    }

    remap_display_bits(buffer, H, W);

    if (write_serial(buffer) != 0)
    {
        std::cerr << "tty open failed!\n";
    }

    return 0;
}

int read_stdin(std::vector<uint8_t> &buf)
{
    size_t total_read = 0;
    while (total_read < buf.size())
    {
        ssize_t n = read(0, buf.data() + total_read, buf.size() - total_read);
        if (n <= 0)
            break; // EOF or error
        total_read += n;
    }

    if (total_read != buf.size())
    {
        // std::cerr << "Not enough data!\n";
        return 1;
    }

    return 0;
}

int remap_display_bits(std::vector<uint8_t> &vec, int H, int W)
{
    std::vector<uint8_t> buffer(H * (W / 8));

    for (int col_ind = 0; col_ind < W; col_ind++)
    {
        for (int row_ind = 0; row_ind < H; row_ind++)
        {
            bool val;
            val = vec[col_ind / 8 + row_ind * W / 8] & (1 << (col_ind % 8));
            buffer[row_ind / 8 + col_ind * H / 8] |= (val << (row_ind % 8));
        }
    }
    vec = buffer;
    return 0;
}

int write_serial(std::vector<uint8_t> &buf)
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