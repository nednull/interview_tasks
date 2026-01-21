#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct point_2d
{
  double x;
  double y;  
};


struct circle
{
  point_2d position;
  double radius;
};


std::vector<circle> parse_input(std::string& filename)
{
  std::vector<circle> circles = {};
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::string word;
    std::vector<std::string> tokens;
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ' ') {
        tokens.push_back(word);
        word = "";
        continue;
      }
      word += std::string(1, line[i]);
    }
    tokens.push_back(word);
    circles.push_back(circle{
      point_2d{std::stod(tokens[0]), std::stod(tokens[1])},
      std::stod(tokens[2])
    });
  }
  return circles;
}


bool has_collision(std::vector<circle>& circles)
{
  for (int i = 0; i < circles.size(); i++) {
    for (int j = 0; j < circles.size(); j++) {
      if (i == j) continue;
      double dx = circles[j].position.x - circles[i].position.x;
      double dy = circles[j].position.y - circles[i].position.y;
      double r_added = circles[j].radius + circles[i].radius;
      if (std::pow(dx, 2.0) + std::pow(dy, 2.0) < std::pow(r_added, 2.0)) return true;
    }
  }
  return false;
}


int main(int argc, char** argv)
{
  std::string fileName(argv[1]);
  std::vector<circle> circles = {};
  
  
  bool result = has_collision(circles);
  std::cout << "has_collision: " << (result ? "yes" : "no") << std::endl;

  return 0;
}