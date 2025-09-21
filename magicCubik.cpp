<<<<<<< Updated upstream
#include <bits/stdc++.h>
#include <deque>
#include <string>
#include <iostream>
=======
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map> // NOVO: Para a heurística

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

inline void clearScreen() {
    std::system(CLEAR_SCREEN);
}
>>>>>>> Stashed changes

using namespace std;

// Estrutura que representa um estado (configuração) do cubo.
struct CubikState {
    string up[2][2];
    string down[2][2];
    string left[2][2];
    string right[2][2];
    string front[2][2];
    string back[2][2];

    // Armazena a sequência de movimentos para chegar a este estado.
    vector<char> moveHistory; 
    
    // MODIFICADO: Campos para o algoritmo A*
    int g_cost; // Custo real do estado inicial até o estado atual (número de movimentos)
    int h_cost; // Custo estimado (heurística) do estado atual até a solução

    // Função para calcular o custo total f(n) = g(n) + h(n)
    int f_cost() const {
        return g_cost + h_cost;
    }
};

// NOVO: Estrutura comparadora para a fila de prioridade do A*
// A fila de prioridade do C++ é um max-heap por padrão.
// Precisamos de um min-heap para obter o estado com o MENOR f_cost.
// Por isso, a lógica é invertida (retorna true se 'a' tiver custo maior que 'b').
struct CompareState {
    bool operator()(const CubikState& a, const CubikState& b) const {
        return a.f_cost() > b.f_cost();
    }
};


class magicCubik2x2x2 {
private:
    string up[2][2];
    string down[2][2];
    string left[2][2];
    string right[2][2];
    string front[2][2];
    string back[2][2];

    deque<CubikState> stateHistory; // Fila que armazena os estados para o modo manual

    // Retorna o "inner" colorido (2 espaços com background ANSI)
    string inner(const string &s) const {
        if (s.empty()) return "  ";
        char c = s[0];
        switch (c) {
<<<<<<< Updated upstream
            case 'W': return string("\033[107m  \033[0m");
            case 'Y': return string("\033[103m  \033[0m");
            case 'O': return string("\033[48;5;202m  \033[0m");
            case 'R': return string("\033[48;5;196\m  \033[0m");
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
=======
            case 'W': return string("\033[107m  \033[0m"); // Branco
            case 'Y': return string("\033[103m  \033[0m"); // Amarelo
            case 'O': return string("\033[48;5;208m  \033[0m"); // Laranja
            case 'R': return string("\033[48;5;196m  \033[0m"); // Vermelho
            case 'G': return string("\033[102m  \033[0m"); // Verde
            case 'B': return string("\033[104m  \033[0m"); // Azul
            default: return string("  ");
>>>>>>> Stashed changes
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

    void moveU () {
        string temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
        
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
<<<<<<< Updated upstream
        string temp[2][2];
        temp[0][0] = front[0][0]; temp[0][1] = front[0][1];
=======
        char temp[2][2];
>>>>>>> Stashed changes
        temp[1][0] = front[1][0]; temp[1][1] = front[1][1];
        
        front[1][0] = left[1][0]; front[1][1] = left[1][1];
        left[1][0] = back[1][0];  left[1][1] = back[1][1];
        back[1][0]  = right[1][0];  back[1][1]  = right[1][1];
        right[1][0]  = temp[1][0];  right[1][1]  = temp[1][1];

        string tempDown = down[0][0];
        down[0][0] = down[1][0];
        down[1][0] = down[1][1];
        down[1][1] = down[0][1];
        down[0][1] = tempDown;
    }

    void moveR () {
<<<<<<< Updated upstream
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
=======
        char temp[2];
        temp[0] = front[0][1]; temp[1] = front[1][1];
        
        front[0][1] = down[0][1]; front[1][1] = down[1][1];
        down[0][1]  = back[1][0]; down[1][1]  = back[0][0];
        back[1][0]  = up[0][1];   back[0][0]  = up[1][1];
        up[0][1]    = temp[0];    up[1][1]    = temp[1];
>>>>>>> Stashed changes

        string tempRight = right[0][0];
        right[0][0] = right[1][0];
        right[1][0] = right[1][1];
        right[1][1] = right[0][1];
        right[0][1] = tempRight;
    }
    
    void moveL () {
<<<<<<< Updated upstream
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
=======
        char temp[2];
        temp[0] = front[0][0]; temp[1] = front[1][0];
        
        front[0][0] = up[0][0];   front[1][0] = up[1][0];
        up[0][0]    = back[1][1]; up[1][0]    = back[0][1];
        back[1][1]  = down[0][0]; back[0][1]  = down[1][0];
        down[0][0]  = temp[0];    down[1][0]  = temp[1];

        char tempLeft = left[0][0];
        left[0][0] = left[1][0];
        left[1][0] = left[1][1];
        left[1][1] = left[0][1];
        left[0][1] = tempLeft;
    }

    void moveF () {
        char temp[2];
        temp[0] = up[1][0]; temp[1] = up[1][1];
>>>>>>> Stashed changes

        up[1][0] = left[1][1];   up[1][1] = left[0][1];
        left[1][1] = down[0][1]; left[0][1] = down[0][0];
        down[0][1] = right[0][0]; down[0][0] = right[1][0];
        right[0][0] = temp[0];    right[1][0] = temp[1];

        string tempFront = front[0][0];
        front[0][0] = front[1][0];
        front[1][0] = front[1][1];
        front[1][1] = front[0][1];
        front[0][1] = tempFront;
    }

    void moveB () {
<<<<<<< Updated upstream
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
=======
        char temp[2];
        temp[0] = up[0][0]; temp[1] = up[0][1];

        up[0][0] = right[0][1]; up[0][1] = right[1][1];
        right[0][1] = down[1][1]; right[1][1] = down[1][0];
        down[1][1] = left[1][0]; down[1][0] = left[0][0];
        left[1][0] = temp[0]; left[0][0] = temp[1];
        
        char tempBack = back[0][0];
        back[0][0] = back[1][0];
        back[1][0] = back[1][1];
        back[1][1] = back[0][1];
        back[0][1] = tempBack;
>>>>>>> Stashed changes
    }

public:
    magicCubik2x2x2() {
        reset();
    }
    
    void reset() {
        for (int i = 0; i < 2; ++i) {

            for (int j = 0; j < 2; ++j) {
<<<<<<< Updated upstream
                up[i][j] = "W" + to_string(i+j);
                down[i][j] = "Y" + to_string(i+j);
                left[i][j] = "O" + to_string(i+j);
                right[i][j] = "R" + to_string(i+j);
                front[i][j] = "G" + to_string(i+j);
                back[i][j] = "B" + to_string(i+j);
=======
                up[i][j]    = 'W';
                down[i][j]  = 'Y';
                left[i][j]  = 'O';
                right[i][j] = 'R';
                front[i][j] = 'G';
                back[i][j]  = 'B';
>>>>>>> Stashed changes
            }
        }
        stateHistory.clear();
        CubikState initialState = this->getCurrentState();
        initialState.moveHistory.push_back('I');
        stateHistory.push_front(initialState);
    }
    
<<<<<<< Updated upstream
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
=======
    void applyMove(char move) {
        switch(move) {
            case 'U': moveU(); break;
            case 'D': moveD(); break;
            case 'L': moveL(); break;
            case 'R': moveR(); break;
            case 'F': moveF(); break;
            case 'B': moveB(); break;
        }
    }

    void shuffleCubik () {
        srand(time(0));
        int shuffle_moves = 6;
        char moves[] = {'U', 'D', 'L', 'R', 'F', 'B'};
        
        reset();
        cout << "Embaralhando o cubo com " << shuffle_moves << " movimentos..." << endl;
        for (int i = 0; i < shuffle_moves; ++i) {
            this->applyMove(moves[rand() % 6]);
        }
        stateHistory.clear(); // Limpa o histórico após embaralhar
    }
    
    bool isSolved() const {
        char u = up[0][0], d = down[0][0], l = left[0][0], r = right[0][0], f = front[0][0], b = back[0][0];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (up[i][j] != u || down[i][j] != d || left[i][j] != l ||
                    right[i][j] != r || front[i][j] != f || back[i][j] != b)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void checkStateAndPrintSolution() {
        if (isSolved()) {
            cout << "Solução encontrada!!!" << endl << endl;
            if (!stateHistory.empty() && stateHistory.back().moveHistory.front() != 'I') {
                const auto& history = stateHistory.back().moveHistory;
                cout << "Movimentos realizados: " << history.size() << endl;
                cout << "Sequência de movimentos: ";
                for (char c : history) {
                    cout << c << " ";
                }
                cout << endl;
            } else {
                cout << "O cubo já está resolvido. 0 movimentos." << endl;
            }
        }
    }

    void performAndRecordMove(char m) {
        vector<char> previousHistory;
        if (!stateHistory.empty()) {
            previousHistory = stateHistory.back().moveHistory;
            if (previousHistory.front() == 'I') {
                previousHistory.clear();
            }
>>>>>>> Stashed changes
        }
        
        applyMove(m);
        
        CubikState newState = this->getCurrentState();
        newState.moveHistory = previousHistory;
        newState.moveHistory.push_back(m);
        stateHistory.push_back(newState);
    }

    CubikState getCurrentState() const {
        CubikState currentState;
<<<<<<< Updated upstream
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                currentState.up[i][j] = up[i][j];
                currentState.down[i][j] = down[i][j];
                currentState.left[i][j] = left[i][j];
=======
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                currentState.up[i][j]    = up[i][j];
                currentState.down[i][j]  = down[i][j];
                currentState.left[i][j]  = left[i][j];
>>>>>>> Stashed changes
                currentState.right[i][j] = right[i][j];
                currentState.front[i][j] = front[i][j];
                currentState.back[i][j]  = back[i][j];
            }
        }
        return currentState;
    }
<<<<<<< Updated upstream

    // Impressão com bordas compartilhadas (junções) entre células
    void printCubik() {

        cout << "==========================================" << endl;

        cout << "Historico de Movimentos:" << endl;

=======
>>>>>>> Stashed changes
    
    void setState(const CubikState& state) {
         for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                up[i][j]    = state.up[i][j];
                down[i][j]  = state.down[i][j];
                left[i][j]  = state.left[i][j];
                right[i][j] = state.right[i][j];
                front[i][j] = state.front[i][j];
                back[i][j]  = state.back[i][j];
            }
        }
    }
<<<<<<< Updated upstream

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

=======

    void printCubik() {
        cout << "==========================================" << endl;

        cout << "\t" << " " << endl;
        cout << "      " << inner(up[0][0]) << " " << inner(up[0][1]) << endl;
        cout << "      " << " " << endl;
        cout << "      " << inner(up[1][0]) << " " << inner(up[1][1]) << endl;
        cout << "      " << " " << endl;

        cout << inner(left[0][0])  << " " << inner(left[0][1])  << "  "
             << inner(front[0][0]) << " " << inner(front[0][1]) << "  "
             << inner(right[0][0]) << " " << inner(right[0][1]) << "  "
             << inner(back[0][0])  << " " << inner(back[0][1])  << endl;
        cout << " " << endl;
        cout << inner(left[1][0])  << " " << inner(left[1][1])  << "  "
             << inner(front[1][0]) << " " << inner(front[1][1]) << "  "
             << inner(right[1][0]) << " " << inner(right[1][1]) << "  "
             << inner(back[1][0])  << " " << inner(back[1][1])  << endl;

        cout << "\t" << endl;
        cout << "      " << inner(down[0][0]) << " " << inner(down[0][1]) << endl;
        cout << "      " << " " << endl;
        cout << "      " << inner(down[1][0]) << " " << inner(down[1][1]) << endl;
        cout << "      " << " " << endl;

        cout << "==========================================" << endl;
        cout << "\t" << "MANUAL DE INSTRUÇÕES" << endl;
        cout << "U -> Face superior | D -> Face inferior" << endl;
        cout << "L -> Face esquerda | R -> Face direita" << endl;
        cout << "F -> Face frontal  | B -> Face traseira" << endl;
        cout << "S -> Embaralhar    | Q -> Sair" << endl;
        cout << "Z -> Resolver (DFS)| X -> Resolver (BFS)" << endl;
        cout << "A -> Resolver (A*) | C -> Limpar" << endl; // MODIFICADO
    }
};



class algorithms {
public:
    // Converte um estado do cubo em uma string única para fácil comparação e armazenamento
    string stateToString(const CubikState& s) {
        string res = "";
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) res += s.up[i][j];
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) res += s.down[i][j];
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) res += s.left[i][j];
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) res += s.right[i][j];
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) res += s.front[i][j];
        for(int i=0; i<2; ++i) for(int j=0; j<2; ++j) res += s.back[i][j];
        return res;
    }

    // Verifica se um estado do cubo está resolvido
    bool isStateSolved(const CubikState& s) {
        char u = s.up[0][0], d = s.down[0][0], l = s.left[0][0], r = s.right[0][0], f = s.front[0][0], b = s.back[0][0];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (s.up[i][j] != u || s.down[i][j] != d || s.left[i][j] != l ||
                    s.right[i][j] != r || s.front[i][j] != f || s.back[i][j] != b)
                {
                    return false;
                }
            }
        }
        return true;
    }

    vector<char> bfs(const CubikState &start) {
        if (isStateSolved(start)) {
            return {}; // Já está resolvido
        }

        queue<CubikState> q;
        q.push(start);

        set<string> visited;
        visited.insert(stateToString(start));
        
        char moves[] = {'U', 'D', 'L', 'R', 'F', 'B'};

        while(!q.empty()) {
            CubikState current = q.front();
            q.pop();

            for (char move : moves) {
                magicCubik2x2x2 tempCube;
                tempCube.setState(current);
                tempCube.applyMove(move);

                CubikState neighbor = tempCube.getCurrentState();
                string neighborStr = stateToString(neighbor);
                
                if (visited.find(neighborStr) == visited.end()) {
                    neighbor.moveHistory = current.moveHistory;
                    neighbor.moveHistory.push_back(move);
                    
                    if (isStateSolved(neighbor)) {
                        return neighbor.moveHistory;
                    }

                    visited.insert(neighborStr);
                    q.push(neighbor);
                }
            }
        }
        return {}; 
    }
    vector<char> dfs(const CubikState& start, int max_depth) {
        if (isStateSolved(start)) {
            return {}; 
        }
        
        set<string> visited;
        vector<char> path;
        
        if (dfs_recursive(start, visited, path, max_depth)) {
            return path; 
        }

        return {}; 
    }

    
    vector<char> a_star(const CubikState& start) {
        if (isStateSolved(start)) {
            return {}; // Já resolvido
        }

        // Fila de prioridade que armazena estados e os ordena pelo menor f_cost
        priority_queue<CubikState, vector<CubikState>, CompareState> open_list;

        // Conjunto para armazenar strings de estados já visitados e evitar ciclos
        set<string> visited;

        CubikState start_node = start;
        start_node.g_cost = 0; // Custo para chegar ao início é 0
        start_node.h_cost = heuristic_misplaced_stickers(start_node); // Calcula a heurística inicial
        start_node.moveHistory.clear(); // Começa com histórico limpo

        open_list.push(start_node);

        char moves[] = {'U', 'D', 'L', 'R', 'F', 'B'};

        while (!open_list.empty()) {
            // Pega o estado com o menor f_cost da fila
            CubikState current = open_list.top();
            open_list.pop();

            string currentStr = stateToString(current);

            // Se já visitamos esse estado, pulamos
            if (visited.count(currentStr)) {
                continue;
            }
            visited.insert(currentStr);

            // Se o estado atual é a solução, retornamos o caminho
            if (isStateSolved(current)) {
                return current.moveHistory;
            }

            // Gera os 6 vizinhos (próximos estados)
            for (char move : moves) {
                magicCubik2x2x2 tempCube;
                tempCube.setState(current);
                tempCube.applyMove(move);
                CubikState neighbor = tempCube.getCurrentState();
                
                // Se o vizinho ainda não foi visitado
                if (visited.find(stateToString(neighbor)) == visited.end()) {
                    neighbor.g_cost = current.g_cost + 1; // Custo para chegar é o do pai + 1
                    neighbor.h_cost = heuristic_misplaced_stickers(neighbor); // Calcula a heurística
                    neighbor.moveHistory = current.moveHistory;
                    neighbor.moveHistory.push_back(move);
                    
                    open_list.push(neighbor); // Adiciona na fila de prioridade
                }
            }
        }

        return {}; // Solução não encontrada
    }

private:
    
    int heuristic_misplaced_stickers(const CubikState& s) const {
        int misplaced_count = 0;

        const char target_colors[6] = {'W', 'Y', 'O', 'R', 'G', 'B'};
        
    
        const char (*faces[6])[2][2] = {&s.up, &s.down, &s.left, &s.right, &s.front, &s.back};

        for (int f = 0; f < 6; ++f) { // Itera sobre as 6 faces
            map<char, int> color_counts;
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    color_counts[(*faces[f])[i][j]]++;
                }
            }
           
            int max_same_color = 0;
            if(!color_counts.empty()){
                for(auto const& [key, val] : color_counts){
                    if(val > max_same_color){
                        max_same_color = val;
                    }
                }
            }
            misplaced_count += (4 - max_same_color);
        }
        
        
        return misplaced_count / 4;
    }


    bool dfs_recursive(const CubikState& current_state, set<string>& visited, vector<char>& path, int max_depth) {
        visited.insert(stateToString(current_state));

        if (isStateSolved(current_state)) {
            return true;
        }

        if (path.size() >= max_depth) {
            return false;
        }
        
        char moves[] = {'U', 'D', 'L', 'R', 'F', 'B'};
        
        for (char move : moves) {
            magicCubik2x2x2 tempCube;
            tempCube.setState(current_state);
            tempCube.applyMove(move);
            CubikState neighbor = tempCube.getCurrentState();
            
            if (visited.find(stateToString(neighbor)) == visited.end()) {
                path.push_back(move); 

                if (dfs_recursive(neighbor, visited, path, max_depth)) {
                    return true;
                }

                path.pop_back();
            }
        }
        
        return false;
    }
};

>>>>>>> Stashed changes
int main() {
    magicCubik2x2x2 cube;
<<<<<<< Updated upstream
    cout << "\n\t MAGIC CUBIK " << endl;
    cube.printCubik();

    char m;
    while (true) {
        cout << "Digite um movimento (U, D, L, R, F, B) ou 'Q' para sair: ";
=======
    algorithms solver;

    char m;
    while (true) {
        cout << "\n\t MAGIC CUBIK 2x2x2" << endl;
        cube.printCubik();
        
        cout << "INSTRUÇÃO : ";
>>>>>>> Stashed changes
        cin >> m;
        m = toupper(m);

        if(m =='U' || m =='D' || m == 'L' || m == 'R' || m == 'F' || m == 'B') {
<<<<<<< Updated upstream
            
            cube.performAndRecordMove(m);

            cube.printCubik();
        } else if (m == 'Q' || m == 'q') {
            break;
        }
        else
        {
=======
            clearScreen();
            cube.performAndRecordMove(m);
            cube.checkStateAndPrintSolution();

        } else if (m == 'Q') {
            break;
        }
        else if (m == 'S') {
            clearScreen();
            cube.shuffleCubik();
        }
        else if (m == 'C') {
            clearScreen();
            cube.reset();
        }
         else if (m == 'Z') {
             clearScreen();
             const int max_depth = 20; // Define o limite de profundidade
             cout << "Procurando a solução via DFS (limite de " << max_depth << " movimentos)..." << endl;
             CubikState startState = cube.getCurrentState();
             
             vector<char> solution = solver.dfs(startState, max_depth);
             
             if (solution.empty()) {
                 if (cube.isSolved()) {
                     cout << "O cubo já está resolvido!" << endl;
                 } else {
                     cout << "Nenhuma solução encontrada com o limite de profundidade." << endl;
                 }
             } else {
                 cout << "Solução encontrada em " << solution.size() << " movimentos!" << endl;
                 cout << "Sequência: ";
                 for(char move : solution) {
                     cout << move << " ";
                 }
                 cout << endl << "Aplicando solução..." << endl;
                 for(char move : solution) {
                     cube.applyMove(move);
                 }
             }
        }
         else if (m == 'X') {
             clearScreen();
             cout << "Procurando a solução via BFS..." << endl;
             CubikState startState = cube.getCurrentState();
             
             vector<char> solution = solver.bfs(startState);
             
             if (solution.empty()) {
                 if (cube.isSolved()) {
                     cout << "O cubo já está resolvido!" << endl;
                 } else {
                     cout << "Nenhuma solução encontrada." << endl;
                 }
             } else {
                 cout << "Solução encontrada em " << solution.size() << " movimentos!" << endl;
                 cout << "Sequência ótima: ";
                 for(char move : solution) {
                     cout << move << " ";
                 }
                 cout << endl << "Aplicando solução..." << endl;
                 for(char move : solution) {
                     cube.applyMove(move);
                 }
             }
         }
       
        else if (m == 'A') {
             clearScreen();
             cout << "Procurando a solução via A*..." << endl;
             CubikState startState = cube.getCurrentState();
             
             vector<char> solution = solver.a_star(startState);
             
             if (solution.empty()) {
                 if (cube.isSolved()) {
                     cout << "O cubo já está resolvido!" << endl;
                 } else {
                     cout << "Nenhuma solução encontrada." << endl;
                 }
             } else {
                 cout << "Solução ótima encontrada em " << solution.size() << " movimentos!" << endl;
                 cout << "Sequência: ";
                 for(char move : solution) {
                     cout << move << " ";
                 }
                 cout << endl << "Aplicando solução..." << endl;
                 for(char move : solution) {
                     cube.applyMove(move);
                 }
             }
        }
        else {
            clearScreen();
>>>>>>> Stashed changes
            cout << "Movimento inválido. Tente novamente." << endl;
        }
    }
    return 0;
}