#include "ocrgiflabelwidget.h"

#include <QTimer>

#define GIF_CICLE_BLUE          58

OCRGifLabelWidget::OCRGifLabelWidget(QWidget *parent)
    : QLabel(parent)
{
    m_index = -1;
    m_isRunning = false;
    m_infinited = true;

    setFixedSize(GIF_CICLE_BLUE, GIF_CICLE_BLUE);

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), SLOT(timeout()));
}

OCRGifLabelWidget::OCRGifLabelWidget(Type type, QWidget *parent)
    : OCRGifLabelWidget(parent)
{
    setType(type);
}

OCRGifLabelWidget::~OCRGifLabelWidget()
{
    delete m_timer;
}

void OCRGifLabelWidget::setType(Type type)
{
    switch(m_type = type)
    {
        case CicleBlue: setFixedSize(GIF_CICLE_BLUE, GIF_CICLE_BLUE); break;
        default: break;
    }
}

OCRGifLabelWidget::Type OCRGifLabelWidget::type() const
{
    return m_type;
}

void OCRGifLabelWidget::setInterval(int value)
{
    m_timer->setInterval(value);
}

int OCRGifLabelWidget::interval() const
{
    return m_timer->interval();
}

void OCRGifLabelWidget::setInfinited(bool s)
{
    m_infinited = s;
}

bool OCRGifLabelWidget::infinited() const
{
    return m_infinited;
}

void OCRGifLabelWidget::start()
{
    m_timer->start();
    m_isRunning = true;
}

void OCRGifLabelWidget::stop()
{
    m_timer->stop();
    m_isRunning = false;
}

void OCRGifLabelWidget::timeout()
{
    ++m_index;
    switch(m_type)
    {
        case CicleBlue:
            {
                if(m_index == 12 && infinitedModeCheck())
                {
                    break;
                }
                setStyleSheet(QString("background-image: url(':/gif/lb_cicle_blue'); \
                                       margin-left:-%1px;").arg(GIF_CICLE_BLUE*m_index));
                break;
            }
        default: break;
    }
}

bool OCRGifLabelWidget::infinitedModeCheck()
{
    m_index = 0;
    if(!m_infinited)
    {
        stop();
        return true;
    }
    else
    {
        return false;
    }
}
