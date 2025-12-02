#include "ocrapplication.h"
#include "ui_ocrapplication.h"
#include "ocrapplicationmodule.h"
#include "ocrfunctionlistuiobject.h"
#include "ocrwidgetutils.h"
#include "ocrfileutils.h"
#include "ocrgrabwidget.h"
#include "ocrthread.h"
#include "ocruiobject.h"
#ifdef TTK_BUILD_BY_PDF
#  include "document.h"
#endif
#include <QScrollBar>

OCRApplication *OCRApplication::m_instance = nullptr;

OCRApplication::OCRApplication(QWidget *parent)
    : TTKAbstractMoveResizeWidget(false, parent),
      m_ui(new Ui::OCRApplication),
      m_count(0)
{
    m_instance = this;

    m_applicationModule = new OCRApplicationModule(this);

    m_ui->setupUi(this);
    setMinimumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    setMaximumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);

    m_ui->iconLabel->setPixmap(QPixmap(":/image/lb_app_logo").scaled(m_ui->iconLabel->size()));
    m_ui->background->setPixmap(QPixmap(":/image/lb_background").scaled(size()));

    m_ui->minButton->setStyleSheet(TTK::UI::FuncMin);
    connect(m_ui->minButton, SIGNAL(clicked()), SLOT(showMinimized()));

    m_ui->closeButton->setStyleSheet(TTK::UI::FuncClose);
    connect(m_ui->closeButton, SIGNAL(clicked()), SLOT(quitWindowClose()));

    m_ui->openButton->setStyleSheet(TTK::UI::PushButtonStyle01);
    m_ui->screenshotButton->setStyleSheet(TTK::UI::PushButtonStyle01);
    m_ui->startButton->setStyleSheet(TTK::UI::PushButtonStyle01);
    m_ui->clearButton->setStyleSheet(TTK::UI::PushButtonStyle01);

    connect(m_ui->openButton, SIGNAL(clicked()), SLOT(openButtonClicked()));
    connect(m_ui->screenshotButton, SIGNAL(clicked()), SLOT(screenshotButtonClicked()));
    connect(m_ui->startButton, SIGNAL(clicked()), SLOT(startButtonClicked()));
    connect(m_ui->clearButton, SIGNAL(clicked()), SLOT(clearButtonClicked()));

    m_ui->pixScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->pixScrollArea->setWidgetResizable(true);
    m_ui->pixScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->pixScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->pixScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->pixScrollArea->verticalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle01);

    m_ui->textScrollArea->setWidgetResizable(true);
    m_ui->textScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->textScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->textScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->textScrollArea->verticalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle01);
    m_ui->textScrollArea->horizontalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle02);

    m_ui->textScrollAreaWidget->setReadOnly(true);
    m_ui->textScrollAreaWidget->verticalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle01);
    m_ui->textScrollAreaWidget->horizontalScrollBar()->setStyleSheet(TTK::UI::ScrollBarStyle02);

    // Objects Mouse tracking
    setObjectsTracking({m_ui->background});

#ifndef QT_NO_SSL
    // ssl support check
    TTK_INFO_STREAM("Application network support ssl:" << (QSslSocket::supportsSsl() ? "true" : "false"));
#endif
    TTK::Widget::adjustWidgetPosition(this);
}

OCRApplication::~OCRApplication()
{
    deleteItems();
    delete m_applicationModule;
    delete m_ui;
}

OCRApplication *OCRApplication::instance()
{
    return m_instance;
}

void OCRApplication::quitWindowClose()
{
    m_applicationModule->quit();
}

void OCRApplication::openButtonClicked()
{
    QStringList list(TTK::File::getOpenFileNames(this, "Image Files (*.png *.bmp *.jpg);;PDF Files (*.pdf)"));
    if(list.isEmpty())
    {
        return;
    }

    clearButtonClicked();

    const QString &path = list.first();
    if(TTK_FILE_SUFFIX(QFileInfo(path)) == "pdf")
    {
#ifdef TTK_BUILD_BY_PDF
        MuPDF::Document *document = new MuPDF::Document(path);
        for(int i = 0; i < document->numPages(); ++i)
        {
            OCRRequestItem *item = new OCRRequestItem(this);
            item->m_index = i;

            MuPDF::Page *page = document->page(i);
            item->m_image = QPixmap::fromImage(page->renderImage());
            QLabel *v = new QLabel(m_ui->pixScrollAreaWidget);
            v->setPixmap(item->m_image.scaled(405, 405, Qt::KeepAspectRatio));
            delete page;
            m_ui->pixScrollAreaWidgetLayout->addWidget(v);
            item->m_obj = v;

            m_fileList << item;
        }
        delete document;
#else
        qDebug() << "Don't support pdf files";
#endif
        return;
    }

    for(int i = 0; i < list.count(); ++i)
    {
        OCRRequestItem *item = new OCRRequestItem(this);
        item->m_index = i;
        item->m_image = QPixmap(list[i]);

        QLabel *v = new QLabel(m_ui->pixScrollAreaWidget);
        v->setPixmap(item->m_image.scaled(405, 405, Qt::KeepAspectRatio));
        m_ui->pixScrollAreaWidgetLayout->setAlignment(Qt::AlignHCenter);
        m_ui->pixScrollAreaWidgetLayout->addWidget(v);
        item->m_obj = v;

        m_fileList << item;
    }
}

void OCRApplication::screenshotButtonClicked()
{
    OCRGrabWidget *w = new OCRGrabWidget(this);
    connect(w, SIGNAL(pixmapChanged(QPixmap)), SLOT(pixmapChanged(QPixmap)));
    w->show();
}

void OCRApplication::startButtonClicked()
{
    if(m_fileList.isEmpty())
    {
        return;
    }

    m_count = 0;
    TTK::File::removeRecursively(CACHE_DIR_FULL);

    for(OCRRequestItem *item : qAsConst(m_fileList))
    {
        OCRNetworkRequest *request = new OCRNetworkRequest(item);
        connect(request, SIGNAL(downLoadDataChanged(QString)), SLOT(downLoadDataChanged()));
        request->startToRequest(item);
    }

    stateChanged(true);
}

void OCRApplication::clearButtonClicked()
{
    if(m_fileList.isEmpty())
    {
        return;
    }

    m_count = 0;
    deleteItems();

    TTK::File::removeRecursively(CACHE_DIR_FULL);
    m_ui->textScrollAreaWidget->clear();
}

void OCRApplication::downLoadDataChanged()
{
    ++m_count;
    if(m_count == m_fileList.count())
    {
        const QStringList files(QDir(CACHE_DIR_FULL).entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name));
        TTKIntList data;
        for(const QString &path : qAsConst(files))
        {
            const QString &fileName = QFileInfo(path).baseName();
            data << fileName.trimmed().toInt();
        }
        std::sort(data.begin(), data.end());

        QString content;
        for(int i = 0; i < m_fileList.count(); ++i)
        {
            QFile file(QString("%1/%2").arg(CACHE_DIR_FULL).arg(i));
            if(file.open(QIODevice::ReadOnly))
            {
                content.append(file.readAll());
                file.close();
            }
            else
            {
                content.append("No OCR Data Found \r\n");
            }

            content.append("===========================================");
#ifdef Q_OS_UNIX
            content.append("==========");
#endif
            content.append(TTK_WLINEFEED);
        }

        m_ui->textScrollAreaWidget->appendPlainText(content);
        TTK::File::removeRecursively(CACHE_DIR_FULL);

        stateChanged(false);
    }
}

void OCRApplication::pixmapChanged(const QPixmap &pix)
{
    OCRRequestItem *item = new OCRRequestItem(this);
    item->m_index = m_fileList.count();
    item->m_image = pix;

    QLabel *label = new QLabel(m_ui->pixScrollAreaWidget);
    label->setPixmap(pix.scaled(405, 405, Qt::KeepAspectRatio));
    m_ui->pixScrollAreaWidgetLayout->addWidget(label);
    item->m_obj = label;

    m_fileList << item;
}

void OCRApplication::deleteItems()
{
    while(!m_fileList.isEmpty())
    {
        OCRRequestItem *item = m_fileList.takeLast();
        delete item->m_obj;
        delete item;
    }
}

void OCRApplication::stateChanged(bool state)
{
    if(state)
    {
        m_ui->stateLabel->raise();
        m_ui->stateLabel->show();
        m_ui->stateLabel->start();
    }
    else
    {
        m_ui->stateLabel->stop();
        m_ui->stateLabel->hide();
    }

    m_ui->openButton->setEnabled(!state);
    m_ui->screenshotButton->setEnabled(!state);
    m_ui->startButton->setEnabled(!state);
    m_ui->clearButton->setEnabled(!state);
}
