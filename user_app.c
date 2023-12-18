#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <netdb.h>
#include <errno.h>

#define SSD1306_DEV_FILE    "/dev/ssd1306_lcd"


static void showMenu(void);
static void showHost(void);
static void showCPU(void);
static void printLCD(char *user_cmd);
static void clearLCD(void);
static void exitApp(void);

int ret;
int fd;
char user_cmd[50];
char temp_cmd[10];
char *user_msg;

int main()
{
    /* Try open the LCD dev file */
    fd = open(SSD1306_DEV_FILE, O_WRONLY, 0222);

    if (fd == -1)
    {
        printf("Open /dev/ssd1306_lcd failed. Please check the dev folder\n");
        exit(EXIT_FAILURE);
    }

    system("clear");
    showMenu();

    while (1)
    {
        /* Get user command */
        printf("\nEnter your command: ");
        fgets(user_cmd, 50, stdin);

        /* Analyze the command */
        ret = sscanf(user_cmd, "%s", temp_cmd);

        if ( !strcmp(temp_cmd, "showHost"))
        {
            showHost();
        }
        else if ( !strcmp(temp_cmd, "showCPU"))
        {
            showCPU();
        }
        else if ( !strcmp(temp_cmd, "print"))
        {
            printLCD(user_cmd);
        }
        else if ( !strcmp(temp_cmd, "clear"))
        {
            clearLCD();
        }
        else if ( !strcmp(temp_cmd, "exit"))
        {
            exitApp();
        }
        else
        {
            printf("Invalid command. Please try again!\n");
        }
    }
    return 0;
}

static void showMenu(void)
{
    printf("\n-----------------SSD1306 LCD CONTROL APPLICATION--------------\n");
    printf("Type the commands below to display information on the LCD:\n");
    printf("1. showHost         : show Host information\n");
    printf("2. showCPU          : show CPU information\n");
    printf("3. print <string>   : print a string (max 40 characters) on the display\n");
    printf("4. clear            : clear the display\n");
    printf("5. exit             : exit the application\n");
}

static void printLCD(char *user_cmd)
{
    char *user_msg;
    user_msg = user_cmd + 6;
    write(fd, user_msg, strlen(user_msg));
    memset(user_msg, 0, sizeof(user_msg));
}

static void showHost(void)
{
    char Name[30];
    char IP[30];
    char OSVer[30];
    char Kernel[30];
    char Arch[30];
    char temp_buf[30];

    FILE *fp = popen("uname -r", "r");
    fscanf(fp, "%s", temp_buf);
    sprintf(Kernel, "\nKernel:%s\n", temp_buf);

    fp = popen("hostname -I", "r");
    fscanf(fp, "%s", temp_buf);
    sprintf(IP, "\nIpv4: %s\n", temp_buf);

    fp = popen("hostname", "r");
    fscanf(fp, "%s", temp_buf);
    sprintf(Name, "\nUser: %s\n", temp_buf);


    printf("Host Name   : %s", Name);
    printf("Host IP     : %s", IP);
    printf("Host Kernel : %s", Kernel);
    
    clearLCD();
    write(fd, "--Host Information--\n", strlen("--Host Information--\n"));
    write(fd, Name, strlen(Name));
    write(fd, IP, strlen(IP));
    write(fd, Kernel, strlen(Kernel));
}

static void showCPU()
{
    
}

static void clearLCD()
{
    write(fd, "clear", 5);
}

static void exitApp(void)
{
    clearLCD();
    write(fd, "\n------ Goodbye ------\n", sizeof("\n------ Goodbye ------\n"));
    write(fd, "\n--- See you later ---\n", sizeof("\n--- See you later ---\n"));
    sleep(2);
    clearLCD();
    close(fd);
    exit(0);
}