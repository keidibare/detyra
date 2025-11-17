#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

void printTable(const vector<Process>& p) {
    cout << "\n------------------------------------------------------\n";
    cout << "ID\tAT\tBT\tWT\tTAT\n";
    cout << "------------------------------------------------------\n";
    for (auto &x : p) {
        cout << "P" << x.id << "\t"
             << x.arrival << "\t"
             << x.burst << "\t"
             << x.waiting << "\t"
             << x.turnaround << "\n";
    }
}

// ======================================================
//             FCFS  (First Come First Served)
// ======================================================
void FCFS(vector<Process> p) {
    int time = 0;

    cout << "\n\n=== FCFS Scheduling ===\nGantt Chart:\n";

    for (int i = 0; i < p.size(); i++) {

        if (time < p[i].arrival)
            time = p[i].arrival;

        cout << "| P" << p[i].id << " ";

        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }

    cout << "|\n";

    printTable(p);
}

// ======================================================
//                ROUND ROBIN
// ======================================================
void RoundRobin(vector<Process> p, int quantum) {
    int n = p.size();
    vector<int> remaining(n);
    queue<int> q;
    int time = 0;

    for (int i = 0; i < n; i++)
        remaining[i] = p[i].burst;

    cout << "\n\n=== Round Robin Scheduling ===\nGantt Chart:\n";

    int completed = 0;
    vector<bool> added(n, false);

    while (completed < n) {

        // fut proceset qe kane ardhur
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && added[i] == false) {
                q.push(i);
                added[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front();
        q.pop();

        cout << "| P" << p[idx].id << " ";

        int use = (remaining[idx] > quantum ? quantum : remaining[idx]);

        remaining[idx] -= use;
        time += use;

        if (remaining[idx] == 0) {
            completed++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        } else {
            for (int i = 0; i < n; i++) {
                if (p[i].arrival <= time && added[i] == false) {
                    q.push(i);
                    added[i] = true;
                }
            }
            q.push(idx);
        }
    }

    cout << "|\n";
    printTable(p);
}

// ======================================================
//                    MAIN
// ======================================================
int main() {
    int n;
    cout << "Numri i proceseve: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "\nProcesi P" << p[i].id << ":\n";
        cout << "Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
    }

    FCFS(p);

    int quantum;
    cout << "\nVendos quantum per Round Robin: ";
    cin >> quantum;

    RoundRobin(p, quantum);

    cout << "\n\nProgrami perfundoi me sukses!\n";
    return 0;
}
