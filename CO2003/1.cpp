/*
 * Cho node root của một danh sách liên kết đơn, hiện thực hàm sau đây:
 * void reduceDuplicate(Node* root);
 * để giảm các phần tử trùng lặp liên tiếp trong danh sách. Nếu có các phần tử liên tiếp giống nhau, ta chỉ giữ lại 1 phần tử.
 * Ví dụ, ta có 1 danh sách 122234452, sau khi thực hiện hàm reduceDuplicate ta thu được danh sách 123452. (số 2 cuối cùng giữ nguyên do nó không liên tiếp với dãy 222 phía trước)
 * Lưu ý: Các bạn có thể include thêm thư viện nếu cần thiết
 * Cấu trúc của một node được cho bên dưới. Các bạn chỉ cần viết nội dung hàm reduceDuplicate, các cấu trúc khác đã được import sẵn.
 */

class Node
{
  int data;
  Node *next;

public:
  Node() : data(0), next(nullptr) {}

  Node(int data, Node *next)
  {
    this->data = data;
    this->next = next;
  }

  int getData()
  {
    return this->data;
  }

  void setData(int data)
  {
    this->data = data;
  }

  Node *getNext()
  {
    return this->next;
  }

  void setNext(Node *next)
  {
    this->next = next;
  }
};

void reduceDuplicate(Node *root)
{
}

int main(int, char **)
{
  /*
    HEAD -> 0 -> 1 -> 1 -> NULL
    HEAD -> 0 -> 1 -> NULL
   */
  Node *node1 = new Node(1, nullptr);
  Node *node2 = new Node(1, node1);
  Node *node3 = new Node(0, node2);
  printList(node3);
  reduceDuplicate(node3);
  printList(node3);
}