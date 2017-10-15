#ifndef MUPDF_LINK_H
#define MUPDF_LINK_H

class QRectF;
class QString;

namespace MuPDF
{

class LinkPrivate;

class Link
{
public:
    enum LinkType
    {
        None = 0,
        Goto, ///< Goto a position in current file
        URI, ///< A URI link
        Launch, ///< Launch a file (a document or a executable)
        Named, ///< Named action to perform
        GotoR ///< Goto a position in another file
    };

    virtual ~Link();

    virtual LinkType linkType() const {return None;}
    virtual QRectF linkArea() const;

protected:
    Link(LinkPrivate *linkp) : d(linkp) {}

    LinkPrivate *d;

friend class OutlineItemPrivate;
};

/**
 * @brief Goto a position in current file.
 */
class LinkGoto : public Link
{
public:
    LinkType linkType() const {return Goto;}
    int page() const;
    bool fitHorizontally() const;
    bool fitVertically() const;
    float zoom() const;

protected:
    LinkGoto(LinkPrivate *linkp) : Link(linkp) {}

friend class OutlineItemPrivate;
};

/**
 * @brief A URI link.
 */
class LinkURI : public Link
{
public:
    LinkType linkType() const {return URI;}
    QString uri() const;
    bool isMap() const;

private:
    LinkURI(LinkPrivate *linkp) : Link(linkp) {}

friend class OutlineItemPrivate;
};

/**
 * @brief Launch a file (a document or a executable).
 */
class LinkLaunch : public Link
{
public:
    LinkType linkType() const {return Launch;}
    QString file() const;
    bool newWindow() const;
    bool isURI() const;

private:
    LinkLaunch(LinkPrivate *linkp) : Link(linkp) {}
    
friend class OutlineItemPrivate;
};

/**
 * @brief Named action to perform.
 */
class LinkNamed : public Link
{
public:
    LinkType linkType() const {return Named;}
    QString named() const;
    
private:
    LinkNamed(LinkPrivate *linkp) : Link(linkp) {}

friend class OutlineItemPrivate;
};

/**
 * @brief Goto a position in another file.
 */
class LinkGotoR : public LinkGoto
{
public:
    LinkType linkType() const {return GotoR;}
    int page() const;
    QString destination() const;
    QString file() const;
    bool newWindow() const;

private:
    LinkGotoR(LinkPrivate *linkp) : LinkGoto(linkp) {}

friend class OutlineItemPrivate;
};

}

#endif // end MUPDF_LINK_H
