#include <bits/stdc++.h>
#include <queue>
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
};

class magicCubik2x2x2 {
private:
    string up[2][2];
    string down[2][2];
    string left[2][2];
    string right[2][2];
    string front[2][2];
    string back[2][2];

    std::queue<char> moveHistory; // Fila que armazena os movimentos
    std::queue<CubikState> stateHistory; // Fila que armazena os estados


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
              // blue
            default:
                // fallback: mostra a própria string (até 2 chars) sem cor
                {
                    string out = s;
                    if (out.size() < 2) out += ' ';
                    return out;
                }
        }
    }

    // Componentes de uma face 2x2 com bordas compartilhadas
    string face_top() const { return "┌──┬──┐"; }
    string face_middle_junction() const { return "├──┼──┤"; }
    string face_bottom() const { return "└──┴──┘"; }
    // linha do meio da face contendo os dois inner (por ex: │<i0>│<i1>│)
    string face_row_middle(const string &a, const string &b) const {
        return string("│") + inner(a) + "│" + inner(b) + "│";
    }

public:
    magicCubik2x2x2() {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) {
                up[i][j] = "W" + to_string(i+j);
                down[i][j] = "Y" + to_string(i+j);
                left[i][j] = "O" + to_string(i+j);
                right[i][j] = "R" + to_string(i+j);
                front[i][j] = "G" + to_string(i+j);
                back[i][j] = "B" + to_string(i+j);
            }
    }


    void addMove(char m)
    {
        moveHistory.push(m);
    }

    std::queue<char> & getMoveHistory()
    { 
        return moveHistory; 
    }

    std::queue<CubikState> & getStateHistory()
    { 
        return stateHistory; 
    }
    

    CubikState getCurrentState() const {
        CubikState currentState;
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {
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

    // Movimentos (mantidos sem alteração)
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

    // Impressão com bordas compartilhadas (junções) entre células
    void printCubik() {
        cout << "==========================================" << endl;

        // ---- UP (centrado com tab)
        cout << "\t" << " " << face_top() << endl;
        cout << "\t" << " " << face_row_middle(up[0][0], up[0][1]) << endl;
        cout << "\t" << " " << face_middle_junction() << endl;
        cout << "\t" << " " << face_row_middle(up[1][0], up[1][1]) << endl;
        cout << "\t" << " " << face_bottom() << endl;

        // ---- MIDDLE: Left | Front | Right | Back
        // top borders
        cout
             << face_top() << "  " << face_top() << "  " << face_top() << "  " << face_top() << endl;
        // row 0 middles
        cout
             << face_row_middle(left[0][0], left[0][1]) << "  "
             << face_row_middle(front[0][0], front[0][1]) << "  "
             << face_row_middle(right[0][0], right[0][1]) << "  "
             << face_row_middle(back[0][0], back[0][1]) << endl;
        // junctions between row 0 and row 1
        cout
             << face_middle_junction() << "  " << face_middle_junction() << "  "
             << face_middle_junction() << "  " << face_middle_junction() << endl;
        // row 1 middles
        cout
             << face_row_middle(left[1][0], left[1][1]) << "  "
             << face_row_middle(front[1][0], front[1][1]) << "  "
             << face_row_middle(right[1][0], right[1][1]) << "  "
             << face_row_middle(back[1][0], back[1][1]) << endl;
        // bottom borders
        cout
             << face_bottom() << "  " << face_bottom() << "  " << face_bottom() << "  " << face_bottom() << endl;

        // ---- DOWN (centrado)
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
    std::cout << "\n\t MAGIC CUBIK " << std::endl;
    cube.printCubik();

    cube.getMoveHistory().push('I');
    cube.getStateHistory().push(cube.getCurrentState());

    char m;
    while (true) {
        std::cout << "Digite um movimento (U, D, L, R, F, B) ou 'Q' para sair: ";
        std::cin >> m;

        if(m =='U' || m =='D' || m == 'L' || m == 'R' || m == 'F' || m == 'B') {
            
            switch(m)
            {
                case 'U':
                    cube.moveU();
                    break;
                case 'D':
                    cube.moveD();
                    break;
                case 'L':
                    cube.moveL();
                    break;
                case 'R':
                    cube.moveR();
                    break;
                case 'F':
                    cube.moveF();
                    break;
                case 'B':
                    cube.moveB();
                    break;
            }

            cube.getMoveHistory().push(m);
            cube.getStateHistory().push(cube.getCurrentState());

            cube.printCubik();
        } else if (m == 'Q' || m == 'q') {
            break;
        }
        else
        {
            std::cout << "Movimento inválido. Tente novamente." << std::endl;
        }
    }
    return 0;
}

