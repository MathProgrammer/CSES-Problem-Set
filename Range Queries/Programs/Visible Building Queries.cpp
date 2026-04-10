#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Query
{
    int left, right, index;
    
    Query(int L, int R, int I)
    {
        left = L;
        right = R;
        index = I;
    }
};

int sort_by_left(Query &L, Query&R)
{
    if(L.left == R.left)
    {
        return L.right < R.right;
    }
    
    return (L.left < R.left);
}

class SegmentTree
{
    #define LEFT(n) (2*n)
    #define RIGHT(n) (2*n + 1)
    
    private:
    int no_of_elements;
    vector <int> tree;
    
    void update(int n, int left, int right, int position, int value)
    {
        if(position < left || right < position)
        {
            return;
        }
        
        if(left == right)
        {
            tree[n] = value;
            return;
        }
        
        int mid = (left + right)/2;
        update(LEFT(n), left, mid, position, value);
        update(RIGHT(n), mid + 1, right, position, value);
        
        tree[n] = tree[LEFT(n)] + tree[RIGHT(n)];
    }
    
    int get_sum(int n, int left, int right, int query_left, int query_right)
    {
        if(query_right < left || right < query_left || query_right < query_left)
        {
            return 0;
        }
        
        if(query_left <= left && right <= query_right)
        {
            return tree[n];
        }
        
        int mid = (left + right)/2;
        int left_sum = get_sum(LEFT(n), left, mid, query_left, query_right);
        int right_sum = get_sum(RIGHT(n), mid + 1, right, query_left, query_right);
        int answer = left_sum + right_sum;
        
        return answer;
    }
    
    public:
    SegmentTree(int n)
    {
        no_of_elements = n;
        tree.resize(4*no_of_elements, 0);
    }
    
    void update(int position, int value)
    {
        return update(1, 1, no_of_elements, position, value);
    }
    
    int get_sum(int left, int right)
    {
        return get_sum(1, 1, no_of_elements, left, right);
    }
};

void remove(stack <int> &S, SegmentTree &segmentTree)
{
    int n = S.top();
    S.pop();
    segmentTree.update(n, 0);
}

void insert(int n, stack <int> &S, SegmentTree &segmentTree)
{
    S.push(n);
    segmentTree.update(n, 1);
}

int main()
{
    int no_of_elements, no_of_queries;
    cin >> no_of_elements >> no_of_queries;
    
    vector <int> A(no_of_elements + 1);
    for(int i = 1; i <= no_of_elements; i++)
    {
        cin >> A[i];
    }
    
    vector <Query> queries;
    for(int q = 1; q <= no_of_queries; q++)
    {
        int left, right;
        cin >> left >> right;
        
        queries.push_back(Query(left, right, q));
    }
    sort(queries.begin(), queries.end(), sort_by_left);
    
    SegmentTree segmentTree(no_of_elements);
    vector <int> answer(no_of_queries + 1);
    stack <int> prefix_maxima;
    for(int i = no_of_elements, q = no_of_queries - 1; i >= 1; i--)
    {
        while(!prefix_maxima.empty() && A[i] >= A[prefix_maxima.top()])
        {
            remove(prefix_maxima, segmentTree);
        }
        
        insert(i, prefix_maxima, segmentTree);
        
        while(q >= 0 && queries[q].left == i)
        {
            answer[queries[q].index] = segmentTree.get_sum(queries[q].left, queries[q].right);
            q--;
        }
    }
    
    for(int q = 1; q <= no_of_queries; q++)
    {
        cout << answer[q] << "\n";
    }
    
    return 0;
}
