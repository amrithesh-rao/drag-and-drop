#define  _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#define RECOGNIZED(s) { printf(s); fflush(stdout); recognized++; }

static const size_t        mousedev_seq_len    = 6;
static const unsigned char mousedev_imps_seq[] =
                { 0xf3, 200, 0xf3, 100, 0xf3, 80 };

static int bytetoint(const unsigned char c) {
    return ( (c < 128? c : c-256) ); }

int main(int argc, char *argv[]) {
    char          *devpath = (argc>1?argv[1]:"/dev/input/mice");
    int           msglevel = (argc>2?atoi(argv[2]):3);
    int           devfd = (-1);
    unsigned char buffer[4];
    ssize_t       len = (-1);
    int           nactions=0, wasleft=0, wasmiddle=0, wasright=0;

    /* Open the mouse. */
    fflush(NULL);
    do { devfd = open(devpath, O_RDWR | O_NOCTTY);
       } while (devfd == -1 && errno == EINTR);
    if (devfd == -1) {
        printf("Cannot open %s: %s.\n", devpath, strerror(errno));
        goto end_of_job; }

    /* Switch the mouse to ImPS/2 protocol. */
    if (write(devfd, mousedev_imps_seq, mousedev_seq_len)
    != (ssize_t)mousedev_seq_len) {
        printf("Cannot switch to ImPS/2 protocol.\n");
        goto end_of_job; }

    if (read(devfd, buffer, sizeof buffer) != 1 || buffer[0] != 0xFA) {
        printf("Failed to switch to ImPS/2 protocol.\n");
        goto end_of_job; }

    printf("Mouse device %s opened successfully.\n", devpath);
    printf("Press CTRL+C to exit.\n" /*, (int)getpid()*/ );

    /* IntelliMouse protocol uses four byte reports:
     *      Bit   7     6     5     4     3     2     1     0
     * --------+-----+-----+-----+-----+-----+-----+-----+-----
     *  Byte 0 |  0     0   Neg-Y Neg-X   1    Mid  Right Left
     *  Byte 1 |  X     X     X     X     X     X     X     X
     *  Byte 2 |  Y     Y     Y     Y     Y     Y     Y     Y
     *  Byte 3 |  W     W     W     W     W     W     W     W
     *.
     * XXXXXXXX, YYYYYYYY, and WWWWWWWW are 8-bit two's complement values
     * indicating changes in x-coordinate, y-coordinate, and scroll wheel.
     * That is, 0 = no change, 1..127 = positive change +1 to +127,
     * and 129..255 = negative change -127 to -1.
     *
     * Left, Right, and Mid are the three button states, 1 if being depressed.
     * Neg-X and Neg-Y are set if XXXXXXXX and YYYYYYYY are negative,
     * respectively.  */

    while (1) {
        int x, y, wheel, left, middle, right;
        int recognized = 0;
        nactions++;
        fflush(stdout);

        len = read(devfd, buffer, 4);
        if (len == -1) {
          if (errno == EINTR) continue;
          printf("%s.\n", strerror(errno));
          break; }
        /* We are only interested in four-byte reports,
         * that have bit 3 set in the first byte. */
        if (len != 4 || !(buffer[0] & 0x08)) {
          printf("Warning: Ignored a %d-byte report.\n", (int)len);
          continue; }

        /* --- Unpack. --- */
        left = buffer[0] & 1;
        middle = buffer[0] & 4;
        right = buffer[0] & 2;
        x = bytetoint(buffer[1]);
        y = bytetoint(buffer[2]);
        wheel = bytetoint(buffer[3]);
        if ( msglevel >= 1 ) {
          printf("(%d) buffer=%02x,%02x,%02x,%02x"
                 ", xy=%d,%d, lmrw=%d,%d,%d,%d:  ",
                 nactions, buffer[0],buffer[1],buffer[2],buffer[3],
                 x,y, left,middle,right,wheel); fflush(stdout); }

        /* --- Describe: --- */
        if (x) { RECOGNIZED(" x"); printf("%+d", x); }
        if (y) { RECOGNIZED(" y"); printf("%+d", y); }
        if (wheel) { RECOGNIZED(" w"); printf("%+d", wheel); }

        if (left && !wasleft) { RECOGNIZED(" LeftDown"); }
        else if (left && wasleft) { RECOGNIZED(" Left"); }
             else if (!left && wasleft) { RECOGNIZED(" LeftUp"); }

        if (middle && !wasmiddle) { RECOGNIZED(" MiddleDown"); }
        else if (middle && wasmiddle) { RECOGNIZED(" Middle"); }
             else if (!middle && wasmiddle) { RECOGNIZED(" MiddleUp"); }

        if (right && !wasright) { RECOGNIZED(" RightDown"); }
        else if (right && wasright) { RECOGNIZED(" Right"); }
             else if (!right && wasright) { RECOGNIZED(" RightUp"); }

        printf(" (recognized %d)\n",recognized);
        wasleft=left;  wasmiddle=middle;  wasright=right;
        } /* --- end-of-while(1) --- */

    /* Done. */
    end_of_job: if ( devfd!=(-1) ) close(devfd);
    fflush(NULL);
    return EXIT_SUCCESS;
    } /* --- end-of-main() --- */