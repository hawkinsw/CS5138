#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#ifdef UNIX
#include <unistd.h>
#else
#include <io.h>
#endif

#include <errno.h>

extern int errno;

/* Contents of file.bin:
00000000  18 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000010  00 00 00 00 00 00 00 00  12 34 00 00 00 00 00 00  |.........4......|
00000020  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*/

#define TARGET_NUMBER 0x3412

int main()
{
    uint32_t number = 0;

    int fd = open("./file.bin", O_RDONLY);

    if (fd < 0) {
        printf("Error opening file: %s", strerror(errno));
        return 1;
    }

    // Read the first four bytes of the binary file from the disk into
    // the memory where _number_ is stored. Because the number is in
    // little endian on disk *and* the platform (x86) is little endian,
    // we can interpret this without translation. If that were *not* the
    // case, we could use ntohl (or something like it) to swap the endianness.
    int result = read(fd, &number, sizeof(uint32_t));
    if (result != sizeof(uint32_t)) {
        printf("Did not read the entire index: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    // The four bytes that we read from the beginning of the file tell
    // us the location (in the file!) of the integer that we want to read.
    // So, we will *seek* to that location in the file.
    if (number != lseek(fd, number, SEEK_SET)) {
        printf("Did not seek to the proper place in the file!\n");
        close(fd);
        return 1;
    }

    // Now that we are there, read the next four bytes from the file
    // and ...
    result = read(fd, &number, sizeof(uint32_t));
    if (result != sizeof(uint32_t)) {
        printf("Did not read the target value: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    // ... interpret them as an integer! (See caveat above about endianness).
    if (number == TARGET_NUMBER) {
        printf("Success!\n");
    } else {
        printf("Oops: Did not read the proper number!\n");
    }

    close(fd);
    return 0;
}
