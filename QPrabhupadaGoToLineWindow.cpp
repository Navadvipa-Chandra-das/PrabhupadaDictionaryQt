
#include "QPrabhupadaGoToLineWindow.h"
//#include "QPrabhupadaUtil.h"

QPrabhupadaGoToLineWindow::QPrabhupadaGoToLineWindow( QStorage *AStorage )
  : inherited()
  , m_Storage( AStorage )
{
  m_ui->setupUi( this );
  QObject::connect( m_ui->PushButtonGo
                  , &QPushButton::clicked
                  , this
                  , &QPrabhupadaGoToLineWindow::PushButtonGoClicked );
  QObject::connect( m_ui->PushButtonCancel
                  , &QPushButton::clicked
                  , this
                  , &QPrabhupadaGoToLineWindow::PushButtonCancelClicked );
}

QPrabhupadaGoToLineWindow::~QPrabhupadaGoToLineWindow()
{
  delete m_ui;
}

void QPrabhupadaGoToLineWindow::LoadFromStream( QDataStream &ST )
{
  inherited::LoadFromStream( ST );

  QStorage::LoadFromStream( m_ui->ComboBoxRowNumber, ST );
}

void QPrabhupadaGoToLineWindow::SaveToStream( QDataStream &ST )
{
  inherited::SaveToStream( ST );

  QStorage::SaveToStream( m_ui->ComboBoxRowNumber, ST );
}

void QPrabhupadaGoToLineWindow::changeEvent( QEvent *event )
{
  if ( event->type() == QEvent::LanguageChange ) {
    m_ui->retranslateUi( this );
  }

  inherited::changeEvent( event );
}

void QPrabhupadaGoToLineWindow::PushButtonGoClicked()
{
  accept();
  emit SignalGoToLine( m_ui->ComboBoxRowNumber->currentText().toInt() );
}

void QPrabhupadaGoToLineWindow::PushButtonCancelClicked()
{
  reject();
}
