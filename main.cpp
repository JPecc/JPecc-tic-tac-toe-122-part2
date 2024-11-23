#include <iostream>
#include <string>

using namespace std;

bool checkWinNormal(const string cells[], const string mark) {
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

bool checkWinBattle(const string cells[], const string mark) {
    // Only Player 1 can use this
    if (mark == "X" && checkWinNormal(cells, mark)) {
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

void displayBoard(const string cells[]) {
    string horizontal = "---+---+---";
    char vert = '|';
    char space = ' ';

    for (int i = 0; i < 7; i += 3) {
        cout << space << cells[i] << space << vert << space << cells[i + 1] << space << vert << space << cells[i + 2] << endl;
        if (i < 6) {
            cout << horizontal << endl;
        }
    }
}

void resetGame(string cells[], string &current_mark, bool &game_over) {
    for (int i = 0; i < 9; i++) {
        cells[i] = to_string(i + 1);
    }
    current_mark = "X";
    game_over = false;
    cout << "The game has been restarted!" << endl;
}

int main() {
    string cells[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string mark_player1 = "X";
    string mark_player2 = "O";
    string current_mark = mark_player1;
    bool game_over = false;
    bool battle_mode = false;

    cout << "Welcome To The TIC-TAC-TOE simulator\n" << endl;

    cout << "Choose a game mode:\n";
    cout << "1) Regular Tic-Tac-Toe\n";
    cout << "2) Battle Tic-Tac-Toe\n";
    cout << "Enter your choice (1 or 2): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 2) {
        battle_mode = true;
        cout << "Battle Tic-Tac-Toe mode selected! Press 'r' during your turn to restart the game.\n";
    } else {
        cout << "Normal Tic-Tac-Toe mode selected!\n";
    }

    while (!game_over) {
        displayBoard(cells);

        string cell_choice;
        bool invalid = true;

        while (invalid) {
            cout << "Player " << (current_mark == mark_player1 ? "1" : "2") << " (" << current_mark << "), make your move (1-9): ";
            getline(cin, cell_choice);

            if (cell_choice == "exit") {
                game_over = true;
                break;
            } else if (battle_mode && cell_choice == "r" && current_mark == mark_player2) {
                resetGame(cells, current_mark, game_over);
                current_mark = mark_player1;  // After reset, Player 1's turn
                invalid = false;
            } else if (battle_mode && current_mark == mark_player1 && cell_choice == "r") {
                cout << "Player 1 cannot reset the game!" << endl;
                invalid = false;
            } else if (cell_choice.length() != 1 || !isdigit(cell_choice[0])) {
                cout << "Invalid input. Please enter a single digit from 1 to 9." << endl;
            } else {
                int cell = stoi(cell_choice) - 1;
                if (cell < 0 || cell > 8) {
                    cout << "That is not a valid cell." << endl;
                } else if (cells[cell] == mark_player1 || cells[cell] == mark_player2) {
                    cout << "That cell is already taken." << endl;
                } else {
                    cells[cell] = current_mark;
                    invalid = false;

                    bool player_wins = battle_mode && current_mark == mark_player1 ? checkWinBattle(cells, current_mark) : checkWinNormal(cells, current_mark);
                    if (player_wins) {
                        displayBoard(cells);
                        cout << "Player " << (current_mark == mark_player1 ? "1" : "2") << " wins!" << endl;
                        game_over = true;
                    } else if (checkTie(cells)) {
                        displayBoard(cells);
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
