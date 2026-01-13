#include "io.hpp"

int read_from_app(std::vector<uint8_t> &buf)
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

void write_to_app(std::vector<uint8_t> &buf){
    write(1, buf.data(), buf.size());
}

