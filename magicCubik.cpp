#include <bits/stdc++.h>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

struct CubikState {
    string up[2][2];
    string down[2][2];
    string left[2][2];
    string right[2][2];
    string front[2][2];
    string back[2][2];

    deque<char> moveHistory;
};

class magicCubik2x2x2 {
private:
    string up[2][2];
    string down[2][2];
    string left[2][2];
    string right[2][2];
    string front[2][2];
    string back[2][2];

    deque<CubikState> stateHistory; // Fila que armazena os estados


    // Retorna o "inner" colorido (2 espaços com background ANSI)
    string inner(const string &s) const {
        if (s.empty()) return "  ";
        char c = s[0];
        switch (c) {
            case 'W': return string("\033[107m  \033[0m");
            case 'Y': return string("\033[103m  \033[0m");
            case 'O': return string("\033[48;5;202m  \033[0m");
            case 'R': return string("\033[48;5;196m  \033[0m");
            case 'G': return string("\033[102m  \033[0m");
            case 'B': return string("\033[104m  \033[0m");
            default:
                {
                    string out = s;
                    if (out.size() < 2) out += ' ';
                    return out;
                }
        }
    }
    string face_top() const { return "┌──┬──┐"; }
    string face_middle_junction() const { return "├──┼──┤"; }
    string face_bottom() const { return "└──┴──┘"; }
    string face_row_middle(const string &a, const string &b) const {
        return string("│") + inner(a) + "│" + inner(b) + "│";
    }

    void moveU () {
        string temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];

        front[0][0] = right[0][0]; front[0][1] = right[0][1];
        right[0][0] = back[0][0];  right[0][1] = back[0][1];
        back[0][0]  = left[0][0];  back[0][1]  = left[0][1];
        left[0][0]  = temp[0][0];  left[0][1]  = temp[0][1];

        string tempUp = up[0][0];
        up[0][0] = up[1][0];
        up[1][0] = up[1][1];
        up[1][1] = up[0][1];
        up[0][1] = tempUp;
    }

    void moveD () {
        string temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];

        front[1][0] = right[1][0]; front[1][1] = right[1][1];
        right[1][0] = back[1][0];  right[1][1] = back[1][1];
        back[1][0]  = left[1][0];  back[1][1]  = left[1][1];
        left[1][0]  = temp[1][0];  left[1][1]  = temp[1][1];

        string tempDown = down[0][0];
        down[0][0] = down[1][0];
        down[1][0] = down[1][1];
        down[1][1] = down[0][1];
        down[0][1] = tempDown;
    }

    void moveR () {
        string temp[2][2];
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

        string tempRight = right[0][0];
        right[0][0] = right[1][0];
        right[1][0] = right[1][1];
        right[1][1] = right[0][1];
        right[0][1] = tempRight;
    }

    void moveL () {
        string temp[2][2];
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

        string tempLeft = left[0][0];
        left[0][0] = left[0][1];
        left[0][1] = left[1][1];
        left[1][1] = left[1][0];
        left[1][0] = tempLeft;
    }

    void moveF () {
        string temp[2][2];
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

        string tempFront = front[0][0];
        front[0][0] = front[1][0];
        front[1][0] = front[1][1];
        front[1][1] = front[0][1];
        front[0][1] = tempFront;
    }

    void moveB () {
        string temp[2][2];
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

        string tempBack = back[0][0];
        back[0][0] = back[0][1];
        back[0][1] = back[1][1];
        back[1][1] = back[1][0];
        back[1][0] = tempBack;
    }


public:
    magicCubik2x2x2() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                up[i][j] = "W" + to_string(i) + to_string(j);
                down[i][j] = "Y" + to_string(i) + to_string(j);
                left[i][j] = "O" + to_string(i) + to_string(j);
                right[i][j] = "R" + to_string(i) + to_string(j);
                front[i][j] = "G" + to_string(i) + to_string(j);
                back[i][j] = "B" + to_string(i) + to_string(j);
            }
        }

        CubikState initialState = this->getCurrentState();
        initialState.moveHistory.push_front('I');
           
        stateHistory.push_front(initialState);
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

        cout << "==========================================" << endl;

        cout << "\t" << " " << face_top() << endl;
        cout << "\t" << " " << face_row_middle(up[0][0], up[0][1]) << endl;
        cout << "\t" << " " << face_middle_junction() << endl;
        cout << "\t" << " " << face_row_middle(up[1][0], up[1][1]) << endl;
        cout << "\t" << " " << face_bottom() << endl;

        cout
             << face_top() << "  " << face_top() << "  " << face_top() << "  " << face_top() << endl;
        cout
             << face_row_middle(left[0][0], left[0][1]) << "  "
             << face_row_middle(front[0][0], front[0][1]) << "  "
             << face_row_middle(right[0][0], right[0][1]) << "  "
             << face_row_middle(back[0][0], back[0][1]) << endl;
        cout
             << face_middle_junction() << "  " << face_middle_junction() << "  "
             << face_middle_junction() << "  " << face_middle_junction() << endl;
        cout
             << face_row_middle(left[1][0], left[1][1]) << "  "
             << face_row_middle(front[1][0], front[1][1]) << "  "
             << face_row_middle(right[1][0], right[1][1]) << "  "
             << face_row_middle(back[1][0], back[1][1]) << endl;
        cout
             << face_bottom() << "  " << face_bottom() << "  " << face_bottom() << "  " << face_bottom() << endl;

        cout << "\t" << " " << face_top() << endl;
        cout << "\t" << " " << face_row_middle(down[0][0], down[0][1]) << endl;
        cout << "\t" << " " << face_middle_junction() << endl;
        cout << "\t" << " " << face_row_middle(down[1][0], down[1][1]) << endl;
        cout << "\t" << " " << face_bottom() << endl;

        cout << "==========================================" << endl;
        cout << " MOVIMENTOS: U D L R F B " << endl << endl;
    }
};

int main() {
    magicCubik2x2x2 cube;
    cout << "\n\t MAGIC CUBIK " << endl;
    cube.printCubik();

    char m;
    while (true) {
        cout << "Digite um movimento (U, D, L, R, F, B) ou 'Q' para sair: ";
        cin >> m;
        m = toupper(m);

        if(m =='U' || m =='D' || m == 'L' || m == 'R' || m == 'F' || m == 'B') {
            
            cube.performAndRecordMove(m);

            cube.printCubik();
        } else if (m == 'Q' || m == 'q') {
            break;
        }
        else
        {
            cout << "Movimento inválido. Tente novamente." << endl;
        }
    }
    return 0;
}

