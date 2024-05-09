#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv) {
    int fd = 0;
    if (argc == 2) {
        char *filename = argv[1];
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            exit(1);
        }
    } else {
        exit(1);
    }
    int line_count = 0;
    do {
        unsigned char buffer[16];
        ssize_t res = read(fd, buffer, 16);
        if (res == -1) {
            exit(1);
        } else if (res > 0) {
            printf("%08x: ", line_count);
            while (res < 16) {
                ssize_t new_res = read(fd, buffer + res, (size_t) (16 - res));
                if (new_res > 0) {
                    res += new_res;
                } else {
                    break;
                }
            }
            for (int i = 0; i < 16; i++) {
                if (i < res) {
                    printf("%02x", buffer[i]);
                } else {
                    printf("  ");
                }
                if (i + 1 < res) {
                    printf("%02x ", buffer[i + 1]);
                    i++;
                } else {
                    printf("   ");
                    i++;
                }
            }
            printf(" ");
            for (int i = 0; i < res; ++i) {
                printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
            }
            printf("\n");
        }
        line_count += 16;
    } while (res > 0);
    res = close(fd);
    if (res == -1) {
        exit(1);
    }
    return 0;
}
