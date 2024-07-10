#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>
#include <windows.h>

using namespace std;

const int rows = 10, columns = 31;
int posX = 5, posY = 8, enemyPosX = 25, enemyPosY = 2, enemy2PosX = 25, enemy2PosY = 5, enemy3PosX = 25, enemy3PosY = 8;
string level[rows] = {
    "******************************",
    "*                            *",
    "*                            *",
    "*====    ====================*",
    "*                            *",
    "*                            *",
    "*====================   =====*",
    "*                            *",
    "*                            *",
    "******************************",
};
clock_t lastSetTime = clock();
const double enemyProjectileInterval = CLOCKS_PER_SEC * 3.0, projectileInterval = CLOCKS_PER_SEC * 0.5;
bool enemyProjectileFired = false;
int lives = 6;
int score = 0;
bool gameWon = false;

void printLevel() {
    system("cls");
    for (int i = 0; i < rows; ++i)
        cout << level[i] << endl;
}

void updateScore() {
    score += 10; // Incrementa la puntuación por cada iteración del bucle principal
}

int main() {
    char key;
    while (lives > 0 && !gameWon) {
        printLevel();

        if (clock() - lastSetTime > enemyProjectileInterval) {
            int projectileY = enemyPosY, projectileX = enemyPosX - 1;
            level[projectileY][projectileX] = '<';
            int projectileY2 = enemy2PosY, projectileX2 = enemy2PosX - 1;
            level[projectileY2][projectileX2] = '<';
            int projectileY3 = enemy3PosY, projectileX3 = enemy3PosX - 1;
            level[projectileY3][projectileX3] = '<';
            lastSetTime = clock();
            enemyProjectileFired = true;
        }

        // Verifica si el jugador es golpeado por una bola y reduce una vida si es así
        if (level[posY][posX - 1] == '<' || level[posY][posX - 2] == '<' || level[posY][posX - 3] == '<') {
            lives--;
            level[posY][posX] = ' '; // Remueve al jugador del camino de la bola
        }

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < columns; ++x) {
                if (level[y][x] == '<') {
                    if (x > 0) {
                        level[y][x] = ' ';
                        if (x == 1) {
                            for (int i = 1; i <= 3; ++i) {
                                if (y + i < rows) {
                                    if (level[y + i][x] != '=')
                                        level[y + i][x] = '6';
                                    else {
                                        level[y][x] = ' ';
                                        enemyProjectileFired = false;
                                        break;
                                    }
                                } else {
                                    level[y][x] = ' ';
                                    enemyProjectileFired = false;
                                    break;
                                }
                            }
                        } else {
                            x--;
                            level[y][x] = '<';
                        }
                    }
                }
            }
        }

        level[posY][posX] = 'H';
        level[enemyPosY][enemyPosX] = 'M';
        level[enemy2PosY][enemy2PosX] = ' ';
        level[enemy3PosY][enemy3PosX] = ' ';

        // Nuevo personaje "Ganaste" en la esquina superior derecha
        level[1][columns - 2] = 'W';

        cout << "Lives: " << lives << endl;
        cout << "Score: " << score << endl;

        // Actualiza la puntuación
        updateScore();

        // Verifica si el jugador toca al nuevo personaje
        if (posX == enemyPosX && posY == enemyPosY) {
            gameWon = true;
            break;
        }

        // Verifica si el jugador se coloca encima del nuevo personaje
        if (level[posY - 1][posX] == 'M') {
            gameWon = true;
            break;
        }

        if (_kbhit()) {
            key = _getch();
            if (key == 'w' && posY > 0 && level[posY - 1][posX] != '=')
                level[posY--][posX] = ' ';
            else if (key == 's' && posY < rows - 1 && level[posY + 1][posX] != '=')
                level[posY++][posX] = ' ';
            else if (key == 'a' && posX > 0 && level[posY][posX - 1] != '|' && level[posY][posX - 1] != '=')
                level[posY][posX--] = ' ';
            else if (key == 'd' && posX < columns - 1 && level[posY][posX + 1] != '|' && level[posY][posX + 1] != '=')
                level[posY][posX++] = ' ';
        }
        Sleep(50);
    }

    if (gameWon) {
        cout << "Congratulations! You won the game!" << endl;
        cout << "Final Score: " << score << endl;
    } else {
        cout << "Game over! You lost all your lives." << endl;
        cout << "Final Score: " << score << endl;
    }

    return 0;

    }
