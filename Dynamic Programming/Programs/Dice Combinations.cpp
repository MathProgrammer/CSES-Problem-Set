#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int sum;
    cin >> sum;

    const int MOD = 1e9 + 7, NO_OF_FACES = 6;
    vector <int> no_of_ways(sum + 1);
    no_of_ways[0] = 1;
    for(int i = 1; i <= sum; i++)
    {
        for(int dice = 1; dice <= NO_OF_FACES && dice <= i; dice++)
        {
            no_of_ways[i] += no_of_ways[i - dice];
            no_of_ways[i] %= MOD;
        }
    }

    cout << no_of_ways[sum] << "\n";
    return 0;
}
