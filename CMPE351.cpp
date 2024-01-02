#include <iostream>
#include <iterator>
#include<algorithm>
#include <getopt.h>
#include <iomanip>
using namespace std;

struct processData {
	int burst_time;
	int arrival_time;
	int priority;
};

char *file_input=NULL;
char *file_output=NULL;
  
int main (int argc, char *argv[]){
    int file_count;

	if(argc<2){
		cout<<"You should introduce 2 arguments";
		exit(0);
	}
	
	while((file_count = getopt(argc, argv, "f:o:")) != -1){
		switch (file_count){
			case 'f':
				file_input=optarg;
				break;
			case 'o':
				file_output=optarg;
				break;
			default:
				break;
		}
	}
	if(file_input==NULL || file_output==NULL){
		cout<<"use the parameter f for input and o for output";
		exit(0);
	}
	
	
	while (true){
		
		int Select;
		
		cout<<"Cpu scheduler similator";
		cout<<"1. Scheduling method";
		cout<<"2. Preemptive mode";
		cout<<"3. Show result";
		cout<<"4. End program";
		cout<<"Option > ";
		cin>>Select;
		
		switch (Select){
			case 1 : int selectScheduling;
			cout<<"Choose the method";
			cout<<"1. None method Scheduling";
			cout<<"2. First came , First served Scheduling";
			cout<<"3. Short Test Job First Scheduling";
			cout<<"4. Priority Scheduling";
			cout<<"5. Round Robin";
			cout<<"Option > ";
			cin>>selectScheduling;
			
			switch (selectScheduling){
				case 1 ://Implement the first fonction 
				break; 
				
				case 2 ://Implement the second fonction 
				break;
				
				case 3 ://Implement the third fonction 
				break;
				
				case 4 ://Implement the forth fonction 
				break;
				
				case 5 ://Implement the fifth fonction 
				break;
				
				default:cout<<"Make a good choice";
				break;
			}
			break;
			
			case 2 : //Preemptive mode
			break;
			
			case 3 : //Show result 
			break;
			
			case 4 : cout<<"Exit the program";
			return 0 ;
			break;
			
			default : cout<<"Select one of this ";
			break;
			
			
		}
	}
	return 0;
}
