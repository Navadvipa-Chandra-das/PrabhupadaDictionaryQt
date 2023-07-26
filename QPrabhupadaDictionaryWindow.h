#ifndef QPRABHUPADADICTIONARYWINDOW_H
#define QPRABHUPADADICTIONARYWINDOW_H

#include <QMainWindow>
#include "QPrabhupada.h"
#include "QPrabhupadaDictionary.h"
#include "ui_QPrabhupadaDictionaryWindow.h"

//QT_BEGIN_NAMESPACE
//namespace Ui {
//class QPrabhupadaDictionaryWindow;
//}
//QT_END_NAMESPACE

class QPrabhupadaDictionaryWindow : public QStorageMainWindow {
    Q_OBJECT
public:
    int m_SanskitHeaderSize = 50;
    int m_TranslateHeaderSize = 50;
    bool m_StartResize = false;

    QPrabhupadaDictionaryWindow() = delete;
    QPrabhupadaDictionaryWindow( QPrabhupadaDictionary *APrabhupadaDictionary
                              , QWidget *parent = nullptr );
    ~QPrabhupadaDictionaryWindow();
    Ui::QPrabhupadaDictionaryWindow *m_ui = new Ui::QPrabhupadaDictionaryWindow;
    QPrabhupadaDictionary *m_PrabhupadaDictionary;
    void PrepareDictionary();
    void FirstShow();
private:
    using inherited = QStorageMainWindow;

    void actionExit_Program();
    void actionFind();
    void actionCaseSensitive( bool Value );
    void actionRegularExpression( bool Value );
    void actionAutoPercentBegin( bool Value );
    void actionAutoPercentEnd( bool Value );
    void actionDelete();
    void actionInsert();
    void actionRemove_Duplicates();
    void actionWhats_This_mode();
    void actionGoToRow();
    void actionAbout();
    void actionDeleteAllBookmarks();
    void ActionSaveAllLetterToFile();
    void actionSet_Bookmark( unsigned short B );
    void actionSet_Bookmark_0();
    void actionSet_Bookmark_1();
    void actionSet_Bookmark_2();
    void actionSet_Bookmark_3();
    void actionSet_Bookmark_4();
    void actionSet_Bookmark_5();
    void actionSet_Bookmark_6();
    void actionSet_Bookmark_7();
    void actionSet_Bookmark_8();
    void actionSet_Bookmark_9();
    void actionGo_to_bookmark( unsigned short B );
    void actionGo_to_bookmark_0();
    void actionGo_to_bookmark_1();
    void actionGo_to_bookmark_2();
    void actionGo_to_bookmark_3();
    void actionGo_to_bookmark_4();
    void actionGo_to_bookmark_5();
    void actionGo_to_bookmark_6();
    void actionGo_to_bookmark_7();
    void actionGo_to_bookmark_8();
    void actionGo_to_bookmark_9();
    void PrepareLanguages();
    void Language_IndexChanged( int Value );
    void LanguageUI_IndexChanged( int Value );
    void DoOrderBy( QPrabhupadaDictionaryOrderBy Value );

    void CaseSensitiveChanged( bool Value );
    void RegularExpressionChanged( bool Value );
    void AutoPercentBeginChanged( bool Value );
    void AutoPercentEndChanged( bool Value );

    void PrabhupadaFilterSlovarChanged( QFilterSlovar Value );
    void DoGoToLine( int Value );
    void Connects();
    void Emits();
    void TablePrabhupadaCurrentRowChanged( const QModelIndex &current, const QModelIndex &previous );
    void TablePrabhupadaHeaderSectionResized( int logicalIndex, int oldSize, int newSize );
protected:
    void changeEvent( QEvent *event ) override;
    void closeEvent( QCloseEvent *event ) override;
    void LoadFromStream( QDataStream &ST ) override;
    void SaveToStream( QDataStream &ST ) override;
    void SpinBoxFontSizeChanged( int Value );
    virtual void FontSizeChanged( int Value );
    virtual void PrabhupadaTableResized();
    void resizeEvent( QResizeEvent *event ) override;
};
#endif // QPRABHUPADADICTIONARYWINDOW_H
