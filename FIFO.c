/*
1. process burst time is inserted in burst_time array in the order in which the arrive.
2. NUMPROCESS is the no. of process in the waiting queue
*/
#include<stdio.h>
#define NUMPROCESS 5

typedef struct process{
	int waiting_time;
	int burst_time;
	int turnaround_time;
} Process;

void FIFO(int[]);
void setDefaultOfProcess(Process[], int[]);
float avg_waiting_time(Process[]);
void displayStatistics(Process[]);
int main(){
	int burst_time[] = {3,7,9,3,24};
	FIFO(burst_time);
	return 0;
}

void FIFO(int burst_time[]){
	Process p[NUMPROCESS];
	setDefaultOfProcess(p,burst_time);
	int clock = 0;
	int i, j;
	for(i = 0; i < NUMPROCESS; i++){
		while(p[i].burst_time){
			p[i].burst_time--;
			clock++;
			for(j = 0; j < NUMPROCESS; j++){
				if(i < j){ // checks to increase waiting time of already done process
					p[j].waiting_time++;
				}
			}
		}
	}
	printf("Average waiting time = %f units", avg_waiting_time(p));
	printf("\nTotal time taken= %d units", clock);
	displayStatistics(p);
}

void setDefaultOfProcess(Process p[], int burst_time[]){
	int i;
	for(i = 0; i < NUMPROCESS; i++){
		p[i].waiting_time = 0;
		p[i].burst_time = p[i].turnaround_time = burst_time[i];
	}
}

float avg_waiting_time(Process p[]){
	int i;
	float sum = 0.0;
	for(i = 0; i < NUMPROCESS; i++){
		sum += p[i].waiting_time;
		 p[i].turnaround_time += p[i].waiting_time; //not related to avg time. computing turnaround time here for saving another loop
	}
	return sum/NUMPROCESS;
}

void displayStatistics(Process p[]){
	int i;
	printf("\n\nProcess | Waiting Time  | Turnaround Time");
	printf("\n-----------------------------------------");
	for(i = 0; i < NUMPROCESS; i++){
		printf("\nP%d\t|\t%d\t|\t%d", i+1, p[i].waiting_time, p[i].turnaround_time);
	}
}
