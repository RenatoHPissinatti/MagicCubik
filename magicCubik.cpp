#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

inline void clearScreen() {
    std::system(CLEAR_SCREEN);
}

using namespace std;

struct CubikState {
    char up[2][2];
    char down[2][2];
    char left[2][2];
    char right[2][2];
    char front[2][2];
    char back[2][2];

    deque<char> moveHistory;
};

class magicCubik2x2x2 {
private:
    char up[2][2];
    char down[2][2];
    char left[2][2];
    char right[2][2];
    char front[2][2];
    char back[2][2];

    deque<CubikState> stateHistory; // Fila que armazena os estados


    // Retorna o "inner" colorido (2 espaços com background ANSI)
    string inner(char c) const {
        switch (c) {
            case 'W': return string("\033[107m  \033[0m");
            case 'Y': return string("\033[103m  \033[0m");
            case 'O': return string("\033[48;5;208m  \033[0m");
            case 'R': return string("\033[48;5;196m  \033[0m");
            case 'G': return string("\033[102m  \033[0m");
            case 'B': return string("\033[104m  \033[0m");
            default: return string("  ");

        }
    }

    void moveU () {
        char temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];

        front[0][0] = right[0][0]; front[0][1] = right[0][1];
        right[0][0] = back[0][0];  right[0][1] = back[0][1];
        back[0][0]  = left[0][0];  back[0][1]  = left[0][1];
        left[0][0]  = temp[0][0];  left[0][1]  = temp[0][1];

        char tempUp = up[0][0];
        up[0][0] = up[1][0];
        up[1][0] = up[1][1];
        up[1][1] = up[0][1];
        up[0][1] = tempUp;
    }

    void moveD () {
        char temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];

        front[1][0] = right[1][0]; front[1][1] = right[1][1];
        right[1][0] = back[1][0];  right[1][1] = back[1][1];
        back[1][0]  = left[1][0];  back[1][1]  = left[1][1];
        left[1][0]  = temp[1][0];  left[1][1]  = temp[1][1];

        char tempDown = down[0][0];
        down[0][0] = down[1][0];
        down[1][0] = down[1][1];
        down[1][1] = down[0][1];
        down[0][1] = tempDown;
    }

    void moveR () {
        char temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];

        front[0][1] = down[0][1];
        front[1][1] = down[1][1];
        down[0][1]  = back[1][0];
        down[1][1]  = back[0][0];
        back[0][0]  = up[1][1];
        back[1][0]  = up[0][1];
        up[1][1]    = temp[1][1];
        up[0][1]    = temp[0][1];

        char tempRight = right[0][0];
        right[0][0] = right[1][0];
        right[1][0] = right[1][1];
        right[1][1] = right[0][1];
        right[0][1] = tempRight;
    }

    void moveL () {
        char temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];

        front[0][0] = down[0][0];
        front[1][0] = down[1][0];
        down[0][0]  = back[1][1];
        down[1][0]  = back[0][1];
        back[1][1]  = up[0][0];
        back[0][1]  = up[1][0];
        up[0][0]    = temp[0][0];
        up[1][0]    = temp[1][0];

        char tempLeft = left[0][0];
        left[0][0] = left[0][1];
        left[0][1] = left[1][1];
        left[1][1] = left[1][0];
        left[1][0] = tempLeft;
    }

    void moveF () {
        char temp[2][2];
        temp[0][0] = up[0][0]; temp[0][1] = up[0][1];
        temp[1][0] = up[1][0]; temp[1][1] = up[1][1];

        up[1][0] = left[1][1];
        up[1][1] = left[0][1];
        left[1][1] = down[0][1];
        left[0][1] = down[0][0];
        down[0][1] = right[0][0];
        down[0][0] = right[1][0];
        right[0][0] = temp[1][0];
        right[1][0] = temp[1][1];

        char tempFront = front[0][0];
        front[0][0] = front[1][0];
        front[1][0] = front[1][1];
        front[1][1] = front[0][1];
        front[0][1] = tempFront;
    }

    void moveB () {
        char temp[2][2];
        temp[0][0] = up[0][0]; temp[0][1] = up[0][1];
        temp[1][0] = up[1][0]; temp[1][1] = up[1][1];

        up[0][0] = left[1][0];
        up[0][1] = left[0][0];
        left[1][0] = down[1][1];
        left[0][0] = down[1][0];
        down[1][1] = right[0][1];
        down[1][0] = right[1][1];
        right[0][1] = temp[0][0];
        right[1][1] = temp[0][1];

        char tempBack = back[0][0];
        back[0][0] = back[0][1];
        back[0][1] = back[1][1];
        back[1][1] = back[1][0];
        back[1][0] = tempBack;
    }


public:
    magicCubik2x2x2() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                up[i][j] = 'W';
                down[i][j] = 'Y';
                left[i][j] = 'O';
                right[i][j] = 'R';
                front[i][j] = 'G';
                back[i][j] = 'B';
            }
        }

        CubikState initialState = this->getCurrentState();
        initialState.moveHistory.push_front('I');
           
        stateHistory.push_front(initialState);
    }

    void shuffleCubik () {
        srand(time(0));
        long long randNum = rand();

        for (long long i = randNum; i > 0; i /=6) {
            int mov = i%6;
            switch (mov)
            {
            case 0: this->moveU(); break;
            case 1: this->moveD(); break;
            case 2: this->moveL(); break;
            case 3: this->moveR(); break;
            case 4: this->moveF(); break;
            case 5: this->moveB(); break;
            default: return;
            }
        }
    }

    void checkState () {
        bool solved = false;
        set<char> checkUp;
        set<char> checkDown;
        set<char> checkLeft;
        set<char> checkRight;
        set<char> checkFront;
        set<char> checkBack;

        for (int i = 0; i < 2; ++i) {
            if (solved) break;
            for (int j = 0; j < 2; ++j) {

                checkUp.insert(up[i][j]);
                checkDown.insert(down[i][j]);
                checkLeft.insert(left[i][j]);
                checkRight.insert(right[i][j]);
                checkFront.insert(front[i][j]);
                checkBack.insert(back[i][j]);

                if (
                    checkUp.size() > 1 ||
                    checkDown.size() > 1 || 
                    checkLeft.size() > 1 ||
                    checkRight.size() > 1 ||
                    checkFront.size() > 1 ||
                    checkBack.size() > 1
                ) {
                    solved = true;
                    break;
                }
            }
        }

        if (!solved) {
            cout << "Solução encontrada!!!" << endl << endl;
            cout << "Movimentos realizados: ";
            if (!stateHistory.empty()) {
                deque<char> tempHistory = stateHistory.back().moveHistory;
                int moveCount = 0;

                for (char c : tempHistory) {
                    if (c != 'I') ++moveCount;
                }
                cout << moveCount << endl;
                cout << "Sequência de movimentos: ";
                
                for (char c : tempHistory) {
                    if (c != 'I') cout << c << " ";
                }
                cout << endl;
                stateHistory.clear();
            } else {
                cout << "0" << endl;
            }
        }
    }

    
    void performAndRecordMove(char m) { //Método centralizador que realiza os movimentos e armazena na lista

        deque<char> previousHistory = stateHistory.back().moveHistory;

        switch (m) {
            case 'U': this->moveU(); break;
            case 'D': this->moveD(); break;
            case 'L': this->moveL(); break;
            case 'R': this->moveR(); break;
            case 'F': this->moveF(); break;
            case 'B': this->moveB(); break;
            default: return;
        }
        
        CubikState newState = this->getCurrentState();
        newState.moveHistory = previousHistory;
        newState.moveHistory.push_back(m);
        stateHistory.push_back(newState);
    }

    deque<CubikState> & getStateHistory()
    { 
        return stateHistory; 
    }
    

    CubikState getCurrentState() const {
        CubikState currentState;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                currentState.up[i][j] = up[i][j];
                currentState.down[i][j] = down[i][j];
                currentState.left[i][j] = left[i][j];
                currentState.right[i][j] = right[i][j];
                currentState.front[i][j] = front[i][j];
                currentState.back[i][j] = back[i][j];
            }
        }
        return currentState;
    }

    // Impressão com bordas compartilhadas (junções) entre células
    void printCubik() {
/*
        cout << "==========================================" << endl;

        cout << "Historico de Movimentos:" << endl;

    
    if (!stateHistory.empty()) {
        deque<char> tempMoveHistory = stateHistory.back().moveHistory;

        while (!tempMoveHistory.empty()) {
            cout << tempMoveHistory.front() << " ";
            tempMoveHistory.pop_front();
        }
        cout << endl;
    }else{
        cout << "Nenhum movimento registrado." << endl;
        return;
    
    }
*/    
        cout << "==========================================" << endl;

        cout << "\t" << " " << endl;
        cout << "       " << inner(up[0][0]) << " " << inner(up[0][1]) << endl;
        cout << "       " << endl;
        cout << "       " << inner(up[1][0]) << " " << inner(up[1][1]) << endl;
        cout << "       " << endl;

        cout
             << inner(left[0][0]) << " " <<  inner(left[0][1]) << "  "
             << inner(front[0][0]) << " " << inner(front[0][1]) << "  "
             << inner(right[0][0]) << " " <<  inner(right[0][1]) << "  "
             << inner(back[0][0]) << " " <<  inner(back[0][1]) << endl;
        cout
             << "  "
             << endl;
        cout
             << inner(left[1][0]) << " " << inner(left[1][1]) << "  "
             << inner(front[1][0]) << " " <<  inner(front[1][1]) << "  "
             << inner(right[1][0]) << " " << inner(right[1][1]) << "  "
             << inner(back[1][0]) << " " <<  inner(back[1][1]) << endl;

        cout << "\t" << endl;
        cout << "       " << inner(down[0][0]) << " " << inner(down[0][1]) << endl;
        cout << "       " << " " << endl;
        cout << "       " << inner(down[1][0]) << " " << inner(down[1][1]) << endl;
        cout << "       " << " " << endl;

        cout << "==========================================" << endl;
        cout << "\t" << "MANUAL DE INSTRUÇÕES" << endl;
        cout << "U -> Face superior" << "     |  ";
        cout << "D -> Face inferior" << endl;
        cout << "L -> Face esquerda" << "     |  ";
        cout << "R -> Face direita" << endl;
        cout << "F -> Face frontal" << "      |  ";
        cout << "B -> Face traseira" << endl;
        cout << "S -> Embaralhar o cubo" << " |  ";
        cout << "Q -> Encerrar programa" << endl << endl;
    }
};


class algorithms {
    public:
        vector<char> bfs(const CubikState &start);
        vector<char> dfs(const CubikState &start, int godNumber = 14);
        vector<char> aEstrela(const CubikState &start);
};

int main() {
    clearScreen();
    magicCubik2x2x2 cube;

    char m;
    while (true) {
        cout << "\n\t MAGIC CUBIK " << endl;
        cube.printCubik();
        
        cout << "INSTRUÇÃO : ";
        cin >> m;
        clearScreen();
        m = toupper(m);

        if(m =='U' || m =='D' || m == 'L' || m == 'R' || m == 'F' || m == 'B') {
            cube.performAndRecordMove(m);
            cube.checkState();

        } else if (m == 'Q' || m == 'q') {
            break;
        }
        else if (m == 'S') {
            cube.shuffleCubik();

        } else {
            cout << "Movimento inválido. Tente novamente." << endl;
        }
    }
    return 0;
}

