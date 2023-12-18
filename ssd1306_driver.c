#include "ssd1306_lib.h"

#define MAX_DEVICES 1


/*******************************************************************
*                           FUNCTION PROTOTYPES
********************************************************************/

/* Module init & exit functions */
static int __init ssd1306_init(void);
static void __exit ssd1306_exit(void);

/* Probe & remove functions */
static int ssd1306_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int ssd1306_remove(struct i2c_client *client);

/* File operation functions */
static int ssd1306_open(struct inode *inode, struct file *filp);
static int ssd1306_release(struct inode *inode, struct file *filp);
static ssize_t ssd1306_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs);


/*******************************************************************
*                           GLOBAL VARIABLES
********************************************************************/

/* Global struct variable for the lcd */
struct ssd1306 my_ssd1306 = {
    .cursorPos = 0,
    .lineNum = 0,
    .fontSize = SSD1306_FONT_SIZE_5,
};

/* Device tree id table */
static const struct of_device_id ssd1306_of_table[] = {
    {.compatible = "gia,ssd1306"},
    { }
};
MODULE_DEVICE_TABLE(of, ssd1306_of_table);

/* Driver */
static struct i2c_driver ssd1306_driver = {
    .driver = {
        .name = "ssd1306-i2c",
        .of_match_table = of_match_ptr(ssd1306_of_table),
    },
    .probe = ssd1306_probe,
    .remove = ssd1306_remove,
};

/* File operations */
static struct file_operations fops = {
    .open  = ssd1306_open,
    .write = ssd1306_write,
    .release = ssd1306_release,
};

/* Character device variables */
dev_t devNum;
struct class *pClass;
struct cdev cdev;
struct device *pDevice;

/*******************************************************************
*                           FUNCTION DEFINITIONS
********************************************************************/


/*************************************************************************
 * @fn				- ssd1306_probe
 *
 * @brief			- get called if there is a matching with device tree
 *                  - create character device file & initialize the LCD
 *
 * @return			- 0 if success, error code if failed
 */
static int ssd1306_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret;

    pr_info("%s - started - %d\n", __func__, __LINE__);

    my_ssd1306.client = client;

    /* Check the device's address */
    if (client->addr != 0x3c)
    {
        pr_err("%s: Wrong address\n", __func__);
        return -1;
    }
    
    /* Initialize the device */
    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;
    ret = cdev_add(&cdev, devNum, 1);

    if (ret < 0)
    {
        pr_err("%s - cdev_add failed\n", __func__);
        return ret;
    }

    /* Create the device  */
    pDevice = device_create(pClass, NULL, devNum, NULL, "ssd1306_lcd");

    if (IS_ERR(pDevice))
    {
        pr_err("%s - Device create failed\n", __func__);
        /* Undo the previous step */
        cdev_del(&cdev);
        /* Return the error code */
        ret = PTR_ERR(pDevice);
        return ret;
    }

    /* Initialize the LCD */
    SSD1306_Init();

    SSD1306_PrintString("-----SSD1306 LCD----");

    pr_info("%s - completed - %d\n", __func__, __LINE__);

    return 0;
}

/*************************************************************************
 * @fn				- ssd1306_remove
 *
 * @brief			- get called when unloading the driver
 *                  - delete the device, cdev
 * 
 * @return			- 0 if success, error code if failed
 */
static int ssd1306_remove(struct i2c_client *client)
{
    pr_info("%s - called\n", __func__);

    device_destroy(pClass, devNum);
    cdev_del(&cdev);

    SSD1306_Clear();

    pr_info("%s - remove driver completely\n", __func__);
    return 0;
}

/*************************************************************************
 * @fn				- ssd1306_open
 *
 * @brief			- perform an open()
 *
 * @return			- 0 if success, error code if failed
 */
static int ssd1306_open(struct inode *inode, struct file *filp)
{
    //pr_info("%s - called\n", __func__);
    return 0;
}


/*************************************************************************
 * @fn				- ssd1306_release
 *
 * @brief			- perform a close() action
 *
 * @return			- 0 if success, error code if failed
 */
static int ssd1306_release(struct inode *inode, struct file *filp)
{
    //pr_info("%s - called\n", __func__);
    return 0;
}


/*************************************************************************
 * @fn				- ssd1306_write
 *
 * @brief			- perform a write() action
 *
 * @return			- 0 if success, error code if failed
 */
static ssize_t ssd1306_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
    int ret;

    /* Copy the buffer from user */
    ret = copy_from_user(my_ssd1306.recv_buf, user_buffer, count);
    if (ret)
    {
        pr_err("%s - copy_from_user failed\n", __func__);
        return -EFAULT;
    }

    /* If the string is "clear", clear the display */
    if ( !strncmp("clear", my_ssd1306.recv_buf, 5))
    {
        SSD1306_Clear();
    }
    else
    {
        SSD1306_PrintString(my_ssd1306.recv_buf);
    }

    /* Make the buffer empty */
    memset(my_ssd1306.recv_buf, 0, sizeof(my_ssd1306.recv_buf));
    
    return count;
}

/*************************************************************************
 * @fn				- ssd1306_init
 *
 * @brief			- allocate a device number, create a device class
 *                  - register the i2c driver with the core
 *
 * @return			- 0 if success, error code if failed
 */
static int __init ssd1306_init(void)
{
    int ret;

    pr_info("%s - started\n", __func__);

    /* Register a device number for an individual slave (can add more later) */
    ret = alloc_chrdev_region(&devNum, 0, MAX_DEVICES, "ssd1306_dev");
    if (ret < 0)
    {
        pr_err("%s - alloc_chrdev_region failed\n", __func__);
        return ret;
    }
    pr_info("%s - device number - major: %d - minor: %d\n", __func__, MAJOR(devNum), MINOR(devNum));

    /* Create a class for the device */
    pClass = class_create(THIS_MODULE, "ssd1306_class");
    if (IS_ERR(pClass))
    {
        pr_err("Class creation failed\n");
        /* Undo the previous step */
        unregister_chrdev_region(devNum, MAX_DEVICES);
        /* Return the error code */
        ret = PTR_ERR(pClass);
        return ret;
    }

    /* Register the i2c protocol driver */
    i2c_add_driver(&ssd1306_driver);

    pr_info("%s - finished\n", __func__);

    return 0;
}


/*************************************************************************
 * @fn				- ssd1306_exit
 *
 * @brief			- de-initialize from the top: delete i2c driver, class, device number
 *
 * @return			- 0 if success, error code if failed
 */
static void __exit ssd1306_exit(void)
{
    i2c_del_driver(&ssd1306_driver);
    class_destroy(pClass);
    unregister_chrdev_region(devNum, MAX_DEVICES);

    pr_info("%s - module unloaded\n", __func__);
}


/*******************************************************************
*                           MODULE REGISTRATIONS
********************************************************************/
module_init(ssd1306_init);
module_exit(ssd1306_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gia Nguyen");
MODULE_DESCRIPTION("SSD1306 Linux Device Driver");