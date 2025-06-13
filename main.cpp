#include <QApplication>
#include "sudokuapp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Start window
    QWidget startWindow;
    startWindow.setWindowTitle("Sudoku");
    startWindow.resize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(&startWindow);

    QLabel *titleLabel = new QLabel("SUDOKU", &startWindow);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Calibri", 30));
    layout->addWidget(titleLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *playButton = new QPushButton("Play", &startWindow);
    playButton->setFont(QFont("Calibri", 18));
    playButton->setFixedWidth(120);
    playButton->setStyleSheet("background-color: green;");
    connect(playButton, &QPushButton::clicked, &startWindow, [&startWindow]() {
        startWindow.hide();
        SudokuApp *game = new SudokuApp();
        game->show();
        startWindow.deleteLater();
    });

    QPushButton *exitButton = new QPushButton("Exit", &startWindow);
    exitButton->setFont(QFont("Calibri", 18));
    exitButton->setFixedWidth(120);
    exitButton->setStyleSheet("background-color: red;");
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

    buttonLayout->addStretch();
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addStretch();

    layout->addSpacing(50);
    layout->addLayout(buttonLayout);
    layout->addStretch();

    startWindow.show();

    return app.exec();
}
