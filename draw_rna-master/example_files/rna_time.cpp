#include <bits/stdc++.h>
#include <random>
#include <chrono>

using namespace std;

/// @brief the function validMatch checks if the given two characters are valid base pairs or not
/// @param a one of the constituents of the base pair
/// @param b the other constituent of the base pair
/// @return returns true if the given characters are valid base pairs, false otherwise
bool validMatch(char a, char b)
{
    if ((a == 'A' && b == 'U') || (a == 'C' && b == 'G') || (a == 'U' && b == 'A') || (a == 'G' && b == 'C'))
        return true;
    return false;
}

/// @brief this function finds the maximum number of base pair matchings in the given RNA sequence
/// @details The function begins by initializing the dp matrix. The first for-loop iterates over the RNA sequence, and for each nucleotide, it initializes the corresponding dp cell to zero if the condition i >= j - 4 is met. This condition ensures that only nucleotides that are at least 4 positions apart can form a base pair, which is a rule in RNA secondary structure prediction.
/// @details The function then enters the main part of the algorithm. It iterates over the RNA sequence again, but this time in a different manner. It uses a variable k to represent the distance between the nucleotides being considered. For each pair of nucleotides, it checks if they can form a base pair using the validMatch function. If they can, it calculates the maximum number of base pairs that can be formed by including this pair and compares it to the current maximum. If the new maximum is greater, it updates the maximum and sets a flag match_flag to 2.
/// @details The function then updates the dp matrix with the new maximum number of base pairs. If the match_flag is 1, it means that the maximum number of base pairs is achieved without including the current pair, so it copies the set of base pairs from the previous cell. If the match_flag is 2, it means that the maximum number of base pairs is achieved by including the current pair, so it adds this pair to the set of base pairs and also merges the sets of base pairs from the relevant cells.
/// @details In summary, this function uses dynamic programming to find the secondary structure of an RNA sequence that maximizes the number of base pairs. It ensures that only valid base pairs are considered and that the base pairs are at least 4 positions apart. The result is stored in the dp matrix, where dp[i][j].first represents the maximum number of base pairs that can be formed by the subsequence from i to j, and dp[i][j].second is a set of these base pairs.
/// @param dp this is a 2D vector which stores the maximum number of base pair matchings for the given range of indices
/// @param rna_seq this is the given RNA sequence
/// @param n this is the length of the RNA sequence
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
                dp[i][j].second = dp[i][j - 1].second;
            }
            else if (match_flag == 2)
            {
                if (max_t > 0)
                {
                    dp[i][j].second.insert(dp[i][max_t - 1].second.begin(), dp[i][max_t - 1].second.end());
                }
                dp[i][j].second.insert(dp[max_t + 1][j - 1].second.begin(), dp[max_t + 1][j - 1].second.end());
                dp[i][j].second.insert({j, max_t});
            }
        }
    }
}

// Function to generate random sequences
string generateRandomSequence(int length) {
    string bases = "AUCG";
    string sequence;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, bases.size() - 1);

    for (int i = 0; i < length; ++i) {
        sequence += bases[dis(gen)];
    }

    return sequence;
}

/// @brief the main function. Takes the RNA sequence as input and finds the maximum number of base pair matchings.
int main()
{
    // string rna_seq;
    // cin >> rna_seq;

    int sequenceLength = 1000; // Change this to the desired length
    string rna_seq = generateRandomSequence(sequenceLength);
    cout << "Random Sequence: " << rna_seq << endl;

    int n = rna_seq.size();

    vector<vector<pair<int, set<pair<int, int>>>>> dp(n, vector<pair<int, set<pair<int, int>>>>(n, {-1, set<pair<int, int>>()}));


    auto start = std::chrono::high_resolution_clock::now();

    // Call the function to be timed
    findSecStruct(dp, rna_seq, n);

    // End time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Print the duration
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;


    cout << "\nThe maximum number of base pair matchings is: " << dp[0][n - 1].first << endl;

    cout << "\nThe matchings are (0 based indexing): " << endl;

    string dot_bracket(n, '.');
    for (auto pr : dp[0][n - 1].second)
    {
        // cout << pr.first << "--" << pr.second;
        // cout << endl;
        int left = min(pr.first, pr.second);
        int right = max(pr.first, pr.second);
        cout << rna_seq[left] << "(" << left << ")"
             << "--" << rna_seq[right] << "(" << right << ")";
        cout << endl;
        dot_bracket[left] = '(';
        dot_bracket[right] = ')';
    }
    cout << "\nDot bracket notation: " << endl;
    cout << dot_bracket << endl;
    return 0;
}