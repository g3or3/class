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
  rank ** ranks;
} rankArrayList;

rankArrayList * createBoard();
void            addPieceToBoard(rankArrayList * board, piece * newPiece);
void            expandBoard(rankArrayList * board);
void            cleanBoard(rankArrayList * board);
rank *          createRank();
void            addPieceToRank(rank * rank, piece * newPiece);
void            expandRank(rank * curRank);
void            cleanRank(rank * curRank);


int main() {
  piece * rook;
  rankArrayList * myBoard = createBoard();
  int n = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &rook->rank, &rook->file);
    rook->id = i;
    addPieceToBoard(myBoard, rook);
  }
  printf("\nboard_size: %d board_cap: %d\n", myBoard->size, myBoard->cap);
  for (int j = 0; j < n; j++) {
    printf("location: %d num_pieces: %d capacity: %d", myBoard->ranks[j]->location,
            myBoard->ranks[j]->num_pieces, myBoard->ranks[j]->capacity);
    printf("\nrank: %d file: %d id: %d\n", myBoard->ranks[j]->array->rank,
            myBoard->ranks[j]->array->file, myBoard->ranks[j]->array->id);
  }
  cleanBoard(myBoard);
  return 0;
}

rankArrayList * createBoard() {
  rankArrayList * board = calloc(START_VALUE, sizeof(rankArrayList));
  board->ranks = calloc(START_VALUE, sizeof(rank *));
  board->cap = START_VALUE;
  board->size = 0;
  return board;
}

rank * createRank() {
  rank * row = calloc(START_VALUE, sizeof(rank));
  row->array = calloc(2, sizeof(piece));
  row->location = 0;
  row->num_pieces = START_VALUE;
  row->capacity = START_VALUE;
  return row;
}

void addPieceToBoard(rankArrayList * board, piece * newPiece) {
  if (board->size == board->cap) expandBoard(board);
  for (int i = 0; i < board->size; i++) { // looking
    if (board->ranks[i]->location == newPiece->rank) {
      addPieceToRank(board->ranks[i], newPiece);
      return; // returning because I don't need to increase the size of board
    }         // since that row (location #) is already in there
  }
  rank * newRow = createRank();
  newRow->location = newPiece->rank;
  newRow->array[newRow->num_pieces] = *newPiece;
  board->ranks[board->size] = newRow;
  board->size++;
}

void addPieceToRank(rank * rank, piece * newPiece) {
  if (rank->num_pieces == rank->capacity) expandRank(rank);
  rank->array[rank->num_pieces] = *newPiece;
  rank->num_pieces++;
}

void expandBoard(rankArrayList * board) {
  int newCap = board->cap * 2;
  board->ranks = realloc(board->ranks, newCap * sizeof(rank *));
  board->cap = newCap;
}

void expandRank(rank * curRank) {
  int newCap = curRank->capacity * 2;
  curRank->array = realloc(curRank->array, newCap * sizeof(piece));
  curRank->capacity = newCap;
}

void cleanBoard(rankArrayList * board) {
  for (int i = 0; i < board->size; i++) {
    cleanRank(board->ranks[i]);
  }
  free(board->ranks);
  free(board);
}

void cleanRank(rank * curRank) {
  free(curRank->array);
  free(curRank);
}
