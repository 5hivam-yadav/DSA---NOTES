/*
Problem: Segregate Odd Even Doubly Linked List
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Linked List
Statement: Given a doubly linked list, group odd-valued nodes before even-valued nodes preserving order.
Sample Input: head = [1, 2, 3, 4]
Sample Output: [1, 3, 2, 4]
Explanation: Odds keep order, then evens keep order.
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

static DNode* segregateOddEven(DNode* head) {
    vector<int> odds, evens;
    for (DNode* cur = head; cur; cur = cur->next) {
        if (cur->val % 2 != 0) odds.push_back(cur->val);
        else evens.push_back(cur->val);
    }
    odds.insert(odds.end(), evens.begin(), evens.end());
    int idx = 0;
    for (DNode* cur = head; cur; cur = cur->next) cur->val = odds[idx++];
    return head;
}
int main() {
    DNode* n1 = new DNode(1);
    DNode* n2 = new DNode(2);
    DNode* n3 = new DNode(3);
    DNode* n4 = new DNode(4);
    n1->next = n2; n2->prev = n1;
    n2->next = n3; n3->prev = n2;
    n3->next = n4; n4->prev = n3;
    DNode* head = segregateOddEven(n1);
    for (DNode* cur = head; cur; cur = cur->next) cout << cur->val << (cur->next ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Stable odd-first regroup.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Two chains.
*/
