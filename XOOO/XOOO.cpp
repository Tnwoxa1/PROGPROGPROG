#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class NeuralNetwork {
private:
    vector<vector<double>> weightsInputHidden;
    vector<vector<double>> weightsHiddenOutput;
    vector<double> hiddenLayer;
    vector<double> outputLayer;
    double learningRate;
    vector<pair<vector<int>, vector<int>>> trainingDataX;
    vector<pair<vector<int>, vector<int>>> trainingDataO;

    vector<int> rotate90(const vector<int>& board) {
        vector<int> rotated(9);
        rotated[0] = board[6]; rotated[1] = board[3]; rotated[2] = board[0];
        rotated[3] = board[7]; rotated[4] = board[4]; rotated[5] = board[1];
        rotated[6] = board[8]; rotated[7] = board[5]; rotated[8] = board[2];
        return rotated;
    }

    vector<int> reflectHorizontal(const vector<int>& board) {
        vector<int> reflected(9);
        reflected[0] = board[6]; reflected[1] = board[7]; reflected[2] = board[8];
        reflected[3] = board[3]; reflected[4] = board[4]; reflected[5] = board[5];
        reflected[6] = board[0]; reflected[7] = board[1]; reflected[8] = board[2];
        return reflected;
    }

    void augmentData(vector<pair<vector<int>, vector<int>>>& data) {
        vector<pair<vector<int>, vector<int>>> augmented;
        for (const auto& [board, target] : data) {
            augmented.push_back({ board, target });
            vector<int> board90 = rotate90(board);
            vector<int> target90 = rotate90(target);
            augmented.push_back({ board90, target90 });
            vector<int> board180 = rotate90(board90);
            vector<int> target180 = rotate90(target90);
            augmented.push_back({ board180, target180 });
            vector<int> board270 = rotate90(board180);
            vector<int> target270 = rotate90(target180);
            augmented.push_back({ board270, target270 });
            vector<int> boardH = reflectHorizontal(board);
            vector<int> targetH = reflectHorizontal(target);
            augmented.push_back({ boardH, targetH });
            vector<int> boardH90 = rotate90(boardH);
            vector<int> targetH90 = rotate90(targetH);
            augmented.push_back({ boardH90, targetH90 });
            vector<int> boardH180 = rotate90(boardH90);
            vector<int> targetH180 = rotate90(targetH90);
            augmented.push_back({ boardH180, targetH180 });
            vector<int> boardH270 = rotate90(boardH180);
            vector<int> targetH270 = rotate90(targetH180);
            augmented.push_back({ boardH270, targetH270 });
        }
        data = augmented;
    }

public:
    NeuralNetwork() {
        learningRate = 0.05;
        weightsInputHidden.resize(9, vector<double>(27));
        weightsHiddenOutput.resize(27, vector<double>(9));
        hiddenLayer.resize(27);
        outputLayer.resize(9);

        srand(time(0));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 27; j++) {
                weightsInputHidden[i][j] = (rand() % 1000) / 1000.0 - 0.5;
            }
        }
        for (int j = 0; j < 27; j++) {
            for (int k = 0; k < 9; k++) {
                weightsHiddenOutput[j][k] = (rand() % 1000) / 1000.0 - 0.5;
            }
        }

        int X_train[27][9] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, -1, 0, 0, 0, 0},
            {1, 0, 0, 0, -1, 0, -1, 0, 1},
            {1, -1, 1, 0, -1, 0, -1, 0, 1},
            {1, 0, 0, -1, -1, 0, 0, 0, 1},
            {1, 0, 0, -1, -1, 1, -1, 0, 1},
            {1, 0, -1, -1, -1, 1, 0, 0, 1},
            {1, 0, -1, -1, -1, 1, 1, -1, 1},
            {1, -1, -1, -1, -1, 1, 1, 0, 1},
            {1, 0, -1, 0, 0, 0, 0, 0, 0},
            {1, -1, -1, 0, 0, 0, 1, 0, 0},
            {1, 0, -1, -1, 0, 0, 1, 0, 0},
            {1, 0, -1, -1, 0, 0, 1, -1, 1},
            {-1, 0, 0, 0, 1, 0, 0, 0, 0},
            {-1, 0, 1, 0, 1, 0, -1, 0, 0},
            {-1, 0, 1, 1, 1, 0, -1, -1, 0},
            {-1, 0, 1, -1, 1, 0, 0, 0, 0},
            {-1, 0, 1, 1, 1, -1, -1, 0, 0},
            {-1, 1, 1, 1, 1, -1, -1, -1, 0},
            {-1, 1, 1, 1, 1, -1, -1, 0, -1},
            {1, -1, 0, 0, 0, 0, 0, 0, 0},
            {0, -1, 0, 0, 1, 0, 0, 0, 0},
            {-1, -1, 0, 0, 1, 0, 1, 0, 0},
            {0, -1, -1, 0, 1, 0, 1, 0, 0},
            {1, -1, -1, 0, 1, 0, 1, 0, -1},
            {0, 0, 0, 1, 1, -1, 0, 0, -1}
        };
        int y_train_X[27][9] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0}
        };
        int y_train_O[27][9] = {
            {0, 0, 0, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0}
        };

        for (int i = 0; i < 27; i++) {
            trainingDataX.push_back({ vector<int>(X_train[i], X_train[i] + 9), vector<int>(y_train_X[i], y_train_X[i] + 9) });
            trainingDataO.push_back({ vector<int>(X_train[i], X_train[i] + 9), vector<int>(y_train_O[i], y_train_O[i] + 9) });
        }

        augmentData(trainingDataX);
        augmentData(trainingDataO);
       // cout << "Размер обучающей выборки после аугментации: " << trainingDataX.size() << " (X), " << trainingDataO.size() << " (O)" << endl;
    }

    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    double sigmoidDerivative(double x) {
        return x * (1.0 - x);
    }

    vector<double> forward(const vector<int>& board) {
        for (int j = 0; j < 27; j++) {
            double sum = 0.0;
            for (int i = 0; i < 9; i++) {
                sum += board[i] * weightsInputHidden[i][j];
            }
            hiddenLayer[j] = sigmoid(sum);
        }
        vector<double> output(9, 0.0);
        for (int k = 0; k < 9; k++) {
            double sum = 0.0;
            for (int j = 0; j < 27; j++) {
                sum += hiddenLayer[j] * weightsHiddenOutput[j][k];
            }
            output[k] = sigmoid(sum);
        }
        return output;
    }

    void train(const vector<int>& board, const vector<int>& target) {
        vector<double> output = forward(board);
        vector<double> outputErrors(9);
        vector<double> outputDeltas(9);
        for (int k = 0; k < 9; k++) 
        {
            outputErrors[k] = target[k] - output[k];
            outputDeltas[k] = outputErrors[k] * sigmoidDerivative(output[k]);
        }

        vector<double> hiddenErrors(27, 0.0);
        for (int j = 0; j < 27; j++) 
        {
            for (int k = 0; k < 9; k++) 
            {
                hiddenErrors[j] += outputDeltas[k] * weightsHiddenOutput[j][k];
            }
            hiddenErrors[j] *= sigmoidDerivative(hiddenLayer[j]);
        }

        for (int j = 0; j < 27; j++) 
        {
            for (int k = 0; k < 9; k++) 
            {
                weightsHiddenOutput[j][k] += learningRate * outputDeltas[k] * hiddenLayer[j];
            }
        }

        for (int i = 0; i < 9; i++) 
        {
            for (int j = 0; j < 27; j++) 
            {
                weightsInputHidden[i][j] += learningRate * hiddenErrors[j] * board[i];
            }
        }
    }

    double trainWithData(bool isX) 
    {
        auto& data = isX ? trainingDataX : trainingDataO;
        double totalError = 0.0;
        for (const auto& [board, target] : data) {
            vector<double> predicted = forward(board);
            double error = 0.0;
            for (int k = 0; k < 9; k++) {
                error += (target[k] - predicted[k]) * (target[k] - predicted[k]);
            }
            totalError += error;
            train(board, target);
        }
        double avgError = totalError / data.size();
        cout << "Среднеквадратичная ошибка (" << (isX ? "X" : "O") << "): " << avgError << endl;
        return avgError;
    }

    void preTrain(bool isX) {
        const double targetError = 0.0009;
        int epoch = 0;
        double error;
        cout << "Предварительное обучение начато...\n";
        do {
            error = trainWithData(isX);
            epoch++;
            if (epoch % 500 == 0) {
                cout << "Эпоха " << epoch << ", ошибка: " << error << endl;
            }
        } while (error > targetError && epoch < 5000);
        cout << "Обучение завершено на эпохе " << epoch << " с ошибкой " << error << endl;
    }

    void adaptTrain(const vector<int>& board, int movePos, bool isX) {
        vector<int> target(9, 0);
        target[movePos] = 1;
        train(board, target);
        auto& data = isX ? trainingDataX : trainingDataO;
        data.push_back({ board, target });
    }
};

class TicTacToe {
private:
    vector<int> board;
    NeuralNetwork& nn;
    bool computerIsX;
    bool playerFirst;

    int checkPotentialWin(int player) {
        int lines[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (int i = 0; i < 8; i++) {
            int sum = board[lines[i][0]] + board[lines[i][1]] + board[lines[i][2]];
            if (sum == 2 * player) {
                for (int j = 0; j < 3; j++) {
                    if (board[lines[i][j]] == 0) return lines[i][j];
                }
            }
        }
        return -1;
    }

public:
    TicTacToe(NeuralNetwork& network) : board(9, 0), nn(network) {
        char choice;
        cout << "Кто ходит первым? (P - игрок, C - компьютер): ";
        cin >> choice;
        playerFirst = (choice == 'P' || choice == 'p');
        cout << "Компьютер играет за X (1) или O (-1)? (введите 1 или -1): ";
        int symbol;
        cin >> symbol;
        computerIsX = (symbol == 1);
    }

    void printBoard() {
        for (int i = 0; i < 9; i++) {
            if (board[i] == 1) cout << "X ";
            else if (board[i] == -1) cout << "O ";
            else cout << ". ";
            if ((i + 1) % 3 == 0) cout << endl;
        }
        cout << endl;
    }

    bool isFull() {
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) return false;
        }
        return true;
    }

    int checkWin() {
        int lines[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };
        for (int i = 0; i < 8; i++) {
            int sum = board[lines[i][0]] + board[lines[i][1]] + board[lines[i][2]];
            if (sum == 3) return 1;
            if (sum == -3) return -1;
        }
        return 0;
    }

    void playerMove() {
        int pos;
        do {
            cout << "Ваш ход (0-8): ";
            cin >> pos;
        } while (pos < 0 && pos > 8 && board[pos] != 0);
        board[pos] = computerIsX ? -1 : 1;
    }

    void computerMove() {
        vector<int> available;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) available.push_back(i);
        }
        if (available.empty()) return;

        int computerSymbol = computerIsX ? 1 : -1;
        int playerSymbol = computerIsX ? -1 : 1;

        int winMove = checkPotentialWin(computerSymbol);
        if (winMove != -1) {
            board[winMove] = computerSymbol;
            nn.adaptTrain(board, winMove, computerIsX);
            return;
        }

        int blockMove = checkPotentialWin(playerSymbol);
        if (blockMove != -1) {
            board[blockMove] = computerSymbol;
            nn.adaptTrain(board, blockMove, computerIsX);
            return;
        }

        vector<double> scores = nn.forward(board);
        int bestMove = -1;
        double bestScore = -1.0;
        for (int pos : available) {
            if (scores[pos] > bestScore) {
                bestScore = scores[pos];
                bestMove = pos;
            }
        }
        board[bestMove] = computerSymbol;
        nn.adaptTrain(board, bestMove, computerIsX);
    }

    void play(bool isFirstGame) {
        cout << "Игра начинается!\n";
        cout << "Компьютер играет за " << (computerIsX ? "X" : "O") << endl;

        if (isFirstGame) {
            nn.preTrain(computerIsX);
        }

        bool playerTurn = playerFirst;
        while (true) {
            printBoard();

            if (playerTurn) {
                playerMove();
            }
            else {
                computerMove();
            }

            int result = checkWin();
            if (result == 1) {
                printBoard();
                cout << (computerIsX ? "Компьютер (X) победил!\n" : "Вы (X) победили!\n");
                break;
            }
            if (result == -1) {
                printBoard();
                cout << (computerIsX ? "Вы (O) победили!\n" : "Компьютер (O) победил!\n");
                break;
            }
            if (isFull()) {
                printBoard();
                cout << "Ничья!\n";
                break;
            }

            playerTurn = !playerTurn;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    NeuralNetwork nn;
    bool firstGame = true;
    char playAgain;

    do {
        TicTacToe game(nn);
        game.play(firstGame);
        firstGame = false;
        cout << "Хотите сыграть ещё раз? (Y/N): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
    cout << "Спасибо за игру!\n";
    return 0;
}