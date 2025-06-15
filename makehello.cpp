#include <filesystem> 
#include <fstream>
#include <iostream>
#include <print> 
#include <span>
#include <string_view>

using std::cerr;
using std::filesystem::path;
using std::ofstream;
using std::println;
using std::span;
using std::string_view;

int main(int argc, char* argv[]) {
  const span<char*> args{argv, static_cast<size_t>(argc)};

  if (args.size() < 2) {
    cerr << "Error: Please provide an output filename.\n";
    cerr << "Usage: " << args[0] << " <output_filename.cpp>\n";
    return 1;
  }

  const path output_path = args[1];

  constexpr string_view generated_code = R"cpp(
#include <print>

using std::println;

void sayHello() {
    println("Hello, World!");
}
)cpp";

  println("Attempting to generate file: {}", output_path.string());

  ofstream fout(output_path);

  if (!fout) {
    cerr << "Error: Could not open file for writing: " << output_path << '\n';
    return 1;
  }

  fout << generated_code;
  
  println("Successfully generated {}", output_path.string());

  return 0;
}
