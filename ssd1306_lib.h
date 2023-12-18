#ifndef __SSD1306_LIB_HH__
#define __SSD1306_LIB_HH__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h> 
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/delay.h>

#define SSD1306_FONT_SIZE_5     5
#define SSD1306_WRITE_COMMAND   0
#define SSD1306_WRITE_DATA      1
#define SSD1306_MAX_LINE        7           // Each page has a size of 128x8
#define SSD1306_MAX_SEGMENT     127
#define SSD1306_MAX_SIZE        (128 * 8)


/* Struct for the lcd */
struct ssd1306 
{
    struct i2c_client *client;
    char recv_buf[SSD1306_MAX_SIZE];
    uint8_t lineNum;
    uint8_t cursorPos;
    uint8_t fontSize; 
};


/*******************************************************************
*                           FUNCTION PROTOTYPES
********************************************************************/
int  SSD1306_Init(void);
void SSD1306_Write(uint8_t is_cmd, uint8_t data);
void SSD1306_PrintChar(uint8_t ch);
void SSD1306_PrintString(char *str);
void SSD1306_SetCursor(uint8_t lineNumber, uint8_t cursorPos);
void SSD1306_Fill(uint8_t data);
void SSD1306_Clear(void);
void SSD1306_GoToNextLine(void);

#endif