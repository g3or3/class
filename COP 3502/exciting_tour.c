#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000000

typedef struct Match {
  int matchNum, p1, p2;
  struct Match *leftBracket;
  struct Match *rightBracket;
} Match;

typedef struct Tournament {
    struct Match *finals;
} Tournament;

Tournament * createTournament();
Match * createMatch(int matchNum);
Match * addMatch(Match *currMatch, int matchNum);
void addToRoster(Match *currMatch, int skillLevel, int matchNum);
void beginTournament(Match *currMatch, int* remainingPlayers);
_Bool checkRemainingPlayers(int *remainingPlayers, int player);
int * removePlayer(int *remainingPlayers, int player);

int excitementScore = 0;
int numPlayers;
int previousVictor;

int main() {
  char matches[MAX_LEN];
  char skills[MAX_LEN];

  Tournament *championsLeague = createTournament();

  scanf("%d", &numPlayers);
  scanf(" %[^\n]%*c", matches);
  scanf(" %[^\n]%*c", skills);

  int matchNum = 0;
  int numDigits = 1;

  /* create matches to add to the tournament tree backwards */
  for (int i = strlen(matches) - 1; i > -1; i--) {
    if (isspace(matches[i]) == 0) {
      matchNum += (matches[i] - '0') * numDigits;
      numDigits *= 10;
      championsLeague->finals = addMatch(championsLeague->finals, matchNum);
    }
    else {
      matchNum = 0;
      numDigits = 1;
    }
  }

  char* playerSkill;
  char * space = " ";
  int val, playersAdded = 0, i = 0;
  int *remainingPlayers = calloc(numPlayers, sizeof(int));
  matchNum = 1;
  playerSkill = strtok(skills, space);

  /* add players to the matches in order */
  while(playerSkill != NULL) {
    val = atoi(playerSkill);

    if (playersAdded != 2) {
      addToRoster(championsLeague->finals, val, matchNum);
      playersAdded++;
      if (playersAdded == 2) {
        addToRoster(championsLeague->finals, val, matchNum + 1);
        matchNum++;
        playersAdded = 1;
      }
    }

    remainingPlayers[i++] = val;
    playerSkill = strtok(NULL, space);
  }

  int leftSemifinalist, rightSemifinalist;

  /* tournament divided by left bracket and right bracket */
  beginTournament(championsLeague->finals->leftBracket, remainingPlayers);
  beginTournament(championsLeague->finals->rightBracket, remainingPlayers);

  for (int i = 0; i < numPlayers; i++) {
    if (remainingPlayers[i] > 0) {
      if (!leftSemifinalist) leftSemifinalist = remainingPlayers[i];
      else rightSemifinalist = remainingPlayers[i];
    }
  }

  /* left and right semifinalist compete to compute total excitement score */
  excitementScore += abs(leftSemifinalist - rightSemifinalist);

  printf("%d\n", excitementScore);

  return 0;
}

/* Create a new tournament tree that references the root match (final match played) */
Tournament * createTournament() {
  Tournament *newTourn = calloc(1, sizeof(Tournament));
  newTourn->finals = NULL;

  return newTourn;
}

/* Create a match node with its match number and return it */
Match * createMatch(int matchNum) {
  Match *newMatch = calloc(1, sizeof(Match));
  newMatch->matchNum = matchNum;
  newMatch->leftBracket = NULL;
  newMatch->rightBracket = NULL;

  return newMatch;
}

/* Add the newly created match to the tournament tree */
Match * addMatch(Match *currMatch, int matchNum) {
  if (currMatch == NULL) {
    Match *newMatch = createMatch(matchNum);
    currMatch = newMatch;
    return currMatch;
  }
  if (matchNum < currMatch->matchNum)
    currMatch->leftBracket = addMatch(currMatch->leftBracket, matchNum);

  if (matchNum > currMatch->matchNum)
    currMatch->rightBracket = addMatch(currMatch->rightBracket, matchNum);

  return currMatch;
}

/* Traverses through the tournament tree and adds players to the matches in order */
void addToRoster(Match *currMatch, int skillLevel, int matchNum) {
  if (currMatch == NULL) return;
  if (currMatch->matchNum == matchNum) {
    if (!currMatch->p1) currMatch->p1 = skillLevel;
    else currMatch->p2 = skillLevel;
  }

  addToRoster(currMatch->leftBracket, skillLevel, matchNum);
  addToRoster(currMatch->rightBracket, skillLevel, matchNum);
}

/* Start the tournament and traverse through the tournament tree post order */
void beginTournament(Match *currMatch, int* remainingPlayers) {
  if (currMatch == NULL) return;

  beginTournament(currMatch->leftBracket, remainingPlayers);
  beginTournament(currMatch->rightBracket, remainingPlayers);

  /* check if player 1 is still in the tournament */
  if (checkRemainingPlayers(remainingPlayers, currMatch->p1)) {

    /* player 1 AND player 2 are still in the tournament */
    if (checkRemainingPlayers(remainingPlayers, currMatch->p2)) {
      excitementScore += abs(currMatch->p1 - currMatch->p2);
      if (currMatch->p1 > currMatch->p2) {
        remainingPlayers = removePlayer(remainingPlayers, currMatch->p2);
        previousVictor = currMatch->p1;
      }
      else {
        remainingPlayers = removePlayer(remainingPlayers, currMatch->p1);
        previousVictor = currMatch->p2;
      }
    }

    /* player 1 is still in the tournament but player 2 is not */
    else {
      excitementScore += abs(currMatch->p1 - previousVictor);
      if (currMatch->p1 > previousVictor) {
        remainingPlayers = removePlayer(remainingPlayers, previousVictor);
        previousVictor = currMatch->p1;
      }
      else {
        remainingPlayers = removePlayer(remainingPlayers, currMatch->p1);
      }
    }
  }

  /* player 2 is still in the tournament but player 1 is not */
  else {
    excitementScore += abs(previousVictor - currMatch->p2);
    if (previousVictor > currMatch->p2) {
      remainingPlayers = removePlayer(remainingPlayers, currMatch->p2);
    }
    else {
      remainingPlayers = removePlayer(remainingPlayers, previousVictor);
      previousVictor = currMatch->p2;
    }
  }
}

/* Search through remaining players in the tournament */
_Bool checkRemainingPlayers(int *remainingPlayers, int player) {
  for (int i = 0; i < numPlayers; i++)
    if (remainingPlayers[i] == player) return 1;

  return 0;
}

/* Removes the match loser from the array of remaining players */
int * removePlayer(int *remainingPlayers, int player) {
  for (int i = 0; i < numPlayers; i++) {
    if (remainingPlayers[i] == player) {
      for (int j = i; j < numPlayers; j++) {
        remainingPlayers[j] = remainingPlayers[j + 1];
      }
      remainingPlayers[numPlayers - 1] = 0;
      return remainingPlayers;
    }
  }
  return remainingPlayers;
}
