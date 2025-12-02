#pragma once

class Socket {
private:
  int _fd;

public:
  explicit Socket(int fd);

  ~Socket(); // destructor

  // delete for copying
  Socket(const Socket &) = delete;                 // copy
  Socket &operator=(const Socket &other) = delete; // copy assignment

  // Move
  Socket(Socket &&other) noexcept;   // move
  Socket &operator=(Socket &&other); // move assignment
};
