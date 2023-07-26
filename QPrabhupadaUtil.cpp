/***********************************************************************
*
* Copyright (c) 2012-2022 Barbara Geller
* Copyright (c) 2012-2022 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include <QtCore>
#include "QPrabhupadaUtil.h"

void PrabhupadaMessage( const QString &msg )
{
   QMessageBox msgB;

   msgB.setWindowTitle( "Jaya Shrila Prabhupada!" );
   msgB.setWindowIcon( QIcon( ":/Icon/resources/PrabhupadaDictionary.ico" ) );
   msgB.setIcon( QMessageBox::Information );

   msgB.setText( msg );
   msgB.exec();
}

void PrabhupadaMessage( QWidget *parent, const QString &title, const QString &msg )
{
   QMessageBox msgB( parent );

   if ( parent != nullptr )
      msgB.setWindowModality( Qt::WindowModal );


   msgB.setWindowTitle( title );
   msgB.setWindowIcon( QIcon( ":/Icon/resources/PrabhupadaDictionary.ico" ) );
   msgB.setIcon( QMessageBox::Information );

   msgB.setText( msg );
   msgB.exec();
}

void PrabhupadaLog( const QString &AFileName, const QString &msg )
{
  QSaveFile ASaveFile = QSaveFile( AFileName );
  QDataStream  AStream = QDataStream( &ASaveFile );
  ASaveFile.open( QIODevice::WriteOnly /*| QIODevice::Append*/ );

  QString S = QDateTime::currentDateTime().toString( "dd/MM/yyyy hh:mm:ss:zzz " ) + msg + "\n";
  ASaveFile.seek( ASaveFile.size() );
  AStream << S;

  ASaveFile.commit();
}
