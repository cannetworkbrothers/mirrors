#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <windows.h>

typedef struct
{
    unsigned long id;               // identifier (11 or 29 bit)
    struct {
        unsigned char rtr : 1;      // remote transmit request
        unsigned char extended : 1; // extended identifier
    } flags;

    unsigned char dlc;              // data length code
    unsigned char data[8];          // payload data
    unsigned short timestamp;       // timestamp
} canmsg_t;

unsigned long GetNumberOfDigits(unsigned long number, unsigned long radix)
{
    unsigned long count = 0;
    while(number > 0){
        number /= radix;
        count++;
    }
    
    return count;
}

bool SendMessageToPC(canmsg_t * p_canmsg)
{
    
    // USART transmiter;
    
    //calculate number of chars in result string
    unsigned long string_to_send_length = GetNumberOfDigits(p_canmsg->id, 16);
    
    char *id_prefix = (char*) malloc(2);
    if (p_canmsg->flags.extended == 1)
    {
        id_prefix = (char*) "W";
    }
    else
    {
        id_prefix = (char*) "S";
    }
    char *id_itself = (char*) malloc(string_to_send_length+1);
    itoa(p_canmsg->id, id_itself, 16);
    
    char *id = (char *) malloc(strlen(id_prefix)+strlen(id_itself)+1);
    strcpy(id, id_prefix);
    strcat(id, id_itself);
    free(id_prefix);
    free(id_itself);
    
    for(unsigned long i = 0; i < p_canmsg->dlc; i++){
        string_to_send_length += GetNumberOfDigits(p_canmsg->data[i], 16);
    }
    
    //plus W/S, plus zero end
    string_to_send_length += 2;
    
    //plus number of "D"
    string_to_send_length += p_canmsg->dlc;
    
    char *can_msg_str = (char*) malloc(string_to_send_length);
    strcpy(can_msg_str, id);
    free(id);
    
    for (unsigned long i = 0; i < p_canmsg->dlc; i++)
    {
        char * data = (char *) malloc((GetNumberOfDigits(p_canmsg->data[i], 16) + 1));
        itoa(p_canmsg->data[i], data, 16);
        strcat(can_msg_str, "D");
        strcat(can_msg_str, data);
        free(data);
    }
    printf("%.*s", string_to_send_length, can_msg_str);
    printf("\n");
    // printf(can_msg_str);
    free(can_msg_str);
    return true;
}

int main()
{
    while(true){
        canmsg_t my_id = {};
        srand(time(0));
        my_id.id = rand() % 0x7fffff;
        my_id.flags.rtr = 0;
        if (my_id.id > 0x7ff)
        {
            my_id.flags.extended = 1;   
        }
        else{
            my_id.flags.extended = 0;
        }
        my_id.dlc = 8;
        for (int i = 0; i < 8; ++i)
        {
            my_id.data[i]  = rand() % 255;
        }
        my_id.timestamp = 12212;

        SendMessageToPC(&my_id);
        Sleep(10);
    }
    return 0;
}