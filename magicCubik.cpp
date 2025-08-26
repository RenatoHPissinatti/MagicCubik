#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define fastio ios_base::sync_with_stdio(false);
#define fo(i,n) for(i=0;i<n;i++)
#define si(x)	cin >> x  
#define pi(x)   cout << x
#define pl(x)   cout << x << "\n"


class magicCubik2x2x2 {
    private:
        string up[2][2];
        string down[2][2];
        string left[2][2];
        string right[2][2];
        string front[2][2];
        string back[2][2];

    string color (const string &s) const {
        char c = s[0];
        switch (c) {
            case 'W': // White
                return string("\033[47m  \033[0m"); break;
            case 'Y': // Yellow
                return string("\033[43m  \033[0m"); break;
            case 'O': // Orange - usa 256-color (fallback: brownish)
                return string("\033[48;5;208m  \033[0m"); break;
            case 'R': // Red
                return string("\033[41m  \033[0m"); break;
            case 'G': // Green
                return string("\033[42m  \033[0m"); break;
            case 'B': // Blue
                return string("\033[44m  \033[0m"); break;
            default:
                string out = s;
                return out;
        }
    }
    
    public:
        // Inicializar o cubo:
        magicCubik2x2x2() {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    up[i][j] = "W" + to_string(i+j);
                    down[i][j] = "Y" + to_string(i+j);
                    left[i][j] = "O" + to_string(i+j);
                    right[i][j] = "R" + to_string(i+j);
                    front[i][j] = "G" + to_string(i+j);
                    back[i][j] = "B" + to_string(i+j);
                }
            }
        }
    // Manipulação do cubo
    void moveU () { //CORRETO
    string temp[2][2];
    temp[0][0] = front[0][0];
    temp[0][1] = front[0][1];
    temp[1][0] = front[1][0];
    temp[1][1] = front[1][1];

    front[0][0] = right[0][0];
    front[0][1] = right[0][1];

    right[0][0] = back[0][0];
    right[0][1] = back[0][1];

    back[0][0] = left[0][0];
    back[0][1] = left[0][1];

    left[0][0] = temp[0][0];
    left[0][1] = temp[0][1];

    string tempUp = up[0][0];
    up[0][0] = up[1][0];
    up[1][0] = up[1][1];
    up[1][1] = up[0][1];
    up[0][1] = tempUp;

    }
    void moveD () {
        string temp[2][2];
        temp[0][0] = front[0][0];
        temp[0][1] = front[0][1];
        temp[1][0] = front[1][0];
        temp[1][1] = front[1][1];

        front[1][0] = right[1][0];
        front[1][1] = right[1][1];

        right[1][0] = back[1][0];
        right[1][1] = back[1][1];

        back[1][0] = left[1][0];
        back[1][1] = left[1][1];

        left[1][0] = temp[1][0];
        left[1][1] = temp[1][1];

        string tempDown = down[0][0];
        down[0][0] = down[1][0];
        down[1][0] = down[1][1];
        down[1][1] = down[0][1];
        down[0][1] = tempDown;
    }

    void moveR () { //CORRETO
        string temp[2][2];
        temp[0][0] = front[0][0];
        temp[0][1] = front[0][1];
        temp[1][0] = front[1][0];
        temp[1][1] = front[1][1];

        front[0][1] = down[0][1];
        front[1][1] = down[1][1];

        down[0][1] = back[0][1];
        down[1][1] = back[0][0];
        
        back[0][0] = up[1][1];
        back[0][1] = up[0][1];

        up[1][1] = temp[1][1];
        up[0][1] = temp[0][1];

        string tempRight = right[0][0];

        right[0][0] = right[1][0];
        right[1][0] = right[1][1];
        right[1][1] = right[0][1];
        right[0][1] = tempRight;
    }

    void moveL () { //CORRETO
        string temp[2][2];
        temp[0][0] = front[0][0];
        temp[0][1] = front[0][1];
        temp[1][0] = front[1][0];
        temp[1][1] = front[1][1];

        front[0][0] = down[0][0];
        front[1][0] = down[1][0];

        down[0][0] = back[1][1];
        down[1][0] = back[0][1];

        back[1][1] = up[0][0];
        back[0][1] = up[1][0];

        up[0][0] = temp[0][0];
        up[1][0] = temp[1][0];

        string tempLeft = left[0][0];
        left[0][0] = left[0][1];
        left[0][1] = left[1][1];
        left[1][1] = left[1][0];
        left[1][0] = tempLeft;
    }

    void moveF () { //CORRETO
        string temp[2][2];
        temp[0][0] = up[0][0];
        temp[0][1] = up[0][1];
        temp[1][0] = up[1][0];
        temp[1][1] = up[1][1];
        
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

    void moveB () {//CORRETO
        string temp[2][2];
        temp[0][0] = up[0][0];
        temp[0][1] = up[0][1];
        temp[1][0] = up[1][0];
        temp[1][1] = up[1][1];

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

    // Representação do cubo em 2D
    //         [Up]
    //[Left] [Front] [Right] [Back]
    //        [Down]]

    void printCubik() {
        cout << "==============================" << endl;
        // Up
        cout << "\t" << color(up[0][0]) << color(up[0][1]) << endl;
        cout << "\t" << color(up[1][0]) << color(up[1][1]) << endl;

        // Middle: Left Front Right Back
        cout << " " << color(left[0][0]) << color(left[0][1]) << "  "
             << color(front[0][0]) << color(front[0][1]) << "  "
             << color(right[0][0]) << color(right[0][1]) << "  "
             << color(back[0][0]) << color(back[0][1]) << endl;

        cout << " " << color(left[1][0]) << color(left[1][1]) << "  "
             << color(front[1][0]) << color(front[1][1]) << "  "
             << color(right[1][0]) << color(right[1][1]) << "  "
             << color(back[1][0]) << color(back[1][1]) << endl;

        // Down
        cout << "\t" << color(down[0][0]) << color(down[0][1]) << endl;
        cout << "\t" << color(down[1][0]) << color(down[1][1]) << endl;
        cout << endl;

        cout<< "      " << "MOVIMENTOS: " << endl;
        cout<< "   " << "- U" << "   ";
        cout << "- D" << "   ";
        cout << "- L" << endl;
        cout<< "   " << "- R" << "   ";
        cout << "- F" << "   ";
        cout << "- B" << "   " << endl;
    }
};




int main() {
    magicCubik2x2x2 cube;
    cout << "\n\t MAGIC CUBIK " << endl;
    cube.printCubik();

    char m;
    while(true) {
        cin >> m;
        if (m == 'U') {
            cube.moveU();
            cube.printCubik();
        } else if (m == 'D') {
            cube.moveD();
            cube.printCubik();
        } else if (m == 'L') {
            cube.moveL();
            cube.printCubik();
        } else if (m == 'R') {
            cube.moveR();
            cube.printCubik();
        } else if (m == 'F') {
            cube.moveF();
            cube.printCubik();
        } else if (m == 'B') {
            cube.moveB();
            cube.printCubik();
        } else {
            cout << "Instrução inválida, tente novamente" << endl;
        }
    }

    return 0;
}