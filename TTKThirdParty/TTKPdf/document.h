#ifndef MUPDF_DOCUMENT_H
#define MUPDF_DOCUMENT_H

#include <QImage>
#include <QDateTime>

namespace MuPDF
{
class Page;
class Private;

class Document
{
public:
    /**
     * @brief Load a document.
     * @param filePath document path
     * @return NULL if failed (Note: you need delete manually when it's useless)
     */
    Document(const QString &path);
    /**
     * @brief Load a document.
     * @param bytes document data
     * @return NULL if failed (Note: you need delete manually when it's useless)
     */
    Document(const QByteArray &bytes);
    /**
     * @brief Destructor
     */
    ~Document();

    /**
     * @brief Document is valid or not.
     */
    bool valid() const;

    /**
     * @brief Whether the document needs password
     */
    bool needsPassword() const;
    /**
     * @brief Authenticate password
     * @param password User password or owner password
     * This will first try user password and then owner password.
     * Owner have full access to the document while user don't
     * @return true if succeed, false if failed
     */
    bool authPassword(const QString &password);

    /**
     * @brief Get number of pages. Return -1 when error occurs
     */
    int numPages() const;
    /**
     * @brief Get a page.
     * @param index page index, begin with 0
     * @return You need delete this manually when it's useless.
     */
    Page *page(int index);

    /**
     * @brief PDF version number, for example: 1.7
     */
    QString pdfVersion() const;
    /**
     * @brief PDF title
     */
    QString title() const;
    /**
     * @brief Author of the document
     */
    QString author() const;
    /**
     * @brief The subject of the document
     */
    QString subject() const;
    /**
     * @brief Keywords associated with the document
     */
    QString keywords() const;
    /**
     * @brief If the document was converted to PDF from another format, the name of the application (for example, Adobe FrameMaker®) that created the original document from which it was converted
     */
    QString creator() const;
    /**
     * @brief If the document was converted to PDF from another format, the name of the application (for example, Acrobat Distiller) that converted it to PDF
     */
    QString producer() const;

    /**
     * @brief The date and time the document was most recently modified
     */
    QDateTime modDate() const;
    /**
     * @brief The date and time the document was created
     */
    QDateTime creationDate() const;

private:
    // disable copy
    Document(const Document &);
    Document &operator=(const Document &);

private:
    Private *d;
};


class Page
{
public:
    Page(Private *ptr);

    /**
     * @brief Render page to QImage
     * @param scaleX scale for X direction (Default value: 1.0f; >1.0f: zoom in; <1.0f: zoom out)
     * @param scaleY scale for Y direction (Default value: 1.0f; >1.0f: zoom in; <1.0f: zoom out)
     * @param rotation degree of clockwise rotation (Range: [0.0f, 360.0f))
     * @return This function will return a empty QImage if failed.
     */
    QImage renderImage(float x = 1.0f, float y = 1.0f, float r = 0.0f) const;

private:
    Private *d;
};
}

#endif
