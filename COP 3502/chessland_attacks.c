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
void            addPieceToBoard(rankArrayList *, piece *);
void            expandBoard(rankArrayList *);
void            cleanBoard(rankArrayList *);
rank *          createRank();
void            addPieceToRank(rank *, piece *);
void            expandRank(rank *);
void            cleanRank(rank *);
piece *         findRook(rankArrayList *, int);
void            checkBoard(rankArrayList *, piece *);
int             scanLeft(rankArrayList *, piece *);
int             scanRight(rankArrayList *, piece *);






int main() {
  int id, n = 0;
  piece rook;
  piece * rookPtr = &rook;
  rankArrayList * myBoard = createBoard();
  scanf("%d", &n);
  for (id = 1; id <= n; id++) {
    scanf("%d %d", &rook.rank, &rook.file);
    rook.id = id;
    addPieceToBoard(myBoard, rookPtr);
  }

  //____________________________________________________________________________
  /*                     // DEBUG PRINT STATEMENTS
  printf("\nBOARD SIZE: %d BOARD CAP: %d\n", myBoard->size, myBoard->cap);
  for (int j = 0; j < myBoard->size; j++) {
    printf("\nlocation: %d num_pieces: %d capacity: %d\n", myBoard->ranks[j]->location,
            myBoard->ranks[j]->num_pieces, myBoard->ranks[j]->capacity);
    for (int k = 0; k < myBoard->ranks[j]->num_pieces; k++) {
      printf("\nrank: %d file: %d id: %d\n\n", myBoard->ranks[j]->array[k].rank,
              myBoard->ranks[j]->array[k].file, myBoard->ranks[j]->array[k].id);
    }
  } */

  for (id = 1; id <= n; id++) {
    rookPtr = findRook(myBoard, id);
    checkBoard(myBoard, rookPtr);
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
  row->capacity = START_VALUE;
  return row;
}

void addPieceToBoard(rankArrayList * board, piece * newPiece) {
  if (board->size == board->cap) expandBoard(board);
  for (int i = 0; i < board->size; i++) { // Looping through the board to see if there
    if (board->ranks[i]->location == newPiece->rank) {  // is already a rook in row   (location #)
      addPieceToRank(board->ranks[i], newPiece);  // no new rank will have to be created
      return; // returning because I don't need to increase the size of board
    }         // since that row (location #) is already in there
  }
  rank * newRow = createRank();
  newRow->location = newPiece->rank;
  newRow->array[newRow->num_pieces] = *newPiece;
  newRow->num_pieces = START_VALUE;
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

piece * findRook(rankArrayList * board, int n) {
  piece * rook;
  for (int i = 0; i < board->size; i++) {
    for (int j = 0; j < board->ranks[i]->num_pieces; j++) {
      if (board->ranks[i]->array[j].id == n) {
        rook = &board->ranks[i]->array[j];
        return rook;
      }
    }
  }
  return rook;
}

void checkBoard(rankArrayList * board, piece * rook) {
  rank * row;
  piece leftRook, rightRook;
  int i, leftThreat = 0, rightThreat = 0, threatCount = 0;
  for (i = 0; i < board->size; i++) {
    if (board->ranks[i]->location == rook->rank) row = board->ranks[i];
  }
  // scan to the left of the rook passed from function
  for (i = 0; i < row->num_pieces; i++) {
    if (row->array[i].file < rook->file && leftThreat == 0) {
      threatCount++;
      leftRook = row->array[i];
      leftThreat++;
    }
    if (row->array[i].file < rook->file && leftThreat != 0) {
      if (row->array[i].file > leftRook.file) leftRook = row->array[i];
    }
  }
  //scan to the right of the rook passed from function
  for (i = 0; i < row->num_pieces; i++) {
    if (row->array[i].file > rook->file && rightThreat == 0) {
      threatCount++;
      rightRook = row->array[i];
      rightThreat++;
    }
    if (row->array[i].file > rook->file && rightThreat != 0) {
      if (row->array[i].file < rightRook.file) rightRook = row->array[i];
    }
  }
  if (threatCount != 0) {
    printf("%d ", threatCount);
    if (leftThreat != 0) {
      printf("%d ", leftRook.id);
      if (rightThreat == 0) printf("\n");
    }
    if (rightThreat != 0) {
      printf("%d\n", rightRook.id);
    }
    else
      printf("%d", threatCount);
  }





}
