#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


int pro1[] = { 4, 15, 5, 31, 6, 26, 7, 24, 6, 41, 4, 51, 5, 16, 4 };
int pro2[] = { 9, 28, 11, 22, 15, 21, 12, 28, 8, 34, 11, 34, 9, 29, 10, 31, 7 };
int pro3[] = { 24, 28, 12, 21, 6, 27, 17, 21, 11, 54, 22, 31, 18 };
int pro4[] = { 15, 35, 14, 41, 16, 45, 18, 51, 14, 61, 13, 54, 16, 61, 15 };
int pro5[] = { 6, 22, 5, 21, 15, 31, 4, 26, 7, 31, 4, 18, 6, 21, 10, 33, 3 };
int pro6[] = { 22, 38, 27, 41, 25, 29, 11, 26, 19, 32, 18, 22, 6, 26, 6 };
int pro7[] = { 4, 36, 7, 31, 6, 32, 5, 41, 4, 42, 7, 39, 6, 33, 5, 34, 6, 21, 9 };
int pro8[] = { 5, 14, 4, 33, 6, 31, 4, 31, 6, 27, 5, 21, 4, 19, 6, 11, 6 };


typedef struct node {
	int data;
	node *next;
}*nodePtr;

class List {
private: 
	nodePtr head;
	nodePtr curr;
	nodePtr temp;
	string name;
	int response, taround, wtime;
	int first, fclock, priority;

public:
	List() {
		head = curr = temp = NULL;
		first = 0;
		wtime = 0;
		priority = 1;
	}

	void AddNode(int addData) {
		nodePtr n = new node;
		n->next = NULL;
		n->data = addData;

		if (head != NULL) {
			curr = head;
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = n;
		}
		else {
			head = n;
		}
	}

	void CreateL(string pname, int processes[], int arraySize) {
		for (int i = 0; i < arraySize; i++) {
			AddNode(processes[i]);
		}
		name = pname;
	}

	void CreateIdle() {
		AddNode(-1);
		name = "Idle";
	}

	void DeleteFront() {
		temp = head;
		head = head->next;
	}

	int GetFirst() {
		return head->data;
	}

	string GetName() {
		return name;
	}

	bool CheckFinal() {
		if (head->next == NULL) {
			return true;
		}
		return false;
	}

	void DecrementList() {
		head->data--;
	}

	void Response(int clock){
		if (first == 0 && clock != 0 && name != "P1") {
			first = clock;
		}
	}

	void SetFClock(int clock) {
		fclock = clock;
	}

	int GetTurn() {
		return fclock;
	}

	int GetResponse() {
		return first;
	}

	void AddWait() {
		wtime++;
	}

	int GetBurst() {
		return wtime;
	}

	int GetPriority() {
		return priority;
	}

	void SetPriority(int p) {
		priority = p;
	}
	
};

void InitializeQue(vector<List> & ready_que, List p2, List p3, List p4 , List p5 , List p6 , List p7 , List p8) {
	ready_que.push_back(p2);
	ready_que.push_back(p3);
	ready_que.push_back(p4);
	ready_que.push_back(p5);
	ready_que.push_back(p6);
	ready_que.push_back(p7);
	ready_que.push_back(p8);
}

double RAverage(vector<List> finished) {
	double average = 0;
	for (int i = 0; i < finished.size(); i++) {
		average += finished[i].GetResponse();
	}
	average = average / finished.size();
	return average;
}

double TAverage(vector<List> finished) {
	double average = 0;
	for (int i = 0; i < finished.size(); i++) {
		average += finished[i].GetTurn();
	}
	average = average / finished.size();
	return average;
}

double WAverage(vector<List> finished) {
	double average = 0;
	for (int i = 0; i < finished.size(); i++) {
		average += finished[i].GetBurst();
	}
	average = average / finished.size();
	return average;
}

bool Sort(List & l, List & r) { //sorts the vector to display the info at the end in ascending response time p1-p8
	return l.GetResponse() < r.GetResponse();
}

void NewProcess(int clock, List current, vector<List> q1, vector<List> q2, vector<List> q3, vector<List> io, vector<List> finished) {
	cout << "Current Time: " << clock << endl << endl;
	cout << "Now running: " << current.GetName() << endl << "......................................" << endl;
	cout << "Ready Queue:  Process     Burst     Priority" << endl;

	if (q1.size() == 0 && q2.size() == 0 && q3.size() == 0) { //runs if all queues are empty
		cout << "              [empty]" << endl;
		cout << "......................................" << endl << endl;
	}
	else { //otherwise prints each queue in order of priority
		if (q1.size() != 0) {
			
			for (int i = 0; i < q1.size(); i++) {
				cout << "              " << q1[i].GetName() << "          " << q1[i].GetFirst() << "          " << q1[i].GetPriority() << endl;
			}
		}

		if (q2.size() != 0) {
			
			for (int i = 0; i < q2.size(); i++) {
				cout << "              " << q2[i].GetName() << "          " << q2[i].GetFirst() << "          " << q2[i].GetPriority() << endl;
			}
		}

		if (q3.size() != 0) {
			
			for (int i = 0; i < q3.size(); i++) {
				cout << "              " << q3[i].GetName() << "          " << q3[i].GetFirst() << "          " << q3[i].GetPriority() << endl;
			}
		}
		cout << "......................................" << endl << endl;
	}
	
	if (io.size() == 0) {
		cout << "Now in I/O:     Process     Remaining I/O time" << endl;
		cout << "                [empty]" << endl << endl;
		cout << "......................................" << endl << "......................................" << endl << endl << endl;
	}
	else {
		cout << "Now in I/O:     Process     Remaining I/O time" << endl;
		for (int i = 0; i < io.size(); i++) {
			cout << "                " << io[i].GetName() << "          " << io[i].GetFirst() << endl;
		}
		cout << endl << "......................................" << endl << "......................................" << endl << endl << endl;
	}

	if (finished.size() != 0) {
		cout << "Completed:      ";
		for (int i = 0; i < finished.size(); i++) {
			cout << finished[i].GetName() << "   ";
		}
		cout << endl << endl << "......................................" << endl << endl << endl << endl;
	}
}

void Finished(int clock, int idlec, vector<List> finished) {
	double cutil = clock - idlec;
	cutil = cutil / clock * 100;
	cout << endl << endl << "Good Job ;)" << endl << endl;
	cout << "Total Time: " << clock << endl;
	cout << "CPU Uitilization: " << cutil << "%" << endl << endl;

	cout << "Waiting Times       P1   P2   P3   P4   P5   P6   P7   P8" << endl;
	cout << "                    ";
	for (int i = 0; i < finished.size(); i++) {
		cout << finished[i].GetBurst() << "  ";
	}
	cout << endl << "Average Wait:      " << WAverage(finished) << endl << endl;

	cout << "Turnaround Times    P1   P2   P3   P4   P5   P6   P7   P8" << endl;
	cout << "                    ";
	for (int i = 0; i < finished.size(); i++) {
		cout << finished[i].GetTurn() << "  ";
	}
	cout << endl << "Average Turnaround: " << TAverage(finished) << endl << endl;

	cout << "Response Times     P1   P2   P3   P4   P5   P6   P7   P8" << endl;
	cout << "                    ";
	for (int i = 0; i < finished.size(); i++) {
		cout << finished[i].GetResponse() << "   ";
	}
	cout << endl << "Average Response:  " << RAverage(finished) << endl << endl << endl << endl;
}

int main() {
	List p1, p2, p3, p4, p5, p6, p7, p8, current, idle;
	vector<List> pQue1, pQue2, pQue3, ioQue, finished;
	bool first = true;
	int idlec = 0, clock = 0, pclock = 0;

	p1.CreateL("P1", pro1, sizeof(pro1) / sizeof(int));
	p2.CreateL("P2", pro2, sizeof(pro2) / sizeof(int));
	p3.CreateL("P3", pro3, sizeof(pro3) / sizeof(int));
	p4.CreateL("P4", pro4, sizeof(pro4) / sizeof(int));
	p5.CreateL("P5", pro5, sizeof(pro5) / sizeof(int));
	p6.CreateL("P6", pro6, sizeof(pro6) / sizeof(int));
	p7.CreateL("P7", pro7, sizeof(pro7) / sizeof(int));
	p8.CreateL("P8", pro8, sizeof(pro8) / sizeof(int));
	idle.CreateIdle();
	InitializeQue(pQue1, p2, p3, p4, p5, p6, p7, p8);
	current = p1;

	do {

		//checks if burst is done
		if (current.GetFirst() == 0) {
			pclock = 0;
			first = !first;

			//check if burst is on its last cycle
			if (current.CheckFinal()) {
				current.SetFClock(clock); //sets the turnaround time for the process
				finished.push_back(current); //moves process to the finished vector
				sort(finished.begin(), finished.end(), Sort); //sorts finished vector by ascending respone time p1-p8

				if (pQue1.size() != 0) { //checks if que1 has elements
					current = pQue1[0];
					pQue1.erase(pQue1.begin());
				}

				else if (pQue2.size() != 0) { //else checks if que2 has elements
					current = pQue2[0];
					pQue2.erase(pQue2.begin());
				}

				else if (pQue3.size() != 0) { //else checks if que3 has elements
					current = pQue3[0];
					pQue3.erase(pQue3.begin());
				}

				else {			//else sets current to idle when all queues are empty
					current = idle;
				}
			}

			//otherwise pushed to I/O
			else {
				pclock = 0;
				current.DeleteFront(); //moves to I/O node
				ioQue.push_back(current); //pushes process to the I/O queue

				if (pQue1.size() != 0) { //checks if que1 has elements
					current = pQue1[0]; //assigns current process
					pQue1.erase(pQue1.begin()); //deletes process from queue
				}

				else if (pQue2.size() != 0) { //else checks if que2 has elements
					current = pQue2[0]; //assigns current process
					pQue2.erase(pQue2.begin()); //deletes process from queue
				}

				else if (pQue3.size() != 0) { //else checks if que3 has elements
					current = pQue3[0]; //assigns current process
					pQue3.erase(pQue3.begin()); //deletes process from queue
				}

				else {			//else sets current to idle when all queues are empty
					current = idle;
				}
			}
		}

		//checks if priority 1 is available from IO over any lower priority
		else if ((current.GetPriority() == 2 || current.GetPriority() == 3) && pQue1.size() != 0) {
			first = !first;
			pclock = 0;
			if (current.GetPriority() == 2) {
				pQue2.push_back(current); //pushes current process back into queue2
				cout << current.GetName() << " is priority: " << current.GetPriority() << endl;
				current = pQue1[0]; //assigns current to new priority1
				pQue1.erase(pQue1.begin()); //erases current from queue
				cout << current.GetName() << " just jumped ahead because it has priority: " << current.GetPriority() << endl;
			}
			else {
				pQue3.push_back(current); //pushes current proccess back into queue3
				cout << current.GetName() << " is priority: " << current.GetPriority() << endl;
				current = pQue1[0]; //assigns current to new priority1
				pQue1.erase(pQue1.begin()); //erases current from queue
				cout << current.GetName() << " just jumped ahead because it has priority: " << current.GetPriority() << endl;
			}
		}

		//otherwise checks if priority 2 is available from IO for a p3 currently running
		else if (current.GetPriority() == 3 && pQue2.size() != 0) {
			first = !first;
			pclock = 0;
			pQue3.push_back(current); //pushes current proccess back into queue 3
			cout << current.GetName() << " is priority: " << current.GetPriority() << endl;
			current = pQue2[0]; //assigns current to new priority 2
			pQue2.erase(pQue2.begin()); //erases current from queue
			cout << current.GetName() << " just jumped ahead because it has priority: " << current.GetPriority() << endl;
		}

		//checks if current process is idle
		else if (current.GetFirst() == -1 && (pQue1.size() != 0 || pQue2.size() != 0 || pQue3.size() != 0)) {
			first = !first;
			if (pQue1.size() != 0) {
				current = pQue1[0];
				pQue1.erase(pQue1.begin());
			}
			else if (pQue2.size() != 0) {
				current = pQue2[0];
				pQue2.erase(pQue2.begin());
			}
			else {
				current = pQue3[0];
				pQue3.erase(pQue3.begin());
			}
		}

		//runs clock, handles priority assigtnment, checks IO times and handles idle
		else {
			current.Response(clock); //assigns response time on first cycle
			if (current.GetPriority() == 1 && pclock == 6) { //sets priority to 2
				cout << current.GetName() << " is being switched to next priority from tq: " << pclock << endl;
				pclock = 0; //resets time quantum
				first = !first; //switches to print new process
				current.SetPriority(2); //assigns new priority
				cout << "New priority: " << current.GetPriority() << endl;
				pQue2.push_back(current); //pushes process to end of new priority 2 queue

				if (pQue1.size() != 0) { //checks if any processes in current priority
					current = pQue1[0];
					pQue1.erase(pQue1.begin());
				}

				else if (pQue2.size() != 0) { //checks if any proccesses in next priority
					current = pQue2[0];
					pQue2.erase(pQue2.begin());
				}

				else if (pQue3.size() != 0) { //checks if any proccesses in next priority
					current = pQue3[0];
					pQue3.erase(pQue3.begin());
				}

				else { //if all queues are empty idle is assigned
					current = idle;
				}
			}

			else if (current.GetPriority() == 2 && pclock == 12) { //sets priority to 3
				cout << current.GetName() << " is being switched to next priority from tq: " << pclock << endl;
				pclock = 0; //resets time quantum
				first = !first; //switches to print new process
				current.SetPriority(3); //assigns new priority
				pQue3.push_back(current); //pushes process to end of new priority 3 queue

				if (pQue2.size() != 0) { //checks if any processes in current priority
					current = pQue2[0];
					pQue2.erase(pQue2.begin());
				}

				else if (pQue3.size() != 0) { //checks if any proccesses in next priority
					current = pQue3[0];
					pQue3.erase(pQue3.begin());
				}

				else { //if all queues are empty idle is assigned
					current = idle;
				}

			}

			else { //runs if time quantum is not up or priority is 3

				if (first) { //if the process is just added to current then the information will be displayed
					NewProcess(clock, current, pQue1, pQue2, pQue3, ioQue, finished);
					first = !first; //switch to keep the information from printing every loop
				}

				if (current.GetFirst() != -1) { //run one cycles of process when not idle
					current.DecrementList();
				}
				else { //run one cycle of idle
					idlec++;
				}

				if (pQue1.size() != 0) {
					for (int i = 0; i < pQue1.size(); i++) {//increments wait time of each item in queue1
						pQue1[i].AddWait();
					}
				}
				if (pQue2.size() != 0) {
					for (int i = 0; i < pQue2.size(); i++) {//increments wait time of each item in queue2
						pQue2[i].AddWait();
					}
				}
				if (pQue3.size() != 0) {
					for (int i = 0; i < pQue3.size(); i++) {//increments wait time of each item in queue3
						pQue3[i].AddWait();
					}
				}

				if (ioQue.size() != 0) {

					for (int j = 0; j < ioQue.size(); j++) {
						ioQue[j].DecrementList(); //decrements each item in the IO que

						if (ioQue[j].GetFirst() == 0) { //if a process IO is 0 delete front node, push back into correct priority queue
							ioQue[j].DeleteFront();

							if (ioQue[j].GetPriority() == 1) { //checks if priority 1 and pushes back into queue1
								pQue1.push_back(ioQue[j]);
								ioQue.erase(ioQue.begin() + j);
								j--;
							}

							else if (ioQue[j].GetPriority() == 2) { //checks if priority 2 and pushes back into queue2
								pQue2.push_back(ioQue[j]);
								ioQue.erase(ioQue.begin() + j);
								j--;
							}

							else { //pushes into queue 3
								pQue3.push_back(ioQue[j]);
								ioQue.erase(ioQue.begin() + j);
								j--;
							}
						}

					}
				}

				clock++;
				pclock++;

				if (current.GetPriority() == 3 || current.GetFirst() == -1) { //resets time quantum when idle or p3 are running
					pclock = 0;
				}
			}
		}

	} while (pQue1.size() != 0 || pQue2.size() != 0 || pQue3.size() != 0 || ioQue.size() != 0 || current.GetFirst() != -1);

	NewProcess(clock, current, pQue1, pQue2, pQue3, ioQue, finished); //shows that last process has finished
	Finished(clock, idlec, finished); //prints stats on ttime, wtime, rtimem cpu util
}