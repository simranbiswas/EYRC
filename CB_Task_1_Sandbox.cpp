//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions

#include "CB_Task_1_Sandbox.h"
#define V 33
#define FLOAT_MAX 35

int left_sensor, right_sensor, mid_sensor;
int speed, lvalue, rvalue;
double proportional, integral = 0, lastproportional = 0, derivative;
float kp = 98, ki = 96.1, kd = 4;
int path[7][8], selected_path_nodes[10];

void pid(double pos)
{
	proportional = pos - 1000;
	derivative = proportional - lastproportional;
	integral = integral + proportional;
	lastproportional = proportional;
	speed = (int)((proportional * kp) + (integral * ki) + (derivative * kd));
	if (speed < -100)
	{
		speed = -100;
	}
	else if (speed > 100)
	{
		speed = 100;
	}
	if (speed < 0)
	{
		forward();
		velocity(speed + 100, 100);

	}
	else
	{
		forward();
		velocity(100, 100 - speed);


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
	int checknode = int(node), i = 1;
	while (i <= checknode)
	{
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));
		//Goes forward when black line is senses by the middle sensor and also when left and right sensor senses black line and middle sensor senses white line
		if ((left_sensor == 0 && right_sensor == 0 && mid_sensor > 0) || (left_sensor > 0 && right_sensor > 0 && mid_sensor == 0))
		{
			forward();
			velocity(100, 100);
		}
		//Goes left if the bot is deflected towards left
		else if ((left_sensor ==255  && right_sensor == 0 && mid_sensor == 0) || (left_sensor ==255 && right_sensor == 0 && mid_sensor ==255))
		{
			printf("\nLEFT");
			lvalue = 1;
			rvalue = 0;
			do {
				pid(0);

				left_sensor = int(ADC_Conversion(1));
				right_sensor = int(ADC_Conversion(3));
				mid_sensor = int(ADC_Conversion(2));
				if ((left_sensor ==255 && right_sensor ==255 && mid_sensor > 0) || (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0))
				{
					break;
				}
			} while (left_sensor==255);
			//forward();

			printf("\n%d,%d,%d", left_sensor, mid_sensor, right_sensor);


		}
		//Goes right if the bot is deflected towards right
		else if ((left_sensor == 0 && right_sensor==255 && mid_sensor == 0) || (left_sensor == 0 && right_sensor ==255 && mid_sensor ==255))
		{
			printf("\nRIGHT");
			rvalue = 1;
			lvalue = 0;
			do {
				pid(2000);

				left_sensor = int(ADC_Conversion(1));
				right_sensor = int(ADC_Conversion(3));
				mid_sensor = int(ADC_Conversion(2));
				if ((left_sensor ==255 && right_sensor ==255 && mid_sensor ==255) || (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0))
				{
					break;
				}

			} while (right_sensor==255);
			stop();
			printf("\n%d,%d,%d", left_sensor, mid_sensor, right_sensor);
			//_delay_ms(1000);

		}
		//Node is detected
		else if (left_sensor ==255 && right_sensor ==255 && mid_sensor ==255)
		{
			i++;
			printf("\nnode detected");
			do {
				forward();
				velocity(100, 100);
				left_sensor = int(ADC_Conversion(1));
				right_sensor = int(ADC_Conversion(3));
				mid_sensor = int(ADC_Conversion(2));

			} while (left_sensor != 0 && right_sensor != 0);

		//was continue here
			break;

		}
		//When left sensor,middle sensor,right sensor senses white line
		else if (left_sensor == 0 && right_sensor == 0 && mid_sensor == 0)
		{
			if (lvalue == 1)
			{
				//forward();
				velocity(0, 10);
				left();
				rvalue = 0;
				lvalue = 0;
			}
			if (rvalue == 1)
			{
				//forward();
				velocity(10, 0);
				right();
				rvalue = 0;
				lvalue = 0;

			}

		}
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
	left_sensor = int(ADC_Conversion(1));
	right_sensor = int(ADC_Conversion(3));
	mid_sensor = int(ADC_Conversion(2));
	while (left_sensor != 255)
	{
		left();
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));
	}
	
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
	while (right_sensor != 255)
	{
		right();
		left_sensor = int(ADC_Conversion(1));
		right_sensor = int(ADC_Conversion(3));
		mid_sensor = int(ADC_Conversion(2));
	} 
}

int minDistance(float dist[], bool sptSet[])
{
	// Initialize min value 
	float min = FLOAT_MAX;
	int	min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}
void dijkstra(float graph[V][V], int src)
{
	float dist[V];

	bool sptSet[V];
	for (int i = 0; i < V; i++)
		dist[i] = FLOAT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0 
	dist[src] = 0.0;

	// Find shortest path for all vertices 
	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < V; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != FLOAT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
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

								//   1    2    3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26 27  28  29  30  31  32  33	
	float graph[V][V] = { {0.0,0.65,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.65},  //1
									{0.65,0.0,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},	//2
									{0.0,0.3,0.0,0.28,0.27,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //3
									{0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //4
									{0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //5
									{0.0,0.0,0.3,0.0,0.0,0.0,0.27,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //6
									{0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //7
									{0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.27,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //8
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //9
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//10
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.0,0.27,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//11
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//12
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.27,0.28,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//13
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//14
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//15
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.0,0.68,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//16
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.68,0.0,0.1794,0.685,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//17
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.1794,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//18
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.685,0.0,0.0,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//19
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.27,0.28,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, //20
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//21
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//22
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.0,0.28,0.3,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//23
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//24
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.27,0.28,0.3,0.0,0.0,0.0,0.0,0.0},//25
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//26
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},//27
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.0,0.28,0.3,0.0,0.0,0.0},//28
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0,0.0,0.0},//29
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.28,0.27,0.65}, //30
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.28,0.0,0.0,0.0},//31
									{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.27,0.0,0.0,0.0},//32
									{0.65,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.3,0.0,0.0,0.0}, };//33

	dijkstra(graph, 0);
	forward_wls(1);
//	stop();
	printf("\nTake 1st Right");
	right_turn_wls();
	forward_wls(1);
//	stop();
	
	printf("\nTake 2nd Right");
	right_turn_wls();
	forward_wls(1);
//	stop();
	
	printf("\nTake Left");
	left_turn_wls();
	forward_wls(1);
	_delay_ms(1000);
	pick();
	//_delay_ms(2000);
//	stop();
	
//	printf("\nGo to pickup point");
	
	
//	stop();

	
}
