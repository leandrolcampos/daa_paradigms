/* ----------------------------------------------------------------------- *
 *
 *   Author: Leandro Augusto Lacerda Campos <leandro.campos@dcc.ufmg.br>
 *
 *   Federal University of Minas Gerais (UFMG)
 *   Department of Computer Science
 *   Graduate Program in Computer Science
 *   Design and Analysis of Algorithms
 *
 *   Solution for Go-- problem using dynamic programming.
 *   Problem statement:
 *   https://www.urionlinejudge.com.br/judge/pt/problems/view/2241
 *
 * ----------------------------------------------------------------------- */

#include <algorithm>
#include <iostream>
#include <vector>

// Board is a type alias for a 3D vector of integers. The first, the second and
// the third dimension represents, respectively, a player, a row and a column.
// A element board[p1][i][j] is equal to 1 if there is a stone of the player p1
// in the (i, j) position of the board or if this position is empty; or it is
// equal to 0 if there is a stone of the other player in this position.
using Board = std::vector<std::vector<std::vector<int>>>;

constexpr int kNumPlayers = 2;  // Do not change the value of this constant.

void InitializeBoard(Board &board, int num_rows) {
  int num_cols = num_rows;

  board.resize(kNumPlayers);
  for (int player = 0; player < kNumPlayers; player++) {
    board[player].resize(num_rows);
    for (int row = 0; row < num_rows; row++) {
      board[player][row].resize(num_cols);
      for (int col = 0; col < num_cols; col++) {
        board[player][row][col] = 1;
      }
    }
  }
}

void PlaceStones(Board &board, int num_stones_per_player) {
  int row, col, rival;

  for (int player = 0; player < kNumPlayers; player++) {
    rival = 1 - player;
    for (int stone = 0; stone < num_stones_per_player; stone++) {
      std::cin >> row >> col;
      row--;  // From 1-based index to 0-based index.
      col--;  // From 1-based index to 0-based index.
      board[rival][row][col] = 0;
    }
  }
}

std::vector<int> CalculateScores(Board &board, int num_rows) {
  int num_cols = num_rows;
  std::vector<int> scores(kNumPlayers, 0);
  std::vector<std::vector<int>> sheet(num_rows);
  int signal = -1;
  int value;

  for (int row = 0; row < num_rows; row++) {
    sheet[row].resize(num_cols);
    for (int col = 0; col < num_cols; col++) {
      sheet[row][col] = 0;
    }
  }
  for (int player = 0; player < kNumPlayers; player++) {
    signal *= -1;
    for (int row = 0; row < num_rows; row++) {
      for (int col = 0; col < num_cols; col++) {
        value = board[player][row][col];
        if (row > 0 && col > 0 && value == 1) {
          value += std::min({board[player][row][col - 1],
                             board[player][row - 1][col],
                             board[player][row - 1][col - 1]});
          board[player][row][col] = value;
        }
        sheet[row][col] += signal * value;
      }
    }
  }
  for (int row = 0; row < num_rows; row++) {
    for (int col = 0; col < num_cols; col++) {
      value = sheet[row][col];
      for (int player = 0; player < kNumPlayers; player++) {
        signal *= -1;
        scores[player] += std::max(0, signal * value);
      }
    }
  }
  return scores;
}

int main(void) {
  int num_rows, num_stones_per_player;
  Board board;
  std::vector<int> scores;

  std::cin >> num_rows >> num_stones_per_player;
  InitializeBoard(board, num_rows);
  PlaceStones(board, num_stones_per_player);
  scores = CalculateScores(board, num_rows);
  std::cout << scores[0] << " " << scores[1] << std::endl;
  return 0;
}