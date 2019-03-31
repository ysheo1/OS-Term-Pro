#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

struct Process {
	string process_name;
	double arrival_time;			// �޸𸮿� �� �ð�
	double burst_time;				// ����ð�
	double waiting_time;			// ��ٸ� �ð�
	double turnaround_time;			// �� ����ð�
	double normalized_time;			// ����ȭ �ð�
	double remain_burst_time;       //���� ����ð�
	Process(string process_name, double arrival_time, double burst_time) : process_name(process_name), arrival_time(arrival_time), burst_time(burst_time) {}

};

template <typename T>
void showing(T que) {
	while (!que.empty()) {
		Process p = que.front();
		que.pop();

		cout << "Name of Process: " << p.process_name << endl;
		cout << "Arrival time: " << p.arrival_time << endl;
		cout << "Burst time: " << p.burst_time << endl;
		cout << "Waiting_time: " << p.waiting_time << endl;
		cout << "Turnaround_time: " << p.turnaround_time << endl;
		cout << "Normalized_time: " << (double)p.normalized_time << endl;

		cout << endl;
	}
}

template <typename B>
void findWaitingTime(B &que, int &quant, int &elapsed_time){
	
	que.front().remain_burst_time = que.front().burst_time;

	while (1) {
		bool done = true;

		if (que.front().remain_burst_time > 0) {
			done = false;

			if (que.front().remain_burst_time > quant) {
				elapsed_time += quant;
				que.front().remain_burst_time -= quant;
			}

			else {
				elapsed_time = elapsed_time + que.front().remain_burst_time;
				que.front().waiting_time = elapsed_time - que.front().burst_time;
				que.front().remain_burst_time = 0;
			}
		}
		if (done == true)
			break;
	}
}

template <typename C>
void caculate(C &que, C &que2, int &elasped_time, int &quant) {      //1�ʾ� ����?
	while (!que.empty()) {			  //�����ϰ� �ִ°� ���� ���ҳ�?
		Process p = que.front();
		
		findWaitingTime(que, quant,elasped_time);
		que.front().turnaround_time = que.front().burst_time + que.front().waiting_time;
		que.front().normalized_time = (double)que.front().turnaround_time / (double)que.front().burst_time;
		
		que2.push(que.front());

		que.pop();

	}
}

bool compare(Process &a, Process &b) {
	if (a.arrival_time < b.arrival_time)
		return true;
	else
		return false;
}
int main() {
	int num, y, z;
	string n;
	int elapsed_time = 0;
	int quant;

	queue<Process> que;			// ������ �Է��� ť
	vector<struct Process> v;
	queue<Process> que_temp;

	cout << "Enter number of processes : ";
	cin >> num;
	cout << "Enter Time Quantum: ";
	cin >> quant;
	cout << endl;

	for (int i = 0; i < num; i++) {
		cout << "Enter name of process name: ";
		cin >> n;
		cout << "Enter arrival time & burst time: ";
		cin >> y >> z;
		v.push_back(Process(n, y, z));

		cout << endl;

	}

	sort(v.begin(), v.end(), compare);


	for (Process p : v) {
		que.push(p);
	}

	caculate(que, que_temp, elapsed_time,quant);

	showing(que_temp);

	return 0;

}