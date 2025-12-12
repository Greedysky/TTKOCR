#include "ocrgrabwidget.h"
#include "ocrcoreutils.h"
#include "ttkdesktopscreen.h"

#include <QMenu>
#include <QPainter>
#include <QMouseEvent>

static QRect currentAvailableGeometry()
{
    const int index = TTKDesktopScreen::currentIndex();
    return TTKDesktopScreen::availableGeometry(index);
}


OCRGrabWidget::OCRGrabWidget(QWidget *parent)
    : QWidget(nullptr),
      m_isDrawing(false),
      m_parent(parent)
{
    m_parent->hide();
    TTK::Core::sleep(500);

    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_QuitOnClose);

    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setFixedSize(currentAvailableGeometry().size());
    setCursor(Qt::CrossCursor);

    const QRect &rect = currentAvailableGeometry();
    m_originPixmap = TTKDesktopScreen::grabWindow(rect.x(), rect.y(), width(), height());
}

void OCRGrabWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    m_endPoint.setX(QtPositionX(event));
    m_endPoint.setY(QtPositionY(event));
    update();
}

void OCRGrabWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_originPixmap.isNull())
    {
        return;
    }

    QPainter painter(this);
    QPen pen(QColor(0x15, 0x8F, 0xE1), 1);
    painter.setPen(pen);

    painter.drawPixmap(0, 0, width(), height(), m_originPixmap);

    const int w = m_endPoint.x() - m_startPoint.x();
    const int h = m_endPoint.y() - m_startPoint.y();
    painter.drawRect(m_startPoint.x() - 1, m_startPoint.y() - 1, w + 1, h + 1);

    QPolygon listMarker;
    listMarker.append(QPoint(m_startPoint.x(), m_startPoint.y()));
    listMarker.append(QPoint(m_startPoint.x() + w, m_startPoint.y()));
    listMarker.append(QPoint(m_startPoint.x(), h + m_startPoint.y()));
    listMarker.append(QPoint(m_startPoint.x() + w, h + m_startPoint.y()));

    listMarker.append(QPoint(m_startPoint.x() + (w >> 1), m_startPoint.y()));
    listMarker.append(QPoint(m_startPoint.x() + (w >> 1), h + m_startPoint.y()));
    listMarker.append(QPoint(m_startPoint.x(), m_startPoint.y() + (h >> 1)));
    listMarker.append(QPoint(m_startPoint.x() + w, m_startPoint.y() + (h >> 1)));

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
        m_startPoint = event->pos();
        m_endPoint = m_startPoint;
        m_isDrawing = true;
    }
    update();
}

void OCRGrabWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        m_endPoint = event->pos();
        m_isDrawing = false;
    }
}

void OCRGrabWidget::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if(m_endPoint.x() < m_startPoint.x())
        {
            std::swap(m_startPoint, m_endPoint);
        }

        const int width = m_endPoint.x() - m_startPoint.x();
        const int height = m_endPoint.y() - m_startPoint.y();
        const QRect &rect = currentAvailableGeometry();
        const QPixmap &pix = TTKDesktopScreen::grabWindow(m_startPoint.x() + rect.x(), m_startPoint.y() + rect.y(), width, height);
        Q_EMIT pixmapChanged(pix);

        m_parent->show();
        close();
    }
    else if(event->key() == Qt::Key_Escape)
    {
        m_parent->show();
        close();
    }
}
