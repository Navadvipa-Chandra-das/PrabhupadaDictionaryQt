#include "QPrabhupadaDictionaryWindow.h"
#include <QMessageBox>
#include <QWhatsThis>
#include <QScrollBar>
#include "QPrabhupadaGoToLineWindow.h"
#include "QPrabhupadaAboutWindow.h"

//QPrabhupadaDictionaryWindow::QPrabhupadaDictionaryWindow( QWidget *parent )
//  : QMainWindow(parent)
//  , ui(new Ui::QPrabhupadaDictionaryWindow)
//{
//  ui->setupUi(this);
//}

QPrabhupadaDictionaryWindow::QPrabhupadaDictionaryWindow( QPrabhupadaDictionary *APrabhupadaDictionary
                            , QWidget *parent )
  : inherited( parent )
  , m_PrabhupadaDictionary( APrabhupadaDictionary )
{
  m_ui->setupUi( this );
  m_ui->tbvPrabhupadaDictionary->verticalHeader()->hide();
  m_ui->tbvPrabhupadaDictionary->setModel( m_PrabhupadaDictionary );
  //!!! not work!
  setWindowFlags( windowFlags() & Qt::WindowContextHelpButtonHint );
  Connects();
}

void QPrabhupadaDictionaryWindow::Connects()
{
  QObject::connect( m_ui->actionFind
          , &QAction::triggered
          , this
          , &QPrabhupadaDictionaryWindow::actionFind );
  QObject::connect( m_ui->actionCaseSensitive
           , &QAction::toggled
           , this
           , &QPrabhupadaDictionaryWindow::actionCaseSensitive );
  QObject::connect( m_ui->actionRegularExpression
           , &QAction::toggled
           , this
           , &QPrabhupadaDictionaryWindow::actionRegularExpression );
  QObject::connect( m_ui->actionAutoPercentBegin
           , &QAction::toggled
           , this
           , &QPrabhupadaDictionaryWindow::actionAutoPercentBegin );
  QObject::connect( m_ui->actionAutoPercentEnd
           , &QAction::toggled
           , this
           , &QPrabhupadaDictionaryWindow::actionAutoPercentEnd );
  QObject::connect( m_ui->actionDelete
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionDelete );
  QObject::connect( m_ui->actionInsert
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionInsert );
  QObject::connect( m_ui->actionRemove_Duplicates
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionRemove_Duplicates );
  QObject::connect( m_ui->actionWhats_This_mode
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionWhats_This_mode );
  QObject::connect( m_ui->actionGoToRow
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGoToRow );
  QObject::connect( m_ui->actionAbout
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionAbout );
  QObject::connect( m_ui->actionDeleteAllBookmarks
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionDeleteAllBookmarks );
  QObject::connect( m_ui->ActionSaveAllLetterToFile
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::ActionSaveAllLetterToFile );
  QObject::connect( m_ui->sbFontSize
           , &QSpinBox::valueChanged
           , this
           , &QPrabhupadaDictionaryWindow::SpinBoxFontSizeChanged );
  QObject::connect( &m_PrabhupadaDictionary->m_FontSize
           , &QEmitInt::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::FontSizeChanged );
  QObject::connect( m_ui->ComboBoxLanguage
           , &QComboBox::currentIndexChanged
           , &m_PrabhupadaDictionary->m_LanguageIndex
           , &QLanguageIndex::SetValue );
  QObject::connect( m_ui->ComboBoxLanguageUI
           , &QComboBox::currentIndexChanged
           , &m_PrabhupadaDictionary->m_LanguageUIIndex
           , &QLanguageIndex::SetValue );
  QObject::connect( &m_PrabhupadaDictionary->m_LanguageIndex
           , &QLanguageIndex::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::Language_IndexChanged );
  QObject::connect( &m_PrabhupadaDictionary->m_LanguageUIIndex
           , &QLanguageIndex::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::LanguageUI_IndexChanged );
  QObject::connect( m_ui->tbvPrabhupadaDictionary->horizontalHeader()
           , &QHeaderView::sortIndicatorChanged
           , m_PrabhupadaDictionary
           , &QPrabhupadaDictionary::sortByColumn );
  QObject::connect( &m_PrabhupadaDictionary->m_PrabhupadaOrder
           , &QPrabhupadaOrder::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::DoOrderBy );
  QObject::connect( &m_PrabhupadaDictionary->m_CaseSensitive
           , &QEmitBool::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::CaseSensitiveChanged );
  QObject::connect( &m_PrabhupadaDictionary->m_RegularExpression
           , &QEmitBool::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::RegularExpressionChanged );
  QObject::connect( &m_PrabhupadaDictionary->m_AutoPercentBegin
           , &QEmitBool::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::AutoPercentBeginChanged );
  QObject::connect( &m_PrabhupadaDictionary->m_AutoPercentEnd
           , &QEmitBool::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::AutoPercentEndChanged );
  QObject::connect( &m_PrabhupadaDictionary->m_PrabhupadaFilterSlovar
           , &QPrabhupadaFilterSlovar::SignalValueChanged
           , this
           , &QPrabhupadaDictionaryWindow::PrabhupadaFilterSlovarChanged );
  QObject::connect( m_ui->tbvPrabhupadaDictionary->selectionModel()
           , &QItemSelectionModel::currentRowChanged
           , this
           , &QPrabhupadaDictionaryWindow::TablePrabhupadaCurrentRowChanged );
  QObject::connect( m_ui->tbvPrabhupadaDictionary->horizontalHeader()
           , &QHeaderView::sectionResized
           , this
           , &QPrabhupadaDictionaryWindow::TablePrabhupadaHeaderSectionResized );
  QObject::connect( m_ui->actionSet_Bookmark_0
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_0 );
  QObject::connect( m_ui->actionSet_Bookmark_1
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_1 );
  QObject::connect( m_ui->actionSet_Bookmark_2
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_2 );
  QObject::connect( m_ui->actionSet_Bookmark_3
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_3 );
  QObject::connect( m_ui->actionSet_Bookmark_4
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_4 );
  QObject::connect( m_ui->actionSet_Bookmark_5
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_5 );
  QObject::connect( m_ui->actionSet_Bookmark_6
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_6 );
  QObject::connect( m_ui->actionSet_Bookmark_7
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_7 );
  QObject::connect( m_ui->actionSet_Bookmark_8
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_8 );
  QObject::connect( m_ui->actionSet_Bookmark_9
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionSet_Bookmark_9 );
  QObject::connect( m_ui->actionGo_to_bookmark_0
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_0 );
  QObject::connect( m_ui->actionGo_to_bookmark_1
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_1 );
  QObject::connect( m_ui->actionGo_to_bookmark_2
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_2 );
  QObject::connect( m_ui->actionGo_to_bookmark_3
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_3 );
  QObject::connect( m_ui->actionGo_to_bookmark_4
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_4 );
  QObject::connect( m_ui->actionGo_to_bookmark_5
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_5 );
  QObject::connect( m_ui->actionGo_to_bookmark_6
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_6 );
  QObject::connect( m_ui->actionGo_to_bookmark_7
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_7 );
  QObject::connect( m_ui->actionGo_to_bookmark_8
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_8 );
  QObject::connect( m_ui->actionGo_to_bookmark_9
           , &QAction::triggered
           , this
           , &QPrabhupadaDictionaryWindow::actionGo_to_bookmark_9 );
}

void QPrabhupadaDictionaryWindow::Emits()
{
  m_PrabhupadaDictionary->m_LanguageIndex.EmitValueChanged();
  m_PrabhupadaDictionary->m_LanguageUIIndex.EmitValueChanged();
  m_PrabhupadaDictionary->m_FontSize.EmitValueChanged();
  m_PrabhupadaDictionary->m_PrabhupadaOrder.EmitValueChanged();
  m_PrabhupadaDictionary->m_CaseSensitive.EmitValueChanged();
  m_PrabhupadaDictionary->m_RegularExpression.EmitValueChanged();
  m_PrabhupadaDictionary->m_AutoPercentBegin.EmitValueChanged();
  m_PrabhupadaDictionary->m_AutoPercentEnd.EmitValueChanged();
  m_PrabhupadaDictionary->m_PrabhupadaFilterSlovar.EmitValueChanged();
  m_ui->tbvPrabhupadaDictionary->setFocus( Qt::ActiveWindowFocusReason );
}

QPrabhupadaDictionaryWindow::~QPrabhupadaDictionaryWindow()
{
  delete m_ui;
}

void QPrabhupadaDictionaryWindow::SpinBoxFontSizeChanged( int Value )
{
  m_PrabhupadaDictionary->m_FontSize.SetValue( Value );
}

void QPrabhupadaDictionaryWindow::FontSizeChanged( int Value )
{
  m_ui->sbFontSize->setValue( Value );
  QFont F = m_ui->ComboBoxSanskrit->font();
  F.setPointSize( Value );
  m_ui->ComboBoxSanskrit->setFont( F );
  m_ui->ComboBoxTranslate->setFont( F );
  m_ui->tbvPrabhupadaDictionary->setFont( F );

  QHeaderView *verticalHeader = m_ui->tbvPrabhupadaDictionary->verticalHeader();
  //verticalHeader->setSectionResizeMode( QHeaderView::Fixed );
  QFontMetrics FM( F );
  verticalHeader->setDefaultSectionSize( FM.height() );
}

void QPrabhupadaDictionaryWindow::actionFind()
{
  QFilterSlovar& FS = m_PrabhupadaDictionary->m_LanguageVector.m_Vector[ m_PrabhupadaDictionary->m_LanguageIndex.m_Value ].m_FilterSlovar;

  FS.m_PrabhupadaFindOptions = QPrabhupadaFindOptions( m_PrabhupadaDictionary->m_CaseSensitive.m_Value
                            , m_PrabhupadaDictionary->m_RegularExpression.m_Value
                            , m_PrabhupadaDictionary->m_AutoPercentBegin.m_Value
                            , m_PrabhupadaDictionary->m_AutoPercentEnd.m_Value );
  FS.SetSanskrit ( m_ui->ComboBoxSanskrit ->currentText() );
  FS.SetTranslate( m_ui->ComboBoxTranslate->currentText() );

  m_PrabhupadaDictionary->m_PrabhupadaFilterSlovar.SetValue( FS );
}

void QPrabhupadaDictionaryWindow::actionCaseSensitive( bool Value )
{
  m_PrabhupadaDictionary->m_CaseSensitive.SetValue( Value );
}

void QPrabhupadaDictionaryWindow::actionRegularExpression( bool Value )
{
  m_PrabhupadaDictionary->m_RegularExpression.SetValue( Value );
}

void QPrabhupadaDictionaryWindow::actionAutoPercentBegin( bool Value )
{
  m_PrabhupadaDictionary->m_AutoPercentBegin.SetValue( Value );
}

void QPrabhupadaDictionaryWindow::actionAutoPercentEnd( bool Value )
{
  m_PrabhupadaDictionary->m_AutoPercentEnd.SetValue( Value );
}

void QPrabhupadaDictionaryWindow::actionDelete()
{
}

void QPrabhupadaDictionaryWindow::actionInsert()
{
}

void QPrabhupadaDictionaryWindow::actionRemove_Duplicates()
{
}

void QPrabhupadaDictionaryWindow::actionWhats_This_mode()
{
  if ( QWhatsThis::inWhatsThisMode() )
    QWhatsThis::leaveWhatsThisMode();
  else
    QWhatsThis::enterWhatsThisMode();
}

void QPrabhupadaDictionaryWindow::actionGoToRow()
{
  QPrabhupadaGoToLineWindow PrabhupadaGoToLineWindow( m_Storage );

  QObject::connect( &PrabhupadaGoToLineWindow
           , &QPrabhupadaGoToLineWindow::SignalGoToLine
           , this
           , &QPrabhupadaDictionaryWindow::DoGoToLine );

  m_Storage->LoadObject( &PrabhupadaGoToLineWindow, QStorageKind::Memory );
  PrabhupadaGoToLineWindow.exec();
  m_Storage->SaveObject( &PrabhupadaGoToLineWindow, QStorageKind::Memory );
}

void QPrabhupadaDictionaryWindow::actionAbout()
{
  QPrabhupadaAboutWindow PrabhupadaAboutWindow( m_Storage );
  m_Storage->LoadObject( &PrabhupadaAboutWindow, QStorageKind::DB );
  PrabhupadaAboutWindow.exec();
  m_Storage->SaveObject( &PrabhupadaAboutWindow, QStorageKind::DB );
}

void QPrabhupadaDictionaryWindow::actionDeleteAllBookmarks()
{
  m_PrabhupadaDictionary->m_LanguageIndex.LanguageInfo().m_PrabhupadaZakladkaMap.clear();
}

void QPrabhupadaDictionaryWindow::ActionSaveAllLetterToFile()
{
  QMessageBox::StandardButton reply;

  reply = QMessageBox::question( this
                  , tr( "Пожалуйста, внимание!" )
                 , tr( "Собираем все буквы в файл?" )
                 , QMessageBox::Yes | QMessageBox::No );

  if ( reply == QMessageBox::Yes ) {
    QString S, SB;
    std::set< QChar > Set;
    int L = m_PrabhupadaDictionary->m_PrabhupadaSlovarVector.size();
    QString::size_type SL;
    QSanskritTranslate* sp;

    for ( int i = 0; i < L; ++i ) {
      sp = m_PrabhupadaDictionary->m_PrabhupadaSlovarVector[ i ];
      S = sp->m_Sanskrit + sp->m_Translate;
      SL = S.size();
      for ( int j = 0; j < SL; ++j ) {
        Set.insert( S[ j ] );
      }
    }

    QSaveFile ASaveFile = QSaveFile( "AllPrabhupadaLetter.txt" );
    QDataStream  AStream = QDataStream( &ASaveFile );
    ASaveFile.open( QIODevice::WriteOnly );

    for ( std::set< QChar >::iterator I = Set.begin(); I != Set.end(); ++I ) {
      SB.append( (*I) );
      SB += "\t";
      SB.append( (*I) );
      SB += "\n";
    }
    AStream << SB;
    ASaveFile.commit();
  }
}

void QPrabhupadaDictionaryWindow::changeEvent( QEvent *event )
{
  if ( event->type() == QEvent::LanguageChange ) {
    m_ui->retranslateUi( this );
  }

  inherited::changeEvent( event );
}

void QPrabhupadaDictionaryWindow::closeEvent( QCloseEvent *event )
{
  m_Storage->SaveObject( m_PrabhupadaDictionary, QStorageKind::DB );
  m_Storage->SaveObject( &m_PrabhupadaDictionary->m_LanguageUIIndex, QStorageKind::File );
  m_Storage->SaveObject( &m_PrabhupadaDictionary->m_LanguageVector, QStorageKind::File );

  inherited::closeEvent( event );
}

void QPrabhupadaDictionaryWindow::actionExit_Program()
{
  close();
}

void QPrabhupadaDictionaryWindow::LoadFromStream( QDataStream &ST )
{
  inherited::LoadFromStream( ST );
  // 1
  QByteArray AS;
  ST >> AS;
  m_ui->splSanskritTranslate->restoreState( AS );
  // 2
  ST >> AS;
  m_ui->tbvPrabhupadaDictionary->horizontalHeader()->restoreState( AS );
  // 3
  m_Storage->LoadFromStream( ST );
}

void QPrabhupadaDictionaryWindow::SaveToStream( QDataStream &ST )
{
  inherited::SaveToStream( ST );
  // 1
  ST << m_ui->splSanskritTranslate->saveState();
  // 2
  ST << m_ui->tbvPrabhupadaDictionary->horizontalHeader()->saveState();
  // 3
  m_Storage->SaveToStream( ST );
}

void QPrabhupadaDictionaryWindow::PrepareDictionary()
{
  m_PrabhupadaDictionary->PrepareLanguageAndMaxID();
  PrepareLanguages();
}

void QPrabhupadaDictionaryWindow::PrepareLanguages()
{
  m_PrabhupadaDictionary->m_LanguageIndex.PrepareComboBox( m_ui->ComboBoxLanguage );
  m_PrabhupadaDictionary->m_LanguageUIIndex.PrepareComboBox( m_ui->ComboBoxLanguageUI );
}

void QPrabhupadaDictionaryWindow::Language_IndexChanged( int Value )
{
  m_ui->ComboBoxLanguage->setCurrentIndex( Value );
}

void QPrabhupadaDictionaryWindow::LanguageUI_IndexChanged( int Value )
{
  m_ui->ComboBoxLanguageUI->setCurrentIndex( Value );
}

void QPrabhupadaDictionaryWindow::DoOrderBy( QPrabhupadaDictionaryOrderBy Value )
{
  QHeaderView* HV = m_ui->tbvPrabhupadaDictionary->horizontalHeader();
  switch ( Value ) {
  case QPrabhupadaDictionaryOrderBy::SanskritVozrastanie :
    HV->setSortIndicator( 0, Qt::AscendingOrder );
    break;
  case QPrabhupadaDictionaryOrderBy::SanskritUbyvanie :
    HV->setSortIndicator( 0, Qt::DescendingOrder );
    break;
  case QPrabhupadaDictionaryOrderBy::TranslateVozrastanie :
    HV->setSortIndicator( 1, Qt::AscendingOrder );
    break;
  case QPrabhupadaDictionaryOrderBy::TranslateUbyvanie :
    HV->setSortIndicator( 1, Qt::DescendingOrder );
    break;
  }
}

void QPrabhupadaDictionaryWindow::CaseSensitiveChanged( bool Value )
{
  m_ui->actionCaseSensitive->setChecked( Value );
}

void QPrabhupadaDictionaryWindow::RegularExpressionChanged( bool Value )
{
  m_ui->actionRegularExpression->setChecked( Value );

  m_ui->actionCaseSensitive  ->setEnabled( Value );
  m_ui->actionAutoPercentBegin ->setEnabled( !Value );
  m_ui->actionAutoPercentEnd   ->setEnabled( !Value );
}

void QPrabhupadaDictionaryWindow::AutoPercentBeginChanged( bool Value )
{
  m_ui->actionAutoPercentBegin->setChecked( Value );
}

void QPrabhupadaDictionaryWindow::AutoPercentEndChanged( bool Value )
{
  m_ui->actionAutoPercentEnd->setChecked( Value );
}

void QPrabhupadaDictionaryWindow::PrabhupadaFilterSlovarChanged( QFilterSlovar Value )
{
  m_ui->actionCaseSensitive  ->setChecked( Value.m_PrabhupadaFindOptions.m_CaseSensitive );
  m_ui->actionRegularExpression->setChecked( Value.m_PrabhupadaFindOptions.m_RegularExpression );
  m_ui->actionAutoPercentBegin ->setChecked( Value.m_PrabhupadaFindOptions.m_AutoPercentBegin );
  m_ui->actionAutoPercentEnd   ->setChecked( Value.m_PrabhupadaFindOptions.m_AutoPercentEnd );

  if ( Value.m_Sanskrit != m_ui->ComboBoxSanskrit->currentText() ) {
    m_ui->ComboBoxSanskrit ->setCurrentText( Value.m_Sanskrit );
  }
  if ( Value.m_Translate != m_ui->ComboBoxTranslate->currentText() ) {
    m_ui->ComboBoxTranslate->setCurrentText( Value.m_Translate );
  }
  QModelIndex I = m_ui->tbvPrabhupadaDictionary->currentIndex();
  emit m_ui->tbvPrabhupadaDictionary->selectionModel()->currentRowChanged( I, I );
}

void QPrabhupadaDictionaryWindow::DoGoToLine( int Value )
{
  QModelIndex I = m_PrabhupadaDictionary->index( Value - 1, m_ui->tbvPrabhupadaDictionary->currentIndex().column() );
  m_ui->tbvPrabhupadaDictionary->setCurrentIndex( I );
  m_ui->tbvPrabhupadaDictionary->scrollTo( I );
}

void QPrabhupadaDictionaryWindow::TablePrabhupadaCurrentRowChanged( const QModelIndex &current, const QModelIndex &/*previous*/ )
{
  int R = current.row() + 1;
  std::size_t A;
  if ( m_PrabhupadaDictionary->m_FilterSlovarIsEmpty ) {
    A = m_PrabhupadaDictionary->m_PrabhupadaSlovarVector.size();
  } else {
    A = m_PrabhupadaDictionary->m_PrabhupadaSlovarVector.m_SearchCount;
  }
  QString S = QString::number( R ) + " / " + QString::number( A );
  m_ui->lineEditRowIndicator->setText( S );
}

void QPrabhupadaDictionaryWindow::PrabhupadaTableResized()
{
  QTableView *TV = m_ui->tbvPrabhupadaDictionary;
  QScrollBar *SB = TV->verticalScrollBar();
  int SBW = 0;

  if ( SB ) {
    SBW = SB->width() + 2;
  }

  int WidthNew = TV->width()
    , WidthOld = m_SanskitHeaderSize + m_TranslateHeaderSize;

  if ( WidthNew > SBW )
    WidthNew -= SBW;

  TV->setColumnWidth( 0, m_SanskitHeaderSize * WidthNew / WidthOld );
  TV->setColumnWidth( 1, m_TranslateHeaderSize * WidthNew / WidthOld );
}

void QPrabhupadaDictionaryWindow::resizeEvent( QResizeEvent *event )
{
  if ( m_StartResize ) {
    PrabhupadaTableResized();
  }
  inherited::resizeEvent( event );
}

void QPrabhupadaDictionaryWindow::TablePrabhupadaHeaderSectionResized( int /*logicalIndex*/, int /*oldSize*/, int /*newSize*/ )
{
  if ( m_StartResize ) {
    QHeaderView *HV = m_ui->tbvPrabhupadaDictionary->horizontalHeader();

    m_SanskitHeaderSize = HV->sectionSize( 0 );
    m_TranslateHeaderSize = HV->sectionSize( 1 );
    //PrabhupadaLog( "log.txt", QString( "%1 : %2" ).formatArgs( m_SanskitHeaderSize, m_TranslateHeaderSize ) );
  }
}

void QPrabhupadaDictionaryWindow::FirstShow()
{
  Emits();
  show();
  m_StartResize = true;
  TablePrabhupadaHeaderSectionResized( 0, 0, 0 );
  PrabhupadaTableResized();
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark( unsigned short B )
{
  QLanguageInfo& YI = m_PrabhupadaDictionary->m_LanguageIndex.LanguageInfo();
  QPrabhupadaZakladkaMap::iterator I = YI.m_PrabhupadaZakladkaMap.find( B );
  QModelIndex CI = m_ui->tbvPrabhupadaDictionary->currentIndex();
  int ARowNum  = CI.row()
    , AColumnNum = CI.column();
  if ( I == YI.m_PrabhupadaZakladkaMap.end() ) {
    YI.m_PrabhupadaZakladkaMap[ B ] = QPrabhupadaZakladka( ARowNum, AColumnNum, m_PrabhupadaDictionary->m_PrabhupadaFilterSlovar.m_Value );
  } else {
    (*I).second.m_RowNum     = ARowNum;
    (*I).second.m_ColumnNum  = AColumnNum;
    (*I).second.m_FilterSlovar = m_PrabhupadaDictionary->m_PrabhupadaFilterSlovar.m_Value;
  }
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_0()
{
  actionSet_Bookmark( 0 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_1()
{
  actionSet_Bookmark( 1 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_2()
{
  actionSet_Bookmark( 2 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_3()
{
  actionSet_Bookmark( 3 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_4()
{
  actionSet_Bookmark( 4 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_5()
{
  actionSet_Bookmark( 5 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_6()
{
  actionSet_Bookmark( 6 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_7()
{
  actionSet_Bookmark( 7 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_8()
{
  actionSet_Bookmark( 8 );
}

void QPrabhupadaDictionaryWindow::actionSet_Bookmark_9()
{
  actionSet_Bookmark( 9 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark( unsigned short B )
{
  QLanguageInfo& YI = m_PrabhupadaDictionary->m_LanguageVector.m_Vector[ m_PrabhupadaDictionary->m_LanguageIndex.m_Value ];
  QPrabhupadaZakladkaMap::iterator ZI = YI.m_PrabhupadaZakladkaMap.find( B );
  if ( ZI != YI.m_PrabhupadaZakladkaMap.end() ) {
    QPrabhupadaZakladka& PrabhupadaZakladka = YI.m_PrabhupadaZakladkaMap[ B ];
    // Устанавливаем фильтр!
    m_PrabhupadaDictionary->m_PrabhupadaFilterSlovar.SetValue( PrabhupadaZakladka.m_FilterSlovar );
    // Осуществляем переход по номеру строки и столбца!
    QModelIndex I = m_PrabhupadaDictionary->index( PrabhupadaZakladka.m_RowNum
                            , PrabhupadaZakladka.m_ColumnNum );
    m_ui->tbvPrabhupadaDictionary->setCurrentIndex( I );
    m_ui->tbvPrabhupadaDictionary->scrollTo( I );
  }
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_0()
{
  actionGo_to_bookmark( 0 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_1()
{
  actionGo_to_bookmark( 1 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_2()
{
  actionGo_to_bookmark( 2 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_3()
{
  actionGo_to_bookmark( 3 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_4()
{
  actionGo_to_bookmark( 4 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_5()
{
  actionGo_to_bookmark( 5 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_6()
{
  actionGo_to_bookmark( 6 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_7()
{
  actionGo_to_bookmark( 7 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_8()
{
  actionGo_to_bookmark( 8 );
}

void QPrabhupadaDictionaryWindow::actionGo_to_bookmark_9()
{
  actionGo_to_bookmark( 9 );
}
