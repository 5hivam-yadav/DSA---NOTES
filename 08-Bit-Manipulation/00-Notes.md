# 08 — Bit Manipulation

## Concept
- What: Direct binary ops: AND OR XOR NOT shifts. Why: O(1) flags, parity, power-of-2 tricks.
- When: single number, counting bits, subsets, XOR window. Terms: mask, LSB/MSB, two's complement.

## Syntax
```cpp
x & 1; x >> 1; x << k; x & (x-1); __builtin_popcount(x);
a ^ b; ~x; x | (1<<k); x & ~(1<<k);
```

## Patterns
- x&(x-1) clears lowest set bit. XOR cancels pairs. Mask per bit for Mod-3 single-II.
- Subset via bitmask 0..(1<<n). Divide via shifting.

## Algorithms
- Odd/even &1; check/set/clear/toggle kth; power-of-2 (x>0 && (x&(x-1))==0);
- count set bits; single-I XOR; single-II bit-count mod 3; single-III separate by differing bit;
- min flips (XOR popcount); power set mask; divide with shifts + overflow clamp.

## Examples
x=12 (1100), x&(x-1)=8. Single [2,2,1] XOR=1.

## Complexity
O(1) or O(32)/O(n); subsets O(2^n * n).

## Common Mistakes
- Shift >= width UB; signed shift; INT_MIN/-1 overflow; forgetting long long.

## Templates
```cpp
int popcnt(int x){int c=0;while(x){x&=x-1;c++;}return c;}
bool isPow2(int x){return x>0 && (x&(x-1))==0;}
```

## Revision Summary
x&(x-1); XOR cancel; mask per bit; subsets = masks; divide = shifts.
