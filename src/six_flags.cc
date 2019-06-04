/* ----------------------------------------------------------------------- *
 *
 *   Author: Leandro Augusto Lacerda Campos <leandro.campos@dcc.ufmg.br>
 *
 *   Federal University of Minas Gerais (UFMG)
 *   Department of Computer Science
 *   Graduate Program in Computer Science
 *   Design and Analysis of Algorithms
 *
 *   Solution for Six Flags problem using dynamic programming.
 *   Problem statement:
 *   https://www.urionlinejudge.com.br/judge/pt/problems/view/1487
 *
 * ----------------------------------------------------------------------- */

#include <algorithm>
#include <iostream>
#include <vector>

// Represents an attraction of the park.
struct Attraction {
  int duration;  // in minutes.
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

// Returns the highest possible score for a collection of attractions that
// respects the available time provided. An attraction may appear more than
// once in a collection.
int SelectAttractions(std::vector<Attraction>& attractions,
                      int available_time) {
  std::vector<int> scores(available_time + 1, 0);

  for (int t = 1; t <= available_time; t++) {
    for (auto& a : attractions) {
      if (a.duration <= t) {
        scores[t] = std::max(scores[t], a.score + scores[t - a.duration]);
      }
    }
  }
  return scores[available_time];
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