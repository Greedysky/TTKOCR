#include "mupdf-outline.h"
#include "mupdf-outline_p.h"
#include "mupdf-link.h"
#include "mupdf-link_p.h"
#include "mupdf-document_p.h"
#include <QString>

namespace MuPDF
{

Outline::Outline(OutlinePrivate *outlinep)
    : d(outlinep)
{

}

Outline::~Outline()
{
    delete d;
}

OutlinePrivate::OutlinePrivate(DocumentPrivate *dp, fz_outline *o)
    : documentp(dp), context(documentp->context), outline(o)
{

}

OutlinePrivate::~OutlinePrivate()
{
    if (outline) {
        deleteData();
        documentp->outlines.removeAt(documentp->outlines.indexOf(this));
    }
}

/**
 * @brief Top level item.
 */
OutlineItem Outline::topLevelItem() const
{
    OutlineItemPrivate *itemp = new OutlineItemPrivate(d->outline);
    return OutlineItem(itemp);
}

OutlineItem::OutlineItem()
    : d(nullptr)
{

}

/**
 * @brief Constructor.
 *
 * @param itemp if NULL, a invalid outline item will be constructed
 */
OutlineItem::OutlineItem(OutlineItemPrivate *itemp)
    : d(itemp)
{

}

OutlineItem::OutlineItem(const OutlineItem &item)
{
    if (item.isValid()) {
        d = new OutlineItemPrivate(item.d->outline);
    } else {
        d = nullptr;
    }
}

OutlineItem & OutlineItem::operator=(const OutlineItem &item)
{
    delete d;
    if (item.isValid()) {
        d = new OutlineItemPrivate(item.d->outline);
    } else {
        d = nullptr;
    }
    return *this;
}

OutlineItem::~OutlineItem()
{
    delete d;
}

OutlineItemPrivate::OutlineItemPrivate(fz_outline *o)
    : outline(o)
{
    LinkPrivate *linkp = new LinkPrivate(outline->dest);

    switch (outline->dest.kind) {
    case FZ_LINK_NONE:
        link = new MuPDF::Link(linkp);
        break;
        
    case FZ_LINK_GOTO:
        link = new MuPDF::LinkGoto(linkp);
        break;

    case FZ_LINK_URI:
        link = new MuPDF::LinkURI(linkp);
        break;

    case FZ_LINK_LAUNCH:
        link = new MuPDF::LinkLaunch(linkp);
        break;

    case FZ_LINK_NAMED:
        link = new MuPDF::LinkNamed(linkp);
        break;

    case FZ_LINK_GOTOR:
        link = new MuPDF::LinkGotoR(linkp);
        break;

    default:
        link = nullptr;
        delete linkp;
        break;
    }
}

OutlineItemPrivate::~OutlineItemPrivate()
{
    delete link;
}

/**
 * @brief Whether this item is valid or not.
 */
bool OutlineItem::isValid() const
{
    return d ? true : false;
}

/**
 * @brief Title.
 *
 * @note The OutlineItem MUST be valid.
 * @sa isValid()
 */
QString OutlineItem::title() const
{
    return d->outline->title;
}

/**
 * @brief Link.
 *
 * @note Do not delete the returned pointer. It will be
 *       deleted automatically when OutlineItem is deleted.
 * @note The OutlineItem MUST be valid.
 * @sa isValid()
 */
Link * OutlineItem::link() const
{
    return d->link;
}

/**
 * @brief The next outline item.
 *
 * @return a invalid outline item if there is no next outline item
 *
 * @note The OutlineItem MUST be valid.
 * @sa isValid()
 */
OutlineItem OutlineItem::next() const
{
    fz_outline *outline = d->outline->next;
    OutlineItemPrivate *itemp = nullptr;

    if (outline) {
        itemp = new OutlineItemPrivate(outline);
    }

    return OutlineItem(itemp);
}

/**
 * @brief The down outline item.
 *
 * @return a invalid outline item if there is no down outline item
 *
 * @note The OutlineItem MUST be valid.
 * @sa isValid()
 */
OutlineItem OutlineItem::down() const
{
    fz_outline *outline = d->outline->down;
    OutlineItemPrivate *itemp = nullptr;

    if (outline) {
        itemp = new OutlineItemPrivate(outline);
    }

    return OutlineItem(itemp);
}

}
