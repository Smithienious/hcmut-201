/*
 * Cho node root của một cây nhị phân (Binary Tree), hiện thực hàm sau đây:
 * int findS(Node* root);
 * để tính toán giá trị S = max_value_of_tree - min_value_of_tree. Tất cả cây nhị phân trong test case đều chứa ít nhất 2 node.
 * Lưu ý: Các bạn có thể include thêm thư viện cần thiết
 * Giải thích test case 1: Trong cây nhị phân trên, node root có giá trị lớn nhất (7) và node 2 có giá trị bé nhất (2) nên giá trị của S = 7 - 2 = 5.
 * Cấu trúc của một node được cho bên dưới. Các bạn chỉ cần viết nội dung hàm findS, các cấu trúc khác đã được import sẵn.
 */

class Node
{
  int data;
  Node *left;
  Node *right;

public:
  Node() : data(0), left(nullptr), right(nullptr) {}

  Node(int data, Node *left, Node *right)
  {
    this->data = data;
    this->left = left;
    this->right = right;
  }

  int getData()
  {
    return this->data;
  }

  void setData(int data)
  {
    this->data = data;
  }

  Node *getLeft()
  {
    return this->left;
  }

  void setLeft(Node *left)
  {
    this->left = left;
  }

  Node *getRight()
  {
    return this->right;
  }

  void setRight(Node *right)
  {
    this->right = right;
  }
};

int findS(Node* root)
{

}

int main(int, char **)
{
  /*
    5
   */
  Node *node1 = new Node(5, nullptr, nullptr);
  Node *node2 = new Node(2, nullptr, nullptr);
  Node *root = new Node(7, node1, node2);
  cout << findS(root);
}