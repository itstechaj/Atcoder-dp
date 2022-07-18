//Push and store this codes on github
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
		Time coplexity -> O(n)
		Space Complexity = O(n){stack space}+O(n){for storing dp array}
*/
//Function to calculate minEnergy  required to reach 0th index to (n-1)th index.
int minEnergy(int n,vector<int> &heights,vector<int> &dp)
{
	if(n==0) return 0;
	if(dp[n]!=-1) return dp[n];

	int way1=INT_MAX,way2=INT_MAX;
	way1=minEnergy(n-1,heights,dp)+abs(heights[n]-heights[n-1]);
	if(n-2>=0)
		way2=minEnergy(n-2,heights,dp)+abs(heights[n]-heights[n-2]); 
	return dp[n]=min(way1,way2);
}
void recursion_with_dp(vector<int> &heights)
{
	int n=heights.size();
	vector<int> dp(n,-1);
	minEnergy(n-1,heights,dp);
	cout<<dp[n-1]<<endl;
}

// Tabulation method (Bottom up)
/*
		Time coplexity -> O(n)
		Space Complexity = O(n){for storing dp array}
*/
void tabulation(vector<int> &heights)
{
	//Think and make it from the recursion code.
	int n=heights.size();
	vector<int> dp(n,-1);

	//Set the Base case first
	dp[0]=0; //for going to zeroth index we need 0 energy
	int way1=INT_MAX,way2=INT_MAX;
	for(int i=1;i<n;i++)
	{
		way1=dp[i-1]+abs(heights[i]-heights[i-1]);
		if(i-2>=0)
			way2=dp[i-2]+abs(heights[i]-heights[i-2]);
		dp[i]=min(way1,way2);
	}
	cout<<dp[n-1]<<endl;
}

// Effective Tabulation method (Bottom up)
/*
		Time coplexity -> O(n)
		Space Complexity = O(1){it does need any array}

		Hint : if in your dp proablem if inside the call of (i) if there is call of (i-1)
		and/or (i-2) then there is allways an scope for space optimization.
*/
void Effective_tabulation(vector<int> &heights)
{
	//Think and make it from the tabulation code.
	int n=heights.size();

	// we make three variable to store minEnergy required for three consecutive indexs
	int prev2=-1,prev,curr;
	prev=0; //for going to zeroth index we need 0 energy

	int way1=INT_MAX,way2=INT_MAX;
	for(int i=1;i<n;i++)
	{
		way1=prev+abs(heights[i]-heights[i-1]);
		if(i-2>=0)
			way2=prev2+abs(heights[i]-heights[i-2]);

		// shifting towards right
		curr=min(way1,way2);
		prev2=prev;
		prev=curr;
	}
	//Atlast prev variable will store our answer
	cout<<prev<<endl;
}


int main()
{
	int t=1;
	// cin>>t;
	while(t--)
	{
		int n;cin>>n;
		vector<int> heights(n);
		
		for(int i=0;i<n;i++)
		{
			cin>>heights[i];
		}
		recursion_with_dp(heights);
		tabulation(heights);
		Effective_tabulation(heights);
	}
	return 0;
}