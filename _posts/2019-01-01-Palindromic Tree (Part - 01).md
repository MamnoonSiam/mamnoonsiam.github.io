---
published: true
title: Palindromic Tree (Part - 01)
layout: post
comments: true
author: RezwanArefin01
category: [Data Structure, String Processing]
share-img: '/img/eertree/feature.png'
permalink: '/posts/palindromic-tree-01/'
---
সহজ কথায় Palindromic Tree হল একটা Data Structure যেইটা কোন String এর সব Palindrome এ Fast access করার সুযোগ করে দেয়।  

আশা করি আমরা সবাই জানি Palindrome কি জিনিস। যেসব String কে উল্টা করে পড়লেও একই থাকে সেগুলাকে Palindrome বলে। আর Palindromic Tree হল একটা **Linear-size** string data structure যেইটা কোন String এর সমস্ত Palindromic sub-string-এ দ্রুত Access করার ব্যবস্থা করে দেয়। এইটা Formally "EERTREE" নামে পরিচিত। এই Tutorial মূলত [MikhailRubinchik.ru](https://codeforces.com/profile/MikhailRubinchik.ru) এর ["EERTREE: An Efficient Data Structure for Processing Palindromes in Strings"](https://arxiv.org/pdf/1506.04862.pdf) - paper এর উপরে ভিত্তি করে হবে।

### **Prerequisites**
- Basic Trie সম্পর্কে ধারনা থাকা লাগবে। (Must)
- Suffix Link সম্পর্কে ধারণা থাকলে ভাল হয়। না থাকলেও চলবে।   
- KMP এর Complexity Analysis!

### **Structure**
যেহেতু Data structure টার নাম "Palindromic Tree", তাই এইটার অবশ্যই একটা Tree ধরনের structure হবে। অন্যান্য Tree এর মত এরও Node থাকবে, Edge থাকবে।     

সাধারণ Trie এর মত এখানে প্রত্যেক Node একটা String নির্দেশ করবে। পার্থক্য হল, সাধারণ Trie তে একটা Node কোন একটা String এর Prefix কে নির্দেশ করে, কিন্তু এখানে একটা Node **একটা মাত্র String** এর কোন Palindromic Sub-string নির্দেশ করবে। মানে একটা String এর সব গুলা Palindromic Sub-string ই থাকবে Tree এর মধ্যে।      

আবার, Trie তে একটা Transition এর মাধ্যমে আমরা শেষে একটা নতুন Character যোগ করা বুঝাই, কিন্তু Palindrome Tree তে আমরা আমরা শুরু এবং শেষ উভয় দিকে একটা Character যোগ করা বুঝাব। যেমন: একটা Node যদি $bb$ নির্দেশ করে, তাহলে Trie দিয়ে $a$ Edge ধরে আগালে যেই Node পেতাম সেটা $bba$ বুঝাত। কিন্তু Palindromic Tree তে সেই Node টা $abba$ বুঝাবে, মানে দুই দিকেই $a$ যোগ হবে। নিচের Diargam টা দেখলে ব্যাপারটা আরও পরিষ্কার হবে:    

![Trie and Palindromic Tree Difference](/img/eertree/st1.png)

আশা করি বুঝা গেছে ব্যাপারটা। কিন্তু এইখানে একটা সমস্যা আছে। এইভাবে Tree বানালে তো কোন Odd Length এর Palindrome ই পাওয়ার কথা না! কারণ সব String এর Length Even থাকছে।

এই সমস্যা দূর করার জন্য Palindromic Tree তে ২টা Root দেওয়া হয়। মনে করি একটা Root 1 আরেকটা Root 2। Root 1 এর কাল্পনিক String এর Length যদি -1 ধরি তাহলে এর দুই পাশে একটা করে Character লাগালে এর Length হবে 1, তাই Odd length এর ও Palindrome store করা সম্ভব হবে। আর Root 2 এ যদি একটা কাল্পনিক Empty String ধরি তাহলে এর দুই পাশে Character যোগ করলে Even length এর Palindrome ও পাওয়া যাবে।   

যেমন: $eertree$ string এর জন্য Palindromic tree টা নিচের মত হবে:

![eertree for "eertree"](/img/eertree/st2.png)

Node আর Edge এর পাশাপাশি Palindromic Tree আরও যা থাকবে সেটা হল: **Suffix Links**! একটা Node এর Suffix Link হবে ওই Node এর String এর সবচেয়ে বড় Proper suffix (মানে সম্পুর্ণ String এর থেকে ছোট Length এর Suffix), যে নিজেও একটা Palindrome.

যেমন: যেই Node এ $eertree$ আছে সেইটার Suffix Link হবে যেই Node এ $ee$ আছে সেই Node। কারণ $ee$ এর চেয়ে বড় length এর আর কোনও Palindromic Suffix নাই এই $eertree$ এর মধ্যে। লক্ষ্য করার বিষয় হল, আমরা কিন্তু এইটাকে Suffix Link না বলে Prefix Link ও বলতে পারি। কারণ, যেহেতু মূল String Palindrome, আবার আমরা যেই Suffix নিচ্ছি সে নিজেও Palindrome, তাই এই Suffix আসলে মূল String এর Prefix ও হবে!    

উপরের $eertree$ এর Palindromic Tree এর মধ্যে Suffix Link গুলা একে দিলে এমন দেখাবে:  

![eertree for "eertree" with suffix links](/img/eertree/st3.png)

আশা করি এটা দেখে Palindromic Tree এর Suffix Link এর ধারণা পরিষ্কার হবে। Suffix Link কেন প্রয়োজন সেটা একটু পরে পরিষ্কার হবে।    

এখানে লক্ষ্য করার বিষয়, যেই String গুলার কোন Palindromic Suffix নাই (অর্থাৎ 1 length এর String, কারণ অন্য যেকোনো String এর নুন্যতম 1 length এর Palindromic suffix থাকবেই), তাদের Suffix Link হল Empty String এর Node টা। আর Empty String এর Suffix Link হল -1 length এর String টা।

এই হল মোটামুটি Palindromic Tree এর Structure. এবার দেখা যাক কিভাবে Palindromic Tree Build করা যায়।    

### **Construction**
Palindromic Tree Online Construct করা যায়। মানে একটা একটা করে Chatacter Add করা যায়। শুরুতে একটা জিনিষ জানা দরকার:  

> একটা $N$ length এর String এ সর্বোচ্চ $N$ টা **Distinct** Palindromic Substring থাকা সম্ভব।  

এটার কারণ একটা String $S$ এর শেষে একটা Character যোগ করা হলে সর্বোচ্চ একটা নতুন Palindrome পাওয়া সম্ভব যেটা আগে $S$ এর মধ্যে ছিল না। তাই একটা একটা করে $N$ টা Character Add করা হলে সর্বোচ্চ $N$ টা **Distinct** Palindrome পাওয়া সম্ভব। আর যেহেতু আমাদের Palindromic Tree String টার সমস্ত Palindromic Sub-string ধারণ করবে, তাই এই Tree এর Size linear হবে। (অবশ্যই আমরা কোন Node এ আসল Sub-string গুলা Store করব না। তাহলে Size $O(n^2)$ হয়ে যাবে :joy:)

তাহলে আমাদের Tree এর একটা Node এ কি কি থাকবে?
- সাধারণ Trie এর মত, এই Node এর পরে কোন কোন Node এ কি Transition করে যাওয়া যায় তার info।  
- এই Node এর String এর Length।
- আর এই Node এর Suffix Link।

এখন আসল Construction এর কাজে আশা যাক:

আমরা Tree Build করার সময় একটা জিনিস Maintain করব: এই পর্যন্ত মূল String এর যেই Prefix Process করা হয়ে গেছে তার সবচেয়ে বড় Palindromic Suffix কোন Node এ আছে সেটা। যেমন: আমাদের Process করা Prefix যদি হয় $xyxaababa$, তাহলে আমরা $ababa$ যেই Node এ আছে সেইটা Note করে রাখব, মনে করি $t$, এরকম:  

![xyxaababa](/img/eertree/st4.png)

এখন এই Prefix এর সাথে একটা নতুন Character যোগ করার মাধ্যমে যদি কোনও নতুন Palindrome সৃষ্টি হয় তাহলে তাকে অবশই এই $t$ এরই কোনও একটা Suffix কে নিয়ে হতে হবে! যেহেতু আমরা শেষে Character যোগ করছি তাই ওইখান থেকে একটা Sub-string শুরু হলে সেইটা অবশই $t$ এর উপর দিয়ে যাবে!   

এখন আমাদের কাজ অনেকটাই KMP এর মত। আমরা দেখব $t$ এর শেষে আমরা নতুন Character, ধরি $c$ বসালে $t$ এর আগেও এই একই Character আছে নাকি মূল String এ। যদি থাকে তাহলে তো কাজ শেষ! একটা $c$ transition দিয়ে নতুন একটা $c[t]c$ node create করলেই হল! কিন্তু যদি $t$ এর শেষে বসানো সম্ভব না হয় তাহলে? তাহলে আমরা $t$ এর Suffix Link ধরে উপরে উঠে সেখানে বসানোর চেষ্টা করব!   

যেমন উপরের string এর শেষে যদি আমরা $a$ বসানোর চেষ্টা করি, তাহলে দেখব যে মূল string এ $t$ এর আগেও $a$ আছে। মানে $t$ এর আগে পরে $a$ যোগ করা সম্ভব। তাই আমরা একটা নতুন Node Create করব যদি already না থাকে:    

![add a](/img/eertree/st5.png)

Tree তে না দেখে মূল String এ দেখলে এমন হবে:

![add b](/img/eertree/st6.png)

কিন্তু আমরা যদি $b$ যোগ করতে চেতাম শেষে, তাহলে তো আর $t$ এর শেষে দেওয়া যেত না! তখন আমাদের $t$ এর Suffix Link ধরে উপরে যেতে হবে, তাহলে আমরা $t$ এর একটা Suffix পাব, আর দেখব এর পরে আমরা $b$ যোগ করতে পারি নাকি:  

![add b](/img/eertree/st7.png)

বা মূল String এ এইরকম:

![add b](/img/eertree/st8.png)

এভাবে করে মূলত আমরা সবচেয়ে বড় Palindromic Suffix বের করার চেষ্টা করছি যেটাতে নতুন Character টা থাকবে। Suffix Link ধরে আগানোর কারণে আমরা সব সময় ই একটা Suffix এর মধ্যে থাকব, আর তার আগে পরে একটা Character যোগ করলে সেইটাও Suffix ই হয়ে পরবর্তিতে। আর এইযে নতুন Node Create করলাম এইটাই হবে **পরবর্তি Round** এর জন্য $t$। কারণ এখন এইটাই এই Prefix এর সব চেয়ে বড় Palindromic Suffix।  

তাহলে বাদ থাকল কি? বাদ আছে নতুন Node এর জন্য Suffix Link বের করা। এইটাও আসলে সোজা। মনে করি আমরা $X$ Node থেকে $cXc$ Node বানিয়েছি। তাহলে এই $cXc$ Node এর Suffix   বের করার জন্য আমাদের এর সবচেয়ে বড় Palindromic Suffix বের করতে হবে। এখন লক্ষ্য করলে দেখা যাবে যে এই Suffix Link টা আসলে $cYc$ ধরনের হবে, যেইখানে $Y$ হল $X$ এর Suffix। চিত্রের সাহায্যে দেখলে সোজা হবে বুঝতে:   

![add b](/img/eertree/st9.png)

Wait! জিনিসটা চেনা চেনা লাগছে না? কারণ একটু আগে আমরা যেই কাজ করেছই এইটা আবার সেই একই কাজ! আগে $t$ থেকে করেছি, আর এখন $X$ থেকে করছি। কিন্তু দুইটারই কাজ একই, সব চেয়ে বড় Suffix বের করা যেইখানে আমরা নতুন Character টা বসাতে পারি!

এখন ব্যাপার হচ্ছে, এইখানে আমরা Suffix বের করছি না ভেবে যদি Prefix বের করছি ভাবই তাহলে ব্যপারটা আরও ভালকরে বুঝা যাবে। আমরা $cXc$ এর যদি একটা Suffix Palindrome বের করি, তাহলে সে Prefix Palindrome ও হবে অবশই। তার মানে সেইটা আমাদের আগের Process করা Prefix এর মধ্যেই থাকবে। উপরে ছবি থেকে আসা করি বুঝা যাবে। এই জন্য আমরা $X$ এর Link ধরে এগিয়ে যদি একটা Node পাই যার আগে পরে $c$ বসানো সম্ভব, তাহলে আমরা এইটা Sure হতে পারি যে $c$ Transition দিয়ে যেই Node পাব সেইটা অবশই আগে থেকে Tree তে থাকবে, আর সেই Node টাই আমরা একটু আগে বানানো নতুন Node এর Suffix Link হিসাবে ব্যবহার করব।

এভাবে একটা একটা করে Character Add করতে থাকলেই আমাদের Palindromic Tree পেয়ে যাব। :grinning:

### **Implementation**
এখন Implementation এ আশা যাক। শুরুতেই আমাদের Trie এর Transition store করার জন্য একটা Array লাগবে, আর Node Number count করার জন্য একটা Variable লাগবে, আর Last process করা Suffix এর জন্য একটা একটা Variable লাগবে। সাথে প্রত্যেকটা Node এর জন্য Length আর Suffix Link Store করার জন্য আর ২টা Array লাগবে:

```cpp
const int N = 1e5+10;
int tree[N][26], idx;
int len[N], link[N], t;
char s[N]; // 1-indexed
```

এখন শুরুতে আমাদের ২টা Root Create করতে হবে। একটার Length হবে -1, আর Suffix link নিজেই। আরেকটা Empty String বা Length 0, আর Link হল আগের -1 length এর Node টা। এদের Node number $1$ আর $2$ দেই। আর এর পরে Node Indexing করব $3$ থেকে, তাই index Varibale কে $2$ করে দিতে হবে। আর শুরুতে $t$ হবে Empty String এর Node এর index, কারণ এইটার পর থেকেই আমরা Character যোগ করা শুরু করব:

```cpp
len[1] = -1, link[1] = 1,;
len[2] = 0, link[2] = 1;
idx = t = 2;
```

এখন মূল Construction এর জায়গায় আসা যাক। একটা Function লিখব যেইটা $p^{th}$ Character টা কে Palindromic Tree তে যোগ করবে।   

এখন শুরুতেই আমাদের কাজ হল, $s_p$ কে $t$ এর শেষে বা এর $t$ Suffix Link ধরে কোন ছোট Suffix এর পরে বসানো যায় সেটা বের করা:  

```cpp
void extend(int p) {
  while(s[p - len[t] - 1] != s[p]) t = link[t];
  ...
}
```

এখানে আমরা $t$ কেই টেনে উপরে তুলে নিচ্ছি। কারণ আমাদের $t$ কে Change করলে সেখানেই যাওয়ার কথা পরে।  

এখন তাহলে আমাদের $t$ উপরে আলোচনার $X$ এর জায়গায় আছে। এখন আমাদের আবার একই কাজ করতে হবে; $X$ এর Link ধরে এগিয়ে আরেকটা জায়গা বের করতে হবে যার পরে $s_p$ বসানো যায়:   

```cpp
...
  int x = link[t];
  while(s[p - len[x] - 1] != s[p]) x = link[x];
...
```

তাহলে আমাদের যা যা লাগবে সেগুলা বের করা শেষ। এখন নতুন Node টা Create করব, যদি সেটা Already না থাকে। কারণ নতুন যেই Palindrome টা পাচ্ছি আমরা সেইটা এর আগের Process করা Prefix এর মধ্যেই চলে আসতে পারে, তখন যেই Node create করতে চাচ্ছি সেটা আগে থেকেই বানানো থাকবে। তাই না থাকলে Create করতে হবে।

নতুন Node এর length হবে যেই Node থেকে Create করছি তার Length থেকে $2$ বেশি। আর Link হবে $X$ কে উপরে তুলে যেই Node পেয়েছি তার থেকে $s_p$ Transition করে যেই Node এ যাওয়া যায় সেইটা। অবশ্য নতুন Character দিয়ে যেই Palindrome টা হয় তার Length যদি 1 হয়, তাহলে Link হবে Empty string এর Node টা।

```cpp
...
  int c = s[p] - 'a';
  if(!tree[t][c]) { // if t - ctc transition doesn't exist
      tree[t][c] = ++idx; // create new node
      len[idx] = len[t] + 2;
      link[idx] = len[idx] == 1 ? 2 : tree[x][c];
  }
...
```

আর খালি একটা জিনিস বাকি। এর পরের Round এর জন্য $t$ কে Update করা। এইটা হবে নতুন Create করা Node টাই:

```cpp
...
  t = tree[t][c];
}
```

সম্পুর্ণ Code হবে নিচের মত:  

```cpp
// this awesome implementation is by the legendary nirxor vy.
// coolest implementation you'll ever see
void extend(int p) {
  while(s[p - len[t] - 1] != s[p]) t = link[t];
  int x = link[t], c = s[p] - 'a';
  while(s[p - len[x] - 1] != s[p]) x = link[x];
  if(!tree[t][c]) {
    tree[t][c] = ++idx;
    len[idx] = len[t] + 2;
    link[idx] = len[idx] == 1 ? 2 : tree[x][c];
  } t = tree[t][c];
}
```

হয়ে গেল Palindromic Tree Build করা। :grinning:

### **Complexity Analysis**
যদি KMP এর Complexity Analysis জেনে থাকই তাহলে এইটা একদম Obvious হবে। উপরের Code এ একটা Character দিয়ে extend করতেই আমার ২টা While loop চলছে। তাই মনে হতে পারে এইটা $O(n^2)$। কিন্তু একটা Character extend করলে $t$ এর Length সর্বোচ্চ দুই বাড়ে। কিন্তু While loop টাতে $t$ এর Length শুধুই কমে। যেহেতু আমরা $t$ এর length সর্বোচ্চ |S| করতে পারব, তাই While loop গুলাও সব মিলেয়ে সর্বোচ $O(|S|)$ বার চলবে। তাই Ovarall Complexity $O(|S|)$, মানে Linear।

এবার কিছু Basic Problem দেখা যাক।   

### **Practice Problems**   

#### **Problem 1**
[Number of Distinct Palindromes](https://vjudge.net/problem/HDU-3948): এটা সবচেয়ে সহজ Problem। Statement:
> Given a string $S~(1 \leq \mid S \mid \leq 10^5)$. Count the number of distinct palindromic sub-strings in it.

এই Problem টা Suffix Array, Manachar আরও অনেক কিছু দিয়েই অনেক হাবিজাবি করে Solve করা যায়। কিন্তু Palindromic Tree দিয়ে মাত্র 10 line এ solve করা যাবে! Palindromic Tree তে যেহেতু সমস্ত Distinct Palindrome থাকে, তাই মোট Node সংখ্যা বিয়োগ দুই হবে Answer। বিয়োগ দুই কারণ ২টা root node আছে তাই।

#### **Problem 2**
> Given a string $S$. For each position of it, count how many palindromic sub-string ends in that position.

মানে একটা String এর প্রত্যেকটা Prefix এর জন্য বলতে হবে এই Prefix এর কয়টা Suffix Palindrome আছে।

মনে করি আমরা String টার একটা Prefix Process করে ফেলেছি, আর এর সবচেয়ে বড় Suffix Palindrome Tree এর Node $t$ তে আছে। তাহলে আমরা কিন্তু $t$ এর থেকে বড় আর কোনও Suffix Palindrome পেতে পারব না, যদি আর কোন Suffix Palindrome থেকে থাকে তাহলে সে $t$ এরই Suffix হবে, আর এইরকম সবচেয়ে বড় Palindrome আমরা পেতে পারি $t$ এর Suffix Link থেকে!   

মানে $t, link(t), link(link(t)), \ldots, root$ এইভাবে যে কয়টা Node Visit করা সম্ভব ($root$ বাদে অবশ্যই) সেইটাই হবে মোট কয়টা Suffix Palindrome আছে তার পরিমাণ।

এখন এইটা সরাসরি Loop চালায়ে করলে তো প্রত্যেকটা Prefix এর জন্যই $O(n)$ লেগে যাবে। তাই আমরা হাল্কা DP করতে পারি। লক্ষ্য করি $t$ এর জন্য answer হল $t, link(t), link(link(t)), \ldots, root$। আবার $link(t)$ এর জন্য answer $link(t), link(link(t)), \ldots root$।

তাহলে আমরা বলতে পারি $ans(t) = 1 + ans(link(t))$. এখন এইটা $O(1)$! আমরা যখন নতুন Node Create করব তখন এই Value টা Update করলেই হবে।

```cpp
int ans[N]; // ans[u] = number of nodes that can be visited  
            // from u by following suffix links
void extend(int p) {
  ...
  if(!tree[t][c]) {
    ...
    ans[idx] = 1 + ans[link[idx]];
  }
  ...
}

// Inside main()
for(int i = 1; i <= N; i++) {
  extend(i);
  cout << ans[t] << endl;
}
```

[SPOJ - NUMOFPAL](https://www.spoj.com/problems/NUMOFPAL/): এই Problem এ বলা হয়েছে একটা String এ মোট কয়টা Palindromic Substring আছে বের করেত। এইটা উপরের প্রব্লেম এর মত করে করা যায়। প্রত্যেক Position এর জন্য কয়টা Palindrome এখানে শেষ হয় যোগ করলেই মোট Palindrome এর সংখ্যা পাওয়া যাবে।

#### **Problem 3**
[ApIO 2014 - Palindrome](https://oj.uz/problem/view/APIO14_palindrome): এই Problem টা Formally "Palindromic Refrain" নামে পরিচিত। মূলত এটাতে বলা আছে:
> Given a string $S$. For each palindromic sub-string $P$ of it, find maximum value of $\mid P \mid \cdot occ(P)$, where $occ(P)$ if the number of times $P$ occurs in $S$.   

2014 তে আসলে Palindromic Tree আবিষ্কারই হয়েছিল না। তাই এই Problem এর খুব কম AC ছিল আসল Contest এ। আর Judge এর Solution ছিল Suffix Array আর সাথে অনেক কিছু দিয়ে। কিন্তু Palindromic Tree দিয়ে এইটা Solve করা অনেক সহজ।   

উপরের Problem টা বুঝে থাকেল এইটা বুঝা সহজ হবে যে, একটা Character দিয়ে Extend করার পরে যদি আমরা Node $t$ পাই, তার মানে আসলে $t$ এর Occurrence $1$ বাড়ানো। কিন্তু শুধু $t$ এর ই Occurrence $1$ বাড়ছে না, বরং $t$ এর মধ্যে আবার যত গুলা Suffix  Palindrome আছে তাদের সবার Occurrence $1$ বাড়ছে।   

তাই আমরা যদি $occ(t)$ কে বারাতে, তাহলে $occ(link(t)), occ(link(link(t))), \ldots$ এদেরও বারাতে হবে। এইটা Online ভাবে করা কঠিন কিন্তু Offline অনেক সহজে করা যায়। আমরা যখন $t$ কে $1$ বাড়ানর সাথে সাথে সব Suffix Link এর Node গুলা Update না করে একসাথে শেষে Update করতে পারি। মানে যখন কোন Node Occurrence বারাতে হবে, তখন আমরা Lazy রেখে আসব। আর সব Lazy কে শেষে এক সাথে Propagate করে দেব। মানে নিচের দিকের Node গুলা থেকে $occ(link(t)) \gets occ(link(t)) + occ(t)$ করব। তাহলেই সব শেষে $occ(t)$ তে $t$ মোট কয়বার আছে সেটা পাওয়া যাবে।

```cpp
int occ[N];

void extend(int p) {
  ...
  ++occ[t];
}

// Inside main()
for(int i = 1; i <= N; i++) extend(i);
for(int i = idx; i > 2; i--) occ[link[i]] += occ[i];
```

আর মূল Problem Solve করার জন্য শুধু `len[i] * occ[i]` এর maximum value বের করতে হবে।   

উপরের [SPOJ - NUMOFPAL](https://www.spoj.com/problems/NUMOFPAL/) ও এইভাবে Solve করা যায়। প্রত্যেকটা Distinct Palindromic Sub-string এর জন্য এর মোট Occurrence যোগ করলেই সর্বমোট Palindromic Sub-string এর সংখ্যা পাওয়া যাবে।

#### **Problem 4**
[Subpalindrome Pairs](https://vjudge.net/problem/URAL-2060): Problem Statement মোটামুটি এইরকম:
> Given a string S. Count number of tuples $(i, j, k)$ such that $i \leq j < k$ and $s_{i \ldots j}$ and $s_{j+1 \ldots k}$ both are palindromes.

এই Problem টা উপরের Problem 2 এর মত করে Solve করা যায়। আমাদের ২টা জিনিস আগে Calculate করে নিতে হবে:

- $suff_i = s_i$ তে শেষ হয় এমন কত গুলা Palindrome আছে। এটা Problem 2 এর অনুরূপ।
- $pref_i = s_i$ তে শুরু হয় এমন কত গুলা Palindrome আছে। এটা বের করার একটা Approach হল মূল String এর Reverse নিয়ে প্রতি Index এ শেষ হয় কয়টা Palindrome সেটা বের করে Array কে আবার উল্টিয়ে দেওয়া।

এখন আমরা Problem এর $j$ এর উপরে Loop চালাব। একটা Index $j$ এর জন্য $i$ এর সম্ভাব্য উপায় $suff_j$ টা, আর $k$ এর উপায় $pref_{j+1}$ টা। এদের গুনফলের যোগফল নিলেই মোট উপায় পাওয়া যাবে, অর্থাৎ,

$$\sum_{j = 1}^{n - 1} suff_j \cdot pref_{j+1}$$

#### **Problem 5**
[CF 159D - Palindrome pairs](https://codeforces.com/problemset/problem/159/D): ঠিক উপরের Problem টার মতই। কিন্তু এইখানে Quadruple $(a, b, x, y)$ count করতে হবে যেন $a \leq b < x \leq y$ হয় এবং $s_{a \ldots b}$ আর $s_{x \ldots y}$ উভয় Palindrome হয়।
আগের Problem এর মত করে এইখানও $suff_i$ আর $pref_i$ calculate করতে হবে। কিন্তু এখানে উত্তর হবে -

$$\sum_{b = 1}^{n - 1} suff_b \cdot \sum_{x = b+1}^{n} pref_x$$

 মানে প্রথম Palindrome টা $b$ তে শেষ হচ্ছে, আর পরের Palindrome টা এর পরে কোথাও শুরু হচ্ছে। দ্বিতীয় Sum টা Suffix Sum বের করে $O(1)$ এ বের করা সম্ভব, তাই মোট Complexity $O(n)$.

আজকে এই পর্যন্তই। আগামী পর্বে আরও কিছু Application নিয়ে আলোচনা করব। ধন্যবাদ সবাইকে :slightly_smiling_face:
