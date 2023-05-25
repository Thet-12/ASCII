#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define NOTFOUND 128
#define DECIMAL 10
#define BINARY 2
#define HEXA 16
#define ALL 500

int check_flag(const char* flag);
char check_char(const char* ch);
int DtoB(const char ch);
void print(const char ch, const int flag);

int main (const int argc, const char* argv[])
{
    unsigned char c = 0;
    int flag = 0;
    switch (argc)
    {   case 1: 
            printf("Insufficient Arguments\n");
            break;
        case 2: 
            flag = check_flag(argv[1]);
            if(flag != NOTFOUND)
            {
                for(int i=0; i<128; i++)
                {
                    print((char)i,flag);
                    i%10 == 0 ? printf("\n") : printf("\t");
                }
                break;
            }
            else 
            {
                c = check_char(argv[1]);
                if(c == NOTFOUND)
                {
                    printf("Wrong Arguments\n");
                    break;
                }
                print(c,ALL);
                break;
            }
            printf("Wrong Arguments\n");
            break;
        case 3:
            c = check_char(argv[1]);
            flag = check_flag(argv[2]);
            if(c == NOTFOUND || flag == NOTFOUND)
            {
                printf("Wrong Arguments\n");
                break;
            }
            print(c,flag);
            break;
        default:
            printf("Too much Arguments\n");
            break;
    }
    return 0;
}

int check_flag(const char* flag)
{
    if((!strcmp("-d",flag)) || (!strcmp("--decimal",flag)))
        return DECIMAL;
    else if((!strcmp("-b",flag)) || (!strcmp("--binary",flag)))
        return BINARY;
    else if((!strcmp("-x",flag)) || (!strcmp("--hexa",flag)))
        return HEXA;
    else
        return NOTFOUND;
}

char check_char(const char* ch)
{
    if(strlen(ch) != 3)
        return NOTFOUND;
    if((ch[0] != '\'') || (ch[2] != '\''))
        return NOTFOUND;
    if(ch[1] > 127)
        return NOTFOUND;
    return ch[1];
}

int DtoB(const char ch)
{
    int B = 0;
    int B_array[8];
    unsigned int c = (int) ch;
    for(int i=0; i<7; i++)
    {
        B_array[i] = c%2;
        c = c>>1;
        i == 0 ? (B = B_array[i]) : (B = (B*10) + B_array[i]);
    }
    return B;
}

void print(const char ch, const int flag)
{
    switch (flag)
    {
        case DECIMAL:
            printf("%c (%u)",ch,(int)ch);
            break;
        case BINARY:
            printf("%c (0b%d)",ch,DtoB(ch));
            break;
        case HEXA:
            printf("%c (0x%x)",ch,ch);
            break;
        default:
            printf("%c (%u) (0b%d) (0x%x)",ch,(int)ch,DtoB(ch),ch);
            break;
    }    
}