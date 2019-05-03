#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    // clear the screen
    currentFile.clear();

    // create a new text window
    ui->textEdit->setText(QString());

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    // if correct file does not open
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        // warn user something went wrong
        QMessageBox::warning(this, "Warning", "Can NOT open file: " + file.errorString());
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    // open window to save a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
    // create object to hold the file
    QFile file(fileName);

    // open the file, notify user if there is a problem
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        // warn user something went wrong
        QMessageBox::warning(this, "Warning", "Can NOT save file: " + file.errorString());
    }

    // store current file
    currentFile = fileName;
    // set window title to name of file
    setWindowTitle(fileName);

    // when writing to out we are actually writing to file on line 68 below
    QTextStream out(&file);

    // copy text in textEdit widget convert to plain text
    QString text = ui->textEdit->toPlainText();

    // write to file then close file
    out << text;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
