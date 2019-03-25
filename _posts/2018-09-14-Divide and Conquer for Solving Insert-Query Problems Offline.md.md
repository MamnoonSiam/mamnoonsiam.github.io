---
published: true
title: Divide and Conquer for solving Insert-Query Problems Offline
layout: post
comments: true
author: RezwanArefin01
category: [Data Structure, Divide and Conquer]
share-img: '/img/dnc-insert-query/feature.png'
permalink: '/posts/dnc-insert-query/'
---

আজকে একটা Divide and Conquer Trick নিয়ে কথা বলব। কোন Data Structure এ Insert-Query ধরনের  Problem এর জন্য এই Trick কাজে লাগবে। এই Trick ব্যবহার করা যাবে যখন আমরা Data Structure টা সহজেই Statically Build করতে পারি (সব Insert সব Query এর আগে থাকে), কিন্তু Alternatively Insert আর Query করতে পারি না।

আপাত দৃষ্টিতে এই Trick টা মনে হতে পারে খুবই Specific Problem এর জন্য, কিন্তু আসলে না! এই Trick টা আসলে খুবই Powerful। এটা দিয়ে বিভিন্ন DP Optimize ও করা যায়, আবার Dynamic Convex Hull Trick এর Replacement হিসাবেও ব্যবহার করা যায়। :wink:


শুরুতে একটা খুবই সাধারণ Problem দিয়ে শুরু করা যাক --

> You have an empty set. You need to perform following operations --
1. Insert a given number X in the set.
2. Count how many numbers in the set is less than or equal to a given number X.

যেমন এইরকম হতে পারে --

- $Insert(4) \Rightarrow [4]$
- $Insert(2) \Rightarrow [4, 2]$
- $Query(3) \Rightarrow 1$
- $Query(4) \Rightarrow 2$
- $Insert(3) \Rightarrow [4, 2, 3]$
- $Insert(1) \Rightarrow [4, 2, 3, 1]$
- $Query(4) \Rightarrow 4$


এইটা অনেক উপায়েই Solve করা যায়, যেমন: Ordered-Set অথবা Compress + Binary Indexed Tree ইত্যাদি। কিন্তু এইখানে আমরা Divide and Conquer Approach দেখব।    

আগেই বলেছি যে, সব Insert যদি সব Query এর আগে দেওয়া থাকে, তাহলে আমাদের Solve করতে পারতে হবে। এখন সেটা কিভাবে করা যায়?    
খুব সোজা! আমরা সব Insert করা Number গুলা Sort করে ফেলব, এর পরে একটা Query solve করার জন্য একটা Binary search করাই যথেষ্ট!

এখন আমাদের Problem এ তো আর সব Insert গুলা Query এর আগে থাকবে না। তাহলে কি করব?
আমরা Divide and Conquer use করে সব Insert কে Query এর আগে নিয়ে যাব। :wink:

লক্ষ্য করি, একটা Query তার আগের সব Insert গুলার উপরে নির্ভর করে। কিন্তু তার মানে কিন্তু এইটা না যে আমাদের সব Insert করা জিনিশ গুলা একসাথে থাকা লাগবে। আমরা চাইলে আলাদা আলাদা ভাবেও একেকটা Insert কে Consider করতে পারি।     
যেমন, উপরের উদাহরণে এ Last Query এর জন্য আমাদের সমস্ত Insert করা Number গুলা Consider করতে হবে, মানে $[4, 2, 3, 1]$। কিন্তু আমরা $[4, 2]$ আর $[3, 1]$ এর জন্য Answer merge করেও একই Result পেতে পারি!    

সোজা কথা, আমাদের একটা Query এর জন্য তার আগে সব Insert কে Consider করতে হবে, সেটা একসাথে হোক, অথবা অনেক ভাগে ভাগ করে সব গুলার Answer merge করে হোক। এই কাজটাই আমরা Divide and Conquer দিয়ে করব।   

সেটা করার জন্য আমরা সব Operation গুলাকে মোটামুটি সমান ২ ভাগে ভাগ করব --

![Pic 1](/img/dnc-insert-query/alt1.png)

এখন লক্ষ্য করি, Left side এর সমস্ত Insert, Right side এর সমস্ত Query কে Affect করে। তাহলে আমরা সব Left side এর Insert গুলা দিয়ে আগের মত করে একটা Data Structure বানিয়ে ফেলতে পারি। আর সেইটা ব্যবহার করে Right side এর সব Query গুলার Answer update করে ফেলতে পারি --

![Pic 2](/img/dnc-insert-query/alt2.png)

কিন্তু, আমাদের Right side এর Query গুলা তো আর শুধু মাত্র Left side এর Insert গুলার উপরে নির্ভর করে না। বরং আর কিছু Insert তো Right side এর মধ্যেও আছে। সেইগুলার কি হবে? আবার Left side এর কোন Query-ই তো Solve করা হল না! সেইগুলারই বা কি হবে?    
এইখানেই আসল মজা :wink:। আমরা এখন Left আর Right side এর জন্য আবার একই কাজ করব :wink:। কারণ এখন আমাদের Right side এর Query গুলার জন্য আর Left side এর Insert গুলা Consider করতে হবে না। আমাদের যা Consider করা বাকি আছে সেইগুলা হল Left side এর Query এর জন্য Left Side এর Insert, আর Right side এর Query এর জন্য Right side এর Insert। তাই আমরা একই কাজ এই ২ ভাগের জন্য Recursively করতে পারি। এভাবে করলে সবশেষে যেকোনো Query এর জন্য তার আগের সব Insert কেই Consider করা হয়ে যাবে।

যেমন উপরের কাজ টা Continue করলে এমন হবে --

![Pic 3](/img/dnc-insert-query/alt3.png)

এখানে সব Query এর জন্যই তার আগের সব Insert গুলা Consider করা হয়েছে।   

এখন এটা Implement করা যাক। এটার Implementation ও খুব সোজা। আমরা একটা Function লিখব যেটা $l^{th}$ Operation থেকে $r^{th}$ Operation পর্যন্ত Process করবে। Pseudo Code এরকম হতে পারে --   

```cpp
op[1...n] = operations
ans[1...n] = array to store answers
solve(l, r) {
  if op[l...r] has no queries: return
  m = (l + r) / 2
  ds = statically built DS using insert operations in op[l...m]
  for each query operation i in op[m+1...r]:
    ans[i] += ds.query(op[i])
  solve(l, m)
  solve(m+1, r)
}
```

এখন এইটার Time Complexity Analysis করা যাক। আমাদের এই Solve Process টা সর্বচ্চ $O(\log n)$ Depth পর্যন্ত যাবে। Complexity হবে সব Depth এর Total complexity যোগ করে। এইক্ষেত্রে আমাদের একটা Depth এ অনেক গুলা Sort হচ্ছে। কিন্তু সব গুলা Sort যোগ করলে $O(n \log n)$ হবে। এইরকম $O(\log n)$ টা Level রয়েছে। তাই মোট Complexity $O(n \log^2 n)$।

লক্ষ্য করি, এই Trick আমরা অনেক ধরনের Problem এই ব্যবহার করতে পারি। যেখানে --
1. Offline Solution করা যাবে।  
2. সব Insert যদি Query এর আগে থাকে তাহলে Solve করা যাবে সহজে।
3. আমরা যেইটা Query করছি সেইটা Cumulative।


### **Using this trick to calculate DP**
এইবার দেখা যাক এইটা ব্যবহার করে কিভাবে DP Calculate করা যায়। একটা সাধারণ DP নেওয়া যাক, যেমন Longest Increasing Subsequence। এই প্রবলেম এর সাধারণ Solution এইরকম --

```cpp
for(int i = 1; i <= n; i++) {
  for(int j = 1; j < i; j++) if(a[j] < a[i])
    dp[i] = max(dp[i], dp[j] + 1)
}
```

এখন ব্যপার হল আমরা কিন্তু আসলে এই DP কে একটা Update-Query Problem হিসাবে Model করতে পারি। একটা Index $i$ এর জন্য আমাদের এর আগের সব Index $j$ এর জন্য $max\{ \lbrace dp_j \rbrace \}$ বের করতে হবে, যেখানে $a_j < a_i$।

এইটাকে আমরা এইভাবেই দেখতে পারি তাহলে --

```cpp
for(int i = 1; i <= n; i++) {
  dp[i] = query(a[i]);
  insert({a[i], dp[i]});
}
```

মানে এখন আমাদের Problem টা হয়ে গেল `Query(a[1])-Insert(dp[1])-Query(a[2])-Insert(dp[2])` এইরকম।

এইখানেও কিন্তু আমাদের যদি সব Insert আগে হয় তাহলে খুব সহজেই এই Query গুলা Solve করা যায়। আমরা সব `(a[i], dp[i])` pair কে `a` দিয়ে sort করব। আর একটা Prefix Max রাখব `dp[]` গুলার জন্য। এর পরে Query এর জন্য আমরা একটা Binary Search করে কোন Prefix পর্যন্ত সব `a[j] < a[i]` আছে সেটা বের করতে পারব, এর পরে ওই পর্যন্ত `dp[]` এর Prefix Max নিলেই কাজ শেষ!

কিন্তু এখনো একটু ঘাপলা রয়ে গেছে। আমরা আগের বার যেইভাবে Implement করেছি সেইটা আর কাজ করবে না। আগে আমরা করেছি --

```cpp
solve(l, r) {
  m = (l + r) / 2
  make ds with insert operations in [l...m]
  solve queries [m+1...r] using the ds
  solve(l, m)
  solve(m+1, r)
}
```

এইটা কেন এখন আর কাজ করবেনা? কারণ আমাদের DS এ আমরা Insert করছি `(a, dp)` pair গুলা। এখন `dp` value টাই যদি না জানি তাহলে কি Insert করব?    
এইটা খুবই সহজে Fix করা যায়। আমরা Last এ `solve(l, m), solve(m+1, r)` call করছি। এর মধ্যে `solve(l, m)` নিজেই `dp[l..m]` এর সমস্ত Value Calculate করে ফেলে! কারণ আমরা মাঝখানে তো Left side এর কিছুই করছি না, খালি Right side এর DP গুলা Update করছি। তাই আমরা যদি আগে `solve(l, m)` Call করি তাহলেই আমরা Insert করার জন্য প্রয়োজনীয় DP Value গুলা পেয়ে যাব। :wink:   


```cpp
solve(l, r) {
  m = (l + r) / 2
  solve(l, m)
  make ds with a[l..m] and dp[l..m]
  update dp[m+1..r] using the ds
  solve(m+1, r)
}
```

Done! :wink:

এবার কিছু Problem Solve করা যাক --   

#### **Problem 1:**
>[Live Archive - 5871 - Arnooks's Defensive Line](https://icpcarchive.ecs.baylor.edu/external/58/5871.pdf): প্রবলেম টা হল একটা DS Maintain করতে হবে যাতে এই ২টা Operation করা যায় --   
1. Insert a segment $[l, r]$ in set.
2. Given a segment $[a, b]$. Count how many segments in the set satisfies $l \leq a \leq b \leq r$.

একটা Solution হয় সব সেগমেন্ট Compress করে এর পরে 2D Segment Tree Use করা। কিন্তু সেটার Code অনেক বড় হয়ে যাবে আর Constant ও অনেক বেশি। তাই আমরা এই Divide and Conquer দিয়ে এইটা Solve করব।    

Divide and Conquer যে Use করা যাবে সেইটা আশাকরি সবাই বুঝতে পেরেছি। এখন খালি বের করতে হবে যে, সব Insert যদি সব Query এর আগে হয়,  তাহলে কিভাবে এটা সহজে Solve করা যায়।    

লক্ষ্য করি, এখানে আমাদের একটা Segment $[a, b]$ এর Answer এর জন্য কি করতে হচ্ছে? আমরা চাই **"কয়টা Semgent $[l, r]$ আছে যাতে $l \leq a \leq b \leq r$ হয়?"**। এখন এই জিনিশটাকে আমরা অন্যভাবেও পড়তে পারি -- **"যেইসব Segment এর $l \leq a$, তাদের মধ্যে কয়জনের $r \geq b$?"** এইভাবে ভেবে দেখলে আমরা একটা সহজ Solution পাই --   

আমরা সব Segment কে Sort করব, Insert করার গুলাকেও, Query করার গুলাকেও। শুরুতে Left Side দিয়ে, যদি Tie হয় তাহলে Right Side দিয়ে। এখন আমরা চাই যখন আমরা Segment $[a, b]$ এর জন্য Solution বের করতে যাব তখন যেন যত গুলা Segment এর $l \leq a$ আছে তাদের $r$ একটা DS এ Inserted থাকে। তাহলে আমরা ওই DS এর মধ্যে কয়টা Element $\geq b$ আছে সেইটা বের করলেই হবে। এই DS হিসাবে আমরা Ordered-Set, Segment Tree, BIT অনেক কিছুই ব্যবহার করতে পারি।     

Pseudo Code এইরকম হতে পারে --   

```cpp
ds = data structure that supports inserting an element
     and counting number of elements >= a number
UpdateAnswer(segment[], query[]) {
  sort segments and queries
  l = 0
  for each query i:
    while segment[l].l <= query[i].a:
      ds.insert(segment[l].r), l++
    ans[i] += ds.query(query[i].b)
}
```

Done! :wink: এইবার এইটার উপরে আগের সেই Divide and Conquer লাগায়ে দিলেই Solution Complete। :grin:


#### **Problem 2:**
>[SPOJ - LIS2 - Another Longest Increasing Subsequence Problem](https://www.spoj.com/problems/LIS2/): কতগুলা Pair দেওয়া আছে - $P_1, P_2, \ldots, P_n$। এদের Longest Increasing Subsequence বের করতে হবে। একটা Pair $(a, b)$ আরেকটা Pair $(b, c)$ থেকে ছোট হবে যদি $a < b$ এবং $c < d$ হয়।    

এই প্রবলেমটা ও অবশ্য সব Number Compress করার পরে 2d Segment Tree / BIT দিয়ে করা যায়। কিন্তু তাতে Memory বেশি লাগবে। এই প্রবলেমটা আমরা উপরে করা DP Problem টার মত করে করে ফেলতে পারি। আসলে আমাদের State-Transition সবই কিন্তু 1D LIS এর মতই, খালি একটা Element আরেকটা থেকে ছোট হওয়ার Condition আলাদা। এখানেও আসলে Pair গুলা Sort করে আগের প্রবলেমর মত একটা Dimention কমিয়ে ফেলা যায়। নিজে ভেবে দেখি। :wink:

#### **Problem 3: Most Problems needing Dynamic Convex Hull Trick**
সাধারণত [Convex Hull Trick](https://rezwanarefin01.github.io/posts/convex-hull-trick/) লাগে এমন প্রবলেম এর Format এইরকম হয় --   

```cpp
for(int i = 1; i <= n; i++) {
  dp[i] = query(i);
  insert(f(dp[i]), g(i));
}
```

এখন আমাদের যদি Dynamic Convex Hull Trick লাগে তখন সমস্যা হয়ে যায় (Template না থাকলে :stuck_out_tongue_winking_eye:)। তাই আমরা এইটার উপরে আমাদের Divide and Conquer লাগায়ে দিলে তখন সব Insert আগে চলে আসবে। তখন আমরা Line গুলা Sort করে Normal CHT দিয়েই কাজ চালাতে পারব।

ধন্যবাদ সবাইকে। :slightly_smiling_face:

References: [HKOI 2018 Training](https://assets.hkoi.org/training2018/dc.pdf), and [Tasmeem Reza](http://stats.ioinformatics.org/people/5851).
