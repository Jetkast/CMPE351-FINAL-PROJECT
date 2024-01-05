#include <vector>
#include <iostream>
#include <iterator>
#include<algorithm>
#include <getopt.h>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct processData {
	int burst_time;
	int arrival_time;
	int priority;
	int execution_time;
	int exectution_end;
	int in_queue;
};

void addProcessToQ(processData *scProcesses, int etime, int nbreline){
	for(int i=0; i<nbreline; i++){
	//	cout<<scProcesses[i].processus[0]<<"\n";
		int *process = scProcesses[i];
		if(scProcesses[i].in_queue==0 && scProcesses[i].arrival_time==etime){
			scProcesses[i].in_queue=1;
			//cout<<i<<" In queue \n";
		}
	}
}

void processExecution(processData *eProcesses, int eProcessTE, int nbreline){
	int counter=0; 
	//cout<<"executionProcess start\n";
	for(int i=0; i<nbreline; i++){
		
		if (i==eProcessTE && eProcesses[i].execution_end==0){
			eProcesses[i].burst_time=eProcesses[i].burst_time-1;
			//cout<<eProcesses[i].burst_time<<"Process \n";
			if(eProcesses[i].burst_time==0){
					eProcesses[i].execution_end=1;
			}
			//cout<<eProcesses[i].execution_end<<"End \n";
		}else if(eProcesses[i].in_queue==1 && eProcesses[i].execution_end==0){
			eProcesses[i].execution_time=eProcesses[i].execution_time+1;
			//cout<<eProcesses[i].execution_time<<"Waiting \n";
		}else{
			
		}
		
		counter++;
	}

}
int processChoiceSelection(processData *scProcesses, int type, int nbreline){
	int processSelected =-1;
	int lowestProcess = 0;
	int counter=0;
	bool boolProcessSelected =false;
	//cout<<"schedulingProcessChoice start\n";
	//cout<<sizeof(scProcesses)<<"\n";
	for(int i=0; i<nbreline; i++){
	//	cout<<scProcesses[i].processus[0]<<"\n";

		
		if((boolProcessSelected==false && scProcesses[i].in_queue==1 && scProcesses[i].execution_end==0) || 
			(boolProcessSelected==true && scProcesses[i].in_queue==1 && scProcesses[i].execution_end==0 && scProcesses[i][type]<lowestProcess))
		{
				lowestProcess=scProcesses[i][type];
				processSelected=counter;
				boolProcessSelected=true;
		}
		counter++;
	}
	//cout<<processSelected<<"selected \n";
	return processSelected;
}

}
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
	int lineNbre=0;
	vector<processData> fileData{};

	std::ifstream file(file_input);
	std::string str;
	while(std::getline(file, str)){
		vector<string> lineInfo{};
		string delimiter=":";

		int pos;
		string lineText=str;
		
		while((pos = lineText.find(delimiter))!= string::npos){
			lineInfo.push_back(lineText.substr(0, pos));
			lineText.erase(0, pos+delimiter.length());
		}
		
		
		processData infoOfLine={{stoi(lineInfo[0]),stoi(lineInfo[1]),stoi(lineText)}};
		fileData.push_back(infoOfLine);
		lineNbre++;
	}
		processData allProcesses[lineNbre];
	int j=0;
	for(const auto &ar: fileData){
		allProcesses[j]=ar;
		j++;
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
				case 1 ://No method
				 cout<<"None: none of scheduling method chosen\n";
				break; 
				
				case 2 ://First C First S 
				bool checkEnd=true;
						int time=0;
						cout<<"schedulingPreemptive start\n";
						while(checkEnd==true){
							addProcessToQ(allProcesses, time, lineNbre);
							int processesToExecute=processChoiceSelection(allProcesses, 1, lineNbre);
							if(processesToExecute==-1){
								checkEnd=false;
							}
							else{
								processExecution(allProcesses, processesToExecute, lineNbre);
								time++;
							}
							
						}
						cout<<"Scheduling Finish\n";
						cout<<time<<"time\n";
				break;
				
				case 3 ://Implement the third fonction
				cout<<"Shortest-Job-First Scheduling\n";
						bool checkEnd=true;
						int time=0;
						cout<<"schedulingPreemptive start\n";
						while(checkEnd==true){
							addProcessToQ(allProcesses, time, lineNbre);
							int processesToExecute=processChoiceSelection(allProcesses, 0, lineNbre);
							if(processesToExecute==-1){
								checkEnd=false;
							}
							else{
								processExecution(allProcesses, processesToExecute, lineNbre);
								time++;
							}
							
						}
						cout<<"Scheduling Finish\n";
						cout<<time<<"time\n";  
				break;
				
				case 4 ://Implement the forth fonction
				cout<<"Priority Scheduling\n";
						bool checkEnd=true;
						int time=0;
						cout<<"schedulingPreemptive start\n";
						while(checkEnd==true){
							addProcessToQ(allProcesses, time, lineNbre);
							int processesToExecute=processChoiceSelection(allProcesses, 2, lineNbre);
							if(processesToExecute==-1){
								checkEnd=false;
							}
							else{
								processExecution(allProcesses, processesToExecute, lineNbre);
								time++;
							}
							
						}
						cout<<"Scheduling Finish\n";
						cout<<time<<"time\n";
						break;
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
