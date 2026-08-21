#include <textutil.h>
char* showBits(char b) {
    static char line[9];
    for (int i = 7; i >= 0; i--) {
        line[7 - i] = ((b & (1 << i)) != 0) + '0'; // works because ascii
    }
    line[8] = 0x00;
    return line;
}