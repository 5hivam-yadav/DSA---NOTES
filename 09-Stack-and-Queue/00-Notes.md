# 09 — Stack and Queue

## Concept
- What: LIFO stack, FIFO queue; monotonic variants keep order. Why: nesting, next-greater, windows.
- When: parens, postfix, NGE, trapping, sliding max, LRU. Terms: monotonic stack, deque, circular.

## Syntax
```cpp
stack<int> st; st.push(x); st.top(); st.pop();
queue<int> q; deque<int> dq;
```

## Patterns
- Stack for nesting/cancel (parens, asteroid). Postfix eval. Infix->postfix precedence.
- Monotonic decreasing for NGE/previous-smaller (strictness matters).
- Deque window max; two stacks queue; queue via stack; min-stack pair.

## Algorithms
- Valid parens map; min-stack (val,min); prefix/infix/postfix conversions;
- NGE/NSE/PSE to left/right one pass; trapping min(Lmax,Rmax)-h; sum subarray minimums contribution; asteroid collisions; largest rectangle heights+sentinel; sliding max deque; LRU hash+DLL.

## Examples
[2,1,5,6,2,3] largest rect=10. NGE [4,5,2,25] -> [5,25,25,-1].

## Complexity
Each pushed/popped once: O(n)/O(n); queue ops O(1).

## Common Mistakes
- Strict vs non-strict pop (dup widths); sentinel forgotten; deque stale index; postfix order a op b.

## Templates
```cpp
vector<int> nge(vector<int>&a){int n=a.size();vector<int>r(n,-1);vector<int>st;for(int i=n-1;i>=0;i--){while(!st.empty()&&a[st.back()]<=a[i])st.pop_back();if(!st.empty())r[i]=a[st.back()];st.push_back(i);}return r;}
```

## Revision Summary
Nesting=stack; NGE/monotonic; window=deque; conversions=precedence+stack.
