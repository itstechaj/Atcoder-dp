#include<bits/stdc++.h>
using namespace std;
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define neg1 cout<<"-1"<<endl
#define MOD 1000000007
#define lli long long int
#define max_size 1e6+5

// Recursion solution with dp
/*
		Time coplexity -> O(n*k)
		Space Complexity = O(n){stack space}+O(n){for storing dp array}
*/
//Function to calculate minEnergy  required to reach 0th index to (n-1)th index.
int minEnergy(int n,int k,vector<int> &heights,vector<int> &dp)
{
	if(n==0) return 0;
	if(dp[n]!=-1) return dp[n];

	int way=INT_MAX;
	// if i am at nth index now then i could have came from any one of k stones before the nth index stone.
	for(int i=n-1;i>=n-k;i--)
	{
		if(i>=0)
			way=min(way,minEnergy(i,k,heights,dp)+abs(heights[n]-heights[i]));
	}
	return dp[n]=way;
}
void recursion_with_dp(vector<int> &heights,int k)
{
	int n=heights.size();
	vector<int> dp(n,-1);
	minEnergy(n-1,k,heights,dp);
	cout<<dp[n-1]<<endl;
}

// Tabulation method (Bottom up)
/*
		Time coplexity -> O(n*k)
		Space Complexity = O(n){for storing dp array}
*/
void tabulation(vector<int> &heights,int k)
{
	//Think and make it from the recursion code.
	int n=heights.size();
	vector<int> dp(n,-1);

	//Set the Base case first
	dp[0]=0; //for going to zeroth index we need 0 energy
	int way;
	for(int i=1;i<n;i++)
	{
		way=INT_MAX;
		for(int j=i-1;j>=i-k;j--)
		{
			if(j>=0)
				way=min(way,dp[j]+abs(heights[i]-heights[j]));
		}
		dp[i]=way;
	}
	cout<<dp[n-1]<<endl;
}

// Effective Tabulation method (Bottom up)
/*
		Time coplexity -> O(n)
		Space Complexity = O(k){it does need any array}

		Hint : if in your dp proablem if inside the call of (i) if there is call of (i-1)
		and/or (i-2) then there is allways an scope for space optimization.
*/
void Effective_tabulation(vector<int> &heights,int k)
{
	//Think and make it from the tabulation code.
	int n=heights.size();
	//We use deque to store answer for previous k neighbours of n.
	deque<int> dq(k,INT_MAX);

	//Set the Base case first
	dq[k-1]=0; //for going to zeroth index we need 0 energy
	int curr;
	for(int i=1;i<n;i++)
	{
		curr=INT_MAX;
		for(int j=i-1;j>=i-k;j--)
		{
			if(j>=0)
				curr=min(curr,dq[j-i+k]+abs(heights[i]-heights[j]));
		}
		dq.pop_front();
		dq.push_back(curr);
	}
	cout<<dq[k-1]<<endl;
}


int main()
{
	int t=1;
	// cin>>t;
	while(t--)
	{
		int n,k;cin>>n>>k;
		vector<int> heights(n);
		
		for(int i=0;i<n;i++)
		{
			cin>>heights[i];
		}
		recursion_with_dp(heights,k);
		tabulation(heights,k);
		Effective_tabulation(heights,k);
	}
	return 0;
}

// Author -> Abhijit Kumar