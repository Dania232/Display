#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>


int read_from_app(std::vector<uint8_t> &buf);
void write_to_app(std::vector<uint8_t> &buf);
