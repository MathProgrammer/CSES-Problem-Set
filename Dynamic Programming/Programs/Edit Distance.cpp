#include <iostream>
#include <vector>

using namespace std;

int min_3(int x, int y, int z)
{
    return min(x, min(y, z));
}

int main()
{
    string M, N;
    cin >> M >> N;

    const int oo = 1e9;
    vector <vector <int> > distance(M.size() + 1, vector <int> (N.size() + 1, oo));
    for(int i = 0; i <= M.size(); i++)
    {
        for(int j = 0; j <= N.size(); j++)
        {
            if(i == 0 || j == 0)
            {
                int insert_cost = (j == 0 ? i : 0);
                int delete_cost= (i == 0 ? j : 0);
                distance[i][j] = (i == 0 ? delete_cost : insert_cost);
                continue;
            }

            if(M[i - 1] == N[j - 1])
            {
                distance[i][j] = distance[i - 1][j - 1];
            }
            else
            {
                int update_cost = 1 + distance[i - 1][j - 1];
                int insert_cost = 1 + distance[i - 1][j];
                int delete_cost = 1 + distance[i][j - 1];

                distance[i][j] = min_3(update_cost, insert_cost, delete_cost);
            }
        }
    }

    cout << distance[M.size()][N.size()] << "\n";
}
