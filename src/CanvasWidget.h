#pragma once

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QVector>

// A stroke is a single continuous line drawn by the user.
// It's represented by a vector of points.
using Stroke = QVector<QPoint>;

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(int fontId, QWidget *parent = nullptr);

    // Public method for the MainWindow to get the current canvas image.
    QImage getCanvasImage() const;

    // Public method to draw the final answer text onto the canvas.
    void drawAnswer(const QString& answer);

    // Public method to get the position of the last point drawn.
    QPoint getLastPoint() const;

public slots:
    // Clears the entire canvas.
    void clearCanvas();
    // Undoes the last drawn stroke.
    void undo();

protected:
    // Overridden Qt event handlers for mouse input.
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    // Overridden paint event to draw the canvas content.
    void paintEvent(QPaintEvent *event) override;
    // Overridden resize event to handle window resizing.
    void resizeEvent(QResizeEvent *event) override;

private:
    // Redraws the entire canvas from the stored strokes.
    void redrawAllStrokes();

    // The off-screen buffer where all drawing occurs.
    QImage m_image;
    // Is the user currently drawing?
    bool m_isDrawing = false;
    // The last point recorded during a mouse move.
    QPoint m_lastPoint;

    // Stores all the strokes that make up the current drawing.
    QVector<Stroke> m_strokes;
    // The current stroke being drawn.
    Stroke m_currentStroke;
    int m_fontId;
};