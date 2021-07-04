#include "mupdf-document.h"
#include "mupdf-document_p.h"
#include "mupdf-page.h"
#include "mupdf-page_p.h"
#include "mupdf-outline.h"
#include "mupdf-outline_p.h"
extern "C" {
#include <mupdf/fitz.h>
}
#include <QString>
#include <QDateTime>

namespace MuPDF
{

/**
 * @brief Load a document.
 *
 * @param filePath document path
 *
 * @return NULL if failed (Note: you need delete manually when it's useless)
 */
Document * loadDocument(const QString &filePath)
{
    DocumentPrivate *documentp;
    Document *document;

    // Create DocumentPrivate
    documentp = new DocumentPrivate(filePath);
    if (!documentp)
        return NULL;
    else if (!documentp->context || !documentp->document) {
        delete documentp;
        return NULL;
    }

    // Create Document
    document = new Document(documentp);
    return document;
}

/**
 * @brief Load a document.
 *
 * @param bytes document data
 *
 * @return NULL if failed (Note: you need delete manually when it's useless)
 */
Document * loadDocument(const QByteArray &bytes)
{
    DocumentPrivate *documentp;
    Document *document;

    // Create DocumentPrivate
    documentp = new DocumentPrivate((unsigned char *)bytes.data(), bytes.length());
    if (!documentp)
        return NULL;
    else if (!documentp->context || !documentp->document) {
        delete documentp;
        return NULL;
    }

    // Create Document
    document = new Document(documentp);
    return document;
}

DocumentPrivate::DocumentPrivate(const QString &filePath)
    : context(NULL), document(NULL)
    , transparent(false)
    , b(-1), g(-1), r(-1), a(-1)
{
    // create context
    context = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!context)
        return;

    // register the default file types
    fz_register_document_handlers(context);

    // open document
    fz_try(context)
    {
        document = fz_open_document(context, filePath.toUtf8().data());
    }
    fz_catch(context)
    {
        deleteData();
    }
}

DocumentPrivate::DocumentPrivate(unsigned char *bytes, int len)
    : context(NULL), document(NULL)
    , transparent(false)
    , b(-1), g(-1), r(-1), a(-1)
{
    // create context
    context = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!context)
        return;

    // register the default file types
    fz_register_document_handlers(context);

    // open document
    fz_try(context)
    {
        // access to the bytes stream
        fz_stream* stream = fz_open_memory(context, bytes, len);

        document = fz_open_document_with_stream(context, ".pdf", stream);
    }
    fz_catch(context)
    {
        deleteData();
    }
}

/**
 * @brief Destructor
 */
Document::~Document()
{
    delete d;
    d = NULL;
}

/**
 * @brief Whether the document needs password
 */
bool Document::needsPassword() const
{
    return fz_needs_password(d->context, d->document);
}

/**
 * @brief Authenticate password
 *
 * @param password User password or owner password
 * This will first try user password and then owner password.
 * Owner have full access to the document while user don't
 *
 * @return true if succeed, false if failed
 */
bool Document::authPassword(const QString &password)
{
    return fz_authenticate_password(d->context, d->document,
            password.toLocal8Bit().data());
}

/**
 * @brief Get number of pages. Return -1 when error occurs
 */
int Document::numPages() const
{
    int ret = -1;
    fz_try(d->context)
    {
        ret = fz_count_pages(d->context, d->document);
    }
    fz_catch(d->context)
    {
        ret = -1;
    }
    return ret;
}

/**
 * @brief Get a page.
 *
 * @param index page index, begin with 0
 *
 * @return You need delete this manually when it's useless.
 */
Page * Document::page(int index) const
{
    PagePrivate *pagep;
    Page *page;

    // Create PagePrivate
    pagep = new PagePrivate(d, index);
    if (!pagep)
        return NULL;
    else if (!pagep->page) {
        delete pagep;
        return NULL;
    }

    // Create Page
    page = new Page(pagep);
    if (page)
        d->pages << pagep;
    return page;
}

/**
 * @brief The root outline of the document.
 *
 * @return Return NULL if there is no outline.
 *
 * @note Delete the returned pointer when it's useless.
 */
Outline * Document::outline() const
{
    fz_outline *o;
    OutlinePrivate *outlinep;
    
    o = fz_load_outline(d->context, d->document);
    if (o) {
        outlinep = new OutlinePrivate(d, o);
        d->outlines << outlinep;
        return new Outline(outlinep);
    }

    return NULL;
}

/**
 * @brief PDF version number, for example: 1.7
 */
QString Document::pdfVersion() const
{
    pdf_document *xref = (pdf_document *)d->document;
    return QString::number(xref->version / 10.0f);
}

/**
 * @brief PDF title
 */
QString Document::title() const
{
    return d->info("Title");
}

/**
 * @brief Author of the document
 */
QString Document::author() const
{
    return d->info("Author");
}

/**
 * @brief The subject of the document
 */
QString Document::subject() const
{
    return d->info("Subject");
}

/**
 * @brief Keywords associated with the document
 */
QString Document::keywords() const
{
    return d->info("Keywords");
}

/**
 * @brief If the document was converted to PDF from another format, the name of the application (for example, Adobe FrameMaker®) that created the original document from which it was converted
 */
QString Document::creator() const
{
    return d->info("Creator");
}

/**
 * @brief If the document was converted to PDF from another format, the name of the application (for example, Acrobat Distiller) that converted it to PDF
 */
QString Document::producer() const
{
    return d->info("Producer");
}

/**
 * @brief The date and time the document was created
 */
QDateTime Document::creationDate() const
{
    QString str = d->info("CreationDate");
    if (str.isEmpty()) {
        return QDateTime();
    }
    // see pdf_reference_1.7.pdf 2.8.3 Dates
    return QDateTime::fromString(str.left(16),
            "'D:'yyyyMMddHHmmss");
}

/**
 * @brief The date and time the document was most recently modified
 */
QDateTime Document::modDate() const
{
    QString str = d->info("ModDate");
    if (str.isEmpty()) {
        return QDateTime();
    }
    // see pdf_reference_1.7.pdf 2.8.3 Dates
    return QDateTime::fromString(str.left(16),
            "'D:'yyyyMMddHHmmss");
}

/**
 * @brief Set transparent rendering for all pages.
 * For one page transparent rendering setting,
 * use Page::setTransparentRendering() instead.
 *
 * @param enable True: transparent; False: not transparent(default).
 */
void Document::setTransparentRendering(bool enable)
{
    d->transparent = enable;
}

/**
 * @brief Set background color.
 * This function modify global setting of all pages.
 * For particular page setting, use Page::setBackgroundColor() instead.
 *
 * @note This function will only work when page is not transparent.
 * This function won't change content of your file, it only change
 * the way you render the page.
 *
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel(default with non transparent)
 */
void Document::setBackgroundColor(int r, int g, int b, int a)
{
    d->r = r;
    d->g = g;
    d->b = b;
    d->a = a;
}

DocumentPrivate::~DocumentPrivate()
{
    for (OutlinePrivate *outlinep : outlines) {
        outlinep->deleteData();
    }
    for (PagePrivate *pagep : pages) {
        pagep->deleteData();
    }

    deleteData();
}

} // end namespace MuPDF
