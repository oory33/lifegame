#include <vector>   //vector
#include <cstdlib>  // rand
#include <iostream> // cout
#include <thread>   // thread
#include <chrono>   // chrono

struct table // tableストラクタの定義
{
  std::vector<std::vector<bool>> data;
  table(int N) //初期化・コンストラクタ
  {
    for (int i = 0; i < N; i++)
    {
      data.emplace_back();
      for (int j = 0; j < N; j++)
      {
        data.at(i).push_back(rand() % 2);
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
  std::vector<bool> at(int y)
  {
    return data.at(y);
  }
  void replace(int x, int y, bool val)
  {
    data[y][x] = val;
    return;
  }
};

bool at_cell(table data, int x, int y) // dataの(x,y)のセルの状態を返す関数
{
  if (x < 0 || y < 0 || x >= data.width() || y >= data.height())
  {
    return false;
  }
  else
  {
    return data.at(y).at(x);
  }
}

int count_surround(table data, int x, int y) //周囲のセルの合計値を返す
{
  return at_cell(data, x - 1, y) + at_cell(data, x - 1, y - 1) + at_cell(data, x, y - 1) +
         at_cell(data, x + 1, y - 1) + at_cell(data, x + 1, y) + at_cell(data, x + 1, y + 1) +
         at_cell(data, x, y + 1) + at_cell(data, x - 1, y + 1);
}

bool dead_or_alive(table data, int x, int y) //周囲のセルを探査し、生存しているセルの周囲が2か3生存ならtrue、それ以外はfalse、死んだセルの周囲が3つならtrue
{
  if (at_cell(data, x, y)) //セルが生存している場合
  {
    return count_surround(data, x, y) == 2 || count_surround(data, x, y) == 3 ? true : false;
  }
  else //セルが死んでいる場合
  {
    return count_surround(data, x, y) == 3 ? true : false;
  }
}

void print_table(table data) //テーブルを表示する関数
{
  for (int i = 0; i < data.width() + 2; i++)
  {
    std::cout << "-";
  }
  std::cout << std::endl;
  for (int i = 0; i < data.height(); i++)
  {
    std::cout << "|";
    for (int j = 0; j < data.width(); j++)
    {
      data.at(i).at(j) ? std::cout << "■" : std::cout << " ";
    }
    std::cout << "|" << std::endl;
  }
  for (int i = 0; i < data.width() + 2; i++)
  {
    std::cout << "-";
  }
  std::cout << std::endl;
  return;
}

table next_gen(table &data) //次世代の盤面を作る
{
  for (int i = 0; i < data.height(); i++)
  {
    for (int j = 0; j < data.width(); j++)
    {
      data.replace(j, i, dead_or_alive(data, j, i));
    }
  }
  return data;
}

int main()
{
  table t(20);

  while (1)
  {
    print_table(t);
    t = next_gen(t);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
}
