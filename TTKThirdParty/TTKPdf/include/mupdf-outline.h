#ifndef MUPDF_OUTLINE_H
#define MUPDF_OUTLINE_H

class QString;

namespace MuPDF
{

class Outline;
class OutlinePrivate;
class OutlineItem;
class OutlineItemPrivate;
class Link;

/**
 * @brief A tree of the outline of a document (also known
 *        as table of contents).
 */
class Outline
{
public:
    ~Outline();

    OutlineItem topLevelItem() const;

private:
    Outline(OutlinePrivate *outlinep);

    OutlinePrivate *d;

friend class Document;
};

/**
 * @brief A outline item.
 */
class OutlineItem
{
public:
    OutlineItem();
    OutlineItem(const OutlineItem &item);
    OutlineItem & operator=(const OutlineItem &item);
    ~OutlineItem();

    bool isValid() const;
    QString title() const;
    Link * link() const;
    OutlineItem next() const;
    OutlineItem down() const;

private:
    OutlineItem(OutlineItemPrivate *itemp);

    OutlineItemPrivate *d;

friend class Outline;
};

}

#endif // end MUPDF_OUTLINE_H
