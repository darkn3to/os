#include<bits/stdc++.h> 
using namespace std; 

void firstFit(vector<int> blockSize, int m, vector<int> processSize, int n) { 
	int allocation[n]; 
	memset(allocation, -1, sizeof(allocation)); 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < m; j++) { 
			if (blockSize[j] >= processSize[i]) { 
				allocation[i] = j; 
				blockSize[j] -= processSize[i]; 
				break; 
			} 
		} 
	} 
    cout << "First Fit: ";
	cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
	for (int i = 0; i < n; i++) { 
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		if (allocation[i] != -1) cout << allocation[i] + 1; 
		else cout << "Not Allocated"; 
		cout << endl; 
	} 
    cout << endl;
} 

void bestFit(vector<int>& blockSize, int m, vector<int>& processSize, int n) {
    int allocation[n];
    memset(allocation, -1, sizeof(allocation));
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    cout << "Best Fit: ";
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1) cout << allocation[i] + 1;
        else cout << "Not Allocated";
        cout << endl;
    }
    cout << endl;
}

void worstFit(vector<int>& blockSize, int m, vector<int>& processSize, int n) {
    int allocation[n];
    memset(allocation, -1, sizeof(allocation));
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    cout << "Worst Fit: ";
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1) cout << allocation[i] + 1;
        else cout << "Not Allocated";
        cout << endl;
    }
    cout << endl;
}


int main() { 
    int n, x, nb;
    cout << "Enter the number of blocks: ";
    cin >> nb;
    vector<int> blocks(nb, 0);
    cout << "Enter the block size: ";
    for (int i=0; i<nb; i++) {
        cin >> x;
        blocks[i]=x;
    }
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<int> processes(n, 0);
    cout << "Enter the process sizes: ";
    for (int i=0; i<n; i++) {
        cin >> x;
        processes[i]=x;
    }
    //firstFit(blocks, nb, processes, n);
    bestFit(blocks, nb, processes, n);
    //worstFit(blocks, nb, processes, n);
	return 0 ; 
} 
