#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv) {
    int d = 0;
    if (argc == 2) {
        char *nm = argv[1];
        d = open(nm, O_RDONLY);
        if (d == -1) {
            exit(1);
        }
    } else {
        exit(1);
    }
    ssize_t r;
    int l = 0;
    do {
        unsigned char b[16];
        r = read(d, b, 16);
        if (r == -1) {
            exit(1);
        } else if (r > 0) {
            printf("%08x: ", l);
            while (r < 16) {
                ssize_t nr = read(d, b + r, (size_t) (16 - r));
                if (nr > 0) {
                    r += nr;
                } else {
                    break;
                }
            }
            for (int i = 0; i < 16; i++) {
                if (i < r) {
                    printf("%02x", b[i]);
                } else {
                    printf("  ");
                }
                if (i + 1 < r) {
                    printf("%02x ", b[i + 1]);
                    i++;
                } else {
                    printf("   ");
                    i++;
                }
            }
            printf(" ");
            for (int i = 0; i < r; ++i) {
                printf("%c", isprint(b[i]) ? b[i] : '.');
            }
            printf("\n");
        }
        l += 16;
    } while (r > 0);
    r = close(d);
    if (r == -1) {
        exit(1);
    }
    return 0;
}
