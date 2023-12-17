/**************************************************************
* Class:  CSC-415-01 Spring 2023
* Name: Viajyraj Tolnoorkar
* Student ID: 922110069
* GitHub ID: Vijayt2001
* Project: Assignment 6 – Device Driver
*
* File: secure_notes.c
*
* Description: This file consists character device encrytpion and decryptions. 
    Also includes driver supports functions like
     reading, writing, and ioctl commands 
**************************************************************/


#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "/home/student/Downloads/csc415-device-driver-Vijayt2001-main/Module/hello.txt" //Device name
#define MAX_SIZE 1024 //Size for the buffer
#define IOCTL_SET_MODE _IOW('a', 'a', int*) 

static int major_num; //number for the device
static char data[MAX_SIZE]; //buffer data
static int used = 0;   //Checking if the data was used
static int SHIFT = 3; // Default to encryption mode


//Decrypting and transferrign data

static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset) {
    int i;
    for(i = 0; i < len && i < MAX_SIZE; i++) {
        char ch = data[i] - SHIFT;
        if(copy_to_user(buffer + i, &ch, 1)) {
            return -EFAULT;
        }
    }
    used = 0;
    return i;
}

static ssize_t device_write(struct file *flip, const char *buffer, size_t len, loff_t *offset) {
    int i;
    for(i = 0; i < len && i < MAX_SIZE; i++) {
        if(get_user(data[i], buffer + i)) {
            return -EFAULT;
        }
        data[i] += SHIFT;
    }
    used = 1;
    return i;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case IOCTL_SET_MODE:
            if(arg == 0) {
                SHIFT = -3;  // Decryption mode
            } else {
                SHIFT = 3;   // Encryption mode
            }
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "secure_notes device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "secure_notes device closed\n");
    return 0;
}

static struct file_operations file_ops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
};

static int __init secure_notes_init(void) {
    major_num = register_chrdev(0, DEVICE_NAME, &file_ops);
    if (major_num < 0) {
        printk(KERN_ALERT "Could not register device: %d\n", major_num);
        return major_num;
    } else {
        printk(KERN_INFO "secure_notes module loaded with device major number %d\n", major_num);
        return 0;
    }
}


//Exit function
static void __exit secure_notes_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Goodbye, secure_notes unloaded\n");
}

//Meta data

module_init(secure_notes_init);
module_exit(secure_notes_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Secure Notes Device Driver");

