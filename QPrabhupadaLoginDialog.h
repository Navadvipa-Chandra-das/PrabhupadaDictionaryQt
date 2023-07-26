#ifndef QPRABHUPADALOGINDIALOG_H
#define QPRABHUPADALOGINDIALOG_H

#include <QDialog>
#include "QPrabhupada.h"
#include "QPrabhupadaDictionary.h"
#include "ui_QPrabhupadaLoginDialog.h"

//QT_BEGIN_NAMESPACE
//namespace Ui {
//class QPrabhupadaLoginDialog;
//}
//QT_END_NAMESPACE

class QPrabhupadaLoginDialog : public QStorageDialog
{
    Q_OBJECT

public:
    QPrabhupadaLoginDialog(QWidget *parent = nullptr) = delete;
    QPrabhupadaLoginDialog() = delete;
    QPrabhupadaLoginDialog( QPrabhupadaDictionary *APrabhupadaDictionary
                         , QWidget *parent = nullptr );
    ~QPrabhupadaLoginDialog();
    Ui::QPrabhupadaLoginDialog *m_ui = new Ui::QPrabhupadaLoginDialog;
    QString m_DriverName;
    QString m_Schema;
    QPrabhupadaDictionary *m_PrabhupadaDictionary = nullptr;
    bool Connect( QSqlDatabase *DB );
private:
    using inherited = QStorageDialog;
    void Connects();
    void Emits();
    void SQLRadioButton( bool checked );
    void DatabaseToWidget( QSqlDatabase *DB );
    void WidgetToDatabase( QSqlDatabase *DB );
    void LanguageUI_IndexChanged( int Value );
    void pushButtonOKClicked();
    void pushButtonCancelClicked();
protected:
    void LoadFromStream( QDataStream &ST ) override;
    void SaveToStream( QDataStream &ST ) override;
    void changeEvent( QEvent *event ) override;
};

#endif // QPRABHUPADALOGINDIALOG_H
