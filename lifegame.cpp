#include <vector>   //vector
#include <cstdlib>  // rand
#include <iostream> // cout

struct table // tableストラクタの定義
{
  std::vector<std::vector<bool>> data;
  table(int N) //初期化・コンストラクタ
  {
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        data.at(i).at(j) = rand() % 2;
      }
    }
  };
  int width() //メンバ関数定義
  {
    return data.at(0).size();
  }
  int height()
  {
    return data.size();
  }
};

table table_in(10);

int main()
{
  table t(10);
  std::cout << t.height() << std::endl;
}
