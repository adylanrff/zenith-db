#include "socket.h"
#include <unistd.h>

Socket::Socket(int fd) : _fd(fd) {}

Socket::~Socket() {
  if (_fd != -1) {
    close(_fd);
  }
}

Socket::Socket(Socket &&other) noexcept : _fd(other._fd) {
  other._fd = -1;
}; // move

Socket &Socket::operator=(Socket &&other) {
  if (this != &other) {
    if (_fd != -1) {
      close(_fd);
    }

    _fd = other._fd;
    other._fd = -1;
  }

  return *this;
}
