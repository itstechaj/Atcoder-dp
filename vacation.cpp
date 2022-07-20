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
		Time coplexity -> O(n*3)
		Space Complexity = O(n){stack space}+O(n*4){for storing dp matrix}
*/
//Function to calculate maxPoints for day days if activity done at (day+1)th day is last.
int maxPoints(int day,int prev,vector<vector<int>> &act,vector<vector<int>> &dp)
{
    // prev-> Index of activity done on (day+1)th day.(it ranges in [0,3]. 3 means no activities done on previous day).
    // 0-based indexing
	if(day==0)
    {
        int maxp=0;
        for(int i=0;i<3;i++)
        {
            if(i!=prev)
            {
                maxp=max(maxp,act[0][i]);
            }
        }
        return maxp;
    }

    if(dp[day][prev]!=-1) return dp[day][prev];
    int maxp=0;
    for(int i=0;i<3;i++)
    {
        if(i==prev) continue;
        maxp=max(maxp,act[day][i]+maxPoints(day-1,i,act,dp));
    }
    return dp[day][prev]=maxp;
}
void recursion_with_dp(vector<vector<int>> &activities)
{
	int n=activities.size();
    //Our recursion has two state(two parameters are changing) so we need 2D dp array.
	vector<vector<int>> dp(n,vector<int> (4,-1));
    
    //We are passing 3 as prev in last day because there is no previous for last day.
	int ans=maxPoints(n-1,3,activities,dp);
    cout<<ans<<endl;
}

// Tabulation method (Bottom up)
/*
		Time coplexity -> O(n*4*3) //here is a diffrence from recursion by a const factor.
		Space Complexity = O(n*4){for storing dp matrix}
*/
void tabulation(vector<vector<int>> &activities)
{
	//Think and make it from the recursion code.
	int n=activities.size();
    //We need same size dp array as in recursion.
	vector<vector<int>> dp(n,vector<int> (4,-1));

	//Set the Base case first (Base case is when day==0)
	for(int prev=0;prev<=3;prev++)
    {
        for(int i=0;i<3;i++)
        {
            if(i==prev) continue;
            dp[0][prev]=max(dp[0][prev],activities[0][i]);
        }
    }

    //start from day 1
    for(int day=1;day<n;day++)
    {
        for(int prev=0;prev<=3;prev++)
        {
            //prev can be from 0 to 3
            for(int i=0;i<3;i++)
            {
                //i denotes the index of avialable activity for today it can be from 0 to 2 only.
                if(i==prev) continue;//He can't do the task he has done on previous day
                dp[day][prev]=max(dp[day][prev],activities[day][i]+dp[day-1][i]);
            }
        }
    }
    //for answer we call dp using same parameter as we call in recursion
    cout<<dp[n-1][3]<<endl;
}

// Effective Tabulation method (Bottom up)
/*
		Time coplexity -> O(n*4*3) //Same as tabulation
		Space Complexity = O(1){We use array of size 4}

		Hint : if in your dp proablem if inside the call of (i) if there is call of (i-1)
		and/or (i-2) then there is allways an scope for space optimization.
*/
void Effective_tabulation(vector<vector<int>> &activities)
{
	//Think and make it from the tabulation code.
	int n=activities.size();

	// we make Linear array of size 4 to store one row of dp array at a time
	vector<int> dp(4,-1);
    //Initializing dp with base case (day==0)
    for(int prev=0;prev<=3;prev++)
    {
        for(int i=0;i<3;i++)
        {
            if(i==prev) continue;
            dp[prev]=max(dp[prev],activities[0][i]);
        }
    }
    //start from day 1
	for(int day=1;day<n;day++)
    {
        vector<int> curr_dp(4,-1);
        for(int prev=0;prev<=3;prev++)
        {
            for(int i=0;i<3;i++)
            {
                if(i==prev) continue;
                curr_dp[prev]=max(curr_dp[prev],activities[day][i]+dp[i]);
            }
        }
        //We only need just one previous row values to calculate current row
        dp=curr_dp;
    }
    //dp[3] will contain our answer
    cout<<dp[3]<<endl;
}


int main()
{
	int t=1;
	// cin>>t;
	while(t--)
	{
		int n;cin>>n;
		vector<vector<int>> activities(n,vector<int>(3,0));
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<3;j++)
            {
                cin>>activities[i][j];
            }
		}
		recursion_with_dp(activities);
		tabulation(activities);
		Effective_tabulation(activities);
	}
	return 0;
}