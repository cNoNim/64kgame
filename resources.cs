using System;
using System.IO;
using System.Text;
using System.Linq;

class resources
{
  static void Main(string[] args)
  {
    Console.WriteLine("Build resources");

    string[] resources = { "hello.txt" };

    using (var @out = new StreamWriter(File.Open(@"inc\resources.hxx", FileMode.Create), Encoding.UTF8))
    {
      @out.WriteLine("#pragma once");
      @out.WriteLine("#include \"core/array\"");
      @out.WriteLine("");
      @out.WriteLine("namespace resources");
      @out.WriteLine("{");
      foreach (var resource in resources)
      {
        using (var @in = File.Open(@"res\" + resource, FileMode.Open))
        {
          var length = @in.Length + 1;
          var resName = new StringBuilder(resource.Length);
          var first = resource.First();
          if (char.IsLetter(resource.First()))
          {
            resName.Append("_");
          }
          foreach (var c in resource)
          {
            resName.Append(char.IsLetterOrDigit(c) ? c : '_');
          }
          @out.WriteLine("  inline core::array<char, {1}> & {0}()", resName.ToString(), length);
          @out.WriteLine("  {");
          @out.WriteLine("    static unsigned char data[] = {");
          @out.Write("      ");

          const long column = 8;

          while (@in.Position != @in.Length)
          {
            @out.Write("0x{0:X2}, ", @in.ReadByte());

            if (@in.Position % column == 0)
            {
              @out.WriteLine("");
              @out.Write("      ");
            }
          }
          @out.WriteLine("0x00");
          @out.WriteLine("    };");
          @out.WriteLine("    return *reinterpret_cast<core::array<char, {0}> *>(data);", length);
          @out.WriteLine("  };");
        }
      }
      @out.WriteLine("}");
    }
  }
}
