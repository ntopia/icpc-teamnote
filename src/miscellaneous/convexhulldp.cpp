//O(n^3) -> O(n^2)

#define sz 100001
long long s[sz];
long long dp[2][sz];
//deque {index, x pos }
int dqi[sz];
long long dqm[sz];
//pointer to deque
int ql,qr;
//dp[i][j] = max(dp[i][k] + s[j]*s[k] - s[k]^2)
//let y = dp[i][j], x = s[j] -> y = max(s[k]*x + dp[i][k] - s[k]^2);
 
//push new value to deque
//i = index, x = current x pos
void setq(int i, int x)
{
    //a1,b1 = prv line, a2,b2 = new line
    int a1, a2 = s[i];
    long long b1, b2 = dp[0][i] - s[i] * s[i], r;
    //renew deque
    while (qr>=ql)
    {
        //last line enqueued
        a1 = s[dqi[qr]];
        b1 = dp[0][dqi[qr]] - s[dqi[qr]] * s[dqi[qr]];
        //tie breaking to newer one
        if (a1 == a2)
        {
            dqi[qr] = i;
            return;
        }
        // x intersection between last line and new line
        r = (b1 - b2) / (a2 - a1);
        if ((b1 - b2) % (a2 - a1)) r++;
        //last line is not needed
        if (r <= dqm[qr])
        {
            qr--;
        }
        else break;
    }
    if (r < 0) r = 0;
    //push back new line
    if (dqm[qr] < s[n - 1] && r <= s[n - 1])
    {
        dqi[++qr] = i;
        dqm[qr] = r;
    }
    //discard old lines
    while (qr-ql && dqm[ql+1] <= x)
    {
        ql++;
    }
}

int main()
{
    for (int j = 0; j < k; j++)
    {
        ql = 0;
        qr = 1;
        dqi[0] = dqm[0] = 0;
        for (int i = 1; i < n; i++)
        {
            //get line used by current x pos
            setq(i, s[i]);
            //line index to use
            int g = dqi[ql];
            //set dp value
            dp[1][i] = dp[0][g] + s[g] * (s[i] - s[g]);
        }
        for (int i = 0; i < n; i++)
        {
            dp[0][i] = dp[1][i];
            dp[1][i] = 0;
        }
    }
}
