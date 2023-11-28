#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<vector<int>> gProc;
vector<vector<int>> gRes;

set<int> l;

bool findCycle(int start, bool proc) {
	if (proc) {
		l.insert(start);
		for (auto it : gProc[start]) {
			if (findCycle(it, false))
				return true;
		}
		l.erase(start);
	}
	else {
		for (auto it : gRes[start]) {
			if (l.find(it) != l.end())
				return true;
			if (findCycle(it, true))
				return true;
		}
	}
	return false;
}

bool findCycle() {
	for (int i = 0; i < gProc.size(); i++) {
		l.clear();
		findCycle(i, true);
		if (l.empty())
			cout << "no cycle\n";
		else {
			cout << "cycle: ";
			for (auto it : l)
				cout << it << " ";
			cout << "\n";
			return true;
		}
	}
	return false;
}

void coutGraph() {
	cout << "Processes:\n";
	for (int i = 0; i < gProc.size(); i++) {
		cout << "	p" << i << ": ";
		for (auto it2 : gProc[i])
			cout << it2 << " ";
		cout << "\n";
	}
	cout << "Resourcess:\n";
	for (int i = 0; i < gRes.size(); i++) {
		cout << "	p" << i << ": ";
		for (auto it2 : gRes[i])
			cout << it2 << " ";
		cout << "\n";
	}
}

int main() {
	gProc.push_back({ 1, 4 });
	gProc.push_back({ 2, 4, 5 });
	gProc.push_back({ 0 });

	gRes.push_back({ 1 });
	gRes.push_back({ 2 });
	gRes.push_back({ 0 });
	gRes.push_back({});
	gRes.push_back({});
	gRes.push_back({});

	coutGraph();

	if (findCycle())
		gProc[*l.begin()].clear();

	coutGraph();

	findCycle();
}