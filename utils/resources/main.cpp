#include <vector>
#include <string>
#include <iomanip>
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
  auto inc_path = base_path + "inc\\";
  auto emb_path = inc_path + "emb\\";

  static string resources[] = {
    "test.txt"
  };

  auto header = ofstream(inc_path + "resources.hxx", ios::out | ios::trunc);

  if (header.is_open()) {
    header << "#pragma once\n\n";
    header << "#include \"core/array\"\n\n";
    for (auto resName : resources) {
      auto resource = ifstream(res_path + resName, ios::in | ios::binary | ios::ate);
      if (resource.is_open()) {
        auto resSize = resource.tellg();
        resSize+=1;
        resource.seekg(0, ios::beg);
        auto embName = resName + ".inc";
        auto embedded = ofstream(emb_path + embName, ios::out | ios::trunc);
        if (embedded.is_open()) {
          size_t const column = 8;
          size_t num = 0;
          embedded << "#pragma once\n";
          embedded << "namespace resources\n";
          embedded << "{\n";
          embedded << "  inline core::array<char, " << resSize << "> ";
          for (auto c : resName) {
            embedded << (isalnum(c) ? c : '_');
          }
          embedded << "()\n";
          embedded << "  {\n";
          embedded << "    static char data[] = {\n      ";
          for (auto c = resource.get(); resource.good(); c = resource.get()) {
            num++;
            embedded << "0x" << hex << setw(2) << setfill('0') << uppercase << c << (num % column ? ", " : ",\n      ");
          }
          embedded << dec << "0x00\n    };\n";
          embedded << "    return *reinterpret_cast<core::array<char, " << resSize << "> *>(data);\n";
          embedded << "  }\n}\n";
          embedded.close();

          header << "#include \"emb/" << embName << "\"\n";
        }
        resource.close();
      }
    }
    header.close();
  }

  return 0;
}