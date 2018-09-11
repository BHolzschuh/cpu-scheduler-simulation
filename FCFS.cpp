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
	int first, fclock;

public:
	List() { //constructor for the object
		head = curr = temp = NULL;
		first = 0;
		wtime = 0;
	}

	void AddNode(int addData) { //adds each node to the list
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

	void CreateL(string pname, int processes[], int arraySize) { //reads an array to create a linked list
		for (int i = 0; i < arraySize; i++) {
			AddNode(processes[i]);
		}
		name = pname;
	}

	void CreateIdle() { //creates an idle object
		AddNode(-1);
		name = "Idle";
	}

	void DeleteFront() { //deletes the front node, assigns head to the next node
		temp = head;
		head = head->next;
	}

	int GetFirst() { //returns data in the first node
		return head->data;
	}

	string GetName() { //returns name of the object
		return name;
	}

	bool CheckFinal() { //checks to see if its the last node
		if (head->next == NULL) {
			return true;
		}
		return false;
	}
	void DecrementList() {//decrements the data in the first node
		head->data--;
	}

	void Response(int clock){ //sets the response time, p1 is always 0
		if (first == 0 && clock != 0 && name != "P1") {
			first = clock;
		}
	}

	void SetFClock(int clock) { //assigns the turnaround time
		fclock = clock;
	}

	int GetTurn() { //getter
		return fclock;
	}

	int GetResponse() { //getter
		return first;
	}

	void AddWait() { //increments the wait time of processes in the rque
		wtime++;
	}

	int GetWait() { //getter
		return wtime;
	}
	
};

//initializes the ready queue vector
void InitializeQue(vector<List> & ready_que, List p2, List p3, List p4 , List p5 , List p6 , List p7 , List p8) {
	ready_que.push_back(p2);
	ready_que.push_back(p3);
	ready_que.push_back(p4);
	ready_que.push_back(p5);
	ready_que.push_back(p6);
	ready_que.push_back(p7);
	ready_que.push_back(p8);
}

double RAverage(vector<List> finished) { //calculates response time average
	double average = 0;
	for (int i = 0; i < finished.size(); i++) {
		average += finished[i].GetResponse();
	}
	average = average / finished.size();
	return average;
}

double TAverage(vector<List> finished) { //calculates turnaround time average
	double average = 0;
	for (int i = 0; i < finished.size(); i++) {
		average += finished[i].GetTurn();
	}
	average = average / finished.size();
	return average;
}

double WAverage(vector<List> finished) { //calculates wait time average
	double average = 0;
	for (int i = 0; i < finished.size(); i++) {
		average += finished[i].GetWait();
	}
	average = average / finished.size();
	return average;
}

bool Sort(List & l, List & r) { //sorts the vector to display the info at the end in ascending response time p1-p8
	return l.GetResponse() < r.GetResponse();
}

int main() {
	List p1, p2, p3, p4, p5, p6, p7, p8, current, idle;
	vector<List> rQue, ioQue, finished;
	bool first = true;
	int idlec = 0, clock = 0;
	
	p1.CreateL("P1", pro1, sizeof(pro1) / sizeof(int));
	p2.CreateL("P2", pro2, sizeof(pro2) / sizeof(int));
	p3.CreateL("P3", pro3, sizeof(pro3) / sizeof(int));
	p4.CreateL("P4", pro4, sizeof(pro4) / sizeof(int));
	p5.CreateL("P5", pro5, sizeof(pro5) / sizeof(int));
	p6.CreateL("P6", pro6, sizeof(pro6) / sizeof(int));
	p7.CreateL("P7", pro7, sizeof(pro7) / sizeof(int));
	p8.CreateL("P8", pro8, sizeof(pro8) / sizeof(int));
	idle.CreateIdle();
	InitializeQue(rQue, p2, p3, p4, p5, p6, p7, p8);
	current = p1;
	p1.Response(clock);

	do {

	//checks if the process burst is complete
	if (current.GetFirst() == 0) {
		first = !first;
		//if the process is on its last burst it will be deleted
		if (current.CheckFinal()) {
			current.SetFClock(clock); //sets the turnaround time
			finished.push_back(current); //moves the process to the finished vector
			sort(finished.begin(), finished.end(), Sort); //sorts based on responsetime p1-p8
			//checks if rque is empty
			if (rQue.size() == 0) {
				current = idle; //if no processes are ready then current process is idle
			}
			else { //the next process in the ready queue is assigned the current process
				current = rQue[0];
				rQue.erase(rQue.begin());
			}

		}
		//otherwise it is pushed to I/O
		else {
			//checks if rque is empty
			if (rQue.size() == 0) {
				current.DeleteFront();
				ioQue.push_back(current);
				current = idle;
			}
			else { //if rque is not empty current is eqal to the first object in the vector
				current.DeleteFront();
				ioQue.push_back(current);
				current = rQue[0];
				current.Response(clock); //assigns response time on the first cycle
				rQue.erase(rQue.begin());
			}
		}
	}

	//runs if the process burst is not complete
	else {

		if (first) { //prints all necessary information about a new process executing
			cout << "Current Time: " << clock << endl << endl;
			cout << "Now running: " << current.GetName() << endl << "......................................" << endl;
			cout << "Ready Queue:  Process     Burst" << endl;

			if (rQue.size() == 0) {
				cout << "              [empty]" << endl;
				cout << "......................................" << endl << endl;
			}
			else {
				for (int i = 0; i < rQue.size(); i++) {
					cout << "              " << rQue[i].GetName() << "          " << rQue[i].GetFirst() << endl;
				}
				cout << "......................................" << endl << endl;
			}

			if (ioQue.size() == 0) {
				cout << "Now in I/O:     Process     Remaining I/O time" << endl;
				cout << "                [empty]" << endl << endl;
				cout << "......................................" << endl << "......................................" << endl << endl << endl;
			}
			else {
				cout << "Now in I/O:     Process     Remaining I/O time" << endl;
				for (int i = 0; i < ioQue.size(); i++) {
					cout << "                " << ioQue[i].GetName() << "          " << ioQue[i].GetFirst() << endl;
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

			first = !first; //switch to keep information from printing every loop
		}
		if (current.GetFirst() != -1) {
			current.DecrementList(); //run one cycle of burst process except for idle
		}
		if (rQue.size() != 0) { //increments wait time for each process in the ready queue
			for (int i = 0; i < rQue.size(); i++) {
				rQue[i].AddWait();
			}
		}
		if (ioQue.size() != 0) {
			for (int j = 0; j < ioQue.size(); j++) {
				ioQue[j].DecrementList(); //decrements each item in the IO que

				if (ioQue[j].GetFirst() == 0) { //if a process IO is 0 delete io vector value, pushed back onto the readyque
					ioQue[j].DeleteFront(); 
					rQue.push_back(ioQue[j]);
					ioQue.erase(ioQue.begin() + j);
					j--;
				}
			}
		}

		if (current.GetFirst() == -1 && rQue.size() != 0) { //assigns the rque object to the current process
			first = !first;
			current = rQue[0];
			rQue.erase(rQue.begin());
		}
		else if (current.GetFirst() == -1 && rQue.size() == 0) { //increments idle time
			idlec++;
		}

		clock++;

	}
	} while (rQue.size() != 0 || ioQue.size() != 0 || current.GetFirst() != -1); 
	//as long as there is an object in rque or ioque or the current process is not idle then the loop will continue


	//outputs all information after simulation executes
	cout << "Current Time: " << clock << endl << endl;
	cout << "Now running: " << current.GetName() << endl << "......................................" << endl;
	cout << "Ready Queue:  Process     Burst" << endl;
	cout << "              [empty]" << endl;
	cout << "......................................" << endl << endl;
	cout << "Now in I/O:     Process     Remaining I/O time" << endl;
	cout << "                [empty]" << endl << endl;
	cout << "......................................" << endl << "......................................" << endl << endl << endl;
	cout << "Completed:      ";
	for (int i = 0; i < finished.size(); i++) {
		cout << finished[i].GetName() << "   ";
	}
	cout << endl << endl << "......................................" << endl << endl << endl << endl;

	double cutil = clock - idlec;
	cutil = cutil / clock * 100;
	cout << endl << endl << "Good Job ;)" << endl << endl;
	cout << "Total Time: " << clock << endl;
	cout << "CPU Uitilization: " << cutil << "%" << endl << endl;

	cout << "Waiting Times       P1   P2   P3   P4   P5   P6   P7   P8" << endl;
	cout << "                    ";
	for (int i = 0; i < finished.size(); i++) {
		cout << finished[i].GetWait() << "  ";
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