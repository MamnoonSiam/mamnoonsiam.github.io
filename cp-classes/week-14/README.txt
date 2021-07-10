https://oj.uz/problem/view/COCI20_zapina (simple dp)
https://oj.uz/problem/view/COCI19_grudanje (BS, subarray distinct)
https://oj.uz/problem/view/COCI19_drvca (php, check all possible)
https://oj.uz/problem/view/COCI20_nivelle (relevant segments are small)
https://oj.uz/problem/view/COCI20_klasika (persistent trie)
Hints:
A: this is somewhat straightforward dp, go from left to right, assign ppl problems from the remaining ones and keep track of if atleast one has received expected amount of problems (alternatively count the number of bad ways to distribute problems, and subtract from total ways)
B: Binary search! :shrek_stare: after that, problem reduces to determining is every uncovered element in a range is unique. so try to find equivalent condition of this, which is easy to check
C: If you arbitrarily take three trees, at least two of them will belong to the same group (by php). so take three smallest trees, and bruteforce which two must be on the same group, then you'll get the difference of one group... okay do i need to say more? :shrek_stare:
D: Fix R, then there are 26 relevant values of L that you can find easily
E: binary trie :shrek_stare:
