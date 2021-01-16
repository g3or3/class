#include <stdlib.h>
#include <stdio.h>

#define START_VALUE 1

typedef struct piece {
  int rank, file, id;
} piece;

typedef struct rank {
  int location, num_pieces, capacity;
  piece * array;
} rank;

typedef struct rankArrayList {
  int size, cap;
  rank * ranks;
} rankArrayList;

rankArrayList * createBoard();
void addPieceToBoard(rankArrayList * board, piece * newPiece);
void expandBoard(rankArrayList * board);
void cleanBoard(rankArrayList * board);

rank * createRank();
void addPieceToRank(rank * rank, piece * newPiece);
void expandRank(rank * curRank);
void cleanRank(rank * curRank);

int main() {
  int n, rank, file;
  rankArrayList * myBoard = createBoard();
  scanf("%d", &n);
  while (n) {
    scanf("%d %d", &rank, &file);
    if (myBoard->size == 0) {
      rank *rows = createRank();
    }
  n--;
  }
  return 0;
}

rankArrayList * createBoard() {
  rankArrayList * board = calloc(START_VALUE, sizeof(rankArrayList));
  board->cap = START_VALUE;
  board->size = 0;
  return board;
}

void addPieceToBoard(rankArrayList * board, piece * newPiece) {
  if (board->size == board->cap) expandBoard(board);
}
void expandBoard(rankArrayList * board) {
  int newCap = board->cap * 2;
  board->ranks = realloc(board, newCap * sizeof(rank));
  board->cap = newCap;
}
void cleanBoard(rankArrayList * board) {

}

rank * createRank() {
  rank * rankArray = calloc(START_VALUE, sizeof(rank));
  rankArray->array = calloc(START_VALUE, sizeof(piece));
  rankArray->location = 1;
  rankArray->num_pieces = 0;
  return rankArray;
}
void addPieceToRank(rank * rank, piece * newPiece) {

}
void expandRank(rank * curRank) {

}
void cleanRank(rank * curRank) {

}
