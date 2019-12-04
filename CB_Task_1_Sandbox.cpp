//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions

#include "CB_Task_1_Sandbox.h"
#include <limits.h>
#include <stdio.h>
#define V 33

int left_sensor, right_sensor, mid_sensor, j = 0, k = 1, i1;

int lvalue, rvalue;//Used to check conditions for the white line traversal
void check_node();
//float kp = 25, ki = 0.15, kd = 1200;
/*
*
* Function Name: forward_wls_white
* Input: nill
* Output: void
* Logic: It uses to follow the bot on the white line
* Example Call: pid(0); //The bot is moving in the left direction so to bring it back on track
*
*/


void forward_wls_white()
{

	while (true)
	{
		left_sensor = int(ADC_Conversion(1));
		mid_sensor = int(ADC_Conversion(2));
		right_sensor = int(ADC_Conversion(3));
		if (left_sensor == 255 && right_sensor == 255 && mid_sensor == 0)
		{
			forward();
			velocity(100, 100);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
		}
		else if ((left_sensor == 255 && mid_sensor == 255 && right_sensor == 0))// || (right_sensor == 0 && mid_sensor == 255 && left_sensor == 255))
		{
			stop();
			//forward();
			//velocity(100, 100);
			do {
				soft_right();
				//velocity(0, 5);
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if ((right_sensor == 255 && mid_sensor == 255 && left_sensor == 255) || (right_sensor == 0 || left_sensor == 0))
					break;
			} while (mid_sensor != 0 || right_sensor == 0);



		}
		else if ((left_sensor == 0 && mid_sensor == 255 && right_sensor == 255))//|| (right_sensor == 255 && mid_sensor == 255 && left_sensor == 0))
		{
			stop();
			//forward();
			//velocity(100, 100);
			do {
				soft_left();
				//velocity(5, 0);
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if ((right_sensor == 255 && mid_sensor == 255 && left_sensor == 255) || (right_sensor == 0 || left_sensor == 0))
					break;
			} while (mid_sensor != 0 || left_sensor == 0);



		}

		else if (left_sensor == 255 && right_sensor == 255 && mid_sensor == 255)
		{ /*While white line traversal if it enters full black path*/
			forward();
			_delay_ms(10);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if ((left_sensor == 0 && right_sensor == 0) || ((left_sensor > 0 && left_sensor < 255) || (mid_sensor > 0 && mid_sensor < 255) || (right_sensor > 0 && right_sensor < 255)))
				break;
			forward();
			// printf("\nbit left");
			for (j = 0; j < 100000 * k; j++)
			{
				printf("\nstablizingbot");
				velocity(0, 5);
				//left();
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if ((mid_sensor == 0) || (((left_sensor > 0) && (left_sensor < 255)) || ((mid_sensor > 0) && (mid_sensor < 255)) || ((right_sensor > 0) && (right_sensor < 255))))
					break;
			}
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if ((mid_sensor == 0) || (((left_sensor > 0) && (left_sensor < 255)) || ((mid_sensor > 0) && (mid_sensor < 255)) || ((right_sensor > 0) && (right_sensor < 255))))
			{
				continue;
				k = 1;
			}
			else
			{
				//printf("\noriginal");
				back();
				//_delay_ms(100);
				for (j = 0; j < 100000 * k; j++)
				{
					printf("\nstablizingbot");
					velocity(0, 5);    //To bring back original position
					//right();
				}

				// printf("\nbit right");
				forward();
				for (j = 0; j < 100000 * k; j++)
				{
					printf("\nstablizingbot");
					velocity(5, 0);
					//right();
					left_sensor = int(ADC_Conversion(1));
					mid_sensor = int(ADC_Conversion(2));
					right_sensor = int(ADC_Conversion(3));
					if ((mid_sensor == 0) || (((left_sensor > 0) && (left_sensor < 255)) || ((mid_sensor > 0) && (mid_sensor < 255)) || ((right_sensor > 0) && (right_sensor < 255))))
						break;
				}
			}
			if ((mid_sensor == 0) || (((left_sensor > 0) && (left_sensor < 255)) || ((mid_sensor > 0) && (mid_sensor < 255)) || ((right_sensor > 0) && (right_sensor < 255))))
			{
				continue;
				k = 1;
			}
			else
			{
				back();
				for (j = 0; j < 100000 * k; j++)
				{
					printf("\nstablizingbot");
					velocity(5, 0);

					//left();//To bring back original position
					//soft_right();
				}


				k++;



			}

		}
		if ((left_sensor == 0 && right_sensor == 0) || ((left_sensor > 0 && left_sensor < 255) || (mid_sensor > 0 && mid_sensor < 255) || (right_sensor > 0 && right_sensor < 255)))
			break;
	}
}
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
	int checknode = int(node), i1 = 1;
	while (i1 <= checknode)
	{
		left_sensor = int(ADC_Conversion(1));
		mid_sensor = int(ADC_Conversion(2));
		right_sensor = int(ADC_Conversion(3));
		if ((mid_sensor == 255 && left_sensor == 0 && right_sensor == 0))//|| (right_sensor == 255 && mid_sensor == 0 && left_sensor == 255))// || (mid_sensor == 0 && left_sensor == 255 && right_sensor == 255)|| (right_sensor == 0 && mid_sensor == 255 && left_sensor == 255)|| (right_sensor == 255 && mid_sensor == 255 && left_sensor == 0))
		{
			forward();
			velocity(100, 100);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
		}
		else if ((left_sensor == 255 && mid_sensor == 0 && right_sensor == 0))// || (right_sensor == 0 && mid_sensor == 255 && left_sensor == 255))
		{
			stop();
			//forward();
			//velocity(100, 100);
			do {
				soft_left();
				//velocity(0, 10);
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if ((right_sensor == 255 && mid_sensor == 255 && left_sensor == 255) || (right_sensor == 255 && mid_sensor == 0 && left_sensor == 255))
					break;
			} while (mid_sensor == 0 || left_sensor == 255);



		}
		else if ((left_sensor == 0 && mid_sensor == 0 && right_sensor == 255))//|| (right_sensor == 255 && mid_sensor == 255 && left_sensor == 0))
		{
			stop();
			//forward();
			//velocity(100, 100);

			do {
				soft_right();
				//velocity(10, 0);
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if ((right_sensor == 255 && mid_sensor == 255 && left_sensor == 255) || (right_sensor == 255 && mid_sensor == 0 && left_sensor == 255))
					break;
			} while (mid_sensor == 0 || right_sensor == 255);



		}
		else if ((right_sensor == 255 && mid_sensor == 255 && left_sensor == 0) || (right_sensor == 0 && mid_sensor == 255 && left_sensor == 255))
		{
			//forward();
			//velocity(100, 100);
			if (left_sensor == 255)
			{
				soft_left();
				// printf("\nLEFT");
			}
			else if (right_sensor == 255)
			{
				soft_right();
				//printf("\nRight");
			}
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
		}
		else if (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0)
		{/*Traversal for zigzag path*/
			forward();
			velocity(100, 100);
			// printf("\nbit left");
			for (j = 0; j < 300000 * k; j++)
			{
				printf("\nstablizingbot");
				velocity(0, 4);
				//left();
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
					break;
			}
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
			{
				continue;
				k = 1;
			}
			else
			{
				//printf("\noriginal");
				back();
				velocity(100, 100);
				//_delay_ms(100);
				for (j = 0; j < 300000 * k; j++)
				{
					printf("\nstablizingbot");
					velocity(0, 4);    //To bring back original position
					//right();
				}

				// printf("\nbit right");
				forward();
				velocity(100, 100);
				for (j = 0; j < 300000 * k; j++)
				{
					printf("\nstablizingbot");
					velocity(4, 0);
					//right();
					left_sensor = int(ADC_Conversion(1));
					mid_sensor = int(ADC_Conversion(2));
					right_sensor = int(ADC_Conversion(3));
					if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
						break;
				}
			}
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
			{
				continue;
				k = 1;
			}
			else
			{
				back();
				velocity(100, 100);
				for (j = 0; j < 300000 * k; j++)
				{
					printf("\nstablizingbot");
					velocity(4, 0);

					//left();//To bring back original position
					//soft_right();
				}


				k++;



			}

		}
		if (left_sensor == 255 && mid_sensor == 0 && right_sensor == 255)
		{
			printf("\nWHITE LINE");
			forward_wls_white();
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if ((left_sensor > 0 && left_sensor < 255) || (mid_sensor > 0 && mid_sensor < 255) || (right_sensor > 0 && right_sensor < 255))
				i1++;
			else
			{
				continue;
			}
		}
		if (left_sensor == 255 && mid_sensor == 255 && right_sensor == 255)
		{
			check_node();
			/*stop();
			_delay_ms(2000);
			printf("\nNODEEEEEEEEEEEE");
			//do {
			forward();
			_delay_ms(200);
			//left_sensor = int(ADC_Conversion(1));
			//mid_sensor = int(ADC_Conversion(2));
			//right_sensor = int(ADC_Conversion(3));
			//} while (left_sensor == 255 && right_sensor == 255);
			//velocity(150, 150);

			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 && mid_sensor == 0 && right_sensor == 255)
			{
			forward_wls_white();
			}
			if (left_sensor == 255 && mid_sensor == 255 && right_sensor == 0)
			{
			do {
			soft_left();
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			} while (left_sensor == 255 && mid_sensor == 255);
			}
			else if (left_sensor == 0 && mid_sensor == 255 && right_sensor == 255)
			{
			do {
			soft_right();
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			} while (right_sensor == 255 && mid_sensor == 255);
			}
			if (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0)
			{/*Traversal for zigzag path*
			forward();
			velocity(100, 100);
			// printf("\nbit left");
			for (j = 0; j < 30000 * k; j++)
			{
			printf("\nstablizingbot");
			velocity(0, 4);
			//left();
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
			break;
			}
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
			{
			continue;
			k = 1;
			}
			else
			{
			//printf("\noriginal");
			back();
			velocity(100, 100);
			//_delay_ms(100);
			for (j = 0; j < 30000 * k; j++)
			{
			printf("\nstablizingbot");
			velocity(0, 4);    //To bring back original position
			//right();
			}

			// printf("\nbit right");
			forward();
			velocity(100, 100);
			for (j = 0; j < 30000 * k; j++)
			{
			printf("\nstablizingbot");
			velocity(4, 0);
			//right();
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
			break;
			}
			}
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
			{
			continue;
			k = 1;
			}
			else
			{
			back();
			velocity(100, 100);
			for (j = 0; j < 30000 * k; j++)
			{
			printf("\nstablizingbot");
			velocity(4, 0);

			//left();//To bring back original position
			//soft_right();
			}


			// k++;



			}

			}
			/*Checking for white line traversal if the condition satisfies*/
			/*left();
			_delay_ms(150);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 && mid_sensor == 255)
			{
			lvalue = 1;
			}
			else
			{
			lvalue = 0;
			}
			right();
			_delay_ms(150);
			right();
			_delay_ms(150);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (right_sensor == 255 && mid_sensor == 255)
			{
			rvalue = 1;
			}
			else
			{
			rvalue = 0;
			}
			if (lvalue==1&&rvalue==1)
			{
			stop();
			_delay_ms(5000);
			//left();
			//_delay_ms(150);
			printf("\nCALLING WHITE LINE FUN");
			stop();
			_delay_ms(5000);
			forward_wls_white();
			printf("\nBREAK FROM WHITE LINE FUN");
			stop();
			_delay_ms(1000);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if ((left_sensor > 0 && left_sensor < 255) || (mid_sensor > 0 && mid_sensor < 255) || (right_sensor > 0 && right_sensor < 255))
			i++;
			else
			{
			continue;
			}
			}
			else
			{/*If white line traversal is not required*
			//left();
			//_delay_ms(150);
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			do {
			forward();
			velocity(150, 150);
			printf("\nForwarded");
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			//if ((left_sensor == 0 && mid_sensor == 255 && right_sensor == 255) || (left_sensor == 255 && mid_sensor == 255 && right_sensor == 0))
			//{
			//break;
			//}
			} while (left_sensor == 255 && right_sensor == 255);
			stop();
			_delay_ms(1000);
			i++;
			//}*/
			i1++;
		}
	}
}
void check_node()
{
	forward();
	_delay_ms(200);
	left_sensor = int(ADC_Conversion(1));
	right_sensor = int(ADC_Conversion(3));
	mid_sensor = int(ADC_Conversion(2));
	if (left_sensor == 255 && right_sensor == 0 && mid_sensor == 255)
	{
		soft_left();

	}
	if (left_sensor == 0 && right_sensor == 255 && mid_sensor == 255)
	{
		soft_right();

	}
	if (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0)
	{
		//forward();
		//velocity(100, 100);
		if (left_sensor == 255)
		{
			soft_left();
			// printf("\nLEFT");
		}
		else if (right_sensor == 255)
		{
			soft_right();
			//printf("\nRight");
		}
		left_sensor = int(ADC_Conversion(1));
		mid_sensor = int(ADC_Conversion(2));
		right_sensor = int(ADC_Conversion(3));
	}
	else if (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0)
	{/*Traversal for zigzag path*/
		forward();
		velocity(100, 100);
		// printf("\nbit left");
		for (j = 0; j < 30000; j++)
		{
			printf("\nstablizingbot");
			velocity(0, 4);
			//left();
			left_sensor = int(ADC_Conversion(1));
			mid_sensor = int(ADC_Conversion(2));
			right_sensor = int(ADC_Conversion(3));
			if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
				break;
		}
		left_sensor = int(ADC_Conversion(1));
		mid_sensor = int(ADC_Conversion(2));
		right_sensor = int(ADC_Conversion(3));
		if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
		{
			//continue;
			k = 1;
		}
		else
		{
			//printf("\noriginal");
			back();
			velocity(100, 100);
			//_delay_ms(100);
			for (j = 0; j < 30000; j++)
			{
				printf("\nstablizingbot");
				velocity(0, 4);    //To bring back original position
				//right();
			}

			// printf("\nbit right");
			forward();
			velocity(100, 100);
			for (j = 0; j < 30000; j++)
			{
				printf("\nstablizingbot");
				velocity(4, 0);
				//right();
				left_sensor = int(ADC_Conversion(1));
				mid_sensor = int(ADC_Conversion(2));
				right_sensor = int(ADC_Conversion(3));
				if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
					break;
			}
		}
		if (left_sensor == 255 || right_sensor == 255 || mid_sensor == 255)
		{
			//continue;
			k = 1;
		}
		else
		{
			back();
			velocity(100, 100);
			for (j = 0; j < 30000; j++)
			{
				printf("\nstablizingbot");
				velocity(4, 0);

				//left();//To bring back original position
				//soft_right();
			}


			//k++;



		}

	}
	do {
		forward();
		velocity(100, 100);
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));


	} while (left_sensor == 255 && right_sensor == 255);

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
	left_sensor = int(ADC_Conversion(1));
	right_sensor = int(ADC_Conversion(3));
	mid_sensor = int(ADC_Conversion(2));

	stop();
	//_delay_ms(5000);
	while (left_sensor == 255)
	{
		//forward();
		soft_left();
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));
	}

	do
	{

		//printf("\nLEFT");
		//forward();
		//left();
		left();
		//velocity(1, 255);
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));

	} while (left_sensor == 0);

	/*while(left_sensor==255)
	{
	//
	left();
	left_sensor = int(ADC_Conversion(1));
	right_sensor = int(ADC_Conversion(3));
	mid_sensor = int(ADC_Conversion(2));
	}*/


	//printf("\nl%d r%d m%d", left_sensor, right_sensor, mid_sensor);
	stop();
	// _delay_ms(5000);
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
	left_sensor = int(ADC_Conversion(1));
	right_sensor = int(ADC_Conversion(3));
	mid_sensor = int(ADC_Conversion(2));
	while (right_sensor == 255)
	{
		soft_right();
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));

	}
	do
	{
		right();
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));
	} while (right_sensor != 255);
}

struct Node
{
	int data;
	int weight;
	struct Node* next;
};

struct Node* head_array[32];

struct Node* create_node()
{
	struct Node* newnode;
	newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->next = NULL;
	newnode->data = -1;
	newnode->weight = 0;
	return newnode;
}

struct Node* create_adjacencylist(struct Node* head)
{
	struct Node* newnode, *temp;
	int i = 1;
	newnode = create_node();
	head = newnode;
	temp = head;
	while (i < 5)
	{
		newnode = create_node();
		temp->next = newnode;
		temp = temp->next;
		i++;
	}
	return head;
}

void traverse_up(int initial, int final)
{
	int i = 0;
	struct Node* temp;
	temp = head_array[initial];
	temp = temp->next;
	while (temp->next != NULL)
	{
		i++;
		if (temp->data == final)
			break;
		temp = temp->next;
	}
	//_delay_ms(100);
	switch (i)
	{
	case 1: left_turn_wls();
		forward_wls(1);
		break;
	case 2: right_turn_wls();
		forward_wls(1);
		break;
	case 3: forward_wls(1);
		break;
	case 4: mid_sensor = int(ADC_Conversion(2)); 
		while (mid_sensor != 0)
		{
			left();
			mid_sensor = int(ADC_Conversion(2));
		}
		while (mid_sensor != 255)
		{
			left();
			mid_sensor = int(ADC_Conversion(2));
		}
		break;
	default: break;
	}
}

void traverse_down(int initial, int final)
{
	int i = 0;
	struct Node* temp;
	temp = head_array[initial];
	temp = temp->next;
	while (temp->next != NULL)
	{
		i++;
		if (temp->data == final)
			break;
		temp = temp->next;
	}
	printf("\n%d", i);
	switch (i)
	{
	case 2: left_turn_wls();
		forward_wls(1);
		break;
	case 1: right_turn_wls();
		forward_wls(1);
		break;
	case 4: forward_wls(1);
		break;
	case 3: mid_sensor = int(ADC_Conversion(2));
		while (mid_sensor != 0)
		{
			left();
			mid_sensor = int(ADC_Conversion(2));
		}
		while (mid_sensor != 255)
		{
			left();
			mid_sensor = int(ADC_Conversion(2));
		}
		forward_wls(1);
		break;
	default: break;
	}
}

int node[V], count = 0, m = 0, dest, source, parent[V], last_node;;


int minDistance(int dist[], bool sptSet[])
{

	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printPath(int parent[], int j)
{


	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);
	//count++;

	printf("%d ", j);
	node[m++] = j;



}

void printSolution(int dist[], int n, int parent[], int source)
{
	int src = source;
	count = 0;
	for (int i = 0; i < V; i++)
	{

		if (i == dest)
		{
			printf("\n%d -> %d \t\t %d ", src, i, src);
			printPath(parent, i);
		}

	}
}

void dijkstra(int graph[V][V], int src, int destination)
{
	dest = destination;
	int i;
	m = 0;
	int dist[V];

	bool sptSet[V];

	int parent[V];

	for (i = 0; i < V; i++)
	{
		parent[i] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++)
	{
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < V; v++)

			if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}
	node[m++] = src;
	printSolution(dist, V, parent, src);
}

void orientation(int current, int next, int last)
{
	if (next > current)
	{
		if (last % 2 == 0 && last > 15)
		{
			left_turn_wls();
		}
		else if (last % 2 != 0 && last > 15)
		{
			right_turn_wls();
		}
	}
	else
	{
		if (last % 2 == 0 && last > 15)
		{
			right_turn_wls();
		}
		else if (last % 2 != 0 && last > 15)
		{
			left_turn_wls();
		}
	}
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

	int g[V][V] = { 0 };
	g[0][1] = 1;
	g[0][2] = 1;
	g[1][3] = 1;
	g[1][0] = 1;
	g[2][0] = 1;
	g[2][4] = 1;
	g[3][1] = 1;
	g[3][5] = 1;
	g[3][16] = 1;
	g[3][17] = 1;
	g[4][2] = 1;
	g[4][6] = 1;
	g[4][18] = 1;
	g[4][19] = 1;
	g[5][3] = 1;
	g[5][6] = 1;
	g[5][7] = 1;
	g[5][20] = 1;
	g[6][4] = 1;
	g[6][5] = 1;
	g[6][8] = 1;
	g[6][21] = 1;
	g[7][5] = 1;
	g[7][9] = 1;
	g[7][22] = 1;
	g[7][23] = 1;
	g[8][6] = 1;
	g[8][10] = 1;
	g[8][24] = 1;
	g[8][25] = 1;
	g[9][7] = 1;
	g[9][10] = 1;
	g[9][11] = 1;
	g[9][26] = 1;
	g[10][8] = 1;
	g[10][9] = 1;
	g[10][12] = 1;
	g[10][27] = 1;
	g[11][9] = 1;
	g[11][13] = 1;
	g[11][28] = 1;
	g[11][29] = 1;
	g[12][10] = 1;
	g[12][14] = 1;
	g[12][30] = 1;
	g[12][31] = 1;
	g[13][11] = 1;
	g[13][15] = 1;
	g[14][12] = 1;
	g[14][15] = 1;
	g[15][13] = 1;
	g[15][14] = 1;
	g[16][3] = 1;
	g[17][3] = 1;
	g[18][4] = 1;
	g[19][4] = 1;
	g[20][5] = 1;
	g[21][6] = 1;
	g[22][7] = 1;
	g[23][7] = 1;
	g[24][8] = 1;
	g[25][8] = 1;
	g[26][9] = 1;
	g[27][10] = 1;
	g[28][11] = 1;
	g[29][11] = 1;
	g[30][12] = 1;
	g[31][12] = 1;

	struct Node* temp;
	int i;

	for (i = 0; i <= 31; i++)
	{
		head_array[i] = create_adjacencylist(head_array[i]);
		head_array[i]->data = (char)i;
	}

	temp = head_array[0];
	temp = temp->next;
	temp->data = 1;
	temp->weight = 3;
	temp = temp->next;
	temp->data = 2;
	temp->weight = 3;

	temp = head_array[1];
	temp = temp->next->next;
	temp->data = 0;
	temp->weight = 3;
	temp = temp->next;
	temp->data = 3;
	temp->weight = 2;

	temp = head_array[2];
	temp = temp->next;
	temp->data = 0;
	temp->weight = 3;
	temp = temp->next->next;
	temp->data = 4;
	temp->weight = 2;

	temp = head_array[3];
	temp = temp->next;
	temp->data = 16;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 17;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 5;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 1;
	temp->weight = 2;

	temp = head_array[4];
	temp = temp->next;
	temp->data = 18;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 19;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 6;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 2;
	temp->weight = 2;

	temp = head_array[5];
	temp = temp->next;
	temp->data = 20;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 6;
	temp->weight = 4;
	temp = temp->next;
	temp->data = 7;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 3;
	temp->weight = 2;

	temp = head_array[6];
	temp = temp->next;
	temp->data = 5;
	temp->weight = 4;
	temp = temp->next;
	temp->data = 21;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 8;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 4;
	temp->weight = 2;

	temp = head_array[7];
	temp = temp->next;
	temp->data = 22;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 23;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 9;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 5;
	temp->weight = 2;

	temp = head_array[8];
	temp = temp->next;
	temp->data = 24;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 25;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 10;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 6;
	temp->weight = 2;

	temp = head_array[9];
	temp = temp->next;
	temp->data = 26;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 10;
	temp->weight = 4;
	temp = temp->next;
	temp->data = 11;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 7;
	temp->weight = 2;

	temp = head_array[10];
	temp = temp->next;
	temp->data = 9;
	temp->weight = 4;
	temp = temp->next;
	temp->data = 27;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 12;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 8;
	temp->weight = 2;

	temp = head_array[11];
	temp = temp->next;
	temp->data = 28;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 29;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 13;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 9;
	temp->weight = 2;

	temp = head_array[12];
	temp = temp->next;
	temp->data = 30;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 31;
	temp->weight = 1;
	temp = temp->next;
	temp->data = 14;
	temp->weight = 2;
	temp = temp->next;
	temp->data = 10;
	temp->weight = 2;

	temp = head_array[13];
	temp = temp->next->next;
	temp->data = 15;
	temp->weight = 3;
	temp = temp->next->next;
	temp->data = 11;
	temp->weight = 2;

	temp = head_array[14];
	temp = temp->next;
	temp->data = 15;
	temp->weight = 3;
	temp = temp->next->next->next;
	temp->data = 12;
	temp->weight = 2;

	temp = head_array[15];
	temp = temp->next;
	temp->data = 13;
	temp->weight = 3;
	temp = temp->next;
	temp->data = 14;
	temp->weight = 3;

	temp = head_array[16];
	temp = temp->next->next;
	temp->data = 3;
	temp->weight = 1;

	temp = head_array[17];
	temp = temp->next;
	temp->data = 3;
	temp->weight = 1;

	temp = head_array[18];
	temp = temp->next->next;
	temp->data = 4;
	temp->weight = 1;

	temp = head_array[19];
	temp = temp->next;
	temp->data = 4;
	temp->weight = 1;

	temp = head_array[20];
	temp = temp->next->next;
	temp->data = 5;
	temp->weight = 1;

	temp = head_array[21];
	temp = temp->next;
	temp->data = 6;
	temp->weight = 1;

	temp = head_array[22];
	temp = temp->next->next;
	temp->data = 7;
	temp->weight = 1;

	temp = head_array[23];
	temp = temp->next;
	temp->data = 7;
	temp->weight = 1;

	temp = head_array[24];
	temp = temp->next->next;
	temp->data = 8;
	temp->weight = 1;

	temp = head_array[25];
	temp = temp->next;
	temp->data = 8;
	temp->weight = 1;

	temp = head_array[26];
	temp = temp->next->next;
	temp->data = 9;
	temp->weight = 1;

	temp = head_array[27];
	temp = temp->next;
	temp->data = 10;
	temp->weight = 1;

	temp = head_array[28];
	temp = temp->next->next;
	temp->data = 11;
	temp->weight = 1;

	temp = head_array[29];
	temp = temp->next;
	temp->data = 11;
	temp->weight = 1;

	temp = head_array[30];
	temp = temp->next->next;
	temp->data = 12;
	temp->weight = 1;

	temp = head_array[31];
	temp = temp->next;
	temp->data = 12;
	temp->weight = 1;

	forward_wls(1);
	dijkstra(g, 0, 18);
	last_node = dest;
	traverse_down(node[0], node[1]);
	if (node[1] == 1)
	{
		right_turn_wls();
	}
	else
	{
		left_turn_wls();
	}
	//forward_wls(1);
	//left_turn_wls();
	for (i = 1; i < m-1; i++)
	{
		traverse_up(node[i], node[i + 1]);
		printf(" Node traversed");
	}
	printf("Loop exit");
	stop();
	_delay_ms(2000);
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 4, 20);
	orientation(node[0], node[1], last_node);
	for (i = 1; i < m-1; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	/*dijkstra(g, 5, 30);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 12, 20); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 5, 22);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 7, 21); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 6, 28);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 11, 21); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 6, 24);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 8, 26);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 9, 19); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 4, 26);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 9, 16); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 3, 27);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	place();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 10, 17); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 3, 15);
	for (i = 1; i < count; i++)
	{
		traverse_up(node[i], node[i + 1]);
	}
	right_turn_wls();
	place();

	dijkstra(g, 15, 25); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	pick();
	mid_sensor = int(ADC_Conversion(2));
	while (mid_sensor != 0)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	while (mid_sensor != 255)
	{
		left();
		mid_sensor = int(ADC_Conversion(2));
	}
	forward_wls(1);

	dijkstra(g, 8, 15); //
	for (i = 1; i < count; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	left_turn_wls();
	place();

	dijkstra(g, 15, 0); //
	for (i = 1; i < count-1; i++)
	{
		traverse_down(node[i], node[i + 1]);
	}
	if (node[i - 1] == 1)
	{
		traverse_down(node[i-1], node[i]);
		left_turn_wls();
	}
	else
	{
		traverse_down(node[i - 1], node[i]);
		right_turn_wls();
	}

	do
	{
		forward();
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));
	} while (left_sensor != 255 && mid_sensor != 255 && right_sensor != 255);*/

	stop();


}
