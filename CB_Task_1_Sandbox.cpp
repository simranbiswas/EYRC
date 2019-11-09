//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions

#include "CB_Task_1_Sandbox.h"
char left_sensor, right_sensor, mid_sensor;

/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
{
	/*while (node<=3)
	{
		while (unsigned char ADC_Conversion(unsigned char 2) != 0 && node<2)
		{
			forward();
		}
		left();
	}*/
	printf("hi simran");
	int no_of_nodes = int(node);
	int i = 1;
	left_sensor = ADC_Conversion(1);
	mid_sensor = ADC_Conversion(2);
	right_sensor = ADC_Conversion(3);
	while (i <= no_of_nodes)// && (left_sensor == -1 || mid_sensor == -1 || right_sensor == -1))
	{
		printf("%d", i);
		forward();
		left_sensor = ADC_Conversion(1);
		mid_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		if (mid_sensor == 0 && (left_sensor == -1 || right_sensor == -1))
		{
			if (left_sensor == -1)
			{
				do
				{
					soft_left();
					mid_sensor = ADC_Conversion(2);
				} while (mid_sensor != -1);
			}
			else if (right_sensor == -1)
			{
				do
				{
					soft_right();
					mid_sensor = ADC_Conversion(2);
				} while (mid_sensor != -1);
			}
			
		}
		else if (mid_sensor == -1 && left_sensor == -1 && right_sensor == -1)
		{
			i++;
		}
	}
	while (mid_sensor != 0 && left_sensor != 0 && right_sensor != 0)
	{
		forward();
		left_sensor = ADC_Conversion(1);
		mid_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
	}

}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
	left();
	_delay_ms(500);
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
	right();
}

/*
*
* Function Name: e_shape
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a e shape path on the arena
* Example Call: e_shape();
*/
void e_shape(void)
{
	
}


/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
	// Write your task 1.1 Logic here
	forward_wls(1);
	left_sensor = ADC_Conversion(1);
	mid_sensor = ADC_Conversion(2);
	right_sensor = ADC_Conversion(3);
	//if(left_sensor == 0 && mid_sensor == 0 && right_sensor == 0)
	left_turn_wls();
	printf("from simran's ganda laptop");
	forward_wls(3);
	right_turn_wls();
	stop();
}

/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
	//write your task 1.2 logic here
}