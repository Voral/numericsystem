/********************************************************************************/
/*                                                                              */
/*    Copyright 2012 Alexander Vorobyev (Voral)                                 */
/*    http://va-soft.ru/                                                        */
/*                                                                              */
/*    This file is part of basetest.                                            */
/*                                                                              */
/*    Basetest is free software: you can redistribute it and/or modify          */
/*    it under the terms of the GNU General Public License as published by      */
/*    the Free Software Foundation, either version 3 of the License, or         */
/*    (at your option) any later version.                                       */
/*                                                                              */
/*    Basetest is distributed in the hope that it will be useful,               */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*    GNU General Public License for more details.                              */
/*                                                                              */
/*    You should have received a copy of the GNU General Public License         */
/*    along with basetest.  If not, see <http://www.gnu.org/licenses/>.         */
/*                                                                              */
/********************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtCore/QList>
#include <QtCore/QTranslator>


const int testItemCount = 10;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void retranslateUi();
    QString inverse(QString str);
    int inverseWord(int value);
    QTranslator appTranslator;
    QTranslator qtTranslator;
    QWidget *main;
    QVBoxLayout *laMain;
    QGroupBox *gbSettings;
    QGroupBox *gbTest;
    QGridLayout *laSettings;
    QGridLayout *laTest;
    QLabel *lbBases;
    QLabel *lbRange;
    QLabel *lbResultTitle;
    QLabel *lbResultCount;
    QLabel *lbResultPercent;
    QLabel *lbBinInverse;
    QLabel *lbEndian;
    QPushButton *btGenerate;
    QPushButton *btCheck;
    QPushButton *btStop;
    QList <QLabel *> lSource;
    QList <QLineEdit *> lDestination;
    QList <QLabel *> lResult;
    QMenu *mnAbout;
    QMenu *mnLang;
    QMenu *mnConf;
    QAction *acAboutQt;
    QAction *acAbout;
    QAction *acConfig;
    QActionGroup *agLang;
    QActionGroup *agPreset;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void changeEvent(QEvent *event);
    void onGenerate();
    void onStop();
    void onCheck();
    void onAbout();
    void onConfig();
    void onUpdatePresets(bool checkOld = false);
    void onLoadPreset(QAction* action);
    void switchLanguage(QAction* action);
};

#endif // MAINWINDOW_H
