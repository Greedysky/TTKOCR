#include "ocrabstractmovewidget.h"
#include "ocrbackgroundmanager.h"
#include "ocrobject.h"

#include <QPainter>
#include <QBoxLayout>

#define WIDTH  4
#define HEIGHT 4

OCRAbstractMoveWidget::OCRAbstractMoveWidget(QWidget *parent)
    : OCRAbstractMoveWidget(true, parent)
{

}

OCRAbstractMoveWidget::OCRAbstractMoveWidget(bool transparent, QWidget *parent)
    : QWidget(parent)
{
    ///Remove the title bar
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint );
    setAttribute(Qt::WA_TranslucentBackground, transparent);

    m_moveOption = false;
    m_leftButtonPress = false;
    m_showShadow = true;
    m_background = nullptr;

    M_BACKGROUND_PTR->addObserver(this);
}

OCRAbstractMoveWidget::~OCRAbstractMoveWidget()
{
    M_BACKGROUND_PTR->removeObserver(this);
}

QString OCRAbstractMoveWidget::getClassName()
{
    return staticMetaObject.className();
}

void OCRAbstractMoveWidget::backgroundChanged()
{
    if(m_background)
    {
        setBackgroundPixmap(size());
    }
}

void OCRAbstractMoveWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_showShadow)
    {
        QPainter painter(this);

        painter.drawPixmap(0, 0, WIDTH, HEIGHT, QPixmap(":/shadow/lb_left_top"));
        painter.drawPixmap(width() - WIDTH, 0, WIDTH, HEIGHT, QPixmap(":/shadow/lb_right_top"));
        painter.drawPixmap(0, height() - HEIGHT, WIDTH, HEIGHT, QPixmap(":/shadow/lb_left_bottom"));
        painter.drawPixmap(width() - WIDTH, height() - HEIGHT, WIDTH, HEIGHT, QPixmap(":/shadow/lb_right_bottom"));

        painter.drawPixmap(0, WIDTH, HEIGHT, height() - 2*WIDTH,
                           QPixmap(":/shadow/lb_left").scaled(WIDTH, height() - 2*HEIGHT));
        painter.drawPixmap(width() - WIDTH, WIDTH, HEIGHT, height() - 2*HEIGHT,
                           QPixmap(":/shadow/lb_right").scaled(WIDTH, height() - 2*HEIGHT));
        painter.drawPixmap(HEIGHT, 0, width() - 2*WIDTH, HEIGHT,
                           QPixmap(":/shadow/lb_top").scaled(width() - 2*WIDTH, HEIGHT));
        painter.drawPixmap(WIDTH, height() - HEIGHT, width() - 2*WIDTH, HEIGHT,
                           QPixmap(":/shadow/lb_bottom").scaled(width() - 2*WIDTH, HEIGHT));
    }
}

void OCRAbstractMoveWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if( event->button() == Qt::LeftButton && !m_moveOption)///Press the left key
    {
        m_leftButtonPress = true;
    }
    m_pressAt = event->globalPos();
}

void OCRAbstractMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if( !m_leftButtonPress )///Not press the left key
    {
        event->ignore();
        return;
    }
    int xpos = event->globalX() - m_pressAt.x();
    int ypos = event->globalY() - m_pressAt.y();
    m_pressAt = event->globalPos();
    move( x() + xpos, y() + ypos);
}

void OCRAbstractMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    m_pressAt = event->globalPos();
    m_leftButtonPress = false;
}

void OCRAbstractMoveWidget::setBackgroundPixmap(QLabel *label, const QSize &size)
{
    m_background = label;
    setBackgroundPixmap(size);
}

void OCRAbstractMoveWidget::setBackgroundPixmap(const QSize &size)
{
    QLabel *label = TTKStatic_cast(QLabel*, m_background);
    label->setPixmap(QPixmap(M_BACKGROUND_PTR->getMBackground()).scaled(size));
}


OCRAbstractMoveSingleWidget::OCRAbstractMoveSingleWidget(QWidget *parent)
    : OCRAbstractMoveSingleWidget(true, parent)
{

}

OCRAbstractMoveSingleWidget::OCRAbstractMoveSingleWidget(bool transparent, QWidget *parent)
    : OCRAbstractMoveWidget(transparent, parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(WIDTH, HEIGHT, WIDTH, HEIGHT);
    l->setSpacing(0);
    m_container = new QWidget(this);
    l->addWidget(m_container);
    setLayout(l);
}

OCRAbstractMoveSingleWidget::~OCRAbstractMoveSingleWidget()
{
    delete m_container;
}

QString OCRAbstractMoveSingleWidget::getClassName()
{
    return staticMetaObject.className();
}
