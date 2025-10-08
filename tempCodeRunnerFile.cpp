    string inner(char &s) const {
        char c = s;
        switch (c) {
            case 'W': return string("\033[107m  \033[0m");
            case 'Y': return string("\033[103m  \033[0m");
            case 'O': return string("\033[48;5;202m  \033[0m");
            case 'R': return string("\033[48;5;196m  \033[0m");
            case 'G': return string("\033[102m  \033[0m");
            case 'B': return string("\033[104m  \033[0m");
            default: return string("  ");

        }
    }