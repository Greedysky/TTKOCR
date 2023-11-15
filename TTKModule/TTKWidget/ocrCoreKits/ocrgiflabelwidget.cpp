#include "ocrgiflabelwidget.h"

#include <QTimer>
#include <QPainter>

static constexpr int GIF_CICLE_BLUE = 58;

OCRGifLabelWidget::OCRGifLabelWidget(QWidget *parent)
    : QLabel(parent),
      m_index(-1),
      m_isRunning(false),
      m_infinited(true)
{
    setFixedSize(GIF_CICLE_BLUE, GIF_CICLE_BLUE);

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), SLOT(updateRender()));
}

OCRGifLabelWidget::OCRGifLabelWidget(Module type, QWidget *parent)
    : OCRGifLabelWidget(parent)
{
    setType(type);
}

OCRGifLabelWidget::~OCRGifLabelWidget()
{
    delete m_timer;
}

void OCRGifLabelWidget::setType(Module type)
{
    m_index = 0;
    switch(m_type = type)
    {
        case Module::CicleBlue: setFixedSize(GIF_CICLE_BLUE, GIF_CICLE_BLUE); break;
        default: break;
    }
}

OCRGifLabelWidget::Module OCRGifLabelWidget::type() const
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

void OCRGifLabelWidget::run(bool run)
{
    if(run)
    {
        show();
        start();
    }
    else
    {
        hide();
        stop();
    }
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

void OCRGifLabelWidget::updateRender()
{
    ++m_index;
    switch(m_type)
    {
        case Module::CicleBlue:
            {
                if(m_index == 12 && infinitedModeCheck())
                {
                    break;
                }

                m_renderer = QPixmap(":/gif/lb_cicle_blue").copy(GIF_CICLE_BLUE * m_index, 0, width(), height());
                update();
                break;
            }
        default: break;
    }
}

void OCRGifLabelWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawPixmap(0, 0, m_renderer);
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
