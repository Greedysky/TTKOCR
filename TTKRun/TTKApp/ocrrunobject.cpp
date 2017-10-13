#include "ocrrunobject.h"
#include "ocrinitobject.h"

#include <QProcess>
#include <QApplication>

class OCRRunObjectPrivate : public OCRPrivate<OCRRunObject>
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
    OCR_INIT_PRIVATE;
    OCR_D(OCRRunObject);

    d->m_process = new QProcess(this);
    connect(d->m_process, SIGNAL(finished(int)), SLOT(finished(int)));
}

void OCRRunObject::checkValid()
{
    OCRInitObject object;
    object.checkValid();
}

void OCRRunObject::run(int argc, char **argv)
{
    OCR_D(OCRRunObject);
    QStringList list(APPNAME);
    if(argc == 3)
    {
        list << argv[1] << argv[2];
    }

    d->m_process->start(S_TTKSERVICE_FULL, list);
}

void OCRRunObject::finished(int code)
{
     if(code == 0)
     {
         qDebug() << "Application exit success!";
     }
     else
     {
         qDebug() << "Application run error, please run TTKService instead!";
     }

     qApp->quit();
}
