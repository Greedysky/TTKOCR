#include "ttkrunobject.h"
#include "ocrinitobject.h"

#include <QProcess>
#include <QApplication>

/*! @brief The class of the ttk run object private.
 * @author Greedysky <greedysky@163.com>
 */
class OCRRunObjectPrivate : public TTKPrivate<OCRRunObject>
{
public:
    OCRRunObjectPrivate();
    ~OCRRunObjectPrivate();

    QProcess *m_process;

};

OCRRunObjectPrivate::OCRRunObjectPrivate()
{
    m_process = nullptr;
}

OCRRunObjectPrivate::~OCRRunObjectPrivate()
{
    delete m_process;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
///
OCRRunObject::OCRRunObject(QObject *parent)
    : QObject(parent)
{
    TTK_INIT_PRIVATE(OCRRunObject);
    TTK_D(OCRRunObject);

    d->m_process = new QProcess(this);
    connect(d->m_process, SIGNAL(finished(int)), SLOT(finished(int)));
}

void OCRRunObject::valid() const
{
    OCRInitObject object;
    object.valid();
}

void OCRRunObject::run(int argc, char **argv) const
{
    TTK_D(OCRRunObject);

    QStringList list(APP_NAME);
    if(argc == 3)
    {
        list << argv[1] << argv[2];
    }

    d->m_process->start(TTK_SERVICE_FULL, list);
}

void OCRRunObject::finished(int code)
{
    if(code == 0)
    {
        TTK_LOGGER_INFO("Application exit success!");
    }
    else
    {
        TTK_LOGGER_INFO("Application run error, please run TTKService instead!");
    }

    qApp->quit();
}
