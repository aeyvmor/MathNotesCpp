#include "CanvasWidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QFontDatabase>

CanvasWidget::CanvasWidget(int fontId, QWidget *parent)
    : QWidget(parent), m_fontId(fontId)
{
    m_image = QImage(size(), QImage::Format_RGB32);
    m_image.fill(Qt::black);

    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        m_lastPoint = event->pos();
        m_currentStroke.clear();
        m_currentStroke.append(m_lastPoint);
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDrawing && (event->buttons() & Qt::LeftButton)) {
        QPainter painter(&m_image);
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen(Qt::white, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(m_lastPoint, event->pos());
        
        m_lastPoint = event->pos();
        m_currentStroke.append(m_lastPoint);
        update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing) {
        m_isDrawing = false;
        if (!m_currentStroke.isEmpty()) {
            m_strokes.append(m_currentStroke);
        }
    }
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(event->rect(), m_image, event->rect());
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > m_image.width() || height() > m_image.height()) {
        int newWidth = qMax(width() + 128, m_image.width());
        int newHeight = qMax(height() + 128, m_image.height());
        QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
        newImage.fill(Qt::black);
        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), m_image);
        m_image = newImage;
    }
    QWidget::resizeEvent(event);
}

void CanvasWidget::clearCanvas()
{
    m_strokes.clear();
    m_image.fill(Qt::black);
    update();
}

void CanvasWidget::undo()
{
    if (!m_strokes.isEmpty()) {
        m_strokes.pop_back();
        redrawAllStrokes();
    }
}

void CanvasWidget::redrawAllStrokes()
{
    m_image.fill(Qt::black);
    QPainter painter(&m_image);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::white, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    for (const auto& stroke : m_strokes) {
        for (int i = 0; i < stroke.size() - 1; ++i) {
            painter.drawLine(stroke[i], stroke[i+1]);
        }
    }
    update();
}

QImage CanvasWidget::getCanvasImage() const
{
    return m_image;
}

QPoint CanvasWidget::getLastPoint() const
{
    if (!m_strokes.isEmpty() && !m_strokes.last().isEmpty()) {
        return m_strokes.last().last();
    }
    return QPoint();
}

void CanvasWidget::drawAnswer(const QString& answer)
{
    QPoint lastPoint = getLastPoint();
    if (lastPoint.isNull()) {
        return;
    }

    QPainter painter(&m_image);
    QStringList families = QFontDatabase::applicationFontFamilies(m_fontId);
    if (families.isEmpty()) {
        qWarning("Could not find font family for loaded font.");
        return;
    }
    QFont font(families.at(0), 100);
    painter.setFont(font);
    painter.setPen(QColor("#FF9500"));

    QPoint textPos = lastPoint + QPoint(70, 20);
    painter.drawText(textPos, answer);
    
    update();
}