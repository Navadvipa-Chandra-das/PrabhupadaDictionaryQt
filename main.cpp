#include "QPrabhupadaDictionaryWindow.h"
#include "QPrabhupadaLoginDialog.h"
#include "QPrabhupada.h"
//#include "QPrabhupadaUtil.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
      const QString baseName = "PrabhupadaDictionary_" + QLocale(locale).name();
      if (translator.load(":/i18n/" + baseName)) {
          a.installTranslator(&translator);
          break;
      }
  }

  QStorage AStorage;

  QPrabhupadaDictionary APrabhupadaDictionary( nullptr );
  APrabhupadaDictionary.setObjectName( "PrabhupadaDictionary" );
  APrabhupadaDictionary.m_Storage = &AStorage;
  a.setObjectName( APrabhupadaDictionary.objectName() );

  AStorage.LoadObject( &APrabhupadaDictionary.m_LanguageVector, QStorageKind::File );
  AStorage.LoadObject( &APrabhupadaDictionary.m_LanguageUIIndex, QStorageKind::File );
  
  QPrabhupadaLoginDialog *PrabhupadaLoginWindow = new QPrabhupadaLoginDialog( &APrabhupadaDictionary );

  PrabhupadaLoginWindow->m_ui->ComboBoxUserName->setEditText( "Navadvipa Chandra das" );
  PrabhupadaLoginWindow->m_ui->ComboBoxDatabaseName->setEditText( "NewNavadvipa" );
  PrabhupadaLoginWindow->m_ui->ComboBoxHostName->setEditText( "127.0.0.1" );
  PrabhupadaLoginWindow->m_ui->ComboBoxPort->setEditText( QString::number( 5432 ) );
  PrabhupadaLoginWindow->m_ui->ComboBoxSchema->setEditText( "\"NewNavadvipa\"" );

  AStorage.LoadObject( PrabhupadaLoginWindow, QStorageKind::File );
  APrabhupadaDictionary.m_LanguageUIIndex.PrepareComboBox( PrabhupadaLoginWindow->m_ui->ComboBoxLanguageUI );

  int R, N = 0;
  while ( ++N < 4 ) {
    R = PrabhupadaLoginWindow->exec();
    if ( R == QDialog::Accepted ) {
      QSqlDatabase DB = QSqlDatabase::addDatabase( PrabhupadaLoginWindow->m_DriverName, "PrabhupadaDB" );
      if ( PrabhupadaLoginWindow->Connect( &DB ) ) {
        // Prepare AStorage
        AStorage.SetDatabase( &DB );
        AStorage.m_Schema = PrabhupadaLoginWindow->m_Schema;
        // Подготавливаем APrabhupadaDictionary
        APrabhupadaDictionary.m_DB = &DB;
        APrabhupadaDictionary.m_Schema = AStorage.m_Schema;
        // Reset settings in DB, if need!
        if ( PrabhupadaLoginWindow->m_ui->CheckBoxResetSettings->isChecked() ) {
            AStorage.ResetSettings();
        }
        AStorage.LoadObject( &APrabhupadaDictionary, QStorageKind::DB );
        QPrabhupadaDictionaryWindow APrabhupadaDictionaryWindow = QPrabhupadaDictionaryWindow( &APrabhupadaDictionary );
        APrabhupadaDictionaryWindow.m_StorageKind = QStorageKind::DB;
        APrabhupadaDictionaryWindow.m_Storage = &AStorage;
        APrabhupadaDictionaryWindow.PrepareDictionary();
        AStorage.LoadObject( &APrabhupadaDictionaryWindow, APrabhupadaDictionaryWindow.m_StorageKind );
        APrabhupadaDictionaryWindow.FirstShow();
        AStorage.SaveObject( PrabhupadaLoginWindow, QStorageKind::File );

        delete PrabhupadaLoginWindow;
        PrabhupadaLoginWindow = nullptr;
        return a.exec();
      }
    } else {
      break;
    }
  }
  if ( PrabhupadaLoginWindow )
      delete PrabhupadaLoginWindow;
  return 0;

  //PrabhupadaDictionaryWindow w;
  //w.show();
  //return a.exec();
}
