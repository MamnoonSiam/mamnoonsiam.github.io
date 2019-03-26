---
published: true
title: Dynamic Programming Optimization - IOI'16 Aliens Trick
layout: post
comments: true
author: RezwanArefin01
category: [Dynamic Programming]
share-img: '/img/wqs/feature.png'
permalink: '/posts/ioi16-aliens-trick/'
---
**History**: IOI 2016 এর Day 2 এ একটা Problem ছিল, Aliens নাম এ। সেই Problem টাতে একটা বিশেষ DP Optimization এর প্রয়োজন হয়েছিল 100 points এর Solution এর জন্য। যদিও 60 points তুলতেই অনেক Observation লাগে। অবশ্য এই Trick এর পূর্বেও Chinese দের মধ্যে প্রচলিত ছিল, WQS-Binary-Search নামে। WQS আসছে Qingshi Wang থেকে, যে Trick টা Chinese Contestants এর মধ্যে Popularize করেছেন। তবে Formally এই Trick টা [Lagrange Multiplier](https://en.wikipedia.org/wiki/Lagrange_multiplier) নাম এ পরিচিত। Competitive Programming এ IOI'16 Aliens Problem টার মাধ্যমেই এইটা জনপ্রিয় হয় বলে এখন এইটা Aliens Trick নামেই বেশি পরিচিত। তবে এটা খালি DP Optimization না, আরও অনেক কিছুই Optimize করতেই কাজে লাগে। :slightly_smiling_face:  

### **Prerequisites**
- Convex Hull Trick জানা থাকলে ভাল হয়।   
- কিছু Graph Plot করতে হতে পারে।   

এই Optimization এর কোন Formal Description এর চেয়ে মনে হয় কিছু Problem দেখে জিনিসটা বুঝাই ভাল হবে। প্রথমে কিছু সহজ Problem দেখা যাক, যেইগুলা বিষয়টা বুঝতে সাহায্য করবে।     

### **Problem 1**
> Given an array $\[a_1, a_2, \cdots, a_n\]$ where $a_i \geq 0$ for all $i$. Divide it into any number of parts you want (parts must contain consecutive elements). Lets say $i^{th}$ part has sum $S_i$. Minimize $\sum S_i^2$.

এটা কিছুক্ষণ ভাবার পরেই বুঝা যাবে যে এই Problem এ আসলে সব সময়ই $n$ টা Part করাই সবচেয়ে Optimal হবে। মনেকরি, আমরা $n$ টা Part করিনি। কোথাও ২টা Element $a$ আর $b$ একসাথে আছে। তাহলে তারা মোট Sum এ $(a + b)^2 = a^2 + b^2 + 2ab$ contribute করে। কিন্তু এদের আলাদা রাখলে $a^2 + b^2$ contribute করত খালি। যেহেতু $a^2 + b^2 \leq (a + b)^2$, এইজন্য যত বেশি Part করব আমরা তত ছোট Sum পাব।       

এবার একই Problem একটু পরিবর্তন করে দেখা যাক -    

### **Problem 2**
> Given an array $\[a_1, a_2, \cdots, a_n\]$ where $a_i \geq 0$ for all $i$. Divide it into any number of parts you want (parts must contain consecutive elements). Lets say $i^{th}$ part has sum $S_i$. Minimize $\sum \lbrace S_i^2 + C \rbrace$, where $C$ is a constant integer.

মনে করি আমরা $k$ টা Part করেছি। তাহলে Sum টাকে লেখা যায় - $\sum_{i = 1}^k \lbrace S_i^2 + C\rbrace = \sum S_i^2 + kC$।  মানে ব্যাপার হল যদি আমরা $k$ টা Part করি তার জন্য আমাদের $kC$ Extra add করতে হচ্ছে এই প্রবলেমে। এখন কিছু Case দেখা যাক -    

- $C \leq 0$, এই ক্ষেত্রে আমদের সবসময় ই $n$ টা Part করা Optimal হবে। কারণ যতবেশি Part করা হবে তত ছোট Sum পাব আমরা।    
- $C = \left(\sum a_i\right)^2$, এইক্ষেত্রে আমাদের সমস্ত Element কে মাত্র ১টা Part এই রাখতে হবে। কারণ এখন ১টা Part এর জন্যই আমাদের $\left(\sum a_i\right)^2$ Extra add করতে হচ্ছে! আমরা যদি ১টা Part করি তাহলে Sum হবে $2C$, কিন্তু ২টা Part করলে তো শুরুতেই আমাদের Extra add করতে হবে $2C$, আর Part গুলার Squared sum তো আছেই। এই জন্য ১টার বেশি Part করলে সেটা কখনোই Optimal হবে না।      
- এখন একটা জিনিস পরিষ্কার, আমরা $C$ কে যত বড় পাব, আমাদের Part ততই কমতে থাকবে। (Intuitive)

এখন এই Problem টা সমাধান করার জন্য Dynamic Programming প্রয়োজন। DP Formula অবশ্য অনেকটা Obvious. মনে করি $f(i)$ হলও শুরুর $i$ টা Element এর জন্য Answer। যদি $p_i = \sum_{j \leq i} a_j$ হয় তাহলে -    

$$f(i) = \min_{j < i} \left\{ f(j) + (p_i - p_j)^2 + C\right\}$$

এটা আমরা সহজেই $O(n^2)$ Complexity তে Implement করতে পারি। আবার $f$ কে একটু সাজিয়ে লিখে Convex Hull Trick দিয়ে $O(n)$ ও করে ফেলতে পারি -    

$$\begin{align*}f(i) &= \min_{j < i} \left\{ 2p_j\times p_i + p_j^2 + f(j) + p_i^2 + C\right\} \\ &= \min_{j < i} \left \{  g_j(p_i)\right\} + p_i^2 + C; \quad g_j(x) = 2p_jx + p_j^2 + f(j)\end{align*}$$

**Off Topic**: এই DP Formula টা আসলে Convex Hull ছাড়াও Optimize করা যায়। আমাদের যদি $\sum S_i^2$ এর বদলে $\sum S_i^3$ থাকত তাহলে কিন্তু আমরা আর CHT ব্যবহার করতে পারতাম না। কিন্তু তাও আরেকভাবে এইটা Optimize করা যায়। [এখানে](https://sites.google.com/site/ubcprogrammingteam/news/1d1ddynamicprogrammingoptimization-parti) শিখা যাবে সেটা। কিন্তু অনেক সংক্ষেপে লেখা এইটা :stuck_out_tongue:। CHT Use করা না গেলে সাধারণত এইটা Use করা যায়, Cost Function Quadrangle Inequality Satisfy করলে।

এবার আসল জায়গায় যাওয়া যাক। এইরকম প্রবলেম হলে কি হবে -    

### **Problem 3**
> Given an array $\[a_1, a_2, \cdots, a_n\]$ where $a_i \geq 0$ for all $i$. Divide it into exactly $k$ parts (parts must contain consecutive elements). Lets say $i^{th}$ part has sum $S_i$. Minimize $\sum S_i^2$.

এই ধরনের Problem ই সাধারণত বেশি দেখা যায়। আর দেখেই বুঝা যায় যে এইটা CHT এর Problem। এইটার জন্য DP Formula Obvious. $f_k(i)$ যদি শুরুর $i$ টা Element কে $k$ টা Part এ ভাগ করলে Optimal Sum হয় তাহলে -   

$$\begin{align*}f_k(i) &= \min_{j < i} \left\{ f_{k - 1}(j) + (p_i - p_j)^2\right\}\\ &= \min_{j < i} \left\{ 2p_j\times p_i + p_j^2 + f_{k - 1}(j) + p_i^2 \right\} \\ &= \min_{j < i} \left \{  g_j(p_i)\right\} + p_i^2; \quad g_j(x) = 2p_jx + p_j^2 + f_{k - 1}(j) \end{align*}$$

এভাবে আমরা সহজেই Bruteforce $O(n^2 k)$ Solution কে $O(nk)$ বানিয়ে ফেলতে পারি। কিন্তু তাহলে সমস্যা কোথায়? ভালই তো Complexity হল!

এখানে সমস্যা হল যদি $k$ এর উপরে কোন ছোট Limit না থাকে তাহলে কি করব? সাধারণত CHT এর এরকম Problem এ Constraints থাকে যে -  $1 \leq k \leq n \leq 5000$, অথবা $1 \leq n \leq 10^5, 1 \leq k \leq 100$। তখন আমরা চোখ বন্ধ করে CHT করে ফেলতে পারি। কিন্তু সমস্যা হল যদি বলা হয় $k \leq n \leq 10^5$? এখন তো আর আমাদের $O(nk)$ হলেও চলবে না! এখনই আমাদের লাগবে IOI'16 Aliens Trick. :wink:

শুরুতে কিছু Observation দেখা যাক। যেমন -   

**Observation 1**: আমরা যদি DP Formula টা কে $f_k(n)$ না ভেবে $f_n(k)$ ভাবি তাহলে কি হয়? মানে $f$ কে যদি $n$ এর Function না ভেবে $k$ এর Function বানাই তাহলে কি হয়? এখানে কিছু Interesting জিনিস ঘটে। প্রথমেই যেইটা বুঝা উচিত সেইটা হল $f_n(k) \geq f_n(k + 1)$। বা কথায় বললে বলা যায়, যদি আমরা $k$ টা Part করি তার থেকে $k + 1$ টা Part করা সব সময়ই Optimal. এইটা মূলত Problem 1 এই আমরা দেখেছি। তার মানে Optimal Solution সব সময় $k$ টা Part ই করবে।    

**Observation 2**: এইটা একটু Less Obvious। আমরা বলতে পারি -  

$$f_n(k - 1) - f_n(k) \geq f_n(k) - f_n(k + 1)$$    

কিন্তু এর মানেই বা কি? এর মানে হল, আমরা আগে যে দেখেছি যত বেশি Part করব আমরা তত ভাল Optimal Solution পাব আমরা। এইখানে বলা হচ্ছে যে আমরা $k - 1$ টা Part এর পরে আরেকটা Part করলে যতটুকু কম Sum পেতাম, এর পরে আরও একটা Part করলে আগের বার যতটুকু কমেছিল তার থেকে কম কমবে। মানে "কমার পরিমাণ" কমতে থাকবে। আরেকভাবে বলা যায় যদি আমরা $f_n$ কে Plot করি তাহলে এইরকম Graph হবে -   

![Plot 1](/img/wqs/plot1.png)

এখানে $x$-axis এ $0$ থেকে $1$ এ গেলে অনেক কমছে Function এর মানটা। এর পরে $2$ তে গেলে মাত্র $3$ ঘর কমছে। এর পরে $3$ এ গেলে মাত্র আরেকঘর। এইভাবে "কমার পরিমাণ" কমছে। বা বলা যায় Graph টার Slope Decreasing.     

এই ধরনের Function কে Convex Function বলে। এটাকে আরও অনেক ভাবে লেখা যায় যেমন -    

$$f_n(k - 1) + f_n(k + 1) \geq 2f_n(k)\\ f(a) + f(b) \geq f\left(\frac{a + b}{2}\right)$$

কিন্তু, এইটা যে Convex Function সেইটা Prove করা একটু কঠিন আসলে। তবে এটা Well Known যে $x^2$ একটা Convex Function। তাই Cost Function এর মধ্যে Convex Function থাকলে সেই DP Formula Convex হবার Chance বেশি।    

আচ্ছা এইবার মূল Trick টা বলা যাক। আমরা একটা নতুন Function Define করি -    

$$\tilde{f_n}(k) = f_n(k) + kC; \; \text{C constant}$$   

এখানে, আমরা Problem 1 আর Problem 2 তে যেই পার্থক্য টা করেছিলাম ঠিক সেইটাই করলাম। মানে প্রত্যেকটা Part এর জন্য আমাদের Extra $C$ "Penalty" Add করতে হবে। তাই $k$ টা Part এর জন্য $kC$ Penalty.    

কিন্তু এইটা আমাদের কিভাবে সাহায্য করে? এখন ব্যাপার হল, আমাদের $\tilde{f_n}$ Function টাও Convex Function বা,  

$$\tilde{f_n}(k - 1) - \tilde{f_n}(k) \geq \tilde{f_n}(k) - \tilde{f_n}(k + 1)$$  

এটা Just Function এর Definition টা Substitute করেই পাওয়া যাবে।    

এখন, $f_n$ আর $\tilde{f_n}$ এর মধ্যে পার্থক্য হল, $f_n$ এর Slope Decreasing ছিল, কিন্তু সেইটা Negative হত না, কিন্তু $\tilde{f_n}$ এর Slope Negative হতে পারে। এর Plot এমন হতে পারে -     

![Plot 2](/img/wqs/plot2.png)

মানে, আমরা খুব কম Part করলেও খারাপ, আবার খুব বেশি Part করলেও খারাপ। Optimal হবে মাঝামাঝি কোন জায়গায়। এইজন্য এই Function টা শুরুতে কমতে থাকবে, "কমার পরিমাণ" ও কমতে থাকবে, কিন্তু এই "কমার পরিমাণ" Negative হয়ে যাবে একসময়।

এইবার আমাদের মূল কাজ, আমরা এই DP Formula থেকে ১টা State ই বাদ দিয়ে দেব। একটা Function Define করি যেইটা যত খুশি Part করে, Exactly $k$ বলে কোন কথা নেই। সেইটাকে আমরা এইভাবে লিখতে পারি -    

$$g_n =  \min_{k = 1}^n \tilde{f_n}(k) = \min_{k = 1}^n \lbrace f_n(k) + kC \rbrace$$   

এখন এইটা Problem টা কিন্তু Exactly আমাদের Problem 2 হয়ে গেছে! এখন আমরা $1$ থেকে $n$ এর মধ্যে যেকোনো সংখ্যক ইচ্ছা Part করতে পারব, বা যতগুলা ইচ্ছা Part করতে পারব, কিন্তু একটা Part এর জন্য আমাদের $C$ করে Penalty আছে। এইটা আমরা আগে যেভাবে করেছি সেইভাবেই করতে পারব।   

তবে সাথে আরেকটা জিনিস Track করতে হবে যে আমাদের Optimal Solution এ আমরা কয়টা Part Use করলাম। মনে করি এটাকে আমরা $p(C)$ বলব, যেটা হল Penalty $C$ হলে $g_n$ Optimal Solution এ কয়টা Part Use করে। এটা করাও সহজ, CHT তে Line Add এর সময় ই আরেকটা জিনিস রেখে দেওয়া যেতে পারে যে আমরা কয়টা Part Use করছি এই State এ আসতে।       

এইবার আমরা আবার Problem 2 এর Case গুলা Formally দেখি -     

- $C = 0$ হলে $p(C) = N$। মানে একটা Part করলে যদি কোন Penalty দেওয়া না লাগে তাহলে আমরা যত খুশি করতে পারি Part। Part যত বেশি তত Optimal.
- $C = (\sum a_i)^2$ হলে $p(C) = 1$। উপরেই বলা হয়েছে কেন।    
- এখন বুঝা যায় যে, আমরা $C$ কে যত বাড়াব, ততই Optimal Solution এ Part এর সংখ্যা কমতে থাকবে।

এইবার **Crux Move**! আমরা $C$ এর উপরে Binary Search করব, যেন আমাদের $g_n$, মানে যত খুশি Part করার Solution টা Exactly $k$ টা Part করে। মনে করি $C = X$ এর জন্য আমাদের $g_n$ এ $k$ টা Part হয়, তাহলে আমাদের মূল Problem এর Answer হবে $g_n - kX$। শেষ! :wink: :grin:    

তবে একটা জিনিস ভাবার আছে, কখনো কি এমন হতে পারে না যে আমারা কোন $C$ ই পাই নি যেইটা Exactly $k$ টা Part করায় Optimal Solution এ? আসলে এমন হতে পারে। কিন্তু এইটা প্রমাণ করা যায় যে এমন সময় যদি আমরা Lowest $C$ যেইটার জন্য Optimal Solution এ $\leq k$ টা Part হয় সেইটা নিয়ে Last এ $kC$ বাদ দিয়ে দেই তাহলেই সঠিক Answer পাওয়া যাবে।    

এবার পুরা জিনিসটাকে Summerize করা যাক -     

```cpp  
solve2(C):
  // Solves the problem without the constraints on the number of
  // parts. But need to add penalty C for each part.  
  // Implement it with CHT, or 1d1d opt using deque,
  // anything that works fast :P
  // It can be done in O(n).
  // Returns pair {optimal solution, number of parts in optimal solution}

solve(k):
  // Finds optimal solution by splitting a[] into exactly k parts
  lo = 0, hi = (sum of a[]) * (sum of a[]);
  best = -1;
  while lo <= hi:
    mid = (lo + hi) / 2;
    if solve2(mid).second <= k:
      best = mid;
      hi = mid - 1;
    else lo = mid + 1;

  pair X = solve2(best);
  return X.first - k * X.second;
```

খুব সহজেই আমাদের $O(nk)$ DP টা $O(n \log S)$ হয়ে গেল! মজার ব্যাপার হলও এখন আমাদের Complexity $k$ এর উপরে Depend ই করে না। :wink:   

এইবার এই Trick Use করে এমন কিছু Problem দেখা যাক -     

#### **Problem 1:**
> একটা Undirected Connected Weighted Graph আছে, $V$ টা Node, $E$ টা Edge, একটা Edge এর Cost সর্বচ্চ $C$। প্রত্যেকটা Edge এর একটা করে Color আছে, White বা Black. আমদের Minimum Spanning Tree বের করতে হবে যেইটাতে Exactly $k$ টা White Edge আছে।  এটা Guranteed যে Solution আছে।  

এইটা অনেক ভাবে Kruskal/Prims' দিয়ে ভাবলেও Aliens Trick ছাড়া মনে হয় Solve করা যায় না। Solution খুবই Simple। উপরের Problem এ আমরা যেমন একটা Penalty Add করে কয়টা Part করছি সেইটা Manipulate করেছিলাম, এইখানে একই ভাবে আমরা কয়টা White Edge নিচ্ছি সেইটা Manipulate করব।    

কিন্তু কিভাবে? Simple! এমরা Kruscall চালানর আগে সব White Edge এর Weight এর সাথে $C$ Add করে নিয়ে এর পরে Minimum Spanning Tree বের করব। এখন $C$ অনেক ছোট হলে MST তে অনেক বেশি White Edge চলে আসতে পারে। আবার $C$ অনেক বড় হলে খুবই কম White Edge আসবে, খালি যেইগুলা না হলে নয় সেইগুলা।    

তাই একই আমরা ভাবে $C$ এর উপরে Binary Search করে Minimum $C$ বের করব যেন আমাদের MST তে $\leq k$ টা White Edge থাকে, এর পরে এই Solution থেকে $kC$ বাদ দিয়ে দিলেই হল। Easy Peasy। :wink:  

এখানেও প্রশ্ন জাগতে পারে যে $\leq k$ টা Edge নিলেও সেটা কেন Answer হবে? এইটাও প্রমাণ করা যায় যে ওই Solution এর ই কিছু Black Edge Remove করে কিছু White Edge Add করা সম্ভব যাতে একই Weight এর MST পাওয়া যায়।     

Complexity হল $O(E \log E \log C)$। কারণ $\log C$ বার আমরা MST বের করব। আর বার বার Sort এর জন্য $O(E \log E)$.  

#### **Problem 2:**
[CF 673E - Levels and Regions](http://codeforces.com/contest/673/problem/E): একই রকমের প্রবলেম, $n$ Length এর একটা Sequence কে $k$ টা Part এ ভাগ করে একটা Objective Function এর Sum Minimize করতে হবে। তবে Function টা অনেক Complex। কিন্তু এইখানেও Function টা Convex এই জন্য আমরা এই Optimization করতে পারি। এই প্রবলেমে $k$ মাত্র $50$, তাই $O(nk)$ Pass করে। তাও Aliens Trick দিয়ে Submit দিয়ে দেখা যেতে পারে।    

একটা প্রশ্ন আসতে পারে যে Function টা আসলেই Convex নাকি বুঝব কি করে? একটা উপায় হল Bruteforce লিখে Check করা :stuck_out_tongue:, অথবা অনেক সময় এমনিই বুঝা যায়, যে বেশি Part করলে Solution Optimize হবার পরিমাণ টা কমতে থাকবে। এই প্রবলেম এটা বুঝা যায় অনেকটা।    

এই Approach এর কিছু Discussion পাওয়া যাবে এখানে - [CF Blog 46693](http://codeforces.com/blog/entry/46693).

#### **Problem 3:**
[CF 739E - Gosha is hunting](http://codeforces.com/contest/739/problem/E): এইটা একটা Div1E Problem, কঠিন হওয়ারই কথা। এই Problem এ Obvious DP তে ৩টা State থাকে। তাই $O(n^3)$ হয়ে যায়। যেহেতু $N \leq 2000$ তাই সেভাবে করা যায় না। কিন্তু মজার ব্যাপার হল আমরা Aliens Trick Use করে DP এর ২টা Dimension ই ফেলে দিতে পারি!!

এই প্রবলেমটা তে একটা জিনিস Minimize করতে না বলে Maximize করতে বলছে। এইজন্য এই প্রবলেম এ আমদের Function টা Convex না আসলে। বরং Concave। অর্থাৎ -    

$$f(k - 1) - f(k) \leq f(k) - f(k + 1); \text{ Or}\\
f(a) + f(b) \leq f\left(\frac{a + b}{2}\right)$$  

অন্যভাবে বলা যায় একটা জিনিস বেশি নিলে Answer যতটা বাড়ে সেই বাড়ার পরিমাণ টা আসতে আসতে কমতে থাকে। এইজন্য এইখানে আমাদের Penalty গুলা যোগ না করে বিয়োগ করতে হবে।     

শুরুতে ১টা Dimension ফেলার চেষ্টা করা যাক, সেটা হবে এরকম - "Find solution without constraints on ultra-balls, but for each ultra-ball, subtract $C$ from answer." এইটা করলে আমাদের DP এর ১টা State কমে যায়। আমার Solution - [37422492](http://codeforces.com/contest/739/submission/37422492)। Complexity $O(n^2 \log n)$.

একই ভাবে আমরা আরও একটা Dimension ফেলে দিতে পারি - "Find solution without constraints on poke ball or ultra ball. But for each ultra ball subtract $C$ from answer, and for each poke ball subtract $D$ form answer". এর পরে আমর Binary Search করে Maximum $C$ আর $D$ বের করব যেন $\leq a$ টা Poke ball আর $\leq b$ টা Ultra ball use হয়। আমার Solution - [37422905](http://codeforces.com/contest/739/submission/37422905)। Complexity $O(n \log^2 n)$।

একটা Div1E এর প্রবলেম এ $n \leq 2000$ এর প্রবলেম এ $O(n \log^2 n)$ Solution থাকা আসলেই আশ্চর্যজনক! এটার কিছু Discussion পাওয়া যাবে এইখানে - [CF Blog 49691](http://codeforces.com/blog/entry/49691)

#### **Problem 4:**
[IOI'16 Aliens](https://oj.uz/problem/view/IOI16_aliens): মূল Problem টাই পরে দিলাম কারণ এইটার State বের করতেই একটু ঝামেলা হতে পারে। এইটার Editorial এইখানে আছে - [IOI'16 Analysis](https://ioinformatics.org/files/ioi2016solutions.pdf)।  

#### **Problem 5:**
[CF 802O - April Fools' Problem (hard)](http://codeforces.com/contest/802/problem/O): Discussion এ এইটার Approach লেখা আছে। এছাড়া Editorial ও আছে।   

#### **Problem 6:**
[ROI'17 Team Selection Contest 2 - Popcorn](https://csacademy.com/contest/romanian-ioi-2017-selection-2/task/popcorn/): এইটা তুলনামূলক কঠিন। এইখানে কিছু Discussion আছে - [CSAcademy Blog at Codeforces](http://codeforces.com/blog/entry/51880).    

এই Aliens Trick টা খুবই Neat। কিন্তু এখনো খুব বেশি Popular না। অনেকেই এখনো জানে না এইটা। তবে এর Problem গুলা Rare। জেনে রাখা ভাল। হয়ত হঠাৎ করে কাজে লাগে যাবে। :slightly_smiling_face:    

ধন্যবাদ সবাইকে। :slightly_smiling_face:
