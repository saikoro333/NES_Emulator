#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

const int kNesHeaderSize = 0x0010;
const int kProgramRomSize = 0x4000;
const int kChapterRomSize = 0x2000;

using namespace std;

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    cerr << "引数なし" << endl;
    return 1;
  }

  //ファイル名からバイナリファイルで読み込む
  std::ifstream ifs(argv[1], std::ios::binary);

  //読込サイズを調べる。
  ifs.seekg(0, std::ios::end);
  long long int size = ifs.tellg();
  ifs.seekg(0);

  //読み込んだデータをchar型に出力する
  char *data = new char[size];
  ifs.read(data, size);
  unsigned short int nes_header[16];

  //サイズを出力する
  std::cout << "size = " << size << "\n";
  for (int i = 1; i < size + 1; i++)
  {
    std::stringstream ss;
    /*16進数文字列に変換する
        　char型をASCIIではなく、数値で出力する場合は先頭に+を付ける*/
    ss << std::hex << +data[i - 1];
    if (i >= 1 && i <= 16)
    {
      nes_header[i - 1] = data[i - 1];
      std::cout << ss.str() << " ";
    }
    else
    {

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
    }
    //16バイト毎に改行する
    if ((i % 16) == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "\nEnd!\n";
  delete data;

  for (int c = 0; c < 16; c++)
  {
    printf("%x ", nes_header[c]);
  }
  cout << "\n";

  unsigned short int characterROMPages = nes_header[5];
  int characterROMStart = 16 /*0x0010*/ + nes_header[4] * 4 * 4096 /*0x4000*/;
  int characterROMEnd = characterROMStart + nes_header[5] * 2 * 4096 /*0x2000*/;
  cout << "characterROMPages" << endl;
  printf("%d\n", characterROMPages);
  cout << "characterROMStart" << endl;
  printf("%d\n", characterROMStart);
  cout << "characterROMEnd" << endl;
  printf("%d\n", characterROMEnd);
  return 0;
}
