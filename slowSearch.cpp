#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <termcolor/termcolor.hpp>
#include <argparse/argparse.hpp>
#include <filesystem>
namespace fs = std::filesystem;

std::string path;
std::string choice = "";

bool isValidPath(const std::string& path) {
    fs::path p(path);
    return fs::exists(p) && fs::is_directory(p);
}

bool isValidFile(const std::string& path, const std::string& file) {
    fs::path p(path);
    p /= file;
    return fs::exists(p) && fs::is_regular_file(p);
}

void list_directory(const std::string& path) {

  for (const auto& entry : fs::directory_iterator(path)) {

    if (fs::is_directory(entry)) {

      std::cout << termcolor::blue << entry.path().filename() << termcolor::reset << "/" << std::endl;
      //list_directory("^ " entry.path());

    } else if (fs::is_regular_file(entry)) {
      std::cout << entry.path().filename() << termcolor::reset << std::endl;
    }

  }

}

int main(int argc, char *argv[]) {

  argparse::ArgumentParser program("fuzz");

  program.add_argument("-l","--list")
    .help("show whatever in the specified directory")
    .default_value(false)
    .implicit_value(true);

  program.add_argument("-e","--editor")
    .help("specify the editor to open files with")
    .default_value(std::string("nano"));

  try { program.parse_args(argc,argv); }
  catch (const std::exception& err) {

    std::cerr << err.what();
    std::cerr << program;
    exit(1);

  }

  auto editor = program.get<std::string>("-e");

  std::cout << termcolor::yellow << "Path: " << termcolor::reset;
  std::cin >> path;
  std::cout << termcolor::red << "warning: 'path' defaults to /home/" << termcolor::reset << std::endl;
  path = "/home/" + path;

  if (program["--list"] == true) {
    list_directory(path);
  }

  std::cout << termcolor::yellow << "ya choice: " << termcolor::reset;
  std::cin >> choice;

  if (fs::is_regular_file(path + "/" + choice)) {
    system((editor + " " + path + "/" + choice).c_str());
  } else if (fs::is_directory(path + "/" + choice)) {

    std::string newPath = path + "/" + choice;
    
    std::cout << termcolor::green << "directory listing:" << termcolor::reset << std::endl;
    list_directory(path + "/" + choice);

    std::cout << termcolor::yellow << "ya choice: " << termcolor::reset;
    std::cin >> choice;
    system((editor + " " + newPath + "/" + choice).c_str());

  }

  return 0;

}
