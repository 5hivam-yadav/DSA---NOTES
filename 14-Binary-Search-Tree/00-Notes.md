# 14 — Binary Search Tree

## Concept
- What: Binary tree with left<root<right (no dup). Why: O(h) search/insert/delete, ordered stats.
- When: ceil/floor, kth, validate, LCA, successor. Terms: inorder sorted, predecessor/successor, height h.

## Syntax
```cpp
TreeNode* searchBST(TreeNode*r,int x){while(r){if(x==r->val)return r;r=(x<r->val)?r->left:r->right;}return nullptr;}
```

## Patterns
- BST property + bounds (validate). Inorder = sorted (kth, two-sum, recover).
- Delete: leaf/one-child/two-child (replace with inorder successor). LCA via value compare.

## Algorithms
- Search/insert iterative; ceil/floor track best; kth via counter; validate min/max range (long long);
- LCA BST; build from preorder bounds; inorder succ/pred; BST iterator stack O(h); recover swapped; two-sum two iterators; largest BST (size,min,max); merge via sorted lists.

## Examples
BST [4,2,6,1,3] ceil(3)=3 floor(3)=3. kth=3 -> 3. LCA(1,3)=2.

## Complexity
Balanced O(log n), worst O(n); iterator O(1) amortized O(h) space.

## Common Mistakes
- int min/max edge (use long long); equal handling; delete successor link; iterator hasNext logic.

## Templates
```cpp
int ceilBST(TreeNode*r,int x){int c=-1;while(r){if(r->val>=x){c=r->val;r=r->left;}else r=r->right;}return c;}
bool valid(TreeNode*r,long long lo,long long hi){return !r||(r->val>lo&&r->val<hi&&valid(r->left,lo,r->val)&&valid(r->right,r->val,hi));}
```

## Revision Summary
Inorder sorted; bounds validate; ceil/floor track; kth counter; LCA by value.
