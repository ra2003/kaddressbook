/*                                                                      
    This file is part of KAddressBook.                                  
    Copyright (c) 2002 Tobias Koenig <tokoe@kde.org>                   
                                                                        
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or   
    (at your option) any later version.                                 
                                                                        
    This program is distributed in the hope that it will be useful,     
    but WITHOUT ANY WARRANTY; without even the implied warranty of      
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the        
    GNU General Public License for more details.                        
                                                                        
    You should have received a copy of the GNU General Public License   
    along with this program; if not, write to the Free Software         
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.           
                                                                        
    As a special exception, permission is given to link this program    
    with any edition of Qt, and distribute the resulting executable,    
    without including the source code for Qt in the source distribution.
*/                                                                      

#ifndef GEOWIDGET_H
#define GEOWIDGET_H

namespace KABC {
class Geo;
}

class GeoMapWidget;

class KComboBox;
class KDoubleSpinBox;

class QLabel;
class QSpinBox;

#include <qwidget.h>

class GeoWidget : public QWidget
{
  Q_OBJECT

  public:
    GeoWidget( QWidget *parent, const char *name = 0 );
    ~GeoWidget();

    /**
      Sets the geo object.
     */
    void setGeo( const KABC::Geo &geo );

    /**
      Returns a geo object.
     */
    KABC::Geo geo();

  signals:
    void changed();

  private slots:
    void updateInputs();

    void decimalInputChanged();
    void sexagesimalInputChanged();
    void geoMapChanged();

  private:
    GeoMapWidget *mMapWidget;

    KDoubleSpinBox *mLatitudeBox;
    KDoubleSpinBox *mLongitudeBox;

    QSpinBox *mLatDegrees;
    QSpinBox *mLatMinutes;
    QSpinBox *mLatSeconds;
    KComboBox *mLatDirection;

    QSpinBox *mLongDegrees;
    QSpinBox *mLongMinutes;
    QSpinBox *mLongSeconds;
    KComboBox *mLongDirection;

    double mLatitude;
    double mLongitude;
};

class GeoMapWidget : public QWidget
{
  Q_OBJECT

  public:
    GeoMapWidget( QWidget *parent, const char *name = 0 );
    ~GeoMapWidget();

    void setLatitude( double latitude );
    double latitude();

    void setLongitude( double longitude );
    double longitude();

  signals:
    void changed();
    
  protected:
    virtual void mousePressEvent( QMouseEvent* );
    virtual void paintEvent( QPaintEvent* );

  private:
    double mLatitude;
    double mLongitude;
};

#endif
