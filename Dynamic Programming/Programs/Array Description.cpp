#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int no_of_elements, element_limit;
    cin >> no_of_elements >> element_limit;

    vector <int> A(no_of_elements + 1);
    for(int i = 1; i <= no_of_elements; i++)
    {
        cin >> A[i];
    }

    const int MOD = 1e9 + 7;
    vector <vector <long long> > no_of_ways(no_of_elements + 1, vector <long long> (element_limit + 2));
    for(int i = 1; i <= no_of_elements; i++)
    {
        if(A[i] != 0)
        {
            no_of_ways[i][A[i]] = (i == 1 ? 1 : no_of_ways[i - 1][A[i] - 1] + no_of_ways[i - 1][A[i]] + no_of_ways[i - 1][A[i] + 1]);
        }
        else
        {
            for(int j = 1; j <= element_limit; j++)
            {
                no_of_ways[i][j] = (i == 1 ? 1 : no_of_ways[i - 1][j - 1] + no_of_ways[i - 1][j] + no_of_ways[i - 1][j + 1]);
                no_of_ways[i][j] %= MOD;
            }
        }
    }

    long long answer = 0;
    for(int j = 1; j <= element_limit; j++)
    {
        answer += no_of_ways[no_of_elements][j];
        answer %= MOD;
    }

    cout << answer << "\n";

    return 0;
}

