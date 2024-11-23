#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_interface.h"

void main(void)
{
	static uint8 Local_u8Counter1 = 1 ;
	static uint8 Local_u8Enter = 0 ;
	static uint8 Local_u8Counter2 = 1 ;

	static uint8 Local_u8OPCounter = 0 ;
	static uint8 Local_u8OP  ;

	uint8 Local_u8ButtonState1 = 1 ;
	uint8 Local_u8ButtonState2 = 1 ;
	uint8 Local_u8ButtonState3 = 1 ;

	uint8 Local_u8Res  ;

	uint8 Local_u8Pattern[8] = {0b00000100,
			0b00001110,
			0b00011111,
			0b00000100,
			0b00000100,
			0b00000100,
			0b00000100,
			0};
	/*set direction*/
	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_INPUT);

	/*pull up*/
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8PIN_HIGH);

	/*start*/
	CLCD_voidInit();
	CLCD_voidGoToXY(0,0);
	CLCD_voidSendNumber(1);
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendData('+');
	CLCD_voidGoToXY(2,0);
	CLCD_voidSendNumber(1);

	CLCD_u8SendSpecialCharacter(0,Local_u8Pattern,0,1);

	while(1)
	{
		DIO_u8ReadPinValue(DIO_u8PORTD,DIO_u8PIN2,&Local_u8ButtonState1);
		DIO_u8ReadPinValue(DIO_u8PORTD,DIO_u8PIN3,&Local_u8ButtonState2);
		DIO_u8ReadPinValue(DIO_u8PORTD,DIO_u8PIN4,&Local_u8ButtonState3);

		if(((!Local_u8ButtonState1)&&(Local_u8ButtonState2)&&(Local_u8ButtonState3))&&(Local_u8Enter == 0))
		{
			_delay_ms(250);
			if(Local_u8Counter1 != 9)
			{
				Local_u8Counter1++;
			}
			else if(Local_u8Counter1 == 9)
			{
				Local_u8Counter1 = 0;
			}
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendNumber(Local_u8Counter1);
		}

		if(((Local_u8ButtonState1)&&(!Local_u8ButtonState2)&&(Local_u8ButtonState3))&&(Local_u8Enter == 0))
		{
			_delay_ms(250);
			if(Local_u8Counter1 != 0)
			{
				Local_u8Counter1--;
			}
			else if(Local_u8Counter1 == 0)
			{
				Local_u8Counter1 = 9 ;
			}
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendNumber(Local_u8Counter1);
		}







		if((!Local_u8ButtonState3))
		{
			_delay_ms(250);
			Local_u8Enter++;

			if(Local_u8Enter == 1)
			{
				CLCD_voidGoToXY(0,1);
				CLCD_voidSendData(' ');
				CLCD_u8SendSpecialCharacter(0,Local_u8Pattern,1,1);
			}

			else if(Local_u8Enter == 2)
			{
				CLCD_voidGoToXY(1,1);
				CLCD_voidSendData(' ');
				CLCD_u8SendSpecialCharacter(0,Local_u8Pattern,2,1);
			}
			else if(Local_u8Enter == 3)
			{
				Local_u8Enter = 3 ;
				CLCD_voidGoToXY(3,0);
				CLCD_voidSendData('=');
				CLCD_voidGoToXY(2,1);
				CLCD_voidSendData(' ');
				CLCD_u8SendSpecialCharacter(0,Local_u8Pattern,4,1);
			}

		}

		if(((!Local_u8ButtonState1)&&(Local_u8ButtonState2)&&(Local_u8ButtonState3))&&(Local_u8Enter == 1))
		{

			_delay_ms(250);
			Local_u8OPCounter++ ;
			if(Local_u8OPCounter == 0)
			{
				Local_u8OP = '+';
			}
			else if(Local_u8OPCounter == 1)
			{
				Local_u8OP = '-';
			}
			else if(Local_u8OPCounter == 2)
			{
				Local_u8OP = '*';
			}

			else if(Local_u8OPCounter == 3)
			{
				Local_u8OP = '/';
			}

			else
			{
				Local_u8OPCounter = 0 ;
				Local_u8OP = '+';

			}

			CLCD_voidGoToXY(1,0);
			CLCD_voidSendData(Local_u8OP);
		}

		if(((Local_u8ButtonState1)&&(!Local_u8ButtonState2)&&(Local_u8ButtonState3))&&(Local_u8Enter == 1))
		{
			_delay_ms(250);
			Local_u8OPCounter--;
			if(Local_u8OPCounter == 0)
			{
				Local_u8OP = '+';
			}
			else if(Local_u8OPCounter == 1)
			{
				Local_u8OP = '-';
			}
			else if(Local_u8OPCounter == 2)
			{
				Local_u8OP = '*';
			}

			else if(Local_u8OPCounter == 3)
			{
				Local_u8OP = '/';
			}

			else
			{
				Local_u8OPCounter = 3 ;
				Local_u8OP = '/';
			}

			CLCD_voidGoToXY(1,0);
			CLCD_voidSendData(Local_u8OP);
		}






		if(((!Local_u8ButtonState1)&&(Local_u8ButtonState2)&&(Local_u8ButtonState3))&&(Local_u8Enter == 2))
		{
			_delay_ms(250);
			if(Local_u8Counter2 != 9)
			{
				Local_u8Counter2 ++;
			}
			else if(Local_u8Counter2 == 9)
			{
				Local_u8Counter2 = 0;
			}
			CLCD_voidGoToXY(2,0);
			CLCD_voidSendNumber(Local_u8Counter2);
		}

		if(((Local_u8ButtonState1)&&(!Local_u8ButtonState2)&&(Local_u8ButtonState3))&&(Local_u8Enter == 2))
		{
			_delay_ms(250);
			if(Local_u8Counter2 != 0)
			{
				Local_u8Counter2--;
			}
			else if(Local_u8Counter2 == 0)
			{
				Local_u8Counter2 = 9 ;
			}
			CLCD_voidGoToXY(2,0);
			CLCD_voidSendNumber(Local_u8Counter2);
		}


		if((Local_u8Enter == 3))
		{
			switch(Local_u8OPCounter)
			{
			case 0 :
				Local_u8Res = Local_u8Counter1 +  Local_u8Counter2 ;
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_u8Res);
				break ;
			case 1 :
				Local_u8Res = Local_u8Counter1 -  Local_u8Counter2 ;
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_u8Res);
				break ;
			case 2 :
				Local_u8Res = Local_u8Counter1 *  Local_u8Counter2 ;
				CLCD_voidGoToXY(4,0);
				CLCD_voidSendNumber(Local_u8Res);
				break ;
			case 3 :
				if (Local_u8Counter2 == 0)
				{
					CLCD_voidGoToXY(4, 0);
					CLCD_u8SendString("Err");
				}
				else
				{
					Local_u8Res =  Local_u8Counter1 / Local_u8Counter2;
					CLCD_voidGoToXY(4, 0);
					CLCD_voidSendNumber((f32)Local_u8Res);
				}
				break ;
			default:
				/**/
				break;
			}




		}


	}  // while(1)

} //main


/*	CLCD_u8SendString("mo ahmed");

	CLCD_voidGoToXY(0,1);
	CLCD_voidSendNumber(555);

	CLCD_u8SendSpecialCharacter(0, Local_u8Pattern,5,1);
 */
