#include "ocrnetworkthread.h"
#include "ocrobject.h"
#include "ttkconcurrent.h"

#include <QHostInfo>

static constexpr int NETWORK_DETECT_INTERVAL = 5000; // second
static constexpr const char *NETWORK_REQUEST_ADDRESS = "www.baidu.com"; // ip

OCRNetworkThread::OCRNetworkThread()
    : QObject(nullptr),
      m_networkState(true)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(networkStateChanged()));
}

OCRNetworkThread::~OCRNetworkThread()
{
    m_timer.stop();
}

void OCRNetworkThread::start()
{
    TTK_INFO_STREAM("Load NetworkThread");
    m_timer.start(NETWORK_DETECT_INTERVAL);
}

void OCRNetworkThread::networkStateChanged()
{
    TTKConcurrent(
    {
        const QHostInfo &info = QHostInfo::fromName(NETWORK_REQUEST_ADDRESS);
        m_networkState = !info.addresses().isEmpty();
        Q_EMIT networkConnectionStateChanged(m_networkState);
    });
}
