/***************************************************************************
    qgscheckboxconfigdlg.cpp
     --------------------------------------
    Date                 : 5.1.2014
    Copyright            : (C) 2014 Matthias Kuhn
    Email                : matthias at opengis dot ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgscheckboxconfigdlg.h"

QgsCheckBoxConfigDlg::QgsCheckBoxConfigDlg( QgsVectorLayer* vl, int fieldIdx, QWidget *parent )
    : QgsEditorConfigWidget( vl, fieldIdx, parent )
{
  setupUi( this );

  connect( leCheckedState, SIGNAL( textEdited( QString ) ), this, SIGNAL( changed() ) );
  connect( leUncheckedState, SIGNAL( textEdited( QString ) ), this, SIGNAL( changed() ) );
}

QgsEditorWidgetConfig QgsCheckBoxConfigDlg::config()
{
  QgsEditorWidgetConfig cfg;

  cfg.insert( QStringLiteral( "CheckedState" ), leCheckedState->text() );
  cfg.insert( QStringLiteral( "UncheckedState" ), leUncheckedState->text() );

  return cfg;
}

void QgsCheckBoxConfigDlg::setConfig( const QgsEditorWidgetConfig& config )
{
  leCheckedState->setText( config.value( QStringLiteral( "CheckedState" ) ).toString() );
  leUncheckedState->setText( config.value( QStringLiteral( "UncheckedState" ) ).toString() );
}
