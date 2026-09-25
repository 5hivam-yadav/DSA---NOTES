# 06 — Linked List

## Concept
- What: Nodes + pointers; singly/doubly. Why: O(1) splice; dynamic size.
- When: constant insert/delete, merge lists. Terms: head/tail, dummy, fast/slow, reverse.

## Syntax
```cpp
struct Node{int data;Node*next;Node(int d):data(d),next(nullptr){}};
Node*d=new Node(1); d->next=new Node(2);
```

## Patterns
- Dummy head for deletes; fast/slow for middle/cycle/nth-from-end.
- In-place reverse prev/curr; merge sorted; add numbers digit-wise.

## Algorithms
- Basics traverse/insert/delete; reverse iter+recur; middle; cycle detect+entry;
- odd-even; remove nth-from-end; sort 0/1/2 chains; Y-intersection; add 1 / add two; sort list; reverse K-group.

## Examples
1->2->3->4 middle=3. Cycle 1->2->3->2 entry=2.

## Complexity
Traverse/reverse O(n)/O(1); merge-sort list O(n log n).

## Common Mistakes
- Losing next; null deref; K-group off-by-one; forgetting head update.

## Templates
```cpp
Node* rev(Node*h){Node*p=nullptr;while(h){Node*n=h->next;h->next=p;p=h;h=n;}return p;}
bool hasCycle(Node*h){Node*s=h,*f=h;while(f&&f->next){s=s->next;f=f->next->next;if(s==f)return true;}return false;}
```

## Revision Summary
Dummy + fast/slow + prev/curr reverse solve 90%. Draw 3 pointers first.
