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

#ifndef QPrabhupadaGoToLineWindow_H
#define QPrabhupadaGoToLineWindow_H

#include <QtCore>
#include <QtGui>
#include <QtSql>
#include "QPrabhupada.h"
//#include "QPrabhupadaDictionary.h"
#include "ui_QPrabhupadaGoToLineWindow.h"

class QPrabhupadaGoToLineWindow : public QStorageDialog
{
  Q_OBJECT

  public:
    QPrabhupadaGoToLineWindow() = delete;
    QPrabhupadaGoToLineWindow( QStorage *AStorage );
    ~QPrabhupadaGoToLineWindow();
    Ui::QPrabhupadaGoToLineWindow *m_ui = new Ui::QPrabhupadaGoToLineWindow;
    QStorage *m_Storage;
  signals:
    void SignalGoToLine( int Value );
  private:
    using inherited = QStorageDialog;
    void PushButtonGoClicked();
    void PushButtonCancelClicked();
  protected:
    void changeEvent( QEvent *event ) override;
    // void showEvent( QShowEvent *event ) override;
    // void closeEvent( QCloseEvent *event ) override;
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
};

#endif
