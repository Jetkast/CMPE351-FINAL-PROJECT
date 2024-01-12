#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
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
    int execution_end;
    int in_queue;
    int position;
};

struct resultData{
	string methodName;
	list<processData> processesInfo;
	double averageTime;
};

list<processData> addProcessToQ(list<processData> scProcesses, int etime, int nbreline) {
    list<processData> scNewProcesses{};
    for (auto it = scProcesses.begin(); it != scProcesses.end(); ++it) {
        processData localProcess = *it;
        if (localProcess.in_queue == 0 && localProcess.arrival_time == etime) {
            localProcess.in_queue = 1;
        }
        scNewProcesses.push_back(localProcess);
    }

    return scNewProcesses;
}

list<processData> processExecution(list<processData> eProcesses, int eProcessTE, int nbreline) {
    list<processData> scNewProcesses{};
    int index = 0;
    for (auto it = eProcesses.begin(); it != eProcesses.end(); ++it) {
        processData localProcessPE = *it;

        if (index == eProcessTE && localProcessPE.execution_end == 0) {
            localProcessPE.burst_time = localProcessPE.burst_time - 1;
            if (localProcessPE.burst_time == 0) {
                localProcessPE.execution_end = 1;
            }
        } else if (localProcessPE.in_queue == 1 && localProcessPE.execution_end == 0) {
            localProcessPE.execution_time = localProcessPE.execution_time + 1;
        }
        scNewProcesses.push_back(localProcessPE);
        index++;
    }

    return scNewProcesses;
}

int processChoiceSelection(list<processData> scProcesses, int type, int nbreline) {
    int processSelected = -1;
    int lowestProcess = 0;
    int counter = 0;
    bool boolProcessSelected = false;
    int selectCriteria;

    for (auto it = scProcesses.begin(); it != scProcesses.end(); ++it) {
        processData localProcessPC = *it;

        if (type == 0) {
            selectCriteria = localProcessPC.burst_time;
        } else if (type == 1) {
            selectCriteria = localProcessPC.arrival_time;
        } else {
            selectCriteria = localProcessPC.priority;
        }

        if ((boolProcessSelected == false && localProcessPC.in_queue == 1 && localProcessPC.execution_end == 0) ||
            (boolProcessSelected == true && localProcessPC.in_queue == 1 && localProcessPC.execution_end == 0 && selectCriteria < lowestProcess)) {
            lowestProcess = selectCriteria;
            processSelected = counter;
            boolProcessSelected = true;
        }
        counter++;
    }

    return processSelected;
}

char *file_input = nullptr;
char *file_output = nullptr;

int main(int argc, char *argv[]) {
    int file_count;

    if (argc < 2) {
        cout << "You should introduce 2 arguments";
        exit(0);
    }

    while ((file_count = getopt(argc, argv, "f:o:")) != -1) {
        switch (file_count) {
            case 'f':
                file_input = optarg;
                break;
            case 'o':
                file_output = optarg;
                break;
            default:
                break;
        }
    }

    if (file_input == nullptr || file_output == nullptr) {
        cout << "use the parameter f for input and o for output";
        exit(0);
    }

    int lineNbre = 0;
    int p=0;
    list<resultData> resultInfo{};
    list<processData> fileData{};

    ifstream file(file_input);
    string str;
    while (getline(file, str)) {
        list<string> lineInfo{};
        string delimiter = ":";

        int pos;
        string lineText = str;

        while ((pos = lineText.find(delimiter)) != string::npos) {
            lineInfo.push_back(lineText.substr(0, pos));
            lineText.erase(0, pos + delimiter.length());
        }

        processData infoOfLine = {stoi(lineInfo.front()), stoi(lineInfo.back()), stoi(lineText), 0, 0, 0, p};
        fileData.push_back(infoOfLine);
        lineNbre++; p++;
    }

    list<processData> allProcesses(fileData.begin(), fileData.end());

    while (true) {
        int Select;

        cout << "Cpu scheduler similator" << endl;
        cout << "1. Scheduling method" << endl;
        cout << "2. Preemptive mode" << endl;
        cout << "3. Show result" << endl;
        cout << "4. End program" << endl;
        cout << "Option > " << endl;
        cin >> Select;

        switch (Select) {
            case 1: {
                int selectScheduling;
                cout << "Choose the method" << endl;
                cout << "1. None method Scheduling" << endl;
                cout << "2. First came, First served Scheduling" << endl;
                cout << "3. Short Test Job First Scheduling" << endl;
                cout << "4. Priority Scheduling" << endl;
                cout << "5. Round Robin" << endl;
                cout << "Option > " << endl;
                cin >> selectScheduling;
                string processName;

                switch (selectScheduling) {
                    case 1:
                        cout << "None: none of scheduling method chosen\n";
                        break;

                   case 2: {
                      cout << "First Come, First Served Scheduling\n";

                        bool checkEnd = true;
                        int time = 0;
                        cout << "schedulingNonPreemptive start\n";
                        allProcesses = addProcessToQ(allProcesses, time, lineNbre);
                        processName = "First Come, First Served Scheduling : schedulingNonPreemptive start";
                        while (checkEnd == true) {
                            cout << "in while non Preemp\n";
                            int processesToExecute = processChoiceSelection(allProcesses, 1, lineNbre);
                            if (processesToExecute == -1) {
                                checkEnd = false;
                            } else {
                                auto iterag = allProcesses.begin();
				    std::advance(iterag, processesToExecute);
				    processData localProcessPCE = *iterag;
				    int ff=0;
				    list<processData> scNewProcessesE(allProcesses.begin(), allProcesses.end());
                                while (localProcessPCE.execution_end == 0 && ff<1) {
                                    scNewProcessesE = processExecution(scNewProcessesE, processesToExecute, lineNbre);
                                    auto iterags = scNewProcessesE.begin();
				    std::advance(iterags, processesToExecute);
				    processData localProcessPCESSS = *iterags;
                                    time++;
                                    scNewProcessesE = addProcessToQ(scNewProcessesE, time, lineNbre);
                                    if(localProcessPCESSS.execution_end == 1){
                                    	ff++;
                                    	allProcesses = scNewProcessesE;
                                    }
                                }
                            }
                        }
                        cout << "Scheduling Finish\n";
                        cout << time << "time\n";
                        break;
                    }
                    case 3: {
                        cout << "Shortest-Job-First Scheduling\n";

                        bool checkEnd = true;
                        int time = 0;
                        cout << "schedulingNonPreemptive start\n";
                        processName = "Shortest-Job-First Scheduling : schedulingNonPreemptive start";
                        allProcesses = addProcessToQ(allProcesses, time, lineNbre);
                        while (checkEnd == true) {
                            int processesToExecute = processChoiceSelection(allProcesses, 0, lineNbre);
                            if (processesToExecute == -1) {
                                checkEnd = false;
                            } else {
                                auto iterag = allProcesses.begin();
				    std::advance(iterag, processesToExecute);
				    processData localProcessPCE = *iterag;
				    int ff=0;
				    list<processData> scNewProcessesE(allProcesses.begin(), allProcesses.end());
                                while (localProcessPCE.execution_end == 0 && ff<1) {
                                    scNewProcessesE = processExecution(scNewProcessesE, processesToExecute, lineNbre);
                                    auto iterags = scNewProcessesE.begin();
				    std::advance(iterags, processesToExecute);
				    processData localProcessPCESSS = *iterags;
                                    time++;
                                    scNewProcessesE = addProcessToQ(scNewProcessesE, time, lineNbre);
                                    if(localProcessPCESSS.execution_end == 1){
                                    	ff++;
                                    	allProcesses = scNewProcessesE;
                                    }
                                }
                            }
                        }
                        cout << "Scheduling Finish\n";
                        cout << time << "time\n";
                        break;
                    }
                    case 4: {
                        cout << "Priority Scheduling\n";

                        bool checkEnd = true;
                        int time = 0;
                        cout << "schedulingNonPreemptive start\n";
                        processName = "Priority Scheduling : schedulingNonPreemptive start";
                        allProcesses = addProcessToQ(allProcesses, time, lineNbre);
                        while (checkEnd == true) {
                            int processesToExecute = processChoiceSelection(allProcesses, 2, lineNbre);
                            if (processesToExecute == -1) {
                                checkEnd = false;
                            } else {
                                auto iterag = allProcesses.begin();
				    std::advance(iterag, processesToExecute);
				    processData localProcessPCE = *iterag;
				    int ff=0;
				    list<processData> scNewProcessesE(allProcesses.begin(), allProcesses.end());
                                while (localProcessPCE.execution_end == 0 && ff<1) {
                                    scNewProcessesE = processExecution(scNewProcessesE, processesToExecute, lineNbre);
                                    auto iterags = scNewProcessesE.begin();
				    std::advance(iterags, processesToExecute);
				    processData localProcessPCESSS = *iterags;
                                    time++;
                                    scNewProcessesE = addProcessToQ(scNewProcessesE, time, lineNbre);
                                    if(localProcessPCESSS.execution_end == 1){
                                    	ff++;
                                    	allProcesses = scNewProcessesE;
                                    }
                                }
                            }
                        }
                        cout << "Scheduling Finish\n";
                        cout << time << "time\n";
                        break;
                    }
                    case 5: {
                        cout << "Round-Robin Scheduling\n";
                        cout << "Insert Quantum\n";
                        int quantum;
                        cin >> quantum;
                        bool checkEnd = true;
                        int time = 0;
                        processName = "Round-Robin Scheduling";
                        cout << "schedulingRoundRobin start\n";
                        allProcesses = addProcessToQ(allProcesses, time, lineNbre);
                        int processListSize = lineNbre;
                        int currentProcess = 0;
                        int processesToExecute = processChoiceSelection(allProcesses, 1, lineNbre);
                        while (checkEnd == true) {
                          cout << " Round Robin start\n";
						
						for (int i = 0; i < quantum; i++) {
                                int processesToExecute = processChoiceSelection(allProcesses, 1, lineNbre);
                                if (processesToExecute == -1) {
                                    checkEnd = false;
                                    break;
                                } else{ 
									auto iterag = allProcesses.begin();
									std::advance(iterag, currentProcess);
									processData localProcessPCE = *iterag;
									list<processData> scNewProcessesE(allProcesses.begin(), allProcesses.end());

									if (localProcessPCE.execution_end == 1) {
										break;
									} else {
										
										scNewProcessesE = processExecution(scNewProcessesE, currentProcess, lineNbre);
										auto iterags = scNewProcessesE.begin();
										std::advance(iterags, currentProcess);
										processData localProcessPCESSS = *iterags;
										time++;
										scNewProcessesE = addProcessToQ(scNewProcessesE, time, lineNbre);
										allProcesses = scNewProcessesE;
									}
								}
                            }
                            currentProcess++;
                            if (currentProcess == processListSize) {
                                currentProcess = 0;
                            }
                        }
                        break;
                    }

                    default:
                        cout << "Make a good choice 1 - 5";
                        break;
                }

		cout << "The Result is:\n";
                cout << processName<<endl;
                float average;
                int sum = 0;
                for (auto it = allProcesses.begin(); it != allProcesses.end(); ++it) {
                    sum = sum + it->execution_time;
                }
                average = (sum / lineNbre);

                for (auto it = allProcesses.begin(); it != allProcesses.end(); ++it) {
                    cout << "P" << distance(allProcesses.begin(), it) + 1 << ": " << it->execution_time << "ms \n";
                }

               cout << "Average :" << average << "ms \n";
               resultData infoOfProcess = {processName, allProcesses, average};
               resultInfo.push_back(infoOfProcess);
               allProcesses= fileData;
                break;
            }
            case 2: {
                int preemptiveSchedulingType;
                cout << "Choose Between the Preemptive Scheduling Preemptinve Type \n";
                cout << "1. None\n";
                cout << "2. First Come, First Served Scheduling\n";
                cout << "3. Shortest-Job-First Scheduling\n";
                cout << "4. Priority Scheduling\n";
                cin >> preemptiveSchedulingType;
                string processName;
                switch (preemptiveSchedulingType) {
                    case 1:
                        cout << "None Scheduling method choosen try again \n";
                        break;
                        
                    case 2: {
                        cout << "First Come, First Served Scheduling\n";
                        bool checkEnd = true;
                        int time = 0;
                        cout << "schedulingPreemptive start\n";
                        processName = "First Come, First Served Scheduling : schedulingPreemptive start";
                        while (checkEnd == true) {
                            cout << "in while\n";
                            allProcesses = addProcessToQ(allProcesses, time, lineNbre);

                            int processesToExecute = processChoiceSelection(allProcesses, 1, lineNbre);
                            if (processesToExecute == -1) {
                                cout << "no process to execute\n";
                                checkEnd = false;
                            } else {
                                allProcesses = processExecution(allProcesses, processesToExecute, lineNbre);
                                time++;
                            }
                        }
                        cout << "Scheduling Finish\n";
                        cout << time << "time\n";
                        break;
                    }
                    case 3: {
                        cout << "Shortest-Job-First Scheduling\n";
                        bool checkEnd = true;
                        int time = 0;
                        cout << "schedulingPreemptive start\n";
                        processName = "Shortest-Job-First Scheduling : schedulingPreemptive start";
                        while (checkEnd == true) {
                            allProcesses = addProcessToQ(allProcesses, time, lineNbre);
                            int processesToExecute = processChoiceSelection(allProcesses, 0, lineNbre);
                            if (processesToExecute == -1) {
                                checkEnd = false;
                            } else {
                                allProcesses = processExecution(allProcesses, processesToExecute, lineNbre);
                                time++;
                            }
                        }
                        cout << "Scheduling Finish\n";
                        cout << time << "time\n";
                        break;
                    }

                    case 4: {
                        cout << "Priority Scheduling\n";
                        bool checkEnd = true;
                        int time = 0;
                        cout << "schedulingPreemptive start\n";
                        processName = "Priority Scheduling : schedulingPreemptive start";
                        while (checkEnd == true) {
                            allProcesses = addProcessToQ(allProcesses, time, lineNbre);
                            int processesToExecute = processChoiceSelection(allProcesses, 2, lineNbre);
                            if (processesToExecute == -1) {
                                checkEnd = false;
                            } else {
                                allProcesses = processExecution(allProcesses, processesToExecute, lineNbre);
                                time++;
                            }
                        }
                        cout << "Scheduling Finish\n";
                        cout << time << "time\n";
                        break;
                    }
                    
 
                    default:
                        cout << "you have to choose between 1 - 4";
                        break;
                }
                cout << "The Result is:\n";
                cout << processName<<endl;
                float average;
                int sum = 0;
                for (auto it = allProcesses.begin(); it != allProcesses.end(); ++it) {
                    sum = sum + it->execution_time;
                }
                average = (sum / lineNbre);

                for (auto it = allProcesses.begin(); it != allProcesses.end(); ++it) {
                    cout << "P" << distance(allProcesses.begin(), it) + 1 << ": " << it->execution_time << "ms \n";
                }

               cout << "Average :" << average << "ms \n";
               resultData infoOfProcess = {processName, allProcesses, average};
               resultInfo.push_back(infoOfProcess);
               allProcesses= fileData;
                break;
            }

            case 3: {
                cout << "The Result is:\n";
		for (auto itInfo = resultInfo.begin(); itInfo !=resultInfo.end(); itInfo++){

			cout << itInfo->methodName<<endl;	
			list<processData> processesInfo = itInfo->processesInfo;
			
			for (auto it = processesInfo.begin(); it != processesInfo.end(); ++it) {
                    		cout << "P" << distance(processesInfo.begin(), it) + 1 << ": " << it->execution_time << "ms \n";
                	}
			cout << "Average :" << itInfo->averageTime << "ms \n";
		}
               
                break;
            }
            case 4: {
                cout << "Exit Program, Thank you  \n";
                ofstream file;
                file.open(file_output);
                
                for (auto itInfo = resultInfo.begin(); itInfo !=resultInfo.end(); itInfo++){

			cout << itInfo->methodName<<endl;	
			list<processData> processesInfo = itInfo->processesInfo;
			
			cout << "Processes waiting Time \n";
			file << "Processes waiting Time \n";
			for (auto it = processesInfo.begin(); it != processesInfo.end(); ++it) {
                    		cout << "P" << distance(processesInfo.begin(), it) + 1 << ": " << it->execution_time << "ms \n";
                    		file << "P" << distance(allProcesses.begin(), it) + 1 << ": " << it->execution_time << "ms \n";
                	}
			cout << "Average :" << itInfo->averageTime << "ms \n";
			file << "Average :" << averages << "ms \n";
		}
		file << " \n";
		file.close();
		
                return 0;
            }
            default:
                cout << "Select one of this"<<endl;
                break;
    }
    }
    return 0;
}
