# 17 — Trie

## Concept
- What: Prefix tree; children per char; end-flag + counts. Why: O(L) prefix ops, autocomplete, XOR max.
- When: implement dict, prefix count, replace words, max XOR. Terms: node[26], cntEnd/cntPref, binary trie.

## Syntax
```cpp
struct Node{Node*ch[26]={};int end=0,pref=0;};
```

## Patterns
- Insert/search/startsWith walk-or-create. Count words/prefix via counters.
- Replace: shortest root walk. Distinct substrings: insert suffixes count nodes.
- Max XOR: binary trie greedy opposite bit. Offline max-xor queries sort + insert.

## Algorithms
- Trie-II counters; longest word with all prefixes (dfs); power set of substrings via trie;
- max XOR pair; query bounds; bit-node pool for speed.

## Examples
Insert apple/app: search app true, startsWith appl true. maxXOR [3,10,5,25,2,8]=28.

## Complexity
Insert/search O(L) alphabet O(26*L) naive; XOR O(32n); space nodes*alphabet.

## Common Mistakes
- Forgetting end-flag; pref vs end; char-index for lowercase only; memory blow (use map/array pool).

## Templates
```cpp
struct Trie{struct N{N*ch[26]={};int end=0,pref=0;};N*root=new N();void insert(string s){N*t=root;for(char c:s){int i=c-'a';if(!t->ch[i])t->ch[i]=new N();t=t->ch[i];t->pref++;}t->end++;}bool search(string s){N*t=root;for(char c:s){int i=c-'a';if(!t->ch[i])return false;t=t->ch[i];}return t->end>0;}};
struct BinTrie{struct N{N*ch[2]={};};N*r=new N();void ins(int x){N*t=r;for(int b=31;b>=0;b--){int bit=(x>>b)&1;if(!t->ch[bit])t->ch[bit]=new N();t=t->ch[bit];}}int maxXor(int x){N*t=r;int ans=0;for(int b=31;b>=0;b--){int bit=(x>>b)&1;if(t->ch[bit^1]){ans|=1<<b;t=t->ch[bit^1];}else t=t->ch[bit];}return ans;}};
```

## Revision Summary
Walk-or-create; end vs pref; XOR = opposite-bit greedy; suffixes count distinct.
