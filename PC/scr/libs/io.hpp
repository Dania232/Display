#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int read_from_app(std::vector<uint8_t> &buf);
void write_to_app(std::vector<uint8_t> &buf);
int write_serial(std::vector<uint8_t> &buf);