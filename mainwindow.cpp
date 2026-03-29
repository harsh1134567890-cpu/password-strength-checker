#include<cctype>
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    QString password = ui->passwordInput->text();
    std::string pass = password.toStdString();

    int n = pass.length();

    // Check length
    if (n < 8) {
        ui->resultLabel->setText("Password is very short");
        return;
    }

    // Flags
    bool up = false, num = false, lower = false, spec = false;

    // Loop through characters
    for (int i = 0; i < n; i++) {
        if (isupper(pass[i])) up = true;
        else if (isdigit(pass[i])) num = true;
        else if (islower(pass[i])) lower = true;
        else spec = true;
    }

    // Score calculation
    int score = 0;
    if (up) score++;
    if (num) score++;
    if (lower) score++;
    if (spec) score++;

    // Crack time calculation
    float crack = score;
    float cc = (crack / 9.0) * n;
    float time = cc / 100.0;
    float min = time * 100;

    // Result
    QString result;

    if (score <= 1) result = "Weak";
    else if (score == 2) result = "Medium";
    else result = "Strong";

    // Final output
    QString finalText = result + "\nTime to crack: " + QString::number(min) + " minutes";

    ui->resultLabel->setText(finalText);
}
