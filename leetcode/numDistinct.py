class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n=len(s)
        m=len(t)
        if n<m:
            return 0
        # dp=[[0]*(m+1) for i in range(n+1)]
        prev=[0]*(m+1)
        # for i in range(n+1):
        #     dp[i][0]=1
        prev[0]=1
        for i in range(1,n+1):
            curr=[0]*(m+1)
            curr[0]=1
            for j in range(1,m+1):
                x=0
                if s[i-1]==t[j-1]:
                    x=prev[j-1]
                y=prev[j]
                curr[j]=x+y
                #     x=dp[i-1][j-1]
                # y=dp[i-1][j]
                # dp[i][j]=x+y
            prev=curr
        return prev[m]
