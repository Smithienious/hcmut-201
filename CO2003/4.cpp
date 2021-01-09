/*
 * Trong ngày hội CSE Job Fair 2020, Ban tổ chức đã treo cờ dọc theo đường dẫn vào tòa H6, có N lá cờ được đánh số từ 1 đến N, lá cờ thứ i có màu Ai. Tuy nhiên, sau khi treo cờ lên, người tổ chức sự kiện - bạn Quang Anh thấy dãy cờ có nhiều màu sắc khác nhau là không hợp lý. Phía Đoàn hội tiến hành rà soát và cho biết còn dư M lá cờ, đánh số từ 1 đến M, lá cờ thứ j có màu Bj. Ban tổ chức quyết định sẽ thay thế một số lá cờ trong số N lá cờ ban đầu để được dãy cờ mới có ít màu nhất có thể. Lá cờ bị thay xuống sẽ bị rách nên không thể dùng lại cho các lần thay tiếp theo, cũng như do thời gian có hạn, bất kì lá cờ nào thay lên cũng không được phép gỡ xuống.
 * Yêu cầu: Hãy tìm cách thay một số (hoặc giữ nguyên) lá cờ đã treo bằng một số lá cờ trong số cờ còn dư sao cho tổng số màu xuất hiện trên dãy cờ chính thức (N lá) là ít nhất.
 * Dữ liệu:
 * Dòng đầu ghi hai số N và M lần lượt là số lá cờ chính thức và số lá cờ còn dư
 * Dòng thứ hai ghi N số nguyên Ai cho biết màu của các lá cờ đã treo (0 <= Ai <= 255, 1<= i <= N)
 * Dòng thứ ba ghi M số nguyên Bj cho biết màu của các lá cờ còn dư (0 <= Bj <= 255, 1<= j <= M)
 * Kết quả: in ra một số duy nhất, không có bất kì khoảng trắng nào, là số màu mới của dãy cờ chính thức sau khi được thay thế.
 * Giải thích testcase 1:
 * Dãy cờ mới sẽ là 1 2 5 5 2 5 5 5 5 -> Có 3 màu trong dãy cờ mới.
 * Các thư viện ĐÃ có trong bài, các bạn KHÔNG được phép thêm bất kì thư viện nào khác:
 * #include <iostream>
 * #include <fstream>
 * #include <string>
 * #include <cmath>
 * #include <vector>
 * #include <algorithm>
 * #include <stack>
 * #include <queue>
 * #include <map>
 */

//Helping functions goes here
int flag(int n, int m, vector<int> A, vector<int> B)
{
  //TODO
}

void Test1()
{
  /*
    3
   */
  int n = 9;
  int m = 4;
  vector<int> A({1, 2, 5, 4, 8, 9, 3, 5, 5});
  vector<int> B({2, 5, 5, 5});
  cout << flag(n, m, A, B);
}

void Test2()
{
  /*
    43
   */
  int n = 45;
  int m = 1;
  vector<int> A({32, 134, 131, 44, 194, 254, 63, 209, 140, 181, 29, 108, 94, 153, 165, 117, 159, 2, 33, 31, 133, 229, 255, 47, 144, 74, 120, 15, 88, 0, 111, 30, 137, 143, 156, 75, 44, 110, 233, 226, 40, 118, 28, 165, 8});
  vector<int> B({151});
  cout << flag(n, m, A, B);
}

int main(int, char **)
{
  return 0;
}