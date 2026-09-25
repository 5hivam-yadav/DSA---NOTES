/*
Problem: Introduction to Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Linked List
Statement: Introduce doubly linked list basics: build 1<->2<->3 and traverse forward and backward.
Sample Input: values = [1,2,3]
Sample Output: forward [1,2,3], backward [3,2,1]
Explanation: Prev/next links run both directions.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>
#include <numeric>
#include <cmath>
#include <climits>
using namespace std;

struct DNode {
    int val;
    DNode* prev;
    DNode* next;
    DNode(int x): val(x), prev(nullptr), next(nullptr) {}
};

int main() {
    DNode* n1 = new DNode(1);
    DNode* n2 = new DNode(2);
    DNode* n3 = new DNode(3);
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    cout << "forward [";
    for (DNode* cur = n1; cur; cur = cur->next) cout << cur->val << (cur->next ? "," : "");
    cout << "], backward [";
    for (DNode* cur = n3; cur; cur = cur->prev) cout << cur->val << (cur->prev ? "," : "");
    cout << "]" << endl;
    return 0;
}

/*
Approach:
Two links per node.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
prev + next.
*/
