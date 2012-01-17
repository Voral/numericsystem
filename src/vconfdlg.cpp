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
#include "vconfdlg.h"
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtGui/QInputDialog>

int VConfDlg::maxRangeValue = 65535;
int VConfDlg::baseSource = 2;
int VConfDlg::baseDestination = 10;
int VConfDlg::rangeMax = 255;
int VConfDlg::rangeMin = 0;
QString VConfDlg::name = "Noname";
bool VConfDlg::binInverse = false;
bool VConfDlg::endianBig = false;

VConfDlg::VConfDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setTitle();
    this->laMain = new QVBoxLayout(this);
    this->setLayout(this->laMain);

    // general
    this->gbGeneral = new QGroupBox(tr("General"));
    this->laMain->addWidget(this->gbGeneral);
    this->lbBases = new QLabel(tr("Bases (sourece/destination) 2 - 36"));
    this->lbRange = new QLabel(tr("Numbers range (min/max) 0 - %1").arg(this->maxRangeValue));
    this->edBaseSource = new QSpinBox();
    this->edBaseSource->setRange(2,36);
    connect(this->edBaseSource,SIGNAL(valueChanged(int)),this,SLOT(onBaseSourceChanged(int)));
    connect(this->edBaseSource,SIGNAL(editingFinished()),this,SLOT(onBaseSourceEdited()));
    this->edBaseDestination = new QSpinBox();
    this->edBaseDestination->setRange(2,36);
    connect(this->edBaseDestination,SIGNAL(valueChanged(int)),this,SLOT(onBaseDestinationChanged(int)));
    this->edRangeMax = new QSpinBox();
    connect(this->edRangeMax,SIGNAL(valueChanged(int)),this,SLOT(onRangeMaxChanged(int)));
    this->edRangeMin = new QSpinBox();
    connect(this->edRangeMin,SIGNAL(valueChanged(int)),this,SLOT(onRangeMinChanged(int)));

    this->laGeneral = new QGridLayout();
    this->laGeneral->addWidget(this->lbBases,0,0,1,1,Qt::AlignLeft);
    this->laGeneral->addWidget(this->edBaseSource,0,1,1,1,Qt::AlignLeft);
    this->laGeneral->addWidget(this->edBaseDestination,0,2,1,1,Qt::AlignLeft);
    this->laGeneral->addWidget(this->lbRange,1,0,1,1,Qt::AlignLeft);
    this->laGeneral->addWidget(this->edRangeMin,1,1,1,1,Qt::AlignLeft);
    this->laGeneral->addWidget(this->edRangeMax,1,2,1,1,Qt::AlignLeft);
    this->gbGeneral->setLayout(this->laGeneral);

    // binary
    this->gbBinary = new QGroupBox(tr("Binary"));
    this->laMain->addWidget(this->gbBinary);
    this->laBinary = new QGridLayout();
    this->chBinInverse = new QCheckBox(tr("Inverse byte order"),this);
    connect(this->chBinInverse,SIGNAL(toggled(bool)),this,SLOT(onBinInverseChanged(bool)));
    this->laBinary->addWidget(this->chBinInverse,0,0,1,1,Qt::AlignLeft);
    this->gbBinary->setLayout(this->laBinary);

    //multibyte
    this->gbMultiByte = new QGroupBox(tr("Multibyte"));
    this->laMain->addWidget(this->gbMultiByte);
    this->laMultiByte = new QGridLayout();
    this->rbEndianBig = new QRadioButton(tr("Big-endian"));
    connect(rbEndianBig,SIGNAL(toggled(bool)),this,SLOT(onEndianBigChanged()));
    this->rbEndianLittle = new QRadioButton(tr("Little-endian"));
    this->rbEndianLittle->setChecked(true);
    this->laMultiByte->addWidget(this->rbEndianBig,0,0,1,1,Qt::AlignLeft);
    this->laMultiByte->addWidget(this->rbEndianLittle,0,1,1,1,Qt::AlignLeft);
    this->gbMultiByte->setLayout(this->laMultiByte);

    this->laButtons = new QHBoxLayout();
    this->btSaveAs = new QPushButton(tr("Save As..."));
    connect(this->btSaveAs,SIGNAL(clicked()),this,SLOT(onSave()));
    this->btDelete = new QPushButton(tr("Delete"));
    connect(this->btDelete,SIGNAL(clicked()),this,SLOT(onDelete()));
    this->btTest = new QPushButton(tr("Close"));
    connect(this->btTest,SIGNAL(clicked()),this,SLOT(accept()));
    this->laButtons->addWidget(this->btSaveAs,0,Qt::AlignRight);
    this->laButtons->addWidget(this->btDelete,0,Qt::AlignRight);
    this->laButtons->addWidget(this->btTest,0,Qt::AlignRight);
    this->laMain->addLayout(this->laButtons);
    this->btSaveAs->adjustSize();
    this->btDelete->setFixedSize(this->btSaveAs->size());
    this->btTest->setFixedSize(this->btSaveAs->size());

    this->offOnMultibyte();
    this->offOnBinary();

    this->setValue();
    this->adjustSize();
    this->setFixedSize(this->size());
    this->setWindowModified(false);
}
void VConfDlg::onLoad(QString iName)
{
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope,"Voral","basetest",0);
    cfg.setIniCodec("UTF-8");
    cfg.beginGroup(iName);
    VConfDlg::baseSource = cfg.value("baseSource",VConfDlg::baseSource).toInt();
    VConfDlg::baseDestination = cfg.value("baseDestination",VConfDlg::baseDestination).toInt();
    VConfDlg::rangeMax = cfg.value("rangeMax",VConfDlg::rangeMax).toInt();
    VConfDlg::rangeMin = cfg.value("rangeMin",VConfDlg::rangeMin).toInt();
    VConfDlg::binInverse = cfg.value("binInverse",VConfDlg::binInverse).toBool();
    VConfDlg::endianBig = cfg.value("endianBig",VConfDlg::endianBig).toBool();
    VConfDlg::name = iName;
    cfg.endGroup();
}

void VConfDlg::onSave()
{
    bool ok;
    QString text = QInputDialog::getText(this,tr("Preset name"),tr("Name"), QLineEdit::Normal, "",&ok);
    if (ok && !text.isEmpty())
    {
        this->name = text;
        QSettings cfg(QSettings::IniFormat, QSettings::UserScope,"Voral","basetest",this);
        cfg.setIniCodec("UTF-8");
        cfg.setValue(QString::fromUtf8("%1/baseSource").arg(this->name),this->baseSource);
        cfg.setValue(QString::fromUtf8("%1/baseDestination").arg(this->name),this->baseDestination);
        cfg.setValue(QString::fromUtf8("%1/rangeMin").arg(this->name),this->rangeMin);
        cfg.setValue(QString::fromUtf8("%1/rangeMax").arg(this->name),this->rangeMax);
        cfg.setValue(QString::fromUtf8("%1/binInverse").arg(this->name),this->binInverse);
        cfg.setValue(QString::fromUtf8("%1/endianBig").arg(this->name),this->endianBig);
        this->setWindowModified(false);
        this->setTitle();
        emit updateList();
    }
}
void VConfDlg::setTitle()
{
    this->setWindowTitle(tr("Preset \"%1\"[*]").arg(this->name));
}
void VConfDlg::setValue()
{
    this->edRangeMax->setRange(0,this->maxRangeValue);
    this->edBaseSource->setValue(this->baseSource);
    this->edBaseDestination->setValue(this->baseDestination);
    this->edRangeMax->setValue(this->rangeMax);
    this->edRangeMin->setRange(0,this->rangeMax-1);
    this->edRangeMin->setValue(this->rangeMin);
    this->chBinInverse->setChecked(binInverse);
    this->rbEndianLittle->setChecked(this->endianBig);
}

void VConfDlg::onBaseSourceChanged(int value)
{
    this->setWindowModified(true);
    this->baseSource = value;
}
void VConfDlg::onBaseSourceEdited()
{
    if (this->edBaseDestination->value()==this->edBaseSource->value())
    {
        if (this->edBaseDestination->value()==edBaseDestination->maximum())
            this->edBaseDestination->setValue(this->edBaseSource->value()-1);
        else
            this->edBaseDestination->setValue(this->edBaseSource->value()+1);
    }
    this->offOnBinary();
    this->offOnMultibyte();
}

void VConfDlg::onBaseDestinationChanged(int value)
{
    this->setWindowModified(true);
    this->baseDestination = value;
}
void VConfDlg::onBaseDestinationEdited()
{
    if (this->edBaseSource->value()==this->edBaseDestination->value())
    {
        if (this->edBaseSource->value()==edBaseSource->maximum())
            this->edBaseSource->setValue(this->edBaseDestination->value()-1);
        else
            this->edBaseSource->setValue(this->edBaseDestination->value()+1);
    }
    this->offOnBinary();
    this->offOnMultibyte();
}
void VConfDlg::onRangeMaxChanged(int value)
{
    this->setWindowModified(true);
    this->rangeMax = value;
    if (this->rangeMin>=value)
    {
        this->rangeMin=value-1;
    }
    this->edRangeMin->setMaximum(value);
    this->offOnMultibyte();
    this->offOnBinary();
}
void VConfDlg::onRangeMinChanged(int value)
{
    this->rangeMin = value;
    this->setWindowModified(true);
}
void VConfDlg::onBinInverseChanged(bool value)
{
    this->setWindowModified(true);
    this->binInverse = value;
}
void VConfDlg::onEndianBigChanged()
{
    this->setWindowModified(true);
    this->endianBig = this->rbEndianBig->isChecked();
}
void VConfDlg::onDelete()
{
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope,"Voral","basetest",this);
    cfg.setIniCodec("UTF-8");
    cfg.remove(this->name);
    VConfDlg::baseSource = 2;
    VConfDlg::baseDestination = 10;
    VConfDlg::rangeMax = 255;
    VConfDlg::rangeMin = 0;
    VConfDlg::name = "Noname";
    VConfDlg::binInverse = false;
    VConfDlg::endianBig = false;
    this->setValue();
    this->setTitle();
    this->setWindowModified(false);
    emit this->updateList();
}

int VConfDlg::getBaseSource()
{
    return VConfDlg::baseSource;
}
int VConfDlg::getBaseDestination()
{
    return VConfDlg::baseDestination;
}
int VConfDlg::getRangeMax()
{
    return VConfDlg::rangeMax;
}
int VConfDlg::getRangeMin()
{
    return VConfDlg::rangeMin;
}
QString VConfDlg::getName()
{
    return VConfDlg::name;
}
bool VConfDlg::getBinInverse()
{
    return VConfDlg::binInverse;
}
bool VConfDlg::getEndianBig()
{
    return VConfDlg::endianBig;
}
int VConfDlg::getMaxRangeValue()
{
    return VConfDlg::maxRangeValue;
}
void VConfDlg::offOnMultibyte()
{
    bool state = (this->rangeMax>255)
            &&((this->baseDestination==2)||(this->baseDestination==16)
            ||(this->baseSource==2)||(this->baseSource==16));

    this->gbMultiByte->setEnabled(state);
    if (!state) this->rbEndianLittle->setChecked(true);
}
void VConfDlg::offOnBinary()
{
    bool state = (this->rangeMax<=255)&&((this->baseDestination==2)||(this->baseSource==2));
    this->gbBinary->setEnabled(state);
    if (!state) this->chBinInverse->setChecked(false);
}
