//prevent overtaking, swapping from x and o, chosing a mark and swapping, win lose draw


#include <iostream>
#include <string>

using namespace std;

bool checkWin(const string cells[], const string mark) {
    for (int i = 0; i < 9; i += 3) {
        if (cells[i] == mark && cells[i + 1] == mark && cells[i + 2] == mark) {
            return true;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (cells[i] == mark && cells[i + 3] == mark && cells[i + 6] == mark) {
            return true;
        }
    }

    if ((cells[0] == mark && cells[4] == mark && cells[8] == mark) ||
        (cells[2] == mark && cells[4] == mark && cells[6] == mark)) {
        return true;
    }

    return false;
}

bool checkTie(const string cells[]) {
    for (int i = 0; i < 9; i++) {
        if (cells[i] != "X" && cells[i] != "O") {
            return false;
        }
    }
    return true;
}

int main() {
    string cells[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string horizontal = "---+---+---";
    char vert = '|';
    char space = ' ';
    string cell_choice;
    bool game_over = false;
    bool settings = false;
    string mark_player1 = "X";
    string mark_player2 = "O",
    string current_mark;
    int tictactoe_choice;

    do {
        cout << "Would you like to play \n 1)normal tic-tac-toe \n 2)BATTLE TIC-TAC-TOE?";
        cin >> tictactoe_choice;

        settings = true;
    } while (!settings);

    while (!game_over) {
        for (int i = 0; i < 7; i = i + 3) {
            cout << space << cells[i] << space << vert << space << cells[i + 1] << space << vert << space << cells[i + 2] << endl;
            if (i == 6) {
                break;
            }
            cout << horizontal << endl;
        }

        bool invalid = true;
        while (invalid) {
            cout << "What is your move? ";
            getline(cin, cell_choice);

            if (cell_choice == "exit") {
                game_over = true;
                break;
            } else if (cell_choice.length() != 1 || !isdigit(cell_choice[0])) {
                cout << "Invalid input. Please enter a single digit from 1 to 9." << endl;
            } else {
                int choice = stoi(cell_choice);
                if (choice > 9 || choice < 1) {
                    cout << "That is not a valid cell." << endl;
                } else if (cells[choice - 1] == mark_player1 || cells[choice - 1] == mark_player2) {
                    cout << "That cell is already taken." << endl;
                } else {
                    cells[choice - 1] = current_mark;
                    invalid = false;
                    if (checkWin(cells, current_mark)) {
                        for (int i = 0; i < 7; i = i + 3) {
                            cout << space << cells[i] << space << vert << space << cells[i + 1] << space << vert << space << cells[i + 2] << endl;
                            if (i == 6) {
                                break;
                            }
                            cout << horizontal << endl;
                        }
                        cout << "Player " << (current_mark == mark_player1 ? "1" : "2") << " wins!" << endl;
                        game_over = true;
                    } else if (checkTie(cells)) {
                        for (int i = 0; i < 7; i = i + 3) {
                            cout << space << cells[i] << space << vert << space << cells[i + 1] << space << vert << space << cells[i + 2] << endl;
                            if (i == 6) {
                                break;
                            }
                            cout << horizontal << endl;
                        }
                        cout << "It's a tie!" << endl;
                        game_over = true;
                    } else {
                        current_mark = (current_mark == mark_player1) ? mark_player2 : mark_player1; 
                    }
                }
            }
        }
    }

    cout << "Game Over!" << endl;
    return 0;
}