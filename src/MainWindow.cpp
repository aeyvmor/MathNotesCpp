#include "MainWindow.h"
#include "CanvasWidget.h"
#include "GeminiClient.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QCoreApplication>

MainWindow::MainWindow(int fontId, QWidget *parent)
    : QMainWindow(parent)
{
    QString apiKey = "AIzaSyAdDUqeSnWvKO4d96T124iKxRULTKtXtmc";

    m_geminiClient = new GeminiClient(apiKey, this);
    setupUI(fontId);

    connect(m_clearButton, &QPushButton::clicked, m_canvasWidget, &CanvasWidget::clearCanvas);
    connect(m_undoButton, &QPushButton::clicked, m_canvasWidget, &CanvasWidget::undo);
    connect(m_calculateButton, &QPushButton::clicked, this, &MainWindow::calculate);
    
    connect(m_geminiClient, &GeminiClient::solutionReceived, this, &MainWindow::onSolutionReceived);
    connect(m_geminiClient, &GeminiClient::errorOccurred, this, &MainWindow::onErrorOccurred);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI(int fontId)
{
    m_canvasWidget = new CanvasWidget(fontId, this);

    m_clearButton = new QPushButton("Clear", this);
    m_undoButton = new QPushButton("Undo", this);
    m_calculateButton = new QPushButton("Calculate", this);
    
    m_calculateButton->setShortcut(QKeySequence(Qt::Key_Return));
    m_undoButton->setShortcut(QKeySequence::Undo);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_clearButton);
    buttonLayout->addWidget(m_undoButton);
    buttonLayout->addWidget(m_calculateButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_canvasWidget);
    mainLayout->addLayout(buttonLayout);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("AI Math Notes");
    resize(1200, 800);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        calculate();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::calculate()
{
    QImage image = m_canvasWidget->getCanvasImage();
    m_geminiClient->solveEquation(image);
    m_calculateButton->setEnabled(false);
}

void MainWindow::onSolutionReceived(const QString& solution)
{
    m_canvasWidget->drawAnswer(solution);
    m_calculateButton->setEnabled(true);
}

void MainWindow::onErrorOccurred(const QString& error)
{
    QMessageBox::critical(this, "Error", error);
    m_calculateButton->setEnabled(true);
}