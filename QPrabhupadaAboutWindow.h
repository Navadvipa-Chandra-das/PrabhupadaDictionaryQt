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

#ifndef QPrabhupadaAboutWindow_H
#define QPrabhupadaAboutWindow_H

#include <QtCore>
#include <QtGui>
#include <QtSql>
#include "QPrabhupada.h"
//#include <QPrabhupadaDictionary.h>
#include "ui_QPrabhupadaAboutWindow.h"

class QPrabhupadaAboutWindow : public QStorageDialog
{
  Q_OBJECT

  public:
    QPrabhupadaAboutWindow() = delete;
    QPrabhupadaAboutWindow( QStorage *AStorage );
    ~QPrabhupadaAboutWindow();
    Ui::QPrabhupadaAboutWindow *m_ui = new Ui::QPrabhupadaAboutWindow;
    QStorage *m_Storage;
  public slots:
    void LoadFromStream( QDataStream &ST );
    void SaveToStream( QDataStream &ST );
  private:
    using inherited = QStorageDialog;
  protected:
    void changeEvent( QEvent *event ) override;
};

#endif
