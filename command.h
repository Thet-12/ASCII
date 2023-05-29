#define NUM_CMD 34

int power(int base, unsigned int p)
{
    int temp = base;
    if(p == 0)
        return 1;
    for(int i=1; i<p; i++)
    {
        temp *= base;
    }
    return temp;
}

const char* command_list[NUM_CMD] = 
{
    "NULL",
    "SOH",
    "STX",
    "ETX",
    "EOT",
    "ENQ",
    "ACK",
    "BEL",
    "BS",
    "HT",
    "LF",
    "VT",
    "FF",
    "CR",
    "SO",
    "SI",
    "DLE",
    "DC1",
    "DC2",
    "DC3",
    "DC4",
    "NAK",
    "SYN",
    "ETB",
    "CAN",
    "EM",
    "SUB",
    "ESC",
    "FS",
    "GS",
    "RS",
    "US",
    "SPACE",
    "DEL"
};

/*
 * Status
 *
 * 1 : ascii : Insuficient Arguments
 * 2 : ascii ['char']
 * 3 : ascii [flag]
 * 4 : ascii [number]
 * 5 : acsii ['char'] [flag]
 * 6 : acsii ['char'] [flag] [flag]
 * 7 : acsii ['char'] [flag] [flag] [flag]
 * 8 : Wrong Arguments
*/