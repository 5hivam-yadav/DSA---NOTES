# 13 — Binary Tree

## Concept
- What: Each node <=2 children; traversals define order. Why: hierarchies, BST/graph base.
- When: paths, views, LCA, diameter, serialization. Terms: height/depth, leaf, ancestor, skewed.

## Syntax
```cpp
struct TreeNode{int val;TreeNode*left,*right;TreeNode(int x):val(x),left(nullptr),right(nullptr){}};
```

## Patterns
- DFS return info (height+diameter, balanced flag). Path root->leaf carry sum/path.
- BFS level views (left/right/top/bottom/vertical via hd map). LCA post-order.
- Build from traversals via map + bounds. Serialize preorder with #.

## Algorithms
- Pre/in/post iterative+recursive; level order; max depth; balanced check -1 sentinel;
- diameter max(lh+rh); max path any-to-any; same tree; zigzag; boundary; vertical/hd; top/bottom view;
- left/right view first-per-level; symmetric mirror; root-to-leaf paths; LCA; width index; children-sum; nodes K distance; burn time; flatten Morris/stack; serialize.

## Examples
[1,2,3,4,5] diameter=3 (4-2-1-3 or 5-2-1-3). LCA(4,5)=2.

## Complexity
O(n) time; skewed O(n) stack, balanced O(log n); views O(n).

## Common Mistakes
- Null checks; height edges vs nodes; diameter update global; index overflow (use long long/unsigned); reference vs copy path.

## Templates
```cpp
int dfsH(TreeNode*r,int&d){if(!r)return 0;int l=dfsH(r->left,d),rr=dfsH(r->right,d);d=max(d,l+rr);return 1+max(l,rr);}
TreeNode* lca(TreeNode*r,TreeNode*p,TreeNode*q){if(!r||r==p||r==q)return r;auto L=lca(r->left,p,q),R=lca(r->right,p,q);return L&&R?r:(L?L:R);}
```

## Revision Summary
DFS info-up; BFS views; LCA post-order; diameter/path globals; index for width.
