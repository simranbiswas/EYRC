//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions

#include "CB_Task_1_Sandbox.h"

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
	char a, b, c;
	int error, setpoint, current;
	a = ADC_Conversion(1);
	printf("%d\n", a);
	b = ADC_Conversion(2);
	printf("%d\n", b);
	c = ADC_Conversion(3);
	printf("%d\n", c);

	while (b == -1 || a == -1 || c == -1)
	{
		forward();
		printf("b=%d\t", b);
		printf("a=%d\t", a);
		printf("c=%d\n", a);

		b = ADC_Conversion(2);
		a = ADC_Conversion(1);
		c = ADC_Conversion(3);
	}
	a = ADC_Conversion(1);
	printf("a=%d\t", a);
	b = ADC_Conversion(2);
	printf("b=%d\t", b);
	c = ADC_Conversion(3);
	printf("c=%d\n", c);

	stop();

	_delay_ms(1000);
	b = ADC_Conversion(2);
	printf("%d\n", b);

	while (b != -1)
	{
		right();

		printf("b=%d\n", b);

		b = ADC_Conversion(2);

	}
	right();
	_delay_ms(70);

	stop();
	_delay_ms(1000);
	a = ADC_Conversion(1);
	printf("%d\n", a);
	b = ADC_Conversion(2);
	printf("%d\n", b);
	c = ADC_Conversion(3);
	printf("%d\n", c);

	while (b == -1 || a == -1 || c == -1)
	{
		forward();
		printf("b=%d\t", b);
		printf("a=%d\t", a);
		printf("c=%d\n", a);

		b = ADC_Conversion(2);
		a = ADC_Conversion(1);
		c = ADC_Conversion(3);
	}
	stop();
	/*right();
	_delay_ms(70);

	stop();
	_delay_ms(1000);
	a = ADC_Conversion(1);
	printf("%d\n", a);
	b = ADC_Conversion(2);
	printf("%d\n", b);
	c = ADC_Conversion(3);
	printf("%d\n", c);

	while (b == -1 || a == -1 || c == -1)
	{
	forward();
	printf("b=%d\t", b);
	printf("a=%d\t", a);
	printf("c=%d\n", a);

	b = ADC_Conversion(2);
	a = ADC_Conversion(1);
	c = ADC_Conversion(3);
	}
	stop();*/
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