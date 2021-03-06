#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

typedef struct Node{
	int P;
	int C;
	int F;
	Node(int p, int c, int f):P(p), C(c), F(f){}
	Node(){}

	void operator += (const Node &rh)
	{
		this->P += rh.P;
		this->C += rh.C;
		this->F += rh.F;
	}
	void operator -= (const Node &rh)
	{
		this->P -= rh.P;
		this->C -= rh.C;
		this->F -= rh.F;
	}
}Node;

bool equal(const Node &a, const Node &b)
{
	if(a.P == b.P && a.C == b.C && a.F == b.F)
		return true;
	return false;
}

bool possible(const Node &a, const Node &target)
{
	if(a.P > target.P || a.C > target.C || a.F > target.F)
		return false;
	return true; // still possible
}

bool dfs(int start, int N, Node &vv, vector<Node> &foods, Node &target)
{
	if(!possible(vv, target))  // pruning
		return false;
	if(equal(vv, target))
		return true;
	else if(start == N)  // searched till end but still not equal
		return false;

	for(int i = start; i < N; i++)
	{
		vv += foods[i];
		if(dfs(i+1, N, vv, foods, target))
			return true;
		vv -= foods[i];  // backtrace
	}
	return false;
}

int main(int argc, char *argv[])
{
	int T, N;
	Node target;
	vector<Node> foods(20);
	int p,c,f;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
	{
		scanf("%d %d %d", &p, &c, &f);
		target.P = p;
		target.C = c;
		target.F = f;
		scanf("%d", &N);
		for(int j = 0; j < N; j++)
		{
			scanf("%d %d %d", &p, &c, &f);
			foods[j].P = p;
			foods[j].C = c;
			foods[j].F = f;
		}
		Node vv(0,0,0);
		bool result = dfs(0, N, vv, foods, target);
		cout << "Case #" << i << ": " << (result ? "yes" : "no") << endl;
	}
	return 0;
}
