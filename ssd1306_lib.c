#include "ssd1306_lib.h"

extern struct ssd1306 my_ssd1306;

/* ASCII letter (a letter consumes 5 bytes)*/
const uint8_t ASCII_font[][SSD1306_FONT_SIZE_5] =
{
    {0x00, 0x00, 0x00, 0x00, 0x00},   // space
    {0x00, 0x00, 0x2f, 0x00, 0x00},   // !
    {0x00, 0x07, 0x00, 0x07, 0x00},   // "
    {0x14, 0x7f, 0x14, 0x7f, 0x14},   // #
    {0x24, 0x2a, 0x7f, 0x2a, 0x12},   // $
    {0x23, 0x13, 0x08, 0x64, 0x62},   // %
    {0x36, 0x49, 0x55, 0x22, 0x50},   // &
    {0x00, 0x05, 0x03, 0x00, 0x00},   // '
    {0x00, 0x1c, 0x22, 0x41, 0x00},   // (
    {0x00, 0x41, 0x22, 0x1c, 0x00},   // )
    {0x14, 0x08, 0x3E, 0x08, 0x14},   // *
    {0x08, 0x08, 0x3E, 0x08, 0x08},   // +
    {0x00, 0x00, 0xA0, 0x60, 0x00},   // ,
    {0x08, 0x08, 0x08, 0x08, 0x08},   // -
    {0x00, 0x60, 0x60, 0x00, 0x00},   // .
    {0x20, 0x10, 0x08, 0x04, 0x02},   // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E},   // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00},   // 1
    {0x42, 0x61, 0x51, 0x49, 0x46},   // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31},   // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10},   // 4
    {0x27, 0x45, 0x45, 0x45, 0x39},   // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30},   // 6
    {0x01, 0x71, 0x09, 0x05, 0x03},   // 7
    {0x36, 0x49, 0x49, 0x49, 0x36},   // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E},   // 9
    {0x00, 0x36, 0x36, 0x00, 0x00},   // :
    {0x00, 0x56, 0x36, 0x00, 0x00},   // ;
    {0x08, 0x14, 0x22, 0x41, 0x00},   // <
    {0x14, 0x14, 0x14, 0x14, 0x14},   // =
    {0x00, 0x41, 0x22, 0x14, 0x08},   // >
    {0x02, 0x01, 0x51, 0x09, 0x06},   // ?
    {0x32, 0x49, 0x59, 0x51, 0x3E},   // @
    {0x7C, 0x12, 0x11, 0x12, 0x7C},   // A
    {0x7F, 0x49, 0x49, 0x49, 0x36},   // B
    {0x3E, 0x41, 0x41, 0x41, 0x22},   // C
    {0x7F, 0x41, 0x41, 0x22, 0x1C},   // D
    {0x7F, 0x49, 0x49, 0x49, 0x41},   // E
    {0x7F, 0x09, 0x09, 0x09, 0x01},   // F
    {0x3E, 0x41, 0x49, 0x49, 0x7A},   // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F},   // H
    {0x00, 0x41, 0x7F, 0x41, 0x00},   // I
    {0x20, 0x40, 0x41, 0x3F, 0x01},   // J
    {0x7F, 0x08, 0x14, 0x22, 0x41},   // K
    {0x7F, 0x40, 0x40, 0x40, 0x40},   // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F},   // M
    {0x7F, 0x04, 0x08, 0x10, 0x7F},   // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E},   // O
    {0x7F, 0x09, 0x09, 0x09, 0x06},   // P
    {0x3E, 0x41, 0x51, 0x21, 0x5E},   // Q
    {0x7F, 0x09, 0x19, 0x29, 0x46},   // R
    {0x46, 0x49, 0x49, 0x49, 0x31},   // S
    {0x01, 0x01, 0x7F, 0x01, 0x01},   // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F},   // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F},   // V
    {0x3F, 0x40, 0x38, 0x40, 0x3F},   // W
    {0x63, 0x14, 0x08, 0x14, 0x63},   // X
    {0x07, 0x08, 0x70, 0x08, 0x07},   // Y
    {0x61, 0x51, 0x49, 0x45, 0x43},   // Z
    {0x00, 0x7F, 0x41, 0x41, 0x00},   // [
    {0x55, 0xAA, 0x55, 0xAA, 0x55},   // Backslash (Checker pattern)
    {0x00, 0x41, 0x41, 0x7F, 0x00},   // ]
    {0x04, 0x02, 0x01, 0x02, 0x04},   // ^
    {0x40, 0x40, 0x40, 0x40, 0x40},   // _
    {0x00, 0x03, 0x05, 0x00, 0x00},   // `
    {0x20, 0x54, 0x54, 0x54, 0x78},   // a
    {0x7F, 0x48, 0x44, 0x44, 0x38},   // b
    {0x38, 0x44, 0x44, 0x44, 0x20},   // c
    {0x38, 0x44, 0x44, 0x48, 0x7F},   // d
    {0x38, 0x54, 0x54, 0x54, 0x18},   // e
    {0x08, 0x7E, 0x09, 0x01, 0x02},   // f
    {0x18, 0xA4, 0xA4, 0xA4, 0x7C},   // g
    {0x7F, 0x08, 0x04, 0x04, 0x78},   // h
    {0x00, 0x44, 0x7D, 0x40, 0x00},   // i
    {0x40, 0x80, 0x84, 0x7D, 0x00},   // j
    {0x7F, 0x10, 0x28, 0x44, 0x00},   // k
    {0x00, 0x41, 0x7F, 0x40, 0x00},   // l
    {0x7C, 0x04, 0x18, 0x04, 0x78},   // m
    {0x7C, 0x08, 0x04, 0x04, 0x78},   // n
    {0x38, 0x44, 0x44, 0x44, 0x38},   // o
    {0xFC, 0x24, 0x24, 0x24, 0x18},   // p
    {0x18, 0x24, 0x24, 0x18, 0xFC},   // q
    {0x7C, 0x08, 0x04, 0x04, 0x08},   // r
    {0x48, 0x54, 0x54, 0x54, 0x20},   // s
    {0x04, 0x3F, 0x44, 0x40, 0x20},   // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C},   // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C},   // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C},   // w
    {0x44, 0x28, 0x10, 0x28, 0x44},   // x
    {0x1C, 0xA0, 0xA0, 0xA0, 0x7C},   // y
    {0x44, 0x64, 0x54, 0x4C, 0x44},   // z
    {0x00, 0x10, 0x7C, 0x82, 0x00},   // {
    {0x00, 0x00, 0xFF, 0x00, 0x00},   // |
    {0x00, 0x82, 0x7C, 0x10, 0x00},   // }
    {0x00, 0x06, 0x09, 0x09, 0x06}    // ~ (Degrees)
};



/*************************************************************************
 * @fn				- SSD1306_Write
 *
 * @brief			- Send 1 byte of data to the LCD
 * 
 * @param[in]		- cmdOrData: pass SSD1306_WRITE_COMMAND if want to send a command
 *                               pass SSD1306_WRITE_DATA if want to send data
 *
 * @return			- none
 */
void SSD1306_Write(uint8_t cmdOrData, uint8_t data)
{
    /*  
        Always send a package of 2 bytes to the lcd
        1st byte: control byte, can be command mode or data mode
        2nd byte: data byte, can be a command or data

        The 6th bit is 0 in control byte -> next byte is a command
        The 6th bit is 1 in control byte -> next byte is data
        0b01000000 = 0x40
    */
    int ret;
    uint8_t package[2];

    if (cmdOrData == SSD1306_WRITE_COMMAND)
    {
        /* Send a command */
        package[0] = 0x00;
    }
    else if (cmdOrData == SSD1306_WRITE_DATA)
    {
        /* Send data */
        package[0] = 0x40;
    }

    package[1] = data;

    ret = i2c_master_send(my_ssd1306.client, package, 2);
    if (ret < 0)
    {
        pr_err("i2c_master_send error\n");
        return;
    }
       
}


/*************************************************************************
 * @fn				- SSD1306_SetCursor
 *
 * @brief			- Set the cursor to any positions (in range) on the display
 * 
 * @param[in]		- lineNumber: the line number will be set
 *                    cursorPos: the cursor position will be set
 *
 * @return			- none
 */
void SSD1306_SetCursor(uint8_t lineNumber, uint8_t cursorPos)
{
    /* Only handle the function if the parameters are in range */
    if ( (lineNumber <= SSD1306_MAX_LINE) && (cursorPos <= SSD1306_MAX_SEGMENT) )
    {
        /* Save the new cursor's position */
        my_ssd1306.lineNum = lineNumber;
        my_ssd1306.cursorPos = cursorPos;

        /* Set column */
        SSD1306_Write(SSD1306_WRITE_COMMAND, 0x21);
        SSD1306_Write(SSD1306_WRITE_COMMAND, cursorPos);
        SSD1306_Write(SSD1306_WRITE_COMMAND, SSD1306_MAX_SEGMENT);

        /* Set line (page) */
        SSD1306_Write(SSD1306_WRITE_COMMAND, 0x22);
        SSD1306_Write(SSD1306_WRITE_COMMAND, lineNumber);
        SSD1306_Write(SSD1306_WRITE_COMMAND, SSD1306_MAX_LINE);      
    }
}


/*************************************************************************
 * @fn				- SSD1306_Fill
 *
 * @brief			- Fill a byte to all the pixels of the display
 * 
 * @param[in]		- data: the byte
 *
 * @return			- none
 */
void SSD1306_Fill(uint8_t data)
{
    int total = 128 * 8;
    int i;
    for (i = 0; i < total; i++)
    {
        SSD1306_Write(SSD1306_WRITE_DATA, data);
    }
}


/*************************************************************************
 * @fn				- SSD1306_GoToNextLine
 *
 * @brief			- Go to the next line on the display
 * 
 * @param[in]		- none
 *
 * @return			- none
 */
void SSD1306_GoToNextLine(void)
{
    /* my_ssd1306.cursorPos = 0; */
    my_ssd1306.lineNum++;

    if (my_ssd1306.lineNum == SSD1306_MAX_LINE)
        my_ssd1306.lineNum = 0;

    SSD1306_SetCursor(my_ssd1306.lineNum, 0);
}


/*************************************************************************
 * @fn				- SSD1306_PrintChar
 *
 * @brief			- Send 1 character to the LCD
 * 
 * @param[in]		- ch: the character
 *
 * @return			- none
 */
void SSD1306_PrintChar(uint8_t ch)
{
    uint8_t byte_send;
    uint8_t i;

    /* 
    *  If the new char has a bigger size than the remaining segment
    *  Or the char is '\n'
    *  Then move to the new line
    */
    if ( ((my_ssd1306.cursorPos + my_ssd1306.fontSize) > SSD1306_MAX_SEGMENT) \
         || (ch == '\n') )
    {
        SSD1306_GoToNextLine();
    }

    if (ch != '\n')
    {
        /* 
        *  In ASCII table, [space] starts at 0x20 
        *  In the 2D array, [space] start at 0
        *  So 'ch' should be minus to 0x20
        */
        ch -= 0x20;
        
        /* Each character takes 5 bytes */
        for (i = 0; i < my_ssd1306.fontSize; i++)
        {
            /* Get the corresponding char then transmit to the LCD */
            byte_send = ASCII_font[ch][i];
            SSD1306_Write(SSD1306_WRITE_DATA, byte_send);

            /* Update new cursor position */
            my_ssd1306.cursorPos++;
        }

        /* Add a small space (1 segment) after the character */
        SSD1306_Write(SSD1306_WRITE_DATA, 0x00);

        /* Update the current position of the cursor */
        my_ssd1306.cursorPos++;
    }
}


/*************************************************************************
 * @fn				- SSD1306_Write
 *
 * @brief			- Send a string to LCD
 * 
 * @param[in]		- str: string
 *
 * @return			- none
 */
void SSD1306_PrintString(char *str)
{
    while (*str != 0)
    {
        SSD1306_PrintChar(*str++);
    }
}


/*************************************************************************
 * @fn				- SSD1306_Clear
 *
 * @brief			- Clear all pixels on the display
 * 
 * @param[in]		- none
 *
 * @return			- none
 */
void SSD1306_Clear(void)
{
    SSD1306_SetCursor(0, 0);
    SSD1306_Fill(0x00);
}


/*************************************************************************
 * @fn				- SSD1306_Init
 *
 * @brief			- Initialize the LCD
 *                  - Reference: https://embetronicx.com/tutorials/linux/device-drivers/ssd1306-i2c-linux-device-driver-using-raspberry-pi/
 * 
 * @param[in]		- none
 *
 * @return			- 0 if success
 */
int SSD1306_Init(void) 
{
    msleep(100);

    /* Initialize the display */
    /* Set display OFF */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xAE); 

    /* Set display clock divide ratio/oscillator frequency */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xD5); 
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x80); /* default setting */

    /* Set multiplex ratio */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xA8);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x3F); /* default setting */

    /* Set display offset */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xD3);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x00); /* default setting */

    /* Set display startline */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x40); /* default setting */

    /* Set charge pump */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x8D);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x14); /* default setting */

    /* Set memory addressing mode */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x20);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x00); /* horizontal addressing mode */

    /* Set segment remap */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xA1);

    /* Set COM output scan direction */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xC8); /* default setting */

    /* Set COM pins hardware configuration */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xDA);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x12);

    /* Set contrast control */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x81);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x80); /* Contrast = 128 */

    /* Set pre-charge period */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xD9);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xF1);

    /* Set VCOMH Deselect level */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xDB);
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x20); /* VCOMH deselect level ~ 0.77 Vcc */

    /* Set Entire display ON */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xA4);

    /* Set display in Normal mode */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xA6);

    /* Deactive scroll */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0x2E);

    /* Display ON in normal mode */
    SSD1306_Write(SSD1306_WRITE_COMMAND, 0xAF);

    /* Clear the display */
    SSD1306_Clear();
    return 0;  
}

