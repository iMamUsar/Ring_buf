/*
*   This program has been written by iMamUsar(imamusar@gmail.com) - Embedded Developer wannabe <3
*   To be use for getting TCP/IP data on Raspberry Pi and send it to AVR by I2C protocol
*   if any problems occured, please let me know or if you can fix it, I will really appreciate it!
*   and a simple way to reduce the code and grammar problem too !!
*/
#include<stdio.h>
#define buf_size 15       
#define buf_startpoint 5      //Free to change startpoint that first ever data goes in the ring buffer
#define buf_init_value 0xFF   //Will be filled with this init value    
unsigned char buf[buf_size];                    
unsigned char buf_start = buf_startpoint; 
unsigned char buf_end = buf_startpoint;  

void buf_init(void)          //Should initalize the buffer before you start using them
{
	int i;
	for (i = 0; i <= buf_size - 1; i++) buf[i] = buf_init_value;		
}
void buf_stat(void)		//You can see what data is stored in buffer
{
	int i;
	printf("\n\n");
	for (i = 0; i <= buf_size - 1; i++) printf("%X, ", buf[i]);
}
int buf_in(void)		//inserting data on buffer
{
	int in;		
	scanf("%X", &in);   
	if (in == 0xAA) return 1;  //Exit if the data just got is 0xAA
	    
    buf[buf_end] = in;	//the endpoint is ahead of where actual data is stored by one
	buf_end += 1;	
	if (buf_end >= buf_size) buf_end = 0; //It is not possible to endpoint be same or over the buffer size. so it goes same or over, this clear startpoint to 0
	return;
}
void buf_out(int out)
{
	int i;
	for (i = 1; i <= out; i++)
	{
		if (buf[buf_start] == 0xFF) return;                //This is to prevent data output when there's nothing
        printf(" Data == %X \t at #%d bufferÛ\n", buf[buf_start], buf_start);
		if (buf_start >= buf_size) buf_start = 0;		
		buf[buf_start] = buf_init_value;				//After data ouput this clear current cell to inital value(0xFF) so it can be rewritten again by buf_in fuction
		buf_start += 1;									//move the startpoint
	}
}
int main(void)
{
	int i = 0;
	buf_init();
	while (1)
	{
		buf_stat();
		printf("\n\n\nEnd Position %d\n\n\n", buf_end);
		if (buf_in() == 1)		//When 0xAA has entered during this fuction, execute the data output mode
		{
			if (buf_start == buf_end)	printf("No more data to Print");	//if startpoint and endpoint 
			else{
				printf("\n\n\nGive me how much data you want out : ");
				scanf("%d", &i);
				if (i <= buf_size) buf_out(i);
			}
		}
	}
} 
