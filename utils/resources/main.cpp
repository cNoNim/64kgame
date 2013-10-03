#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

int main(int argc, char const * argv[]) 
{
  using namespace std;
  if (argc <= 1) return 0;

  cout << "Build resources" << endl;

  string base_path = argv[1];
  auto res_path = base_path + "res\\";
  auto emb_path = base_path + "emb\\";

  static char const * resources[] = {
    "test.txt"
  };

  for (auto resName : resources) {
    auto resource = ifstream(res_path + resName, ios::in | ios::binary);
    if (resource.is_open()) {
      auto embedded = ofstream(emb_path + resName, ios::out | ios::trunc );
      if (embedded.is_open()) {
        size_t const column = 6;
        size_t num = 0;
        embedded << "#pragma once\n\n";
        embedded << "namespace resources\n{\n";
        embedded << "  {\n    ";
        for (auto c = resource.get(); resource.good(); c = resource.get()) {
          num++;
          embedded << "0x" << hex << uppercase << c << ((num % column) ? ", " : ",\n    ");
        }
        embedded << "\n  };\n";
        embedded.close();
      }

      resource.close();
    }
  }

  return 0;
}