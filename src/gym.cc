/* ----------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <leandro.campos@dcc.ufmg.br>
 * 
 *   Federal University of Minas Gerais (UFMG)
 *   Department of Computer Science 
 *   Graduate Program in Computer Science
 *   Design and Analysis of Algorithms
 * 
 *   Solution for Gym problem using dynamic programming.
 *   Problem statement:
 *   https://www.urionlinejudge.com.br/judge/pt/problems/view/2664
 * 
 * ----------------------------------------------------------------------- */

#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

// The function count returns the number of possible workouts considering
// the following restrictions:
// (i)   the duration of each workout is equal to minutes;
// (ii)  the difficulty level of each workout should change by the minute;
// (iii) the minimum and maximum difficulty levels are min_value and 
//       max_value, respectively.
uint64_t count(uint64_t minutes, uint64_t min_value, uint64_t max_value) {
  constexpr uint64_t divisor = uint64_t{1000000007};
  uint64_t length = max_value - min_value + 1;
  uint64_t mem[2][length + 2];
  uint64_t *previous = mem[0];
  uint64_t *current = mem[1];
  uint64_t sum = 0;

  // Set the block of memory with its initial values.
  previous[0] = 0;
  previous[length + 1] = 0;
  for (uint64_t i = 1; i <= length; i++) {
    previous[i] = 1;
  }
  current[0] = 0;
  current[length + 1] = 0;

  // For each time t, calculate the number of possible workouts that
  // end in each difficulty level.
  for (uint64_t t = 1; t < minutes; t++) {
    for (uint64_t i = 1; i <= length; i++) {
      current[i] = (previous[i - 1] + previous[i + 1]) % divisor;
    }
    swap(previous, current);
  }

  // Add the number of possible workouts on all difficulty levels
  // at the last time t.
  for (uint64_t i = 1; i <= length; i++) {
    sum = (sum + previous[i]) % divisor;
  }
  return sum;
}

int main(void) {
  uint64_t minutes;
  uint64_t min_value;
  uint64_t max_value;

  cin >> minutes >> min_value >> max_value;
  cout << count(minutes, min_value, max_value) << endl;
  return 0;
}