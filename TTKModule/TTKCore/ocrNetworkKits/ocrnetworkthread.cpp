#include "ocrnetworkthread.h"
#include "ocrobject.h"

#include <QHostInfo>
#ifdef TTK_GREATER_NEW
#  include <QtConcurrent/QtConcurrent>
#else
#  include <QtConcurrentRun>
#endif

OCRNetworkThread::OCRNetworkThread()
    : QObject(nullptr), m_networkState(true)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(networkStateChanged()));
}

OCRNetworkThread::~OCRNetworkThread()
{
    m_timer.stop();
}

QString OCRNetworkThread::getClassName()
{
    return staticMetaObject.className();
}

void OCRNetworkThread::start()
{
    M_LOGGER_INFO("Load NetworkThread");
    m_timer.start(NETWORK_DETECT_INTERVAL);
}

void OCRNetworkThread::networkStateChanged()
{
    QtConcurrent::run([&]
    {
        QHostInfo info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        emit networkConnectionStateChanged(m_networkState);
    });
}
