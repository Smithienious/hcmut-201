/*
 * Có một trò chơi thẻ bài với n người chơi. Trong trò chơi này, có 60 loại thẻ bài (số lượng thẻ bài của mỗi loại không có giới hạn) được đánh số từ 0 đến 59. Mỗi người chơi được biểu diễn bởi một số nguyên ai (ai đại diện cho người chơi thứ i). Nếu người chơi thứ i có thẻ bài loại j trong bộ bài, thì bit thứ j (2^j) sẽ được bật (giá trị 1) trong biểu diễn nhị phân của ai. Ngược lại, bit này sẽ không được bật (giá trị 0). Ví dụ, người chơi thứ 2 được biểu diễn bởi a2. a2 có giá trị là 5, trong biểu diễn nhị phân là 101, tức là người chơi thứ 2 sẽ có thẻ bài loại 0 và 2 trong bộ bài của mình.
 * Một bộ bài x được xem như mạnh hơn bộ bài y nếu trong x có ít nhất một loại thẻ bài mà bộ bài y lại không có loại thẻ này. Hai bộ bài có thể mạnh hơn lẫn nhau (Ví dụ như bộ bài x chỉ có thẻ bài loại 0 và bộ bài y chỉ có thẻ bài loại 1).
 * Rin muốn tổ chức một giải đấu giữa các người chơi. Để đám bảo công bằng, Rin muốn chọn ra một nhóm người chơi từ n người chơi ban đầu sao cho trong nhóm người này, không ai có bộ bài mạnh hơn tất cả bộ bài của các người chơi còn lại trong nhóm. Bạn hãy giúp Rin tìm ra số lượng người chơi tối đa có thể tham gia vào giải đấu này. Lưu ý nếu ai = 0, tức là người chơi thứ i không có thẻ bài nào, đồng nghĩa với việc anh ấy không đủ tư cách để tham dự giải đấu.
 * Các giới hạn dữ liệu:
 * - 1 <= n <= 3000.
 * - 0 <= ai < 2^60 (0 <= i < n).
 * - Thời gian mỗi testcase: 1 giây.
 * Giải thích testcase 1:
 * Trong testcase này có 3 người chơi:
 * - Người đầu tiên chỉ có thẻ bài loại 1.
 * - Người thứ hai chỉ có thẻ bài loại 1.
 * - Người thứ ba có thẻ bài loại 0 và và 1. Do đó bộ bộ bài người chơi này mạnh hơn tất cả bộ bài của những người chơi còn lại.
 * Vì vậy, chỉ có thể tổ chức giải đấu giữa hai người chơi đầu tiên và người chơi thứ hai.
 */

// Here are some given libraries, you can add more libraries if needed.
#include <stdio.h>
#include <iostream>

using namespace std;

// You can also add more helping functions if needed.

int maxNumOfPlayers(int n, long long a[])
{
  // TODO: return the maximum number of players who can participant in the tournament. In case cannot set up a tournament that meets all the conditions, return 0.
}

void Test1()
{
  /*
    2
   */
  long long a[] = {2, 2, 3};
  int n = sizeof(a) / sizeof(long long);

  cout << maxNumOfPlayers(n, a);
}

void Test2()
{
  /*
    0
   */
  long long a[] = {1, 2, 7, 16};
  int n = sizeof(a) / sizeof(long long);

  cout << maxNumOfPlayers(n, a);
}

int main(int, char **)
{
  return 0;
}