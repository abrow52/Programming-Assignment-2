#include<iostream>
#include<fstream>
using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Function to find the need matrix
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allot[i][j];
}

// Function to check if the system is in a safe state or not
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = { 0 };
    int safeSeq[P];

    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is not in safe state" << endl;
            return false;
        }
    }

    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < P; i++)
        cout << safeSeq[i] << " ";

    return true;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int processes[P];
    int avail[R];
    int max[P][R];
    int allot[P][R];

    for (int i = 0; i < P; i++)
        inputFile >> processes[i];

    for (int i = 0; i < R; i++)
        inputFile >> avail[i];

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            inputFile >> max[i][j];

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            inputFile >> allot[i][j];

    inputFile.close();

    isSafe(processes, avail, max, allot);

    return 0;
}
