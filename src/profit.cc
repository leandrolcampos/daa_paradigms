/* ----------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <leandro.campos@dcc.ufmg.br>
 * 
 *   Federal University of Minas Gerais (UFMG)
 *   Department of Computer Science 
 *   Graduate Program in Computer Science
 *   Design and Analysis of Algorithms
 * 
 *   Solution for Profit problem usign induction.
 *   Problem statement:
 *   https://www.urionlinejudge.com.br/judge/pt/problems/view/1310
 * 
 * ----------------------------------------------------------------------- */

#include <iostream>
#include <vector>

// Updates the elements of the vector v, from v[0] to v[n-1], adding to the 
// value of each of them the integer provided by the standard input.
inline void UpdateVector(std::vector<int>& v) {
  int value;
  for (auto& x : v) {
    std::cin >> value;
    x += value;
  }
}

// Given a vector v[0..(n-1)] of integers (not necessarily positive), this 
// function returns the sum of the elements in a subvector v[i..j] that is 
// maximum over all subvectors of v.
int MaxSubvector(const std::vector<int>& v) {
  int global_max = 0;
  int suffix_max = 0;
  for (const auto& x : v) {
    if (suffix_max + x > global_max) {
      suffix_max = suffix_max + x;
      global_max = suffix_max;
    } else if (suffix_max + x > 0) {
      suffix_max = suffix_max + x;
    } else {
      suffix_max = 0;
    }
  }
  return global_max;
}

int main(void) {
  int num_days;
  int cost_per_day;
  while (std::cin >> num_days) {
    std::cin >> cost_per_day;
    std::vector<int> profit_per_day(num_days, (-1) * cost_per_day);
    UpdateVector(profit_per_day);
    std::cout << MaxSubvector(profit_per_day) << std::endl;
  }
}