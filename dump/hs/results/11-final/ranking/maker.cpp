/*
JS Script for browser console:

section = document.createElement("section");
section.id = "allRes";
document.getElementsByTagName("body")[0].appendChild(section);
inp = document.getElementById("stClassRoll");
btn = document.getElementById("btnAllList");
i = 1201920010001;
getRes = setInterval(() => {
    inp.value = i++;
    btn.click();
    c = document.getElementById("resultInfo").cloneNode(true);
    allRes.appendChild(c);
    if(i > 1201920010666) clearInterval(getRes);
}, 500);
*/


#include  <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

int to_num(string s) {
  int ret = 0;
  for(int i = 0; i < s.size(); i++) {
    ret *= 10; ret += int(s[i] - '0');
  } return ret;
}

// code name cd mcq term-tot ct exam-tot grade gp high
struct subject {
  string code, name;
  int cq, mcq, total;
};
struct student {
  string name, roll;
  bool pass;
  string gpa;
  int total;
  subject subj[8];
  bool operator < (const student &o) const {
    // return subj[7].total > o.subj[7].total;
    // return total > o.total;
    if(pass != o.pass) return pass > o.pass;
    if(pass) {
      return gpa > o.gpa;
    } else if(gpa == o.gpa) {
      return total > o.total;
    } else {
      return roll < o.roll;
    }
  }
};
vector<string> splitByTab(string line) {
  stringstream ss(line);
  string token;
  vector<string> v;
  while(getline(ss, token, '\t'))
    v.push_back(token);
  return v;
}
subject getSubject(string line) {
  vector<string> v = splitByTab(line);
  subject ret;
  ret.code = v[0];
  ret.name = v[1];
  ret.cq = to_num(v[2]);
  ret.mcq = to_num(v[3]);
  ret.total = to_num(v[5]);
  return ret;
}
int GLC = 0;
student getStudent() { // parse 13 lines from stdin
  student ret;
  string line;
  { // name, roll
    getline(cin, line); GLC++;
    vector<string> v = splitByTab(line);
    if(v.empty()) {
      // cout << "yep " << GLC << endl;
      cerr << "something's wrong" << endl;
      exit(0);
    }
    string name = v[0], roll = v[1];
    for(int i = 0; i < 6; i++) name.erase(name.begin());
    for(int i = 0; i < 12; i++) roll.erase(roll.begin());
    ret.name = name;
    ret.roll = roll;
    // cout << roll << endl;
  }
  { // BS line
    getline(cin, line); GLC++; // exam name
    getline(cin, line); GLC++; // titles
  }
  { // 8 subjects
    for(int i = 0; i < 8; i++) {
      getline(cin, line); GLC++;
      ret.subj[i] = getSubject(line);
    }
  }
  { // grand total
    getline(cin, line); GLC++;
    vector<string> v = splitByTab(line);
    ret.total = to_num(v[1]);
  }
  { // pass/fail + gpa
    getline(cin, line); GLC++;
    if(line[0] == 'F') {
      ret.pass = 0;
      ret.gpa = "-&#8734;";
    } else {
      ret.pass = 1;
      vector<string> v = splitByTab(line);
      for(int i = 0; i < 4; i++) {
        v[0].erase(v[0].begin());
      }
      ret.gpa = v[0];
      if(ret.gpa.size() != 4) {
        // cout << ret.roll << ' ' << ret.gpa << endl;
      }
    }
  }
  return ret;
}

string wrapTD(int num) {
  string s = to_string(num);
  s = "<td>" + s + "</td>";
  return s;
}
string wrapTD(string s) {
  s = "<td>" + s + "</td>";
  return s;
}

/*
First clear out those "8 subject not found" entries, delete them.
Make sure you deleted the first entry (if you did ctrl + A while copying)
Then run.
*/

int main(int argc, char const *argv[])
{
#ifdef LOCAL
  freopen("raw-text", "r", stdin);
  freopen("ranking.html", "w", stdout);
#endif
  vector<student> all;
  for(int i = 0; i < 662; i++) {
    // cout << i << endl;
    all.push_back(getStudent());
  }
  /*map<string, int> mp;
  for(student one : all) {
    mp[one.roll]++;
  }
  for(auto el : mp) {
    if(el.second > 1) {
      cout << el.first << ' ' << el.second << endl;
    }
  }*/


  // exit(0);
  sort(all.begin(), all.end());
  int rank = 0;
  cout << "<!DOCTYPE html>\n<!DOCTYPE html>\n<html>\n<head>\n\t<title>Ranklist</title>\n\t<style>\n\t\ttable, th, td {\n\t\t\tborder: 1px solid black;\n\t\t\tborder-collapse: collapse;\n\t\t}\n\t</style>\n</head>\n<body>\n<table>" << endl;
  cout << "<tr><td>Rank</td><td>Roll</td><td>Name</td><td>Bangla 1st paper</td><td>English 1st paper</td><td>Biology 1st paper</td><td>Biology 2nd paper</td><td>Physics 1st paper</td><td>Chemistry 1st paper</td><td>Higher Math 1st paper</td><td>ICT</td><td>Total</td><td>GPA</td></tr>" << endl;
  for(student one : all) {
    cout << "<tr>";
    cout << wrapTD(++rank);
    cout << wrapTD(one.roll);
    cout << wrapTD(one.name);
    for(int i = 0; i < 8; i++) {
      cout << wrapTD(one.subj[i].total);
    }
    cout << wrapTD(one.total);
    cout << wrapTD(one.gpa);
    cout << "</tr>";
    cout << endl;
    cerr << rank << ' ' << one.total << endl;
  }
  cout << "</table>\n</body>\n</html>\n" << endl;

  return 0;
}

/*
<tr>
  <td>Rank</td>
  <td>Roll</td>
  <td>Name</td>
  <td>Bangla 1st paper</td>
  <td>English 1st paper</td>
  <td>Biology 1st paper</td>
  <td>Biology 2nd paper</td>
  <td>Physics 1st paper</td>
  <td>Chemistry 1st paper</td>
  <td>Higher Math 1st paper</td>
  <td>ICT</td>
  <td>Total</td>
  <td>GPA</td>
</tr>
*/