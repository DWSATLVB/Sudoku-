#include "sudokuapp.h"
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <algorithm>
#include <random>    
SudokuApp::SudokuApp(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Try out this Problem", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QGridLayout *gridLayout = new QGridLayout();
    layout->addLayout(gridLayout);

    solutionGrid = generateFullSudoku();
    auto [puzzle, indices] = removeCells(solutionGrid);
    puzzleGrid = puzzle;
    emptyIndices = indices;

    entries.clear();

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int val = puzzleGrid[row][col];
            if (val != 0) {
                QLabel *label = new QLabel(QString::number(val), this);
                label->setAlignment(Qt::AlignCenter);
                label->setFrameStyle(QFrame::Box | QFrame::Plain);
                label->setLineWidth(1);
                label->setFixedSize(40, 40);
                gridLayout->addWidget(label, row, col);
            } else {
                QLineEdit *lineEdit = new QLineEdit(this);
                lineEdit->setMaxLength(1);
                lineEdit->setAlignment(Qt::AlignCenter);
                lineEdit->setFixedSize(40, 40);
                gridLayout->addWidget(lineEdit, row, col);
                entries.append(lineEdit);
            }
        }
    }

    QPushButton *checkButton = new QPushButton("Check", this);
    connect(checkButton, &QPushButton::clicked, this, &SudokuApp::onCheckClicked);
    layout->addWidget(checkButton);
}

void SudokuApp::onCheckClicked() {
    if (validateUserInput()) {
        showResult(true);
    } else {
        showResult(false);
    }
}

bool SudokuApp::validateUserInput() {
    int idx = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (std::find(emptyIndices.begin(), emptyIndices.end(), row * 9 + col) != emptyIndices.end()) {
                bool ok;
                QString text = entries[idx++]->text();
                int value = text.toInt(&ok);
                if (!ok || value != solutionGrid[row][col]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void SudokuApp::showResult(bool isValid) {
    QDialog *resultDialog = new QDialog(this);
    resultDialog->setWindowTitle("Results");
    resultDialog->resize(350, 200);

    QVBoxLayout *vbox = new QVBoxLayout(resultDialog);

    QLabel *label = new QLabel(isValid ? "The Grid is Valid, SKILL ISSUE!" : "The Grid is Invalid. SKILL ISSUE!", resultDialog);
    label->setStyleSheet(isValid ? "color: green;" : "color: red;");
    label->setAlignment(Qt::AlignCenter);
    vbox->addWidget(label);

    QHBoxLayout *hbox = new QHBoxLayout();

    QPushButton *playAgain = new QPushButton("Play Again", resultDialog);
    connect(playAgain, &QPushButton::clicked, this, [this, resultDialog]() {
        resultDialog->close();
        this->close();
        SudokuApp *app = new SudokuApp();
        app->show();
        this->deleteLater(); // Schedule deletion of the current window
    });
    hbox->addWidget(playAgain);

    QPushButton *exitBtn = new QPushButton("Exit", resultDialog);
    connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);
    hbox->addWidget(exitBtn);

    vbox->addLayout(hbox);
    resultDialog->exec();
}

// Generate a full Sudoku grid
Grid SudokuApp::generateFullSudoku() {
    Grid grid(9, QVector<int>(9, 0));
    return grid; 
}

std::pair<Grid, QVector<int>> SudokuApp::removeCells(const Grid& fullGrid) {
    Grid puzzle = fullGrid;
    QVector<int> emptyIndices;

    std::vector<int> indices(81);
    std::iota(indices.begin(), indices.end(), 0); 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    int cellsToRemove = 40;
    for (int i = 0; i < cellsToRemove; ++i) {
        int idx = indices[i];
        int row = idx / 9;
        int col = idx % 9;
        puzzle[row][col] = 0;
        emptyIndices.append(idx);
    }

    return {puzzle, emptyIndices};
}
