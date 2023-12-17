/**************************************************************
* Class:  CSC-415-01 Spring 2023
* Name: Viajyraj Tolnoorkar
* Student ID: 922110069
* GitHub ID: Vijayt2001
* Project: Assignment 6 – Device Driver
*
* File: Tolnoorkar_Vijayraj_HW6_main.c
*
* Description: This file consists the interface for the driver.
**************************************************************/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEVICE "/home/student/Downloads/csc415-device-driver-Vijayt2001-main/Module/hello.txt" //File path
#define IOCTL_SET_MODE _IOW('a', 'a', int*)

int main() {
    char data[100];

  //open
    int fd = open(DEVICE, O_RDWR);
    if(fd == -1) {
        perror("Failed to open device");
        return 1;
    }

    //Encyrption
    int mode = 1;  // Encryption mode
    ioctl(fd, IOCTL_SET_MODE, &mode);

    printf("Writing to the device...\n");
    ssize_t res = write(fd, "", strlen(""));
    if (res == -1) {
        perror("Failed to write to the device");
        return 1;
    }

    mode = 0;  // Decryption mode
    ioctl(fd, IOCTL_SET_MODE, &mode);
    printf("Reading from the device...\n");
    res = read(fd, data, 100);
    if (res == -1) {
        perror("Failed to read from the device");
        return 1;
    }

  //Clsoing device
    printf("Data: %s\n", data);
    close(fd);
    return 0;
}
