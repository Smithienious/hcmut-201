#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

//please make sure your folder contains everything listed here:
//add.txt, remove.txt, search.txt, autoTester.cpp
//result_1.txt to result_5.txt

//copy your your BKUTree here and watch the miracle (or disaster) happens
//starting from before template<class K, class V> class BKUTree{...
//and ending after its ...};
//basically chop down your BKUTree and bring it here
//I seriously don't know if there's a simpler way to word it

//running this on a local compiler (devC, VS, VSC, CodeBlock) is not advised
//writing to files takes ages, probably gonna take a week, idk why
//Repl.it recommended, just give it a try even if it's only for this session
//upload everything to a new repl and run g++ autoTester.cpp -o aT && ./aT
//in the console (or copy everything in this file and paste it in main.cpp there
//and hit run, suit yourself)

//good luck lol

//also if for some reason this breaks then you're shit out of luck
//have fun scrolling in chat looking for mains and files

//code goes here

//code ends here

//functions used during other tests
void compareFile(string fn1, string fn2)
{
  fstream f1(fn1);
  fstream f2(fn2);
  if (f1.fail() || f2.fail())
  {
    cout << "Failed to open " << fn1 << " and " << fn2;
    cout << "\nCheck if the you have those files.\n";
  }
  bool error = false;
  string lineA;
  string lineB;
  int line1 = 0, line2 = 0;
  while (getline(f1, lineA))
  {
    line1++;
    if (getline(f2, lineB))
    {
      if (lineA != lineB)
        error = true;
      line2++;
    }
    if (line1 != line2)
      break;
  }
  if (getline(f2, lineB) || line1 != line2)
    error = true;
  if (error)
    cout << fn1 << " is NOT IDENTICAL to " << fn2 << "\n";
  else
    cout << fn1 << " IS IDENTICAL to " << fn2 << "\n";
}
//functions used during secondary tests
template <typename K, typename V>
void print(K key, V value)
{
  fstream output("pending.txt", ios::app);
  output << key << '\n';
  //cout << key << '\n';
  output.close();
}
void print_path(vector<int> vec)
{
  fstream output("pending.txt", ios::app);
  for (auto e : vec)
  {
    output << e << ' ';
  }
  output << '\n';
  output.close();
}

//secondary testing mains
int sub1()
{ //pure splay
  BKUTree<int, int>::SplayTree Splaytree;

  ifstream input("add.txt");
  ifstream input_2("remove.txt");

  int i = 0;

  for (string line; getline(input, line);)
  {
    Splaytree.add(stoi(line), stoi(line) - 3);
  }

  for (string line; getline(input_2, line); i++)
  {
    Splaytree.remove(stoi(line));
  }

  input.close();
  input_2.close();

  Splaytree.traverseNLR(&print<int, int>);

  return 0;
}
int sub2()
{ //pure avl
  BKUTree<int, int>::AVLTree Splaytree;

  ifstream input("add.txt");
  ifstream input_2("remove.txt");

  int i = 0;

  for (string line; getline(input, line);)
  {
    Splaytree.add(stoi(line), stoi(line) - 3);
  }

  for (string line; getline(input_2, line); i++)
  {
    Splaytree.remove(stoi(line));
  }

  input.close();
  input_2.close();

  Splaytree.traverseNLR(&print<int, int>);

  return 0;
}
int sub3()
{ //bkut add remove
  BKUTree<int, int> BKUtree;

  ifstream input_1("add.txt");
  ifstream input_2("remove.txt");

  for (string line; getline(input_1, line);)
  {
    BKUtree.add(stoi(line), 12);
  }

  for (string line; getline(input_2, line);)
  {
    BKUtree.remove(stoi(line));
  }

  input_1.close();
  input_2.close();

  BKUtree.traverseNLROnAVL(&print<int, int>);
  //cout << "================================" << '\n';
  BKUtree.traverseNLROnSplay(&print<int, int>);

  return 0;
}
int sub4()
{ //bkut add search
  BKUTree<int, int> BKUtree;

  ifstream input_1("add.txt");
  ifstream input_2("remove.txt");

  for (string line; getline(input_1, line);)
  {
    BKUtree.add(stoi(line), 12);
  }

  for (string line; getline(input_2, line);)
  {
    vector<int> path;
    BKUtree.search(stoi(line), path);
    print_path(path);
  }

  //cout << "================================" << '\n';

  input_1.close();
  input_2.close();

  BKUtree.traverseNLROnAVL(&print<int, int>);
  //cout << "================================" << '\n';
  BKUtree.traverseNLROnSplay(&print<int, int>);
  return 0;
}
int sub5()
{ //bkut add search remove
  BKUTree<int, int> BKUtree;

  ifstream input_1("add.txt");
  ifstream input_2("remove.txt");

  for (string line; getline(input_1, line);)
  {
    BKUtree.add(stoi(line), 12);
  }

  for (string line; getline(input_2, line);)
  {
    vector<int> path;
    BKUtree.search(stoi(line), path);
    print_path(path);
  }

  //cout << "================================" << '\n';

  input_1.close();
  input_2.close();

  ifstream input_3("remove.txt");

  for (string line; getline(input_3, line);)
  {
    BKUtree.remove(stoi(line));
  }

  BKUtree.traverseNLROnAVL(&print<int, int>);
  //cout << "================================" << '\n';
  BKUtree.traverseNLROnSplay(&print<int, int>);
  //cout << "================================" << '\n';

  input_3.close();

  BKUtree.clear();

  ifstream input_4("add.txt");
  ifstream input_5("search.txt");

  for (string line; getline(input_4, line);)
  {
    BKUtree.add(stoi(line), 12);
  }

  for (string line; getline(input_5, line);)
  {
    vector<int> path;
    BKUtree.search(stoi(line), path);
    print_path(path);
  }

  input_4.close();
  input_5.close();

  return 0;
}

//other testing mains
int compareResult()
{ //compare answer and result
  for (int i = 1; i <= 5; i++)
  {
    compareFile("answer_" + to_string(i) + ".txt", "result_" + to_string(i) + ".txt");
  }

  return 0;
}
int main()
{
  char const oldName[] = "pending.txt";
  char const *newName[5] = {"answer_1.txt", "answer_2.txt", "answer_3.txt", "answer_4.txt", "answer_5.txt"};
  //wiping all old answer files
  for (int i = 0; i < 5; i++)
  {
    remove(newName[i]);
  }
  remove(oldName);
  //tests start here
  cout << "Generating files...\n";
  sub1();
  cout << "Finished running test 1...\n";
  rename(oldName, newName[0]);
  sub2();
  cout << "Finished running test 2...\n";
  rename(oldName, newName[1]);
  sub3();
  cout << "Finished running test 3...\n";
  rename(oldName, newName[2]);
  sub4();
  cout << "Finished running test 4...\n";
  rename(oldName, newName[3]);
  sub5();
  cout << "Finished running test 5...\n";
  rename(oldName, newName[4]);
  cout << "Comparing files...\n";
  compareResult();

  return 0;
}

//there's a reason why I write stuff down here
//it's to remind people that they're wasting time hunting for
//easter eggs and other random things
//nah jk merry Xmax
