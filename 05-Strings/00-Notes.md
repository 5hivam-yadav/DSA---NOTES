# 05 — Strings

## Concept
- What: Char sequences; ASCII basics. Why: parsing/matching/hashing.
- When: anagrams, palindromes, pattern search. Terms: anagram, palindrome, LPS, rolling hash.

## Syntax
```cpp
string s="ab#c"; s.size(); s.substr(i,len); s.find(t);
sort(s.begin(),s.end()); reverse(s.begin(),s.end());
isalpha(c); tolower(c); stoi(s); to_string(x);
```

## Patterns
- Freq count (anagram, isomorphic two maps). Two pointers palindrome.
- Stack/depth for parens. KMP/Z/Rabin-Karp for matching.

## Algorithms
- Remove outer parens via depth. Reverse words. Largest odd from right. LCP column-wise.
- Isomorphic both maps. Rotate via s+s. Anagram 26-count. Roman value+prev.
- Atoi trim/sign/clamp. KMP LPS O(n+m). Z-box. Min inserts = n-LPS.

## Examples
"(())" outer -> "()". "abc" rotated "cab" found in "abcabc".

## Complexity
Most O(n); sorting O(n log n); KMP/Z O(n+m).

## Common Mistakes
- O(n^2) concat in loop; stoi overflow; LPS fallback; negative modulo.

## Templates
```cpp
vector<int> lpsBuild(const string&p){vector<int>l(p.size(),0);for(size_t i=1;i<p.size();i++){int j=l[i-1];while(j>0&&p[i]!=p[j])j=l[j-1];if(p[i]==p[j])j++;l[i]=j;}return l;}
```

## Revision Summary
Count anagrams; two maps isomorphic; depth parens; s+s rotate; KMP/Z matching.
