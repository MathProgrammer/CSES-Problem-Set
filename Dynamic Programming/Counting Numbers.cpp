#include <iostream>

using namespace std;

string convert_to_string(long long n)
{
    string N;
    while(n > 0)
    {
        N = (char)(n%10 + '0') + N;
        n /= 10;
    }

    return N;
}

long long power(long long x, long long p)
{
    long long answer = 1;
    while(p > 0)
    {
        if(p%2 == 1)
            answer = answer*x;

        x = x*x;
        p = p >> 1;
    }

    return answer;
}

long long numbers_before_with_leading_0s(string N)
{
    long long answer = 0;
    for(int i = 1; i < N.size(); i++)
    {
        int digits_from_here = N.size() - 1 - (i - 1);
        answer += (i == N.size() - 1 ? 10 : power(9, digits_from_here));
    }
    return answer;
}

long long numbers_before_with_same_digits(string N)
{
    long long answer = 0;
    int prefix_good = true;
    for(int i = 0; i < N.size() && prefix_good; i++)
    {
        char starting_for_this_position = (i == 0 && N.size() > 1 ? '1' : '0');
        for(char current_digit = starting_for_this_position; current_digit < N[i]; current_digit++)
        {
            if(i > 0 && current_digit == N[i - 1])
            {
                continue;
            }

            int remaining_digits = N.size() - 1 - i;
            answer += power(9, remaining_digits);
        }

        if(i > 0 && N[i] == N[i - 1])
        {
            prefix_good = false;
        }
    }
    return answer;
}

long long numbers_before(string N)
{
    return numbers_before_with_same_digits(N) + numbers_before_with_leading_0s(N);
}


int main()
{
    long long left, right;
    cin >> left >> right;

    string R_plus_1 = convert_to_string(right + 1), L = convert_to_string(left); //cout << "Done\n";
    long long answer = numbers_before(R_plus_1) - numbers_before(L); //cout << R_plus_1 << " " << L << "\n";

    cout << answer << "\n";
    return 0;
}
