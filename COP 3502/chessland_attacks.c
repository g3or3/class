#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_VALUE 1

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


/* creates an empty "rook", assigns the values captured from the user to
  the rook (row and column #), places them correspodingly on the board,
  goes through the board to find any threats for each rook, and frees any
  memory allocated in the program before returning 0 */
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
  for (id = 1; id <= n; id++) {
    rookPtr = findRook(myBoard, id);
    checkBoard(myBoard, rookPtr);
  }
  cleanBoard(myBoard);
  return 0;
}


/* allocate memory for one "chessboard" and initializes
  values then returns the board */
rankArrayList * createBoard() {
  rankArrayList * board = calloc(DEFAULT_VALUE, sizeof(rankArrayList));
  board->ranks = calloc(DEFAULT_VALUE, sizeof(rank *));
  board->cap = DEFAULT_VALUE;
  board->size = 0;
  return board;
}


/* allocate memory for one "row" and one "rook" in that row
  as well as initialize values then returns the row */
rank * createRank() {
  rank * row = calloc(DEFAULT_VALUE, sizeof(rank));
  row->array = calloc(DEFAULT_VALUE, sizeof(piece));
  row->capacity = DEFAULT_VALUE;
  return row;
}


/* first check to see if board is full and expand if needed
  then see if the row # from the new rook is already on the board
  if so add the new rook to the existing row if not create a
  new row and add the new rook to it */
void addPieceToBoard(rankArrayList * board, piece * newPiece) {
  if (board->size == board->cap) expandBoard(board);
  for (int i = 0; i < board->size; i++) {
    if (board->ranks[i]->location == newPiece->rank) {
      addPieceToRank(board->ranks[i], newPiece);
      return;
    }
  }
  rank * newRow = createRank();
  newRow->location = newPiece->rank;
  newRow->array[newRow->num_pieces] = *newPiece;
  newRow->num_pieces = DEFAULT_VALUE;
  board->ranks[board->size] = newRow;
  board->size++;
}


/* first check to see if the row is full and expand if needed
  then add the new rook to the correspoding row and update the row's
  total number of pieces */
void addPieceToRank(rank * rank, piece * newPiece) {
  if (rank->num_pieces == rank->capacity) expandRank(rank);
  rank->array[rank->num_pieces] = *newPiece;
  rank->num_pieces++;
}


/* double the board's existing capacity (to fit more rows) and
  allocate memory for the total size of the newly expanded board */
void expandBoard(rankArrayList * board) {
  int newCap = board->cap * 2;
  board->ranks = realloc(board->ranks, newCap * sizeof(rank *));
  board->cap = newCap;
}


/* double the corresponding row's existing capacity (to fit more rooks)
  and allocate memory for the total size of the newly expanded row */
void expandRank(rank * curRank) {
  int newCap = curRank->capacity * 2;
  curRank->array = realloc(curRank->array, newCap * sizeof(piece));
  curRank->capacity = newCap;
}


/* first iterate through all the rows in the board and free memory (see below)
  then free the memory allocated for the array of rows as well as the
  memory allocated for the board itself */
void cleanBoard(rankArrayList * board) {
  for (int i = 0; i < board->size; i++) {
    cleanRank(board->ranks[i]);
  }
  free(board->ranks);
  free(board);
}


/* free the memory allocated for each row of rooks and then
  free the memory allocated for the array of rooks */
void cleanRank(rank * curRank) {
  free(curRank->array);
  free(curRank);
}


/* iterate through every row in the board to find the corresponding
  id number passed as an argument then assign the address of the rook
  at id "n" to a pointer and return it */
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


/* with the rook of the pointer being passed as an argument, iterate
  through the board to see how many threats that rook faces and print
  that number as well the id # of the corresponding threats */
void checkBoard(rankArrayList * board, piece * rook) {
  rank * row;
  piece leftRook, rightRook, upRook, downRook;
  int i, j, threatCount = 0;
  int leftThreat = 0, rightThreat = 0, upThreat = 0, downThreat = 0;
  for (i = 0; i < board->size; i++) {
    if (board->ranks[i]->location == rook->rank) row = board->ranks[i];
  }
  // scan to the left
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
  // scan to the right
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
  // scan up
  for (i = 0; i < board->size; i++) {
    for (j = 0; j < board->ranks[i]->num_pieces; j++) {
      if (rook->file == board->ranks[i]->array[j].file) {
        if (rook->id != board->ranks[i]->array[j].id) {
          if (board->ranks[i]->location > rook->rank && upThreat == 0) {
            threatCount++;
            upRook = board->ranks[i]->array[j];
            upThreat++;
          }
          if (board->ranks[i]->location > rook->rank && upThreat != 0) {
            if (board->ranks[i]->location < upRook.rank) {
              upRook = board->ranks[i]->array[j];
            }
          }
        }
      }
    }
  }
  // scan down
  for (i = 0; i < board->size; i++) {
    for (j = 0; j < board->ranks[i]->num_pieces; j++) {
      if (rook->file == board->ranks[i]->array[j].file) {
        if (rook->id != board->ranks[i]->array[j].id) {
          if (board->ranks[i]->location < rook->rank && downThreat == 0) {
            threatCount++;
            downRook = board->ranks[i]->array[j];
            downThreat++;
          }
          if (board->ranks[i]->location < rook->rank && downThreat != 0) {
            if (board->ranks[i]->location > downRook.rank) {
              downRook = board->ranks[i]->array[j];
            }
          }
        }
      }
    }
  }
  if (threatCount != 0) {
    printf("%d ", threatCount);
    if (leftThreat != 0) {
      printf("%d ", leftRook.id);
      if (rightThreat == 0 && upThreat == 0 && downThreat == 0) printf("\n");
    }
    if (rightThreat != 0) {
      printf("%d ", rightRook.id);
      if (upThreat == 0 && downThreat == 0) printf("\n");
    }
    if (upThreat != 0) {
      printf("%d ", upRook.id);
      if (downThreat == 0) printf("\n");
    }
    if (downThreat != 0) {
      printf("%d\n", downRook.id);
    }
  } else printf("%d\n", threatCount);
}
