#define SCULL_MAJOR 0
#define SCULL_MINOR 0
#define SCULL_NR_DEVS 4

struct file_operations scull_file_ops = {
    .owner = THIS_MODULE,
    .open = scull_open,
    .release = scull_close,
    .read = scull_read,
    .write = scull_write
}
