#ifndef QPrabhupada_H
#define QPrabhupada_H

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtGui>
#include <QComboBox>
#include <QMainWindow>
#include <QDialog>
#include <map>
#include <memory>

// В CopperSpice you can make a template
/*
template < class TValueType >
class QEmitValue : public QObject
{
  CS_OBJECT( QEmitValue )
  public:
    using inherited = QObject;
    TValueType m_Value;
    bool m_NeedMainWork = true;
    int m_Stop = 0;
    QEmitValue() = delete;
    QEmitValue( TValueType Value )
      : inherited()
      , m_Value( Value ) {};
    ~QEmitValue() {};

    CS_SIGNAL_1( Public, void SignalValueChanged( TValueType Value ) )
    CS_SIGNAL_2( SignalValueChanged, Value )

    void SetValue( TValueType Value )
    {
      if ( m_Stop == 0 && m_Value != Value ) {
        m_Value = Value;
        m_NeedMainWork = true;
        emit SignalValueChanged( m_Value );
      }
    };
    void LoadFromStream( QDataStream &ST )
    {
      TValueType N;
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
  protected:
};

using QEmitInt  = QEmitValue< int >;
using QEmitBool = QEmitValue< bool >;
*/

class QEmitInt : public QObject
{
    Q_OBJECT
public:
    int m_Value;
    bool m_NeedMainWork = true;
    int m_Stop = 0;
    QEmitInt() = delete;
    QEmitInt( int Value )
        : m_Value( Value ) {};
    ~QEmitInt() {};
signals:
    void SignalValueChanged( int Value );
public:
    void SetValue( int Value )
    {
      if ( m_Stop == 0 && m_Value != Value ) {
        m_Value = Value;
        m_NeedMainWork = true;
        emit SignalValueChanged( m_Value );
      }
    };
    void LoadFromStream( QDataStream &ST )
    {
      int N;
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

class QEmitBool : public QObject
{
    Q_OBJECT
public:
    bool m_Value;
    bool m_NeedMainWork = true;
    int m_Stop = 0;
    QEmitBool() = delete;
    QEmitBool( bool Value )
        : m_Value( Value ) {};
    ~QEmitBool() {};
signals:
    void SignalValueChanged( bool Value );
public:
    void SetValue( bool Value )
    {
      if ( m_Stop == 0 && m_Value != Value ) {
        m_Value = Value;
        m_NeedMainWork = true;
        emit SignalValueChanged( m_Value );
      }
    };
    void LoadFromStream( QDataStream &ST )
    {
      bool N;
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

enum class QStorageKind : quint8 { File, DB, Memory };

class QMapMemoryStorage : public std::map< QString, std::unique_ptr< QDataStream > >
{
  private:
    using inherited = std::map< QString, std::unique_ptr< QDataStream > >;
  public:
    QMapMemoryStorage();
    ~QMapMemoryStorage();
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
};

class QStorage : public QObject
{
  Q_OBJECT

  public:
    QStorage();
    ~QStorage();

    bool m_Enabled = true;
    qint8 m_Version = 0;
    QSqlDatabase* m_Database = nullptr;
    QString m_Schema;

    void SetDatabase( QSqlDatabase* Value );
    void setEnabled( bool Value );
    QString PrefixKeyStorage();
    QString KeyStorage( QObject *O, QStorageKind AStorageKind );
    void ResetSettings();

    static void PrepareHistoryComboBox( QComboBox *CB, int MaxCount );
    static void LoadFromStream( QComboBox *CB, QDataStream &ST );
    static void SaveToStream( QComboBox *CB, QDataStream &ST );

    template< class TMap, class TKey, class TValue >
    static void LoadMap( TMap &MP, QDataStream &ST )
    {
      // 1
      std::size_t L;
      ST >> L;
      // 2
      TKey AKey;
      TValue AValue;
      for ( std::size_t I = 0; I < L; ++I ) {
        ST >> AKey;
        ST >> AValue;
        MP[ AKey ] = AValue;
      }
    }

    template< class TMap >
    static void SaveMap( TMap &MP, QDataStream &ST )
    {
      // 1
      ST << MP.size();
      // 2
      for ( typename TMap::iterator I = MP.begin(); I != MP.end(); ++I ) {
        ST << (*I).first;
        ST << (*I).second;
      }
    }

    template< class TVector, class TValue >
    static void LoadVector( TVector &VC, QDataStream &ST )
    {
      // 1
      std::size_t L;
      ST >> L;
      // 2
      TValue AValue;
      for ( std::size_t I = 0; I < L; ++I ) {
        ST >> AValue;
        VC.push_back( AValue );
      }
    }

    template< class TVector >
    static void SaveVector( TVector &VC, QDataStream &ST )
    {
      // 1
      ST << VC.size();
      // 2
      for ( typename TVector::iterator I = VC.begin(); I != VC.end(); ++I ) {
        ST << (*I);
      }
    }

    bool LoadObject( QObject *O, QStorageKind AStorageKind );
    void SaveObject( QObject *O, QStorageKind AStorageKind );
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
  public:
    void SaveToStreamPrepareHistory( QComboBox *CB, QDataStream &ST, int HistoryCount );

    static const QChar CharPercent;
    static const QChar CharUnderline;

    // This function was suggested to me by Lord Sri Krishna!
    static bool Like( QString::iterator t_end, QString::iterator s_end, QString::iterator t, QString::iterator s );
    // Lord Sri Krishna suggested this function to another programmer! It is better, since there is no recursion and the stack memory cannot overflow!
    static bool LikeBest( const QString& Template, const QString& Source );
  private:
    using inherited = QObject;
    QSqlQuery* m_Query = nullptr;
    QFile *m_File = nullptr;
    QSaveFile *m_SaveFile = nullptr;
    QDataStream *m_Stream = nullptr;
    QString m_FileName;
    QByteArray *m_ByteArray;
    QString m_SQL;
    QMapMemoryStorage m_MapMemoryStorage;
    bool BeginLoad( QObject *O, QStorageKind AStorageKind );
    void EndLoad( QStorageKind AStorageKind );
    void BeginSave( QObject *O, QStorageKind AStorageKind );
    void EndSave( QStorageKind AStorageKind );
};

class QStorageMainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    QStorageMainWindow( QWidget *parent = nullptr );
    ~QStorageMainWindow();
    QStorageKind m_StorageKind = QStorageKind::File;
    QStorage *m_Storage = nullptr;
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
  private:
    using inherited = QMainWindow;
  protected:
    void closeEvent( QCloseEvent *event ) override;
};

class QStorageDialog : public QDialog
{
    Q_OBJECT

public:
    QStorageDialog( QWidget *parent = nullptr );
    ~QStorageDialog();
public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
private:
    using inherited = QDialog;
};

#endif
