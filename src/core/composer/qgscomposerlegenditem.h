/***************************************************************************
                         qgscomposerlegenditem.h  -  description
                         ------------------------
    begin                : May 2010
    copyright            : (C) 2010 by Marco Hugentobler
    email                : marco dot hugentobler at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSCOMPOSERLEGENDITEM_H
#define QGSCOMPOSERLEGENDITEM_H

#include "qgscomposerlegendstyle.h"
#include <QStandardItem>
class QDomDocument;
class QDomElement;

/** \ingroup core
 * Abstract base class for the legend item types
*/
class CORE_EXPORT QgsComposerLegendItem: public QStandardItem
{
  public:
    QgsComposerLegendItem( QgsComposerLegendStyle::Style s = QgsComposerLegendStyle::Undefined );
    QgsComposerLegendItem( const QString& text, QgsComposerLegendStyle::Style s = QgsComposerLegendStyle::Undefined );
    QgsComposerLegendItem( const QIcon& icon, const QString& text, QgsComposerLegendStyle::Style s = QgsComposerLegendStyle::Undefined );
    virtual ~QgsComposerLegendItem();

    enum ItemType
    {
      GroupItem = QStandardItem::UserType,
      LayerItem,
      SymbologyV2Item,
      RasterSymbolItem,
      StyleItem
    };

    virtual void writeXml( QDomElement& elem, QDomDocument& doc ) const = 0;
    /** Read item content from xml
      @param itemElem item to read from
      @param xServerAvailable Read item icons if true (QIcon needs x-server)*/
    virtual void readXml( const QDomElement& itemElem, bool xServerAvailable = true ) = 0;

    virtual ItemType itemType() const = 0;
    virtual QStandardItem* clone() const override = 0;

    QgsComposerLegendStyle::Style style() const { return mStyle; }
    void setStyle( QgsComposerLegendStyle::Style style ) { mStyle = style; }

    // Get text defined by user
    virtual QString userText() const { return mUserText; }
    // Set text defined by user
    virtual void setUserText( const QString & text ) { mUserText = text; }

  protected:
    void writeXmlChildren( QDomElement& elem, QDomDocument& doc ) const;

    QgsComposerLegendStyle::Style mStyle;

    // User defined text
    QString mUserText;
};


class QgsSymbol;

/** \ingroup core
 * \class QgsComposerSymbolItem
 */
class CORE_EXPORT QgsComposerSymbolItem: public QgsComposerLegendItem
{
  public:
    QgsComposerSymbolItem();
    QgsComposerSymbolItem( const QString& text );
    QgsComposerSymbolItem( const QIcon& icon, const QString& text );
    virtual ~QgsComposerSymbolItem();

    virtual QStandardItem* clone() const override;

    virtual void writeXml( QDomElement& elem, QDomDocument& doc ) const override;
    virtual void readXml( const QDomElement& itemElem, bool xServerAvailable = true ) override;

    //! Set symbol (takes ownership)
    void setSymbol( QgsSymbol* s );
    QgsSymbol* symbol() {return mSymbol;}

    ItemType itemType() const override { return SymbologyV2Item; }

  private:
    QgsSymbol* mSymbol;
};

/** \ingroup core
 * \class QgsComposerRasterSymbolItem
 */
class CORE_EXPORT QgsComposerRasterSymbolItem : public QgsComposerLegendItem
{
  public:
    QgsComposerRasterSymbolItem();
    QgsComposerRasterSymbolItem( const QString& text );
    QgsComposerRasterSymbolItem( const QIcon& icon, const QString& text );
    virtual ~QgsComposerRasterSymbolItem();

    virtual QStandardItem* clone() const override;

    virtual void writeXml( QDomElement& elem, QDomDocument& doc ) const override;
    virtual void readXml( const QDomElement& itemElem, bool xServerAvailable = true ) override;

    void setLayerId( const QString& id ) { mLayerID = id; }
    QString layerId() const { return mLayerID; }
    ItemType itemType() const override { return RasterSymbolItem; }

    void setColor( const QColor& c ) { mColor = c; }
    QColor color() const { return mColor; }

  private:
    QString mLayerID;
    QColor mColor;
};

/** \ingroup core
 * \class QgsComposerLayerItem
 */
class CORE_EXPORT QgsComposerLayerItem : public QgsComposerLegendItem
{
  public:
    QgsComposerLayerItem();
    QgsComposerLayerItem( const QString& text );
    virtual ~QgsComposerLayerItem();
    virtual QStandardItem* clone() const override;

    virtual void writeXml( QDomElement& elem, QDomDocument& doc ) const override;
    virtual void readXml( const QDomElement& itemElem, bool xServerAvailable = true ) override;

    ItemType itemType() const override { return LayerItem; }

    /**
     * Sets the associated layer ID.
     * @see layerId()
     */
    void setLayerId( const QString& id ) { mLayerID = id; }

    /**
     * Returns the ID of the associated layer.
     * @see setLayerId()
     */
    QString layerId() const { return mLayerID; }

    void setShowFeatureCount( bool show ) { mShowFeatureCount = show; }
    bool showFeatureCount() const { return mShowFeatureCount; }

    void setDefaultStyle( double scaleDenominator = -1, const QString& rule = "" );

  private:
    QString mLayerID;
    // Show vector feature counts
    bool mShowFeatureCount;
};

/** \ingroup core
 * \class QgsComposerGroupItem
 */
class CORE_EXPORT QgsComposerGroupItem: public QgsComposerLegendItem
{
  public:
    QgsComposerGroupItem();
    QgsComposerGroupItem( const QString& text );
    virtual ~QgsComposerGroupItem();
    virtual QStandardItem* clone() const override;

    virtual void writeXml( QDomElement& elem, QDomDocument& doc ) const override;
    virtual void readXml( const QDomElement& itemElem, bool xServerAvailable = true ) override;

    ItemType itemType() const override { return GroupItem; }
};

/** \ingroup core
 * \class QgsComposerStyleItem
 */
class CORE_EXPORT QgsComposerStyleItem: public QStandardItem
{
  public:
    QgsComposerStyleItem();
    QgsComposerStyleItem( QgsComposerLegendItem *item );
    ~QgsComposerStyleItem();
};

#endif // QGSCOMPOSERLEGENDITEM_H
