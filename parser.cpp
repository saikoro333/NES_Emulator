#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

const int kNesHeaderSize = 0x0010;
const int kProgramRomSize = 0x4000;
const int kChapterRomSize = 0x2000;

int main(int argc, char *argv[])
{

  using namespace std;

  if (argc != 2)
  {
    cerr << "引数なし" << endl;
    return 1;
  }
  //キーボード入力からファイル名を取得する

  //ファイル名からバイナリファイルで読み込む
  std::ifstream ifs(argv[1], std::ios::binary);

  //読込サイズを調べる。
  ifs.seekg(0, std::ios::end);
  long long int size = ifs.tellg();
  ifs.seekg(0);

  //読み込んだデータをchar型に出力する
  char *data = new char[size];
  ifs.read(data, size);

  //サイズを出力する
  std::cout << "size = " << size << "\n";
  for (int i = 1; i < size + 1; i++)
  {
    std::stringstream ss;
    /*16進数文字列に変換する
        　char型をASCIIではなく、数値で出力する場合は先頭に+を付ける*/
    ss << std::hex << +data[i - 1];

    string test = ss.str();
    //符号付きであるか判定する
    if (test.size() > 5)
    {
      //符号付きの場合fが付くため、fを削除する
      string test = ss.str().erase(0, 6);
      std::cout << test << " ";
    }
    else
    {
      //符号付きでない場合そのまま出力する
      std::cout << ss.str() << " ";
    }
    //16バイト毎に改行する
    if ((i % 16) == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "\nEnd!\n";
  delete data;
  return 0;
}
