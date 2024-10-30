#include <jni.h>
#include <vector>
#include "Main.h"

std::vector<std::vector<char>> board(5, std::vector<char>(5, ' '));
char currentPlayer = 'X';
int movesCount = 0;
int activeRow = 0, activeCol = 0;

extern "C" {

JNIEXPORT void JNICALL Java_Main_resetGame(JNIEnv*, jobject) {
    board = std::vector<std::vector<char>>(5, std::vector<char>(5, ' '));
    currentPlayer = 'X';
    movesCount = 0;
    activeRow = 0;
    activeCol = 0;
}

JNIEXPORT jcharArray JNICALL Java_Main_getBoard(JNIEnv* env, jobject) {
    jcharArray result = env->NewCharArray(25);
    jchar temp[25];
    int index = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            temp[index++] = board[i][j];
        }
    }

    env->SetCharArrayRegion(result, 0, 25, temp);
    return result;
}

bool winCheck() {
    for (int i = 0; i < 5; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
            board[i][2] == board[i][3] && board[i][3] == board[i][4])
            return true;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
            board[2][i] == board[3][i] && board[3][i] == board[4][i])
            return true;
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
        board[2][2] == board[3][3] && board[3][3] == board[4][4])
        return true;
    if (board[0][4] != ' ' && board[0][4] == board[1][3] && board[1][3] == board[2][2] &&
        board[2][2] == board[3][1] && board[3][1] == board[4][0])
        return true;

    return false;
}

JNIEXPORT jint JNICALL Java_Main_makeMove(JNIEnv*, jobject, jint row, jint col) {
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        movesCount++;

        bool win = winCheck();
        if (win) return 1;

        if (movesCount == 25) return 2;

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    return 0;
}

JNIEXPORT jchar JNICALL Java_Main_getCurrentPlayer(JNIEnv*, jobject) {
    return currentPlayer;
}

JNIEXPORT jintArray JNICALL Java_Main_getActiveCell(JNIEnv* env, jobject) {
    jintArray result = env->NewIntArray(2);
    jint temp[2] = {activeRow, activeCol};
    env->SetIntArrayRegion(result, 0, 2, temp);
    return result;
}

JNIEXPORT void JNICALL Java_Main_moveActiveCell(JNIEnv*, jobject, jint direction) {
    switch (direction) {
        case 0: activeRow = (activeRow > 0) ? activeRow - 1 : 4; break; //up
        case 1: activeRow = (activeRow < 4) ? activeRow + 1 : 0; break; //down
        case 2: activeCol = (activeCol > 0) ? activeCol - 1 : 4; break; //left
        case 3: activeCol = (activeCol < 4) ? activeCol + 1 : 0; break; //right
    }
}
}
