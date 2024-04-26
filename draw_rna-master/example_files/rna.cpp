#include <bits/stdc++.h>

using namespace std;

bool validMatch(char a, char b)
{
    if ((a == 'A' && b == 'U') || (a == 'C' && b == 'G') || (a == 'U' && b == 'A') || (a == 'G' && b == 'C'))
        return true;
    return false;
}

void findSecStruct(vector<vector<pair<int, set<pair<int, int>>>>> &dp, string rna_seq, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >= j - 4)
            {
                dp[i][j].first = 0;
            }
        }
    }

    // cout << "1\n";

    for (int k = 5; k < n; k++)
    {
        for (int i = 0; i < n - k; i++)
        {

            int j = i + k;
            if (i >= j - 4)
            {
                continue;
            }
            int max = 0;

            int match_flag = 0;
            if (dp[i][j - 1].first > max)
            {
                match_flag = 1;
                max = dp[i][j - 1].first;
            }
            int t = 0;
            int max_t = 0;
            for (t = i; t < j - 4; t++)
            {
                if (validMatch(rna_seq[t], rna_seq[j]))
                {
                    if (t > 0)
                    {
                        if (1 + dp[i][t - 1].first + dp[t + 1][j - 1].first > max)
                        {
                            match_flag = 2;
                            max_t = t;
                            max = 1 + dp[i][t - 1].first + dp[t + 1][j - 1].first;
                        }
                    }
                    else
                    {
                        if (1 + dp[t + 1][j - 1].first > max)
                        {
                            match_flag = 2;
                            max_t = t;
                            max = 1 + dp[t + 1][j - 1].first;
                        }
                    }
                }
            }

            dp[i][j].first = max;

            if (match_flag == 1)
            {
                // cout << "4\n";
                dp[i][j].second = dp[i][j - 1].second;
            }
            else if (match_flag == 2)
            {
                // cout << "51\n";
                if (max_t > 0)
                {
                    dp[i][j].second.insert(dp[i][max_t - 1].second.begin(), dp[i][max_t - 1].second.end());
                }
                // cout << "52\n";
                dp[i][j].second.insert(dp[max_t + 1][j - 1].second.begin(), dp[max_t + 1][j - 1].second.end());
                // cout << "53\n";
                dp[i][j].second.insert({j, max_t});
                // cout << "54\n";
            }
        }
    }
}

int main()
{
    string rna_seq;
    cin >> rna_seq;

    int n = rna_seq.size();
    // cout << n << endl;

    vector<vector<pair<int, set<pair<int, int>>>>> dp(n, vector<pair<int, set<pair<int, int>>>>(n, {-1, set<pair<int, int>>()}));

    // cout << "table: " << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << dp[i][j].first << "\t";
    //     }
    //     cout << "\n";
    // }

    // cout << dp[3][2].second.size() << endl;

    findSecStruct(dp, rna_seq, n);
    // cout << "answer: ";
    // cout << dp[0][n - 1].first << endl;

    // cout << "table: " << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << dp[i][j].first << "\t";
    //     }
    //     cout << "\n";
    // }

    // cout << "base pairs matched index: " << endl;
    string dot_bracket(n, '.');
    // cout << dot_bracket << endl;
    for (auto pr : dp[0][n - 1].second)
    {
        // cout << pr.first << "--" << pr.second;
        // cout << endl;
        int left = min(pr.first, pr.second);
        int right = max(pr.first, pr.second);
        dot_bracket[left] = '(';
        dot_bracket[right] = ')';
    }
    cout << dot_bracket << endl;
    return 0;
}