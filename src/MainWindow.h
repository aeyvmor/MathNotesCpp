#pragma once

#include <QMainWindow>

class CanvasWidget;
class GeminiClient;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int fontId, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void calculate();
    void onSolutionReceived(const QString& solution);
    void onErrorOccurred(const QString& error);

private:
    void setupUI(int fontId);

    CanvasWidget* m_canvasWidget;
    GeminiClient* m_geminiClient;
    
    QPushButton* m_clearButton;
    QPushButton* m_undoButton;
    QPushButton* m_calculateButton;
};