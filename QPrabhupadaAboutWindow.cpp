/***********************************************************************
*
* Copyright (c) 2022-2022 Navadvipa Chandra dasa
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "QPrabhupadaAboutWindow.h"
#include "QPrabhupadaUtil.h"

QPrabhupadaAboutWindow::QPrabhupadaAboutWindow( QStorage *AStorage )
  : inherited()
  , m_Storage( AStorage )
{
  m_ui->setupUi( this );
}

QPrabhupadaAboutWindow::~QPrabhupadaAboutWindow()
{
  delete m_ui;
}

void QPrabhupadaAboutWindow::LoadFromStream( QDataStream &ST )
{
  inherited::LoadFromStream( ST );

  QStorage::LoadFromStream( m_ui->ComboBoxRowNumber, ST );
}

void QPrabhupadaAboutWindow::SaveToStream( QDataStream &ST )
{
  inherited::SaveToStream( ST );

  QStorage::SaveToStream( m_ui->ComboBoxRowNumber, ST );
}

void QPrabhupadaAboutWindow::changeEvent( QEvent *event )
{
  if ( event->type() == QEvent::LanguageChange ) {
    m_ui->retranslateUi( this );
  }

  inherited::changeEvent( event );
}
