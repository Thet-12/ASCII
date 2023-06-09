#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

#define NOT_FOUND   128
#define DECIMAL     10
#define BINARY      11
#define HEXA        12
#define ALPHA       13

int check_flag(const char* flag_str);
unsigned char check_char(const char* char_str);
unsigned char check_cmd(const char* cmd_str);
int check_num(const char* num_str);
void check_h_v(const char* str);
void DtoB_print(const char ch);
void print_Alpha(const char ch);
void print(const char ch, const int flag);
void print_chart(int flag);
void print_help(void);

int main (const int argc, const char* argv[])
{
    unsigned char c = 0;
    int c_num = 0;
    int status = 1;
    int flag_[3] = {0,0,0};

    for(int i=1; i<argc; i++)
    {
        if(argc >5)
        {
            status = 8;
            break;
        }
        if(argc == 2)
            check_h_v(argv[1]);
        if(i == 1)
        {
            c = check_char(argv[i]);
            if (c != NOT_FOUND)
            {
                status = 2;
                continue;
            }
            flag_[i-1] = check_flag(argv[i]);
            if(flag_[i-1] != NOT_FOUND)
                status = 3;
            else
            {
                c_num = check_num(argv[i]);
                status = (c_num == NOT_FOUND) ? 8 : 4;
            }
            
            if(status != 2 && argc != 2)
                status = 8;
            
            if((status == 3) || (status == 4) || (status == 8))
                break;
        }
        flag_[i-2] = check_flag(argv[i]);
        if(flag_[i-2] == NOT_FOUND)
        {
            status = 8;
            break;
        }
        else
            status = argc + 2;
    }
    
    switch (status)
    {    
        case 1:
            system("echo \x1B[91mInsufficient Arguments\x1B[0m\n");
            break;
        case 2:
            system("echo \x1B[94m");
            print(c,ALPHA);
            print(c,DECIMAL);
            print(c,BINARY);
            print(c,HEXA);
            system("echo \x1B[0m");
            break;
        case 3:
            system("echo \x1B[92m");
            print_chart(flag_[0]);
            system("echo \x1B[0m");
            break;
        case 4:
            printf("ASCII character for");
            printf("\x1B[94m");
            printf(" %s ",argv[1]);
            printf("\x1B[0m");
            printf(": ");
            printf("\x1B[94m");
            print(c_num,ALPHA);
            system("echo \x1B[0m");
            break;
        case 5:
            system("echo \x1B[94m");
            print(c,ALPHA);
            print(c,flag_[0]);
            system("echo \x1B[0m");
            break;
        case 6:
            system("echo \x1B[94m");
            print(c,ALPHA);
            print(c,flag_[0]);
            print(c,flag_[1]);
            system("echo \x1B[0m");
            break;
        case 7:
            system("echo \x1B[94m");
            print(c,ALPHA);
            print(c,flag_[0]);
            print(c,flag_[1]);
            print(c,flag_[2]);
            system("echo \x1B[0m");
            break;
        default:
            system("echo \x1B[91mWrong Arguments\x1B[0m\n");
            break;
    }
    return 0;
}

int check_flag(const char* flag_str)
{
    if((!strcmp("-d", flag_str)) || (!strcmp("--decimal", flag_str)))
        return DECIMAL;
    else if((!strcmp("-b", flag_str)) || (!strcmp("--binary", flag_str)))
        return BINARY;
    else if((!strcmp("-x", flag_str)) || (!strcmp("--hexa", flag_str)))
        return HEXA;
    else
        return NOT_FOUND;
}

unsigned char check_char(const char* char_str)
{
    int str_length = strlen(char_str);
    int cmd_length = str_length-1;
    char cmd_str[cmd_length-1];

    if((char_str[0] != '\'') || (char_str[str_length-1] != '\''))
        return NOT_FOUND;
    if(str_length == 3 && char_str[1] < 128)
        return char_str[1];

    for(int i=0; i<str_length-2; i++)
    {
        cmd_str[i] = char_str[i+1];
        if(cmd_str[i] == '\'')
            cmd_str[i] = '\0';
    }
    return check_cmd(cmd_str);
}

unsigned char check_cmd(const char* cmd_str)
{
    int i;
    for(i=0; i<NUM_CMD; i++)
    {
        if(!strcmp(cmd_str,command_list[i]))
            return (i == 33) ? 127 : i;
    }
    return NOT_FOUND;
}

int check_num(const char* num_str)
{
    int num = 0, length = 0, hex_temp = 0;
    length = strlen(num_str);
    if(num_str[1] == 'b' || num_str[1] == 'B')
    {
        if(length>9)
            return NOT_FOUND;
        for(int i=2; i<length; i++)
        {
            if(num_str[i] != '0' && num_str[i] != '1')
                return NOT_FOUND;
            num = (num << 1) + (num_str[i]-48);
        }
    }
    else if(num_str[1] == 'x' || num_str[1] == 'X')
    {
        if(length>4)
            return NOT_FOUND;
        for(int i=2; i<length; i++)
        {
            if(num_str[i] < '0')
                return NOT_FOUND;
            if(num_str[i] > '9' && num_str[i] < 'A')
                return NOT_FOUND;
            if(num_str[i] > 'F' && num_str[i] < 'a')
                return NOT_FOUND;
            if(num_str[i] > 'f')
                return NOT_FOUND;
            hex_temp = (int)num_str[i]-48;
            hex_temp = (num_str[i] >= 'A' && num_str[i] <= 'F') ? (int)num_str[i]-55 : hex_temp;
            hex_temp = (num_str[i] >= 'a' && num_str[i] <= 'f') ? (int)num_str[i]-87 : hex_temp;
            num = (i == 2) ? hex_temp<<4 : num + hex_temp;
        }
    }
    else
    {
        for(int i=0;i<length;i++)
        {   
            if(num_str[i] < '0' || num_str[i] > '9')
                return NOT_FOUND;
            num += (int)(num_str[i]-48) * power(10,(length-i)-1);
        }
    }
    return num;
}

void check_h_v(const char* str)
{
    if((!strcmp("-v", str)) || (!strcmp("--version", str)))
    {
        system("echo \x1B[96m");
        printf("ASCII Table\nVersion 1.0 (2023)\nFree Software by Thomas.");
        system("echo \x1B[0m");
        exit(0);
    }
    else if((!strcmp("-h", str)) || (!strcmp("--help", str)))
    {
        print_help();
        exit(0);//help fun will be added soon
    }
}

void DtoB_print(const char ch)
{
    int B_arr[7];
    unsigned int c = (int) ch;
    for(int i=0; i<7; i++)
    {
        B_arr[i] = c%2;
        c = c>>1;
    }
    printf(" 0b");
    for(int i=6; i>=0; i--)
    {
        printf("%d",B_arr[i]);
    }
    printf("  ");
}

void print_Alpha(const char ch)
{
    if(ch < ' ')
        printf("%-4s ",command_list[(int)ch]);
    else if(ch == ' ')
        printf("\' \'  ");
    else if(ch == 127)
        printf("%-4s ",command_list[33]);
    else
        printf("%-4c ",ch);
}

void print(const char ch, const int flag)
{
    switch (flag)
    {
        case DECIMAL:
            printf("%3u  ",(int)ch);
            break;
        case BINARY:
            DtoB_print(ch);
            break;
        case HEXA:
            if(ch<16)
                printf("0x0%x  ",ch);
            else
                printf("0x%x  ",ch);
            break;
        case ALPHA:
            print_Alpha(ch);
            break;
    }
}

void print_chart(int flag)
{
    for(int i=0; i<128; i++)
    {
        print(i,flag);
        print_Alpha(i);
        if(i%8 == 7)
            printf("\n");
        else
            printf(" ");
    }
}

void print_help(void)
{
    ////////// Usage 1 //////////
    system("echo \x1B[92m");
    printf("Usage 1\x1B[93m : ascii\t[-v | --version] [-h | --help]\n");
    printf("\t\t[-d | --decimal] [-b | --binary] [-x | --hexa]\n");
    printf("Message options\n");
    printf("\t-d, --decimal\tASCII chart with respective decimal numbers\n");
    printf("\t-b, --binary\tASCII chart with respective binary numbers\n");
    printf("\t-x, --hexa\tASCII chart with respective hexadecimal numbers\n");
    system("echo \x1B[94m   +------------------------------------------------+\x1B[92m");
    ////////// Usage 2 //////////
    printf("Usage 2\x1B[93m : ascii\t{decimal}\n\t\t{binary}\n\t\t{hexa}\n");
    printf("Print equivalent ASCII character\n\n");
    printf("Number Format Examples\n");
    printf("\tdecimal\t85\n\tbinary\t0b1010101 | 0B1010101 (7 Bits)\n\thexa\t0x55 | 0X55\n");
    system("echo \x1B[94m   +------------------------------------------------+\x1B[92m");
    ////////// Usage 3 //////////
    printf("Usage 3\x1B[93m : ascii {char}\t[<options>] [<options>] [<options>]\n\n");
    printf("Char Format\n\t\'U\' (cmd) | \"\'U\'\" (powershell)\n");
    printf("Message options\n");
    printf("\tnone\t\tprint respective decimal, binary, and hexadecimal numbers\n");
    printf("\t-d, --decimal\tprint respective decimal numbers\n");
    printf("\t-b, --binary\tprint respective binary numbers\n");
    printf("\t-x, --hexa\tprint respective hexadecimal numbers\n");
    system("echo \x1B[94m   +------------------------------------------------+\x1B[0m");
}