#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <climits>
using namespace std; 
int pageFaults(vector<int> pages, int n, int capacity) { 
	unordered_set<int> s; 
	unordered_map<int, int> indexes; 
	int page_faults = 0; 
	for (int i=0; i<n; i++) { 
		if (s.size() < capacity) { 
			if (s.find(pages[i])==s.end()) { 
				s.insert(pages[i]); 
				page_faults++; 
			} 
			indexes[pages[i]] = i; 
		} 
		else { 
			if (s.find(pages[i]) == s.end()) { 
				int lru = INT_MAX, val; 
				for (auto it=s.begin(); it!=s.end(); it++) { 
					if (indexes[*it] < lru) { 
						lru = indexes[*it]; 
						val = *it; 
					} 
				} 
				s.erase(val); 
				s.insert(pages[i]); 
				page_faults++; 
			} 
			indexes[pages[i]] = i; 
		} 
	} 
	return page_faults; 
} 
int main() { 
	vector<int> pages= {2,3,2,1,5,2,4,5,3,2,5,2}; 
	int capacity = 3; 
	cout << pageFaults(pages, pages.size(), capacity) <<endl; 
	return 0; 
} 
