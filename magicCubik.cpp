#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define fastio ios_base::sync_with_stdio(false);
#define fo(i,n) for(i=0;i<n;i++)
#define si(x)	cin >> x
#define pi(x)   cout << x
#define pl(x)   cout << x << "\n"

void U (string up[2][2], string right[2][2], string left[2][2], string front[2][2], string back[2][2]) {
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
void D (string down[2][2], string right[2][2], string left[2][2], string front[2][2], string back[2][2]) {
    string temp[2][2];
    temp[0][0] = front[0][0];
    temp[0][1] = front[0][1];
    temp[1][0] = front[1][0];
    temp[1][1] = front[1][1];

    front[1][0] = right[0][0];
    front[1][1] = right[0][1];

    right[1][0] = back[0][0];
    right[1][1] = back[0][1];

    back[1][0] = left[0][0];
    back[1][1] = left[0][1];

    left[1][0] = temp[0][0];
    left[1][1] = temp[0][1];

    string tempDown = down[0][0];
    down[0][0] = down[0][1];
    down[0][1] = down[1][1];
    down[1][1] = down[1][0];
    down[1][0] = tempDown;
}

void R (string up[2][2], string down[2][2], string right[2][2], string front[2][2], string back[2][2]) {
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

void L (string up[2][2], string down[2][2], string left[2][2], string front[2][2], string back[2][2]) {
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

void F (string up[2][2], string down[2][2], string left[2][2], string right[2][2], string front[2][2]) {
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

void B (string up[2][2], string down[2][2], string left[2][2], string right[2][2], string back[2][2]) {
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


int main() {
    string up[2][2] = {
        {"a1", "a2"},
        {"a3", "a4"}
    };
    string down[2][2] = {
        {"b1", "b2"},
        {"b3", "b4"}
    };
    string left[2][2] = {
        {"c1", "c2"},
        {"c3", "c4"}
    };
    string right[2][2] = {
        {"d1", "d2"},
        {"d3", "d4"}
    };
    string front[2][2] = {
        {"e1", "e2"},
        {"e3", "e4"}
    };
    string back[2][2] = {
        {"f1", "f2"},
        {"f3", "f4"}
    };


    return 0;
}