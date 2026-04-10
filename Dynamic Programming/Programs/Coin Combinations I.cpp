#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int no_of_coins, total;
    cin >> no_of_coins >> total;

    vector <int> value(no_of_coins + 1);
    for(int i = 1; i <= no_of_coins; i++)
    {
        cin >> value[i];
    }

    const int MOD = 1e9 + 7;
    vector <int> no_of_ways(total + 1);
    no_of_ways[0] = 1;
    for(int i = 1; i <= total; i++)
    {
        for(int c = 1; c <= no_of_coins; c++)
        {
            if(value[c] <= i)
            {
                no_of_ways[i] += no_of_ways[i - value[c]];
                no_of_ways[i] %= MOD;
            }
        }
    }

    cout << no_of_ways[total] << "\n";

    return 0;
}


