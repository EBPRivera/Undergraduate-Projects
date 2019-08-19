/* The knapsack problem is stated as follows: given a set of items with
corresponding weights and values, find the optimal combination
of items whose added weights are less than or equal to the total
capacity of the backpack. The total value of all the included items
is the quantity being optimized in this problem.

There are several ways to solve this problem. Two of which are by
using the greedy algorithm and dynamic programming. The greedy
algorithm would depend on which rule is chosen. In this case, we
chose to use the ”largest value first” rule.

Dynamic programming on the other hand is a better way to find
the optimal value. It computes values in a table and uses said values
to arrive at the optimal value. 

The task is to compare the effciency of the Greedy Algorithm
versus Dynamic Programming. The programming language used
to implement both solutions is C. There were 10 test cases with
3 runs each where the average execution time was taken across
those 3 runs. For every test case, each item was generated with
random values for its weight and value. Of course, the weights
were confined within a number range not greater than 100, the
total capacity of the backpack. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//sources: https://www.geeksforgeeks.org/bubble-sort/

void swap(int *xp, int *yp){ //helper function
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}//end function

int max(int a, int b){ //helper function
	if(a > b) return a;
	else return b;
}

int DynamicProgramming(int item_count, int capacity, int w[], int v[]){
	//Initialization of variables.
	int i, j;
	int V[item_count+1][capacity+1];
	
	for(i = 0; i <= item_count; i++){
		for(j = 0; j <= capacity; j++){
			if(j == 0 || i == 0) V[i][j] = 0;
			else if(j - w[i-1] < 0) V[i][j] = V[i-1][j];
			else V[i][j] = max(V[i-1][j], v[i-1] + V[i-1][j-w[i-1]]);
		}
	}

	//Prints the optimal value of the knapsack problem.
	printf("Optimal Value: %d\n", V[item_count][capacity]);
	return V[item_count][capacity];
	
}

int GreedyAlgorithm(int item_count, int capacity, int w[], int v[]){
	//Greedy rule: take item of largest value
	
	int i, j;
	int flag;
	for (i = 0; i < item_count-1; i++){ //bubble sort in descending order
		flag = 0;
		for (j = 0; j < item_count-i-1; j++){
			if (v[j] < v[j+1]){
				swap(&v[j], &v[j+1]);
				swap(&w[j], &w[j+1]);
				flag = 1;
			}
		}
 
		if (flag == 0){
			break;
		}//end if
	}//end for
	
	printf("Sorted item array in descending order.\n");
	for(i=0;i<item_count;i++){
		printf("V: %d W: %d\n", v[i], w[i]);
	}//end for
	
	int cap_ctr = 0; //use to check current weight
	int val_ctr = 0; //use to keep track of current value
	i=0; //use as item_count counter
	int V[item_count]; //array to store included items' values
	int W[item_count]; //array to store included items' weights
	
	printf("\nIncluded items:\n");
	while(i < item_count && cap_ctr < capacity){
		
		if ((cap_ctr+w[i])<=capacity){
			printf("Item number %d: V(%d) W(%d)\n",i,v[i],w[i]);
			cap_ctr = cap_ctr + w[i];
			val_ctr = val_ctr + v[i];
			i=i+1;
		}else{
			i=i+1;
		}//end if
	}//end while
	
	printf("Total value: %d, Total weight: %d\n",val_ctr,cap_ctr);
	return val_ctr;
	
	
}//end function

int main(){
	//Initializations of variables
	int i, j, k;
	int capacity = 100, value;
	time_t start[3];
	time_t end[3];
	float average_time;
	FILE *fp, *fweights;
	
	fp = fopen("Results Data.txt","w");
	fweights = fopen("Weights Data.txt","w");
	
	srand(time(NULL));
	
	//Sets the number of items between 20 and 100 for 10 test cases.
	for(i = 28; i <= 100; i += 8){
		//Writes into the file the number of items;
		fprintf(fp, "---------Number of items: %d---------\n\n", i);
		fprintf(fweights, "---------Number of items: %d---------\n\n", i);
		
		//Initializes the size of weights and values depending on the number of items.
		int w[i];
		int v[i];
		
		//Sets the weights and values for each item.
		for(j = 0; j < i; j++){
			w[j] = rand() % capacity + 1;
			v[j] = rand() % 100 + 1;
			
			//Writes into the file the items and their corresponding weights and values.
			fprintf(fweights,"Item %3i\tWeight: %3i\tValue: %3i\n",j+1, w[j], v[j]);
		}
		fprintf(fweights,"\n");
		
		//Dynamic Programming method.
		printf("\n----------Solving via Dynamic Programming.----------\n\n");
		fprintf(fp, "Solving via Dynamic Programming\t\t");
		average_time = 0;
		for(k = 0; k < 3; k++){
			start[k] = clock();	//Starts the timer for this run.
			
			printf("Run # %d\n", k+1);
			value = DynamicProgramming(i, capacity, w, v);
			
			end[k] = clock();	//Ends the timer for this run.
			average_time += (end[k] - start[k])*1000/CLOCKS_PER_SEC;	//Adds all of the time computed for the 3 runs;
		}
		average_time = average_time/3; //Computes for the average
		printf("This method ran for an average of %.7f milliseconds for %d items\n", average_time, i);
		fprintf(fp, "Optimal Value: %d\tAverage Time: %.7f\n", value, average_time);
		
		//Greedy Algorithm method.
		printf("\n----------Solving via Greedy Algorithm.----------\n\n");
		fprintf(fp, "Solving via Greedy Algorithm\t\t");
		average_time = 0;
		for(k = 0; k < 3; k++){
			start[k] = clock();	//Starts the timer for this run.
			
			value = GreedyAlgorithm(i, capacity, w, v);
			
			end[k] = clock();	//Ends the timer for this run.
			average_time += (end[k] - start[k])*1000/CLOCKS_PER_SEC;	//Adds all of the time computed for the 3 runs;
		}
		average_time = average_time/3;
		printf("This method ran for an average of %.7f milliseconds for %d items\n", average_time, i);
		fprintf(fp, "Optimal Value: %d\tAverage Time: %.7f\n\n", value, average_time);
	}
	
	fclose(fp);
	fclose(fweights);
}