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
#ifndef VCONFDLG_H
#define VCONFDLG_H

#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QCheckBox>
#include <QtGui/QRadioButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

#define PROGRAM_NAME	"basetest"
#define CFG_NAME	"config"

class VConfDlg : public QDialog
{
    Q_OBJECT
private:
    void setTitle();
    void setValue();
    void offOnMultibyte();
    void offOnBinary();
    static int maxRangeValue;
    static int baseSource;
    static int baseDestination;
    static int rangeMax;
    static int rangeMin;
    static QString name;
    static bool binInverse;
    static bool endianBig;
    QGroupBox *gbGeneral;
    QGroupBox *gbBinary;
    QGroupBox *gbMultiByte;
    QVBoxLayout *laMain;
    QGridLayout *laGeneral;
    QGridLayout *laBinary;
    QGridLayout *laMultiByte;
    QLabel *lbBases;
    QLabel *lbRange;
    QSpinBox *edBaseSource;
    QSpinBox *edBaseDestination;
    QSpinBox *edRangeMin;
    QSpinBox *edRangeMax;
    QCheckBox *chBinInverse;
    QRadioButton *rbEndianBig;
    QRadioButton *rbEndianLittle;
    QHBoxLayout *laButtons;
    QPushButton *btSaveAs;
    QPushButton *btDelete;
    QPushButton *btTest;


public:
    explicit VConfDlg(QWidget *parent = 0);
    static void onLoad(QString iName);
    static int getBaseSource();
    static int getBaseDestination();
    static int getRangeMax();
    static int getRangeMin();
    static QString getName();
    static bool getBinInverse();
    static bool getEndianBig();
    static int getMaxRangeValue();


signals:
    void updateList();

private slots:
    void onSave();
    void onBaseSourceChanged(int value);
    void onBaseSourceEdited();
    void onBaseDestinationChanged(int value);
    void onBaseDestinationEdited();
    void onRangeMaxChanged(int value);
    void onRangeMinChanged(int value);
    void onBinInverseChanged(bool value);
    void onEndianBigChanged();
    void onDelete();
};

#endif // VCONFDLG_H
