// Code is written by Abhijit Kumar
#include<bits/stdc++.h>
using namespace std;
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
#define neg1 cout<<"-1"<<endl
#define MOD 1000000007
#define lli long long int
#define max_size 1e6+5

/*
Recursion With dp 
Time complexity = O(n*w)  
Space Complexity = O(n*w)+ Auxillary stack space
*/
// maxvalue -> returns for index i=0 to i  what maximum value we can take if maximum capacity of knapsack is wt.
lli maxvalue(int i,int wt,vector<int> &weight,vector<int> &value,vector<vector<lli>> &dp)
{
	//Base case -> either no items left or bag is filled (i<0 or wt<=0)
	if(wt<=0) return 0;
	if(i<0) return 0;

	if(dp[i][wt]!=-1) return dp[i][wt];

	lli taken=0,notTaken=0;
	if(wt-weight[i]>=0)
	{
		taken=value[i]+maxvalue(i-1,wt-weight[i],weight,value,dp);
	}
	notTaken=maxvalue(i-1,wt,weight,value,dp);
	return dp[i][wt]=max(taken,notTaken);
}
void recursion_with_dp(int w,vector<int> &weight,vector<int> &value)
{
	int n=weight.size();
	vector<vector<lli>> dp(n,vector<lli>(w+1,-1));
	cout<<maxvalue(n-1,w,weight,value,dp)<<endl;
}


/*
Tabulation method.
Time complexity = O(n*w)  
Space Complexity = O(n*w)
*/
void tabulation(int w,vector<int> &weight,vector<int> &value)
{
	int n=weight.size();
	vector<vector<lli>> dp(n,vector<lli>(w+1,-1));
	
	//filling base cases
	// if knapsack capacity = 0 then return 0
	for(int i=0;i<n;i++)
	{
		dp[i][0] = 0;
	}
	//if we are at i==0 then if possible then pick value
	for(int wt=0;wt<=w;wt++)
	{
		if(wt-weight[0]>=0)
		{
			dp[0][wt]=value[0];
		}
		else dp[0][wt]=0;
	}

	for(int i=1;i<n;i++)
	{
		for(int wt=0;wt<=w;wt++)
		{
			lli taken=0,notTaken=0;
			if(wt-weight[i]>=0)
			{
				taken=value[i]+dp[i-1][wt-weight[i]];
			}
			notTaken=dp[i-1][wt];
			dp[i][wt]=max(taken,notTaken);
		}
		
	}
	cout<<dp[n-1][w]<<endl;
}


/*
Effective Tabulation
Time complexity = O(n*w)  
Space Complexity = O(w)
*/
void Effective_tabulation(int w,vector<int> &weight,vector<int> &value)
{
	int n=weight.size();

	//we are only storing results for diffrent weights corresponding to one value of index only 
	vector<lli> dpPrev(w+1,-1);
	vector<lli> dpCurr(w+1,-1);
	
	//filling base cases
	//if we are at i==0 then if possible then pick value
	for(int wt=0;wt<=w;wt++)
	{
		if(wt-weight[0]>=0)
		{
			dpPrev[wt]=value[0];
		}
		else dpPrev[wt]=0;
	}

	for(int i=1;i<n;i++)
	{
		for(int wt=0;wt<=w;wt++)
		{
			lli taken=0,notTaken=0;
			if(wt-weight[i]>=0)
			{
				taken=value[i]+dpPrev[wt-weight[i]];
			}
			notTaken=dpPrev[wt];
			dpCurr[wt]=max(taken,notTaken);
		}
		dpPrev=dpCurr;
	}
	cout<<dpPrev[w]<<endl;
}



int main()
{
	int  n,w;cin>>n>>w;
	vector<int> weight(n);
	vector<int> value(n);
	for(int i=0;i<n;i++)
	{
		cin>>weight[i]>>value[i];
	}
	recursion_with_dp(w,weight,value);    //(Execution time=218 ms | Memory used=82192 KB)
	tabulation(w,weight,value);           //(Execution time=69 ms | Memory used=82348 KB)
	Effective_tabulation(w,weight,value); //(Execution time=28 ms | Memory used=4736 KB)

	// We can see a huge diffrence in executaion time and memory usage of 3rd wrt 1st and 2nd method.
	//Conclusion : - Effective tabulation method is very fast and also very space efficient.

	return 0;
}
//Abhijit Kumar (Nit Durgapur CSE)