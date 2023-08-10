#ifndef QPrabhupadaDictionary_H
#define QPrabhupadaDictionary_H

#include <QtCore>
#include <QtGui>
#include <QtSql>
#include <vector>
#include <map>
#include <set>
#include "QPrabhupada.h"

enum class QPrabhupadaDictionaryOrderBy : qint8
{
  SanskritVozrastanie
, SanskritUbyvanie
, TranslateVozrastanie
, TranslateUbyvanie
};

class QPrabhupadaOrder : public QObject
{
    Q_OBJECT
public:
    QPrabhupadaDictionaryOrderBy m_Value;
    bool m_NeedMainWork = true;
    int m_Stop = 0;
    QPrabhupadaOrder() = delete;
    QPrabhupadaOrder( QPrabhupadaDictionaryOrderBy Value )
        : m_Value( Value ) {};
    ~QPrabhupadaOrder() {};
signals:
    void SignalValueChanged( QPrabhupadaDictionaryOrderBy Value );
public:
    void SetValue( QPrabhupadaDictionaryOrderBy Value )
    {
        if ( m_Stop == 0 && m_Value != Value ) {
            m_Value = Value;
            m_NeedMainWork = true;
            emit SignalValueChanged( m_Value );
        }
    };
    void LoadFromStream( QDataStream &ST )
    {
        QPrabhupadaDictionaryOrderBy N;
        ST >> N;
        SetValue( N );
    };
    void SaveToStream( QDataStream &ST )
    {
        ST << m_Value;
    };
    inline void EmitValueChanged( bool ANeedResetMainWork = false )
    {
        if ( ANeedResetMainWork ) {
            m_NeedMainWork = true;
        }
        emit SignalValueChanged( m_Value );
        m_NeedMainWork = false;
    };
};

class QStringMap : public std::map< QString, QString >
{
  private:
    using inherited = std::map< QString, QString >;
  public:
    QStringMap();
    ~QStringMap();
};

class QStringSet : public std::set< QString >
{
  private:
    using inherited = std::set< QString >;
  public:
    QStringSet();
    ~QStringSet();
};

class QPrabhupadaFindOptions
{
  public:
    QPrabhupadaFindOptions();
    QPrabhupadaFindOptions( bool ACaseSensitive
                          , bool ARegularExpression
                          , bool AAutoPercentBegin
                          , bool AAutoPercentEnd );
    QPrabhupadaFindOptions( const QPrabhupadaFindOptions& A );
    QPrabhupadaFindOptions( QPrabhupadaFindOptions&& A );
    ~QPrabhupadaFindOptions();

    bool m_CaseSensitive     = true;
    bool m_RegularExpression = false;
    bool m_AutoPercentBegin  = true;
    bool m_AutoPercentEnd    = true;

    void LoadFromStream( QDataStream &ST );
    void SaveToStream  ( QDataStream &ST );
  public:
    QPrabhupadaFindOptions& operator = ( const QPrabhupadaFindOptions&  A );
    QPrabhupadaFindOptions& operator = (       QPrabhupadaFindOptions&& A );
    bool operator == ( const QPrabhupadaFindOptions& A )
    {
      return m_CaseSensitive     == A.m_CaseSensitive &&
             m_RegularExpression == A.m_RegularExpression &&
             m_AutoPercentBegin  == A.m_AutoPercentBegin &&
             m_AutoPercentEnd    == A.m_AutoPercentEnd;
    }
    bool operator != ( const QPrabhupadaFindOptions& A )
    {
      return m_CaseSensitive     != A.m_CaseSensitive ||
             m_RegularExpression != A.m_RegularExpression ||
             m_AutoPercentBegin  != A.m_AutoPercentBegin ||
             m_AutoPercentEnd    != A.m_AutoPercentEnd;
    }
};

inline QDataStream& operator << ( QDataStream &ST, QPrabhupadaFindOptions &PrabhupadaFindOptions )
{
  return ST << PrabhupadaFindOptions.m_CaseSensitive
            << PrabhupadaFindOptions.m_RegularExpression
            << PrabhupadaFindOptions.m_AutoPercentBegin
            << PrabhupadaFindOptions.m_AutoPercentEnd;
}

inline QDataStream& operator >> ( QDataStream &ST, QPrabhupadaFindOptions &PrabhupadaFindOptions )
{
  return ST >> PrabhupadaFindOptions.m_CaseSensitive
            >> PrabhupadaFindOptions.m_RegularExpression
            >> PrabhupadaFindOptions.m_AutoPercentBegin
            >> PrabhupadaFindOptions.m_AutoPercentEnd;
}

class QFilterSlovar
{
  public:
    QPrabhupadaFindOptions m_PrabhupadaFindOptions;
    QString m_Sanskrit;
    QString m_Translate;
    QString m_SanskritWithoutDiakritik;
    QString m_TranslateWithoutDiakritik;
    QFilterSlovar();
    QFilterSlovar( const QFilterSlovar& A );
    QFilterSlovar( QFilterSlovar&& A );
    QFilterSlovar( QPrabhupadaFindOptions APrabhupadaFindOptions
                 , const QString &ASanskrit
                 , const QString &ATranslate );
    ~QFilterSlovar();

    void SetSanskrit( const QString &Value );
    void SetTranslate( const QString &Value );
    void SetSanskritWithoutDiakritik( const QString& Value );
    void SetTranslateWithoutDiakritik( const QString& Value );
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
    QFilterSlovar& operator = ( const QFilterSlovar& A );
    QFilterSlovar& operator = ( QFilterSlovar&& A );
    bool operator == ( const QFilterSlovar& A )
    {
      return m_PrabhupadaFindOptions == A.m_PrabhupadaFindOptions &&
             m_Sanskrit              == A.m_Sanskrit &&
             m_Translate             == A.m_Translate;
    }
    bool operator != ( const QFilterSlovar& A )
    {
      return m_PrabhupadaFindOptions != A.m_PrabhupadaFindOptions ||
             m_Sanskrit              != A.m_Sanskrit ||
             m_Translate             != A.m_Translate;
    }
    bool GetIsEmpty() const
    {
      return m_SanskritWithoutDiakritik.isEmpty() && m_TranslateWithoutDiakritik.isEmpty();
    }
    void Clear()
    {
      m_Sanskrit  = "";
      m_Translate = "";
      m_SanskritWithoutDiakritik  = "";
      m_TranslateWithoutDiakritik = "";
    }
};

inline QDataStream& operator << ( QDataStream &ST, const QFilterSlovar &FilterSlovar )
{
  return ST << FilterSlovar.m_Sanskrit << FilterSlovar.m_Translate;
}

inline QDataStream& operator >> ( QDataStream &ST, QFilterSlovar &FilterSlovar )
{
  QString S;
  ST >> S;
  FilterSlovar.SetSanskrit( S );
  ST >> S;
  FilterSlovar.SetTranslate( S );
  return ST;
}

class QPrabhupadaFilterSlovar : public QObject
{
  Q_OBJECT
  public:
  QFilterSlovar m_Value;
  bool m_NeedMainWork = true;
  int m_Stop = 0;
  QPrabhupadaFilterSlovar() = delete;
  QPrabhupadaFilterSlovar( QFilterSlovar Value )
      : m_Value( Value ) {};
  ~QPrabhupadaFilterSlovar() {};
  signals:
    void SignalValueChanged( QFilterSlovar Value );
  public:
  void SetValue( QFilterSlovar Value )
  {
      if ( m_Stop == 0 && m_Value != Value ) {
            m_Value = Value;
            m_NeedMainWork = true;
            emit SignalValueChanged( m_Value );
      }
  };
  void LoadFromStream( QDataStream &ST )
  {
      QFilterSlovar N;
      ST >> N;
      SetValue( N );
  };
  void SaveToStream( QDataStream &ST )
  {
      ST << m_Value;
  };
  inline void EmitValueChanged( bool ANeedResetMainWork = false )
  {
      if ( ANeedResetMainWork ) {
            m_NeedMainWork = true;
      }
      emit SignalValueChanged( m_Value );
      m_NeedMainWork = false;
  };
};


class QPrabhupadaLetter
{
  public:
    QChar m_Letter;
    int m_Ves;
    QPrabhupadaLetter();
    ~QPrabhupadaLetter();
};

class QPrabhupadaPrimer : public std::map< QChar, QPrabhupadaLetter >
{
  private:
    using inherited = std::map< QChar, QPrabhupadaLetter >;
  public:
    QPrabhupadaPrimer();
    ~QPrabhupadaPrimer();
};

inline QDataStream& operator << ( QDataStream &ST, const QPrabhupadaDictionaryOrderBy &OrderBy )
{
  return ST << (qint8)OrderBy;
}

inline QDataStream& operator >> ( QDataStream &ST, QPrabhupadaDictionaryOrderBy &OrderBy )
{
  return ST >> (qint8&)OrderBy;
}

class QSanskritTranslate
{
  public:
    int m_ID;
    QString m_Sanskrit;
    QString m_Translate;
    QString m_SanskritWithoutDiakritik;
    QString m_TranslateWithoutDiakritik;
    int m_SearchIndex;
    QSanskritTranslate();
    ~QSanskritTranslate();
};

class QPrabhupadaSlovarVector : public std::vector< QSanskritTranslate* >
{
  private:
    using inherited = std::vector< QSanskritTranslate* >;
  public:
    QPrabhupadaSlovarVector();
    ~QPrabhupadaSlovarVector();
    int m_SearchCount = 0;
    void Clear();
};

class QPrabhupadaZakladka
{
  public:
    QPrabhupadaZakladka();
    QPrabhupadaZakladka( int ARowNum
                       , int AColumnNum
                       , QFilterSlovar AFilterSlovar );
    QPrabhupadaZakladka( const QPrabhupadaZakladka& A );
    QPrabhupadaZakladka( QPrabhupadaZakladka&& A );
    ~QPrabhupadaZakladka();

    int m_RowNum;
    int m_ColumnNum;
    QFilterSlovar m_FilterSlovar;

    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
    QPrabhupadaZakladka& operator = ( const QPrabhupadaZakladka& A );
    QPrabhupadaZakladka& operator = ( QPrabhupadaZakladka&& A );
    bool operator == ( const QPrabhupadaZakladka& A )
    {
      return m_RowNum == A.m_RowNum && m_ColumnNum == A.m_ColumnNum && m_FilterSlovar == A.m_FilterSlovar;
    }
    bool operator != ( const QPrabhupadaZakladka& A )
    {
      return m_RowNum != A.m_RowNum || m_ColumnNum != A.m_ColumnNum || m_FilterSlovar != A.m_FilterSlovar;
    }
};

class QPrabhupadaZakladkaMap : public std::map< unsigned short, QPrabhupadaZakladka >
{
  private:
    using inherited = std::map< unsigned short, QPrabhupadaZakladka >;
  public:
    QPrabhupadaZakladkaMap();
    ~QPrabhupadaZakladkaMap();
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
};

class QLanguageInfo
{
  public:
    QLanguageInfo();
    QLanguageInfo( const QLanguageInfo &A );
    ~QLanguageInfo();

    int m_ID;
    QString m_Language;
    QString m_LanguageSlovo;
    int m_CurrentRow = 0;
    QFilterSlovar m_FilterSlovar;
    QPrabhupadaZakladkaMap m_PrabhupadaZakladkaMap;
};

class QLanguageVector : public QObject
{
  Q_OBJECT
  private:
    using inherited = QObject;
  public:
    QLanguageVector();
    ~QLanguageVector();
    using  QVectorType = std::vector< QLanguageInfo >;
    QVectorType m_Vector;
    bool m_LoadSuccess = false;
    int FindLanguage( const QString &S );
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
};

class QLanguageIndex : public QEmitInt
{
    Q_OBJECT
  private:
    using inherited = QEmitInt;
  public:
    QLanguageIndex() = delete;
    QLanguageIndex( int Value
                  , QLanguageVector &ALanguageVector );
    ~QLanguageIndex();
    static const int RussianIndex = 4;
    QLanguageVector& m_LanguageVector;
    void PrepareComboBox( QComboBox *CB );
    void ComboBoxAddItem( QComboBox *CB, const QString &S );
    inline QLanguageInfo& LanguageInfo() { return m_LanguageVector.m_Vector[ m_Value ]; };
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
  protected:
};

class QPrabhupadaDictionary : public QAbstractTableModel
{
  Q_OBJECT
  public:
    using inherited = QAbstractTableModel;
    QSqlDatabase *m_DB = nullptr;
    QStorage* m_Storage;
    bool m_FilterSlovarIsEmpty = true;
    QPrabhupadaDictionary( QObject *parent = nullptr );
    ~QPrabhupadaDictionary();
    QTranslator m_Translator;
    QLanguageVector m_LanguageVector;
    QLanguageIndex m_LanguageIndex   = QLanguageIndex( QLanguageIndex::RussianIndex, m_LanguageVector );
    QLanguageIndex m_LanguageUIIndex = QLanguageIndex( QLanguageIndex::RussianIndex, m_LanguageVector );
    QEmitInt m_FontSize = QEmitInt( 14 );
    QPrabhupadaOrder m_PrabhupadaOrder = QPrabhupadaOrder( QPrabhupadaDictionaryOrderBy::SanskritVozrastanie );

    QEmitBool m_CaseSensitive     = QEmitBool( true );
    QEmitBool m_RegularExpression = QEmitBool( false );
    QEmitBool m_AutoPercentBegin  = QEmitBool( true );
    QEmitBool m_AutoPercentEnd    = QEmitBool( true );

    QPrabhupadaFilterSlovar m_PrabhupadaFilterSlovar = QPrabhupadaFilterSlovar( QFilterSlovar( QPrabhupadaFindOptions(), "", "" ) );
    int m_MaxID;
    QString m_Schema;
    QPrabhupadaSlovarVector m_PrabhupadaSlovarVector;

    void LanguageIndexChanged( int Value );
    void LanguageUIIndexChanged( int Value );
    void FilterSlovarChanged( QFilterSlovar Value );
    void PrepareLanguageAndMaxID();
    void PreparePrabhupadaSlovarVector();

    static const QString PrabhupadaDictionaryFiles;
    static const QString PrabhupadaDictionaryLang;
    static QPrabhupadaPrimer PrabhupadaPrimer;
    static void PreparePrabhupadaPrimer();
    static QString RemoveDiacritics( const QString& S );
    static bool PrabhupadaCompareLess( const QString& A, const QString& B );
    static bool PrabhupadaCompareMore( const QString& A, const QString& B );
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
  public:
    int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const override;

    inline const QFilterSlovar& GetFilterSlovar() const { return m_LanguageVector.m_Vector[ m_LanguageIndex.m_Value ].m_FilterSlovar; };
    void sortByColumn( int column, Qt::SortOrder order );
    void OrderByChanged( QPrabhupadaDictionaryOrderBy Value );
    void CaseSensitiveChanged( bool Value );
    void RegularExpressionChanged( bool Value );
    void AutoPercentBeginChanged( bool Value );
    void AutoPercentEndChanged( bool Value );
  protected:
};

#endif
