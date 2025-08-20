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
    
    public:
        // Inicializar o cubo:
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

        string tempBack = back[0][0]; //Errado
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
        cout << "\t" << "    "; cout << up[0][0] << " " << up[0][1] << endl;
        cout << "\t" << "    "; cout << up[1][0] << " " << up[1][1] << endl;
        cout << "       " << left[0][0]<< " " << left[0][1] << "  " << front[0][0]<<  " " << front[0][1] << "  " << right[0][0] << " " << right[0][1] << "  "; cout << back[0][0] << " " << back[0][1] << endl;
        cout << "       " << left[1][0]<< " " << left[1][1] << "  " << front[1][0]<<  " " << front[1][1] << "  " << right[1][0] << " " << right[1][1] << "  "; cout << back[0][0] << " " << back[0][1] << endl;
        cout << "\t" << "    "; cout << down[0][0] << " " << down[0][1] << endl;
        cout << "\t" << "    "; cout << down[1][0] << " " << down[1][1] << endl;
        cout << endl;
        cout<< "\t" << "MOVIMENTOS: " << endl;
        cout<< "     " << "- U" << "   ";
        cout << "- D" << "   ";
        cout << "- L" << endl;
        cout<< "     " << "- R" << "   ";
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
            cout << "Instrução não reconhecida, tente novamente" << endl;
        }
    }

    return 0;
}