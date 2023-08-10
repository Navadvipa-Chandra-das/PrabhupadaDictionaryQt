#include "QPrabhupadaLoginDialog.h"
// #include "QPrabhupadaUtil.h"
#include "QPrabhupada.h"
#include "ui_QPrabhupadaLoginDialog.h"

QPrabhupadaLoginDialog::QPrabhupadaLoginDialog( QPrabhupadaDictionary *APrabhupadaDictionary
                                            , QWidget *parent )
    : inherited( parent )
    , m_PrabhupadaDictionary( APrabhupadaDictionary )
    /*, m_ui ( new Ui::QPrabhupadaLoginDialog )*/
{
    m_ui->setupUi( this );

    Connects();
    Emits();
}

QPrabhupadaLoginDialog::~QPrabhupadaLoginDialog()
{
    delete m_ui;
}

void QPrabhupadaLoginDialog::Connects()
{
  QObject::connect( m_ui->radioButtonSQLite
                  , &QAbstractButton::toggled
                  , this
                  , &QPrabhupadaLoginDialog::SQLRadioButton );
  m_ui->radioButtonSQLite->setChecked( true );

  QObject::connect( m_ui->ComboBoxLanguageUI
                  // , ( void ( QComboBox::* )( int ) )( QComboBox::currentIndexChanged )
                  , &QComboBox::currentIndexChanged
                  , &m_PrabhupadaDictionary->m_LanguageUIIndex
                  , &QLanguageIndex::SetValue );
  QObject::connect( &m_PrabhupadaDictionary->m_LanguageUIIndex
                  , &QLanguageIndex::SignalValueChanged
                  , this
                  , &QPrabhupadaLoginDialog::LanguageUI_IndexChanged );
  QObject::connect( m_ui->pushButtonOK
                  , &QPushButton::clicked
                  , this
                  , &QPrabhupadaLoginDialog::pushButtonOKClicked );
  QObject::connect( m_ui->pushButtonCancel
                  , &QPushButton::clicked
                  , this
                  , &QPrabhupadaLoginDialog::pushButtonCancelClicked );
}

void QPrabhupadaLoginDialog::Emits()
{
  m_PrabhupadaDictionary->m_LanguageUIIndex.EmitValueChanged();
}

void QPrabhupadaLoginDialog::LoadFromStream( QDataStream &ST )
{
  inherited::LoadFromStream( ST );
  // 1
  QStorage::LoadFromStream( m_ui->ComboBoxUserName, ST );
  // 2
  QStorage::LoadFromStream( m_ui->ComboBoxDatabaseName, ST );
  // 3
  QStorage::LoadFromStream( m_ui->ComboBoxHostName, ST );
  // 4
  QStorage::LoadFromStream( m_ui->ComboBoxPort, ST );
  // 5
  QStorage::LoadFromStream( m_ui->ComboBoxSchema, ST );
  // 6
  bool B;
  ST >> B;
  if ( B ) {
    m_ui->radioButtonSQLite->setChecked( true );
  } else {
    m_ui->radioButtonPostgreSQL->setChecked( true );
  }
}

void QPrabhupadaLoginDialog::SaveToStream( QDataStream &ST )
{
  inherited::SaveToStream( ST );
  // 1
  QStorage::SaveToStream( m_ui->ComboBoxUserName, ST );
  // 2
  QStorage::SaveToStream( m_ui->ComboBoxDatabaseName, ST );
  // 3
  QStorage::SaveToStream( m_ui->ComboBoxHostName, ST );
  // 4
  QStorage::SaveToStream( m_ui->ComboBoxPort, ST );
  // 5
  QStorage::SaveToStream( m_ui->ComboBoxSchema, ST );
  // 6
  ST << m_ui->radioButtonSQLite->isChecked();
}

void QPrabhupadaLoginDialog::pushButtonOKClicked()
{
  accept();
}

void QPrabhupadaLoginDialog::pushButtonCancelClicked()
{
  reject();
}

void QPrabhupadaLoginDialog::changeEvent( QEvent *event )
{
  if ( event->type() == QEvent::LanguageChange ) {
    m_ui->retranslateUi( this );
  }

  inherited::changeEvent( event );
}

void QPrabhupadaLoginDialog::DatabaseToWidget( QSqlDatabase *DB )
{
  m_ui->ComboBoxUserName    ->setEditText( DB->userName() );
  m_ui->ComboBoxDatabaseName->setEditText( DB->databaseName() );
  m_ui->ComboBoxHostName    ->setEditText( DB->hostName() );
  m_ui->ComboBoxPort        ->setEditText( QString::number( DB->port() ) );
}

void QPrabhupadaLoginDialog::WidgetToDatabase( QSqlDatabase *DB )
{
  DB->setUserName( m_ui->ComboBoxUserName->currentText () );
  DB->setPassword( m_ui->LineEditPassword->text() );
  if ( m_ui->radioButtonSQLite->isChecked() ) {
    DB->setDatabaseName( QPrabhupadaDictionary::PrabhupadaDictionaryFiles + "Sanskrit.db" );
  } else {
    DB->setDatabaseName( m_ui->ComboBoxDatabaseName->currentText() );
  }
  DB->setHostName( m_ui->ComboBoxHostName->currentText() );
  DB->setPort( m_ui->ComboBoxPort->currentText().toInt() );
}

void QPrabhupadaLoginDialog::SQLRadioButton( bool checked )
{
  m_ui->LabelUserName       ->setEnabled( !checked );
  m_ui->LabelPassword       ->setEnabled( !checked );
  m_ui->LabelDatabaseName   ->setEnabled( !checked );
  m_ui->LabelHostName       ->setEnabled( !checked );
  m_ui->LabelPort           ->setEnabled( !checked );
  m_ui->LabelSchema         ->setEnabled( !checked );

  m_ui->ComboBoxUserName    ->setEnabled( !checked );
  m_ui->LineEditPassword    ->setEnabled( !checked );
  m_ui->ComboBoxDatabaseName->setEnabled( !checked );
  m_ui->ComboBoxHostName    ->setEnabled( !checked );
  m_ui->ComboBoxPort        ->setEnabled( !checked );
  m_ui->ComboBoxSchema      ->setEnabled( !checked );

  if ( checked ) {
    m_DriverName = "QSQLITE";
    m_Schema = "";
  } else {
    m_DriverName = "QPSQL";
    m_Schema = m_ui->ComboBoxSchema->currentText() + ".";
  }
}

bool QPrabhupadaLoginDialog::Connect( QSqlDatabase *DB )
{
  WidgetToDatabase( DB );
  bool B = DB->open();
  return B;
}

void QPrabhupadaLoginDialog::LanguageUI_IndexChanged( int Value )
{
  m_ui->ComboBoxLanguageUI->setCurrentIndex( Value );
}
