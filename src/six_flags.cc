/* ----------------------------------------------------------------------- *
 *
 *   Author: Leandro Augusto Lacerda Campos <leandro.campos@dcc.ufmg.br>
 *
 *   Federal University of Minas Gerais (UFMG)
 *   Department of Computer Science
 *   Graduate Program in Computer Science
 *   Design and Analysis of Algorithms
 *
 *   Solution for Six Flags problem usign a greedy algorithm.
 *   Problem statement:
 *   https://www.urionlinejudge.com.br/judge/pt/problems/view/1487
 *
 * ----------------------------------------------------------------------- */

#include <algorithm>
#include <iostream>
#include <vector>

// Represents an attraction of the park
struct Attraction {
  int duration;  // in minutes
  int score;
};

// Fills each element of the vector of attractions with information provided
// by the standard input.
inline void GetAttractionsInfo(std::vector<Attraction>& attractions) {
  for (auto& a : attractions) {
    std::cin >> a.duration;
    std::cin >> a.score;
  }
}

// Sorts the vector of attractions in non-increasing order by score per
// minute.
inline void SortAttractions(std::vector<Attraction>& attractions) {
  std::sort(attractions.begin(), attractions.end(),
            [](Attraction& a, Attraction& b) {
              return (a.score * b.duration) > (b.score * a.duration);
            });
}

// Returns the highest possible score for a collection of attractions that
// respects the available time provided. An attraction may appear more than
// once in a collection.
int SelectAttractions(std::vector<Attraction>& attractions,
                      int available_time) {
  int total_score = 0;
  int times;

  SortAttractions(attractions);
  for (auto& a : attractions) {
    if (available_time == 0) break;
    if ((times = available_time / a.duration) > 0) {
      total_score += a.score * times;
      available_time -= a.duration * times;
    }
  }
  return total_score;
}

int main(void) {
  int num_attractions;
  int available_time;
  std::vector<Attraction> attractions;
  int instance = 1;

  while (std::cin >> num_attractions && num_attractions > 0) {
    attractions.resize(num_attractions);
    std::cin >> available_time;
    GetAttractionsInfo(attractions);
    std::cout << "Instancia " << instance++ << std::endl;
    std::cout << SelectAttractions(attractions, available_time) << std::endl;
    std::cout << std::endl;
  }
}