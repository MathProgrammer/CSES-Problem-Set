#include <iostream>
#include <vector>
 
using namespace std;
 
int is_bit_set(long long n, int bit)
{
    return ( (n&(1LL << bit)) != 0);
}
 
int main()
{
    long long n;
    int no_of_primes;
    cin >> n >> no_of_primes;
 
    vector <long long> P(no_of_primes);
    for(int i = 0; i < no_of_primes; i++)
    {
        cin >> P[i];
    }
 
    const int max_mask = (1 << no_of_primes);
    vector <long long> denominator(max_mask, 1);
    vector <long long> sign(max_mask, 0);
    for(int m = 0; m < max_mask; m++)
    {
        int bits = 0;
 
        for(int bit = 0; bit < no_of_primes; bit++)
        {
            if(is_bit_set(m, bit))
            {
                bits++;
 
                if(n/P[bit] >= denominator[m])
                {
                    denominator[m] *= P[bit];
                }
                else
                {
                    denominator[m] = n + 1;
                }
            }
        }
 
        sign[m] = (bits%2 == 0 ? -1 : 1);
    }
 
    long long multiples = 0;
    for(int m = 1; m < max_mask; m++)
    {
        multiples += n/(sign[m]*denominator[m]);
    }
 
    cout << multiples << "\n";
    return 0;
}
