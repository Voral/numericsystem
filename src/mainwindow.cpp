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

#include "mainwindow.h"
#include <QtCore/QDateTime>
#include <QtCore/QDir>
#include <QtGui/QMenuBar>
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QStyle>
#include <QtGui/QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // For lang menu
    tr("English");
    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);
    this->main =new QWidget(this);
    this->gbSettings = new QGroupBox();
    this->gbTest = new QGroupBox();
    this->laMain = new QVBoxLayout();
    this->laMain->addWidget(this->gbSettings,0,Qt::AlignTop);
    this->laMain->addWidget(this->gbTest,0,Qt::AlignTop);
    this->main->setLayout(this->laMain);
    this->setCentralWidget(this->main);

    this->lbBases = new QLabel();
    this->lbRange = new QLabel();
    this->edBaseSource = new QSpinBox();
    this->edBaseSource->setRange(2,36);
    this->edBaseSource->setValue(2);
    this->edBaseDestination = new QSpinBox();
    this->edBaseDestination->setRange(2,36);
    this->edBaseDestination->setValue(10);
    this->edRangeMin = new QSpinBox();
    this->edRangeMin->setRange(0,255);
    this->edRangeMin->setValue(0);
    this->edRangeMax = new QSpinBox();
    this->edRangeMax->setRange(0,255);
    this->edRangeMax->setValue(255);
    this->btGenerate = new QPushButton();
    connect(this->btGenerate,SIGNAL(clicked()),this,SLOT(onGenerate()));

    this->laSettings = new QGridLayout();
    this->laSettings->addWidget(this->lbBases,0,0,1,1,Qt::AlignLeft);
    this->laSettings->addWidget(this->edBaseSource,0,1,1,1,Qt::AlignLeft);
    this->laSettings->addWidget(this->edBaseDestination,0,2,1,1,Qt::AlignLeft);
    this->laSettings->addWidget(this->lbRange,1,0,1,1,Qt::AlignLeft);
    this->laSettings->addWidget(this->edRangeMin,1,1,1,1,Qt::AlignLeft);
    this->laSettings->addWidget(this->edRangeMax,1,2,1,1,Qt::AlignLeft);
    this->laSettings->addWidget(this->btGenerate,0,3,2,1,Qt::AlignCenter);
    this->gbSettings->setLayout(this->laSettings);

    QFont ft =  this->font();
    ft.setFamily("Monospace");
    ft.setStyleHint(QFont::Monospace);

    this->laTest = new QGridLayout();
    for(register int i = 0; i < testItemCount; ++i)
    {
        this->lSource.append(new QLabel());
        this->lDestination.append(new QLineEdit());
        this->lResult.append(new QLabel());
        this->laTest->addWidget(this->lSource.at(i),i,0,1,1,Qt::AlignCenter);
        this->laTest->addWidget(this->lDestination.at(i),i,1,1,1,Qt::AlignLeft);
        this->laTest->addWidget(this->lResult.at(i),i,2,1,1,Qt::AlignLeft);
        this->lSource.at(i)->setFont(ft);
        this->lDestination.at(i)->setFont(ft);
    }
    this->lbResultTitle = new QLabel();
    this->lbResultCount = new QLabel();
    this->lbResultPercent = new QLabel();
    this->laTest->addWidget(this->lbResultTitle,0,3,1,1,Qt::AlignCenter);
    this->laTest->addWidget(this->lbResultCount,1,3,1,1,Qt::AlignCenter);
    this->laTest->addWidget(this->lbResultPercent,2,3,1,1,Qt::AlignCenter);

    this->btCheck = new QPushButton();
    connect(this->btCheck,SIGNAL(clicked()),this,SLOT(onCheck()));
    this->btStop = new QPushButton();
    this->btStop->setFocusPolicy(Qt::NoFocus);
    connect(this->btStop,SIGNAL(clicked()),this,SLOT(onStop()));
    this->laTest->addWidget(this->btStop,testItemCount-2,3,1,1,Qt::AlignCenter);
    this->laTest->addWidget(this->btCheck,testItemCount-1,3,1,1,Qt::AlignCenter);
    this->gbTest->setLayout(this->laTest);
    this->gbTest->setEnabled(false);

    this->mnLang = this->menuBar()->addMenu(tr(""));

    this->agLang = new QActionGroup(this);
    connect(this->agLang, SIGNAL(triggered(QAction *)), this, SLOT(switchLanguage(QAction *)));
    QDir dir(":/trans");
    QStringList fileNames = dir.entryList(QStringList("basetest_*.qm"));
    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.truncate(locale.lastIndexOf('.'));
        QTranslator translator;
        translator.load(fileNames[i], ":/trans");
        QString language = translator.translate("MainWindow", "English");
        QAction *action = new QAction(language, this);
        action->setCheckable(true);
        action->setData(locale);
        this->mnLang->addAction(action);
        this->agLang->addAction(action);
        if (locale.compare(QLocale::system().name().left(2)) == 0) action->setChecked(true);
    }
    this->mnAbout = this->menuBar()->addMenu("");
    this->acAboutQt= new QAction("", this);
    connect(this->acAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    this->acAbout= new QAction("", this);
    connect(this->acAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
    this->mnAbout->addAction(this->acAbout);
    this->mnAbout->addAction(this->acAboutQt);
    retranslateUi();
}

MainWindow::~MainWindow()
{
    this->acAboutQt->deleteLater();
    this->acAbout->deleteLater();
    this->agLang->deleteLater();
    this->mnAbout->deleteLater();
    this->mnLang->deleteLater();
    this->btGenerate->deleteLater();
    this->btCheck->deleteLater();
    this->btStop->deleteLater();
    for(register int i = 0; i < testItemCount; ++i)
    {
        QLabel * label = qobject_cast<QLabel *>(this->lSource.at(i));
        delete label;
        QLineEdit *answer = qobject_cast<QLineEdit *>(this->lDestination.at(i));
        delete answer;
        label = qobject_cast<QLabel *>(this->lResult.at(i));
        delete label;
    }
    this->lbBases->deleteLater();
    this->lbRange->deleteLater();
    this->lbResultTitle->deleteLater();
    this->lbResultCount->deleteLater();
    this->lbResultPercent->deleteLater();
    this->edBaseSource->deleteLater();
    this->edBaseDestination->deleteLater();
    this->edRangeMin->deleteLater();
    this->edRangeMax->deleteLater();
    this->laSettings->deleteLater();
    this->laTest->deleteLater();
    this->gbSettings->deleteLater();
    this->gbTest->deleteLater();
    this->laMain->deleteLater();
    this->main->deleteLater();
}
void MainWindow::onGenerate()
{
    this->gbSettings->setEnabled(false);
    // QT 4.7
    this->lbResultCount->setText("");
    this->lbResultPercent->setText("");
    qsrand((uint)QDateTime::currentMSecsSinceEpoch());

    int maxLenght = QString::number(this->edRangeMax->maximum(),this->edBaseSource->value()).length();
    for(register int i = 0; i < testItemCount; ++i)
    {
        unsigned int value = qrand() % (this->edRangeMax->value() + 1)+ this->edRangeMin->value();
        QLabel * label = qobject_cast<QLabel *>(this->lSource.at(i));
        label->setText(QString("%1").arg(QString::number(value,this->edBaseSource->value()),maxLenght,'0'));
        label = qobject_cast<QLabel *>(this->lResult.at(i));
        label->setText("");
        QLineEdit *answer = qobject_cast<QLineEdit *>(this->lDestination.at(i));
        answer->setText("");
    }
    this->gbTest->setEnabled(true);
}
void MainWindow::onStop()
{
    this->gbSettings->setEnabled(true);
    this->gbTest->setEnabled(false);
}
void MainWindow::onCheck()
{
    int goodAnswer = 0;
    for(register int i = 0; i < testItemCount; ++i)
    {
        QLabel * label = qobject_cast<QLabel *>(this->lSource.at(i));
        bool okSrc, okDst;
        int source = label->text().toInt(&okSrc,this->edBaseSource->value());
        QLineEdit *answer = qobject_cast<QLineEdit *>(this->lDestination.at(i));
        int destination = answer->text().toInt(&okDst,this->edBaseDestination->value());
        label = qobject_cast<QLabel *>(this->lResult.at(i));
        if ((!okSrc)||(!okDst))
        {
            label->setText(tr("Error"));
        }
        else
        {
            if (source==destination)
            {
                label->setText(tr("Ok"));
                ++goodAnswer;
            }
            else
            {
                label->setText(tr("No"));
            }
        }
    }
    this->lbResultCount->setText(QString(tr("%1 from %2")).arg(goodAnswer).arg(testItemCount));
    this->lbResultPercent->setText(QString(tr("%1 %")).arg(goodAnswer*100/testItemCount));
    this->gbTest->setEnabled(true);
}
void MainWindow::onAbout()
{
    QMessageBox::about(this,tr("About Number system"),tr("Simualtor \"Number systems\" for bases between 2 and 36.<br>Version: 1.0<br>Copyright 2012 Alexander Vorobyev (Voral)<br>Autor: Alexander Vorobyev<br>Site: http://va-soft.ru/"));
}

void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();
    appTranslator.load("basetest_" + locale, ":/trans");
    qtTranslator.load("qt_" + locale, ":/trans");
    retranslateUi();
}
void MainWindow::retranslateUi()
{
    this->mnAbout->setTitle(tr("About"));
    this->acAboutQt->setText(tr("About &Qt ..."));
    this->acAbout->setText(tr("About ..."));
    this->mnLang->setTitle(tr("Language"));
    this->btStop->setText(tr("Stop"));
    this->btCheck->setText(tr("Check"));
    this->lbResultTitle->setText(tr("Result:"));
    this->btGenerate->setText(tr("Start"));
    this->lbBases->setText(tr("Bases (sourece/destination) 2 - 36"));
    this->lbRange->setText(tr("Numbers range (min/max) 0 - 255"));
    this->gbTest->setTitle(tr("Test"));
    this->gbSettings->setTitle(tr("Settings"));
    this->setWindowTitle(tr("Number system"));

    this->btCheck->adjustSize();
    this->btStop->setFixedWidth(this->btCheck->width());
    //calc max field size
    QString tSrc, tDst, tErr;
    QLabel * label = qobject_cast<QLabel *>(this->lSource.at(0));
    tSrc = label->text();
    label->setText(QString("%1").arg(QString::number(this->edRangeMax->maximum(),2),8,'0'));
    label = qobject_cast<QLabel *>(this->lResult.at(0));
    tErr = label->text();
    label->setText(tr("not checking"));
    QLineEdit *answer = qobject_cast<QLineEdit *>(this->lDestination.at(0));
    tDst = answer->text();
    answer->setText(QString("%1").arg(QString::number(this->edRangeMax->maximum(),2),8,'0'));

    this->gbSettings->adjustSize();
    this->gbTest->adjustSize();
    this->adjustSize();
    this->setMaximumSize(this->size());

    label = qobject_cast<QLabel *>(this->lSource.at(0));
    label->setText(tSrc);
    label = qobject_cast<QLabel *>(this->lResult.at(0));
    label->setText(tErr);
    answer = qobject_cast<QLineEdit *>(this->lDestination.at(0));
    answer->setText(tDst);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
}

