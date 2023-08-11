#include "QPrabhupada.h"

QMapMemoryStorage::QMapMemoryStorage()
  : inherited()
{
}

QMapMemoryStorage::~QMapMemoryStorage()
{
}

void QMapMemoryStorage::LoadFromStream( QDataStream& ST )
{
  clear();
  // 1
  std::size_t L;
  ST >> L;
  // 2
  QString AFileName;
  QByteArray *BA;
  QBuffer    *BU;
  for ( std::size_t I = 0; I < L; ++I ) {
    BA = new QByteArray();
    BU = new QBuffer( BA );

    ST >> AFileName;
    ST >> *BA;

    if ( BU->open( QIODevice::ReadWrite ) ) {
      emplace( std::make_pair( AFileName, std::make_unique< QDataStream >( BU ) ) );
    }
  }
}

void QMapMemoryStorage::SaveToStream( QDataStream& ST )
{
  // 1
  ST << size();
  // 2
  QDataStream *AStream;
  QByteArray *BA;
  QBuffer    *BU;
  for ( iterator I = begin(); I != end(); ++I ) {
    ST << (*I).first;

    AStream = (*I).second.get();
    BU = static_cast< QBuffer* >( AStream->device() );
    BA = static_cast< QByteArray* >( &BU->buffer() );
    ST << *BA;
  }
}

QStorage::QStorage()
  : inherited()
{
}

QStorage::~QStorage()
{
  if ( m_Query != nullptr ) {
    delete m_Query;
  }
}

void QStorage::SetDatabase( QSqlDatabase *Value )
{
  if ( m_Database != Value ) {
    m_Database = Value;
    if ( m_Query != nullptr ) {
      delete m_Query;
    }
    m_Query = new QSqlQuery( *m_Database );
  }
}

bool QStorage::BeginLoad( QObject *O, QStorageKind AStorageKind )
{
  m_FileName = KeyStorage( O, AStorageKind );
  switch ( AStorageKind ) {
    case QStorageKind::File :
      m_File     = new QFile( m_FileName );
      m_Stream   = new QDataStream( m_File );
      return m_File->open( QIODevice::ReadOnly );
    case QStorageKind::DB :
      if ( m_Query != nullptr ) {
        m_Query->prepare( QString( "select\n"
                                   "  a.\"UserRegKey\"\n"
                                   ", a.\"UserData\"\n"
                                   "from\n"
                                   "    %1\"UserReg\" a\n"
                                   "where a.\"UserRegKey\" = :UserRegKey;" ).arg( m_Schema ) );
        m_Query->bindValue( ":UserRegKey", m_FileName );
        m_Query->exec();
        if ( m_Query->next() ) {
          m_Stream = new QDataStream( m_Query->value( 1 ).toByteArray() );
          return true;
        } else {
          return false;
        }
      }
      break;
    case QStorageKind::Memory :
      QMapMemoryStorage::iterator I = m_MapMemoryStorage.find( m_FileName );
      if ( I != m_MapMemoryStorage.end() ) {
        m_Stream = m_MapMemoryStorage[ m_FileName ].get();
        m_Stream->device()->seek( 0 );
        return true;
      } else {
        return false;
      }
  }
  return false;
}

void QStorage::EndLoad( QStorageKind AStorageKind )
{
  switch ( AStorageKind ) {
    case QStorageKind::File :
      m_File->close();
      delete m_Stream;
      delete m_File;
      m_File   = nullptr;
      break;
    case QStorageKind::DB :
      delete m_Stream;
      m_Query->clear();
      break;
    case QStorageKind::Memory :
      break;
  }
  m_Stream = nullptr;
}

void QStorage::BeginSave( QObject *O, QStorageKind AStorageKind )
{
  QBuffer *BU;
  m_FileName = KeyStorage( O, AStorageKind );
  switch ( AStorageKind ) {
    case QStorageKind::File :
      m_SaveFile = new QSaveFile( m_FileName );
      if ( m_SaveFile->open( QIODevice::WriteOnly ) ) {
        m_Stream = new QDataStream( m_SaveFile );
      }
      break;
    case QStorageKind::DB :
      if ( m_Query != nullptr ) {
        m_Query->prepare( QString( "select\n"
                                  "  a.\"UserRegKey\"\n"
                                  "from\n"
                                  "    %1\"UserReg\" a\n"
                                  "where a.\"UserRegKey\" = :UserRegKey;" ).arg( m_Schema ) );
        m_Query->bindValue( ":UserRegKey", m_FileName );
        m_Query->exec();
        m_ByteArray = new QByteArray();
        BU = new QBuffer( m_ByteArray );
        if ( BU->open( QIODevice::ReadWrite ) ) {
          m_Stream = new QDataStream( BU );
          if ( m_Query->next() ) {
            m_SQL = QString( "update %1\"UserReg\"\n"
                            "set\n"
                            "  \"UserData\" = :UserData\n"
                            "where\n"
                            "    \"UserRegKey\" = :UserRegKey;" ).arg( m_Schema );
          } else {
            m_SQL = QString( "insert into %1\"UserReg\"\n"
                            "( \"UserRegKey\", \"UserData\" )\n"
                            "values\n"
                            "( :UserRegKey, :UserData );" ).arg( m_Schema );
          }
        }
      }
      break;
    case QStorageKind::Memory :
      QMapMemoryStorage::iterator I = m_MapMemoryStorage.find( m_FileName );
      QByteArray *BA;
      QBuffer    *BU;
      if ( I == m_MapMemoryStorage.end() ) {
        BA = new QByteArray();
        BU = new QBuffer( BA );
        if ( BU->open( QIODevice::ReadWrite ) ) {
          auto J = m_MapMemoryStorage.emplace( std::make_pair( m_FileName, std::make_unique< QDataStream >( BU ) ) );
          m_Stream = (*J.first).second.get();
        }
      } else {
        m_Stream = m_MapMemoryStorage[ m_FileName ].get();
        BU = static_cast< QBuffer* >( m_Stream->device() );
        BA = static_cast< QByteArray* >( &BU->buffer() );
        BU->seek( 0 );
        BA->truncate( 0 );
      }
      break;
  }
}

void QStorage::EndSave( QStorageKind AStorageKind )
{
  switch ( AStorageKind ) {
    case QStorageKind::File :
      m_SaveFile->commit();
      delete m_Stream;
      delete m_SaveFile;
      m_SaveFile = nullptr;
      break;
    case QStorageKind::DB :
      m_Query->clear();
      m_Query->prepare( m_SQL );
      m_Query->bindValue( ":UserRegKey", m_FileName );
      m_Query->bindValue( ":UserData", *m_ByteArray, QSql::In | QSql::Binary );
      m_Query->exec();

      delete m_Stream;
      break;
    case QStorageKind::Memory :
      break;
  }
  m_Stream = nullptr;
}

bool QStorage::LoadObject( QObject *O, QStorageKind AStorageKind )
{
  bool LoadSuccess = false, InvokeSuccess = false;
  if ( m_Enabled ) {

    if ( BeginLoad( O, AStorageKind ) ) {
      if ( m_Stream != nullptr ) {
        qint8 V;
        *m_Stream >> V;
        if ( V == m_Version ) {
          InvokeSuccess = QMetaObject::invokeMethod( O, "LoadFromStream", Q_ARG( QDataStream&, *m_Stream ) );
          *m_Stream >> V;
          if ( V == m_Version ) {
            LoadSuccess = true;
          }
        }
      }
    }
    EndLoad( AStorageKind );
  }
  return LoadSuccess && InvokeSuccess;
}

void QStorage::SaveObject( QObject *O, QStorageKind AStorageKind )
{
  if ( m_Enabled ) {
    BeginSave( O, AStorageKind );
    if ( m_Stream != nullptr ) {
      *m_Stream << m_Version;
      QMetaObject::invokeMethod( O, "SaveToStream", Q_ARG( QDataStream&, *m_Stream ) );
      *m_Stream << m_Version;
      EndSave( AStorageKind );
    }
  }
}

void QStorage::RemoveMemory( QObject *O )
{
  QString S = KeyStorage( O, QStorageKind::Memory );
  m_MapMemoryStorage.erase( S );
}

QString QStorage::PrefixKeyStorage()
{
  QString APrefix, AUserName;

  APrefix = qApp->objectName();
  if ( !APrefix.isEmpty() ) {
    APrefix += "-";
  }
  if ( m_Database != nullptr ) {
    AUserName = m_Database->userName();
    if ( !AUserName.isEmpty() ) {
      APrefix += AUserName + "-";
    }
  }

  return APrefix;
}

QString QStorage::KeyStorage( QObject *O, QStorageKind AStorageKind )
{
  QString R, S, APrefix;
  int i = 0;

  if ( AStorageKind == QStorageKind::DB ) {
    APrefix = PrefixKeyStorage();
  }

  while ( O != nullptr ) {
    S = O->objectName();
    if ( !S.isEmpty() ) {
      if ( R.isEmpty() )
        R = S;
      else
        R = S + "." + R;
    }

    O = O->parent();
    ++i;
  }

  if ( !R.isEmpty() )
    R += ".ini";

  if ( !APrefix.isEmpty() )
    R = APrefix + R;

  return R;
}

void QStorage::ResetSettings()
{
  m_Query->clear();
  m_Query->prepare( QString( "delete from %1\"UserReg\" where \"UserRegKey\" like :APrefix || '%';" ).arg( m_Schema ) );
  m_Query->bindValue( ":APrefix", PrefixKeyStorage() );
  m_Query->exec();
}

void QStorage::PrepareHistoryComboBox( QComboBox *CB, int MaxCount )
{
 if ( CB->isEditable() ) {
    QString S = CB->currentText();
    if ( !S.isEmpty() ) {
      int I = CB->findText( S );
      if ( I != -1 ) {
        QString SA = CB->itemText( I );
        CB->setItemText( I, CB->itemText( 0 ) );
        CB->setItemText( 0, SA );
      } else {
        CB->insertItem( 0, S );
      }
      for ( I = CB->count() - 1; I >= MaxCount; --I ) {
        CB->removeItem( I );
      }
      CB->setCurrentIndex( 0 );
    }
  }
}

void QStorage::LoadFromStream( QComboBox *CB, QDataStream &ST )
{
  // 1
  QStringList SL;
  ST >> SL;
  CB->addItems( SL );
  // 2
  QString S;
  ST >> S;
  CB->setCurrentText( S );
}

void QStorage::SaveToStream( QComboBox *CB, QDataStream &ST )
{
  // 1, 2
  QStringList SL;
  int L = CB->count();
  for ( int i = 0; i < L; ++i ) {
    SL << CB->itemText( i );
  }
  ST << SL << CB->currentText();
}

void QStorage::SaveToStreamPrepareHistory( QComboBox *CB, QDataStream &ST, int HistoryCount )
{
  PrepareHistoryComboBox( CB, HistoryCount );
  SaveToStream( CB, ST );
}

void QStorage::LoadFromStream( QDataStream &ST )
{
  m_MapMemoryStorage.LoadFromStream( ST );
}

void QStorage::SaveToStream( QDataStream &ST )
{
  m_MapMemoryStorage.SaveToStream( ST );
}

QStorageMainWindow::QStorageMainWindow( QWidget *parent )
  : inherited( parent )
{
}

QStorageMainWindow::~QStorageMainWindow()
{
}

void QStorageMainWindow::closeEvent( QCloseEvent *event )
{
  if ( m_Storage ) {
    m_Storage->SaveObject( this, m_StorageKind );
  }

  inherited::closeEvent( event );
}

void QStorageMainWindow::LoadFromStream( QDataStream &ST )
{
  QByteArray BA;
  // 1
  ST >> BA;
  restoreGeometry( BA );
  // 2
  ST >> BA;
  restoreState( BA );
}

void QStorageMainWindow::SaveToStream( QDataStream &ST )
{
  // 1, 2
  ST << saveGeometry() << saveState();
}

QStorageDialog::QStorageDialog( QWidget *parent )
    : inherited( parent )
{
}

QStorageDialog::~QStorageDialog()
{
}

void QStorageDialog::LoadFromStream( QDataStream &ST )
{
  QByteArray BA;
  // 1
  ST >> BA;
  restoreGeometry( BA );
}

void QStorageDialog::SaveToStream( QDataStream &ST )
{
  // 1
  ST << saveGeometry();
}
