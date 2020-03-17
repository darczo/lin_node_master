#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

int main(int argc, char *argv[]) {
    int file, count;
    char *str = "UART test";

    if ((file = open("/dev/ttyS4", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Failed to open the device.\n");
        return -1;
    }

    struct termios options;
    tcgetattr(file, &options);
    options.c_cflag = B19200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;
    tcflush(file, TCIFLUSH);
    tcsetattr(file, TCSANOW, &options);

// send the string plus the null character
    if ((count = write(file, str, strlen(str) + 1)) < 0) {
        perror("UART: Failed to write to the output.\n");
        return -1;
    }

    close(file);
    printf("Finished sending the message, exiting.\n");

    return 0;
}