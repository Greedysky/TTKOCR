#include "ocrgrabwidget.h"
#include "ttkdesktopscreen.h"

#include <QMenu>
#include <QPainter>
#include <QMouseEvent>

OCRGrabWidget::OCRGrabWidget(QWidget *parent)
    : QWidget(nullptr),
      m_isDrawing(false)
{
    Q_UNUSED(parent);

    setAttribute(Qt::WA_DeleteOnClose, true);
    setAttribute(Qt::WA_QuitOnClose, true);

    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setFixedSize(TTKDesktopScreen::geometry().size());
    setCursor(Qt::CrossCursor);

    const QRect &rect = TTKDesktopScreen::availableGeometry();
    m_originPixmap = TTKDesktopScreen::grabWindow(rect.x(), rect.y(), width(), height());
}

void OCRGrabWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    m_ptCursor.setX(QtMouseX(event));
    m_ptCursor.setY(QtMouseY(event));

    update();
}

void OCRGrabWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QPen pen(QColor(0x15, 0x8F, 0xE1), 1);
    painter.setPen(pen);

    painter.drawPixmap(0, 0, width(), height(), m_originPixmap);

    int w = 0, h = 0;
    if(m_isDrawing)
    {
        w = m_ptCursor.x() - m_ptStart.x();
        h = m_ptCursor.y() - m_ptStart.y();
        painter.drawRect(m_ptStart.x() - 1, m_ptStart.y() - 1, w + 1, h + 1);
    }
    else if(m_ptEnd != m_ptStart)
    {
        w = m_ptEnd.x() - m_ptStart.x();
        h = m_ptEnd.y() - m_ptStart.y();
        painter.drawRect(m_ptStart.x() - 1, m_ptStart.y() - 1, w + 1, h + 1);
    }

    QPolygon listMarker;
    listMarker.push_back(QPoint(m_ptStart.x(), m_ptStart.y()));
    listMarker.push_back(QPoint(m_ptStart.x() + w, m_ptStart.y()));
    listMarker.push_back(QPoint(m_ptStart.x(), h + m_ptStart.y()));
    listMarker.push_back(QPoint(m_ptStart.x() + w, h + m_ptStart.y()));

    listMarker.push_back(QPoint(m_ptStart.x() + (w >> 1), m_ptStart.y()));
    listMarker.push_back(QPoint(m_ptStart.x() + (w >> 1), h + m_ptStart.y()));
    listMarker.push_back(QPoint(m_ptStart.x(), m_ptStart.y() + (h >> 1)));
    listMarker.push_back(QPoint(m_ptStart.x() + w, m_ptStart.y() + (h >> 1)));

    pen.setWidth(4);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoints(listMarker);
}

void OCRGrabWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        m_ptStart = event->pos();
        m_ptCursor = m_ptStart;
        m_isDrawing = true;
    }
    update();
}

void OCRGrabWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        m_ptEnd = event->pos();
        m_isDrawing = false;
    }
}

void OCRGrabWidget::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        const int width = m_ptEnd.x() - m_ptStart.x();
        const int height = m_ptEnd.y() - m_ptStart.y();
        const QRect &rect = TTKDesktopScreen::availableGeometry();
        const QPixmap &pix = TTKDesktopScreen::grabWindow(m_ptStart.x() + rect.x(), m_ptStart.y() + rect.y(), width, height);
        Q_EMIT pixmapChanged(pix);
        close();
    }
    else if(event->key() == Qt::Key_Escape)
    {
        close();
    }
}
