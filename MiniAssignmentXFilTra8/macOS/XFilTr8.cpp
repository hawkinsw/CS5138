#include <cstdint>
#include <iostream>
#include <fcntl.h>
#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>

extern int errno;

int main() {
  char read_buffer[50]{};
  auto read_buffer_size{sizeof(read_buffer) / sizeof(char) - 1};
  uint32_t bytes_read{0};
  int fd{-1};

  if (0 > (fd = open("secret.txt", O_RDONLY))) {
    std::cout << strerror(errno) << "\n";
    printf("But, I am going to be able to keep going!!\n");
    return -1;
  }

  if (0 > (bytes_read = read(fd, read_buffer, read_buffer_size))) {
    std::cout << strerror(errno) << "\n";
    close(fd);
    return -1;
  }

  std::cout << "Your secret is safe with me: '" << read_buffer << "'.\n";

/*
  for (int i{0}; i<bytes_read; i++) {
    std::cout << std::hex << (uint32_t)read_buffer[i] << "-";
  }
  std::cout << "\n";
*/
  close(fd);

  return 0;
}
