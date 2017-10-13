#include "ocrrunapplication.h"
#include "ocrlocalpeer.h"

#include <QWidget>

class OCRRunApplicationPrivate : public OCRPrivate<OCRRunApplication>
{
public:
    OCRRunApplicationPrivate();
    ~OCRRunApplicationPrivate();

    OCRLocalPeer *m_peer;
    QWidget *m_activeWindow;
};

OCRRunApplicationPrivate::OCRRunApplicationPrivate()
{
    m_peer = nullptr;
    m_activeWindow = nullptr;
}

OCRRunApplicationPrivate::~OCRRunApplicationPrivate()
{
    delete m_peer;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
///
///

OCRRunApplication::OCRRunApplication(int &argc, char **argv, bool GUIenabled)
    : QApplication(argc, argv, GUIenabled)
{
    OCR_INIT_PRIVATE;
    sysInit();
}

OCRRunApplication::OCRRunApplication(const QString &appId, int &argc, char **argv)
    : QApplication(argc, argv)
{
    OCR_INIT_PRIVATE;
    sysInit(appId);
}

#if QT_VERSION < 0x050000
OCRRunApplication::OCRRunApplication(int &argc, char **argv, Type type)
    : QApplication(argc, argv, type)
{
    OCR_INIT_PRIVATE;
    sysInit();
}

#  if defined(Q_WS_X11)
OCRRunApplication::OCRRunApplication(Display* dpy, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, visual, cmap)
{
    OCR_INIT_PRIVATE;
    sysInit();
}

OCRRunApplication::OCRRunApplication(Display *dpy, int &argc, char **argv, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, argc, argv, visual, cmap)
{
    OCR_INIT_PRIVATE;
    sysInit();
}

OCRRunApplication::OCRRunApplication(Display* dpy, const QString &appId, int argc, char **argv, Qt::HANDLE visual, Qt::HANDLE cmap)
    : QApplication(dpy, argc, argv, visual, cmap)
{
    OCR_INIT_PRIVATE;
    sysInit(appId);
}
#  endif
#endif

void OCRRunApplication::initialize(bool dummy)
{
    Q_UNUSED(dummy);
    isRunning();
}

bool OCRRunApplication::isRunning() const
{
    OCR_D(OCRRunApplication);
    return d->m_peer->isClient();
}

QString OCRRunApplication::id() const
{
    OCR_D(OCRRunApplication);
    return d->m_peer->applicationId();
}

void OCRRunApplication::setActivationWindow(QWidget* aw, bool activateOnMessage)
{
    OCR_D(OCRRunApplication);
    d->m_activeWindow = aw;

    if(activateOnMessage)
    {
        connect(d->m_peer, SIGNAL(messageReceived(QString)), this, SLOT(activateWindow()));
    }
    else
    {
        disconnect(d->m_peer, SIGNAL(messageReceived(QString)), this, SLOT(activateWindow()));
    }
}

QWidget* OCRRunApplication::activationWindow() const
{
    OCR_D(OCRRunApplication);
    return d->m_activeWindow;
}

bool OCRRunApplication::sendMessage(const QString &message, int timeout)
{
    OCR_D(OCRRunApplication);
    return d->m_peer->sendMessage(message, timeout);
}

void OCRRunApplication::activateWindow()
{
    OCR_D(OCRRunApplication);
    if(d->m_activeWindow)
    {
        d->m_activeWindow->setWindowState(d->m_activeWindow->windowState() & ~Qt::WindowMinimized);
        d->m_activeWindow->raise();
        d->m_activeWindow->activateWindow();
    }
}

void OCRRunApplication::sysInit(const QString &appId)
{
    OCR_D(OCRRunApplication);
    d->m_peer = new OCRLocalPeer(this, appId);
    connect(d->m_peer, SIGNAL(messageReceived(QString)), SIGNAL(messageReceived(QString)));
}
