#include "uart_parse.h"

void uart1_parse(void)
{
	if(uart1_rx_buffer[0]=='a')
	{
		System_state.cmd=1;
	}
	else if(uart1_rx_buffer[0]=='b')
	{
		System_state.cmd=2;
	}
	else if(uart1_rx_buffer[0]=='c')
	{
		System_state.cmd=3;
	}
	else if(uart1_rx_buffer[0]=='d')
	{
		System_state.cmd=4;
	}
	else if(uart1_rx_buffer[0]=='e')
	{
		System_state.cmd=5;
	}
	else if(uart1_rx_buffer[0]=='1')
	{
		System_state.Kit_num=1;
	}
	else if(uart1_rx_buffer[0]=='2')
	{
		System_state.Kit_num=2;
	}
	else if(uart1_rx_buffer[0]=='3')
	{
		System_state.Kit_num=3;
	}
	else if(uart1_rx_buffer[0]=='4')
	{
		System_state.Kit_num=4;
	}
	else if(uart1_rx_buffer[0]=='5')
	{
		System_state.Kit_num=5;
	}
	else if(uart1_rx_buffer[0]=='6')
	{
		System_state.Kit_num=6;
	}
	else if(uart1_rx_buffer[0]=='z')
	{
		if(uart1_rx_buffer[1]=='a')
		{
			System_state.cmd=1;
		}
		else if(uart1_rx_buffer[1]=='b')
		{
			System_state.cmd=2;
		}
		else if(uart1_rx_buffer[1]=='c')
		{
			System_state.cmd=3;
		}
		else if(uart1_rx_buffer[1]=='d')
		{
			System_state.cmd=4;
		}
		else if(uart1_rx_buffer[1]=='e')
		{
			System_state.cmd=5;
		}
		else if(uart1_rx_buffer[1]=='1')
		{
			System_state.Kit_num=1;
		}
		else if(uart1_rx_buffer[2]=='2')
		{
			System_state.Kit_num=2;
		}
		else if(uart1_rx_buffer[3]=='3')
		{
			System_state.Kit_num=3;
		}
		else if(uart1_rx_buffer[4]=='4')
		{
			System_state.Kit_num=4;
		}
		else if(uart1_rx_buffer[5]=='5')
		{
			System_state.Kit_num=5;
		}
		else if(uart1_rx_buffer[6]=='6')
		{
			System_state.Kit_num=6;
		}
	}
}

void uart2_parse(void)
{
	if(uart2_rx_buffer[5]=='=')//SPO2
	{
		if(uart2_rx_buffer[6]=='N')
		{
			System_state.spo2=0;
		}
		else if(uart2_rx_buffer[10]=='O')//2位数字
		{
			System_state.spo2=(int)(uart2_rx_buffer[6]-'0')*10+(int)(uart2_rx_buffer[7]-'0');
		}
		else if(uart2_rx_buffer[11]=='O')//3位数字
		{
			System_state.spo2=(int)(uart2_rx_buffer[6]-'0')*100+(int)(uart2_rx_buffer[7]-'0')*10+(int)(uart2_rx_buffer[8]-'0');
		}
	}
	else if(uart2_rx_buffer[6]=='=')//HEART
	{
		if(uart2_rx_buffer[7]=='N')
		{
			System_state.heart=0;
		}
		else if(uart2_rx_buffer[11]=='O')//2位数字
		{
			System_state.heart=(int)(uart2_rx_buffer[7]-'0')*10+(int)(uart2_rx_buffer[8]-'0');
		}
		else if(uart2_rx_buffer[12]=='O')//3位数字
		{
			System_state.heart=(int)(uart2_rx_buffer[7]-'0')*100+(int)(uart2_rx_buffer[8]-'0')*10+(int)(uart2_rx_buffer[9]-'0');
		}
	}
}

void uart3_parse(void)
{
	
}
