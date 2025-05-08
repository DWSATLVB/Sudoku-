#ifndef SUDOKUAPP_H
#define SUDOKUAPP_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>

class SudokuApp : public QMainWindow {
    Q_OBJECT

public:
    explicit SudokuApp(QWidget *parent = nullptr);

private slots:
    void onCheckClicked();
    void onPlayAgain();

private:
    QVector<QLineEdit*> entries;
    QVector<int> emptyIndices;
    Grid puzzleGrid;
    Grid solutionGrid;

    bool validateUserInput();
    void showResult(bool isValid);
};

#endif // SUDOKUAPP_H