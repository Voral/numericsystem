#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QGridLayout>
#include <QtGui/QSpinBox>
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
    QSpinBox *edBaseSource;
    QSpinBox *edBaseDestination;
    QSpinBox *edRangeMin;
    QSpinBox *edRangeMax;
    QPushButton *btGenerate;
    QPushButton *btCheck;
    QPushButton *btStop;
    QList <QLabel *> lSource;
    QList <QLineEdit *> lDestination;
    QList <QLabel *> lResult;
    QMenu *mnAbout;
    QMenu *mnLang;
    QAction *acAboutQt;
    QAction *acAbout;
    QActionGroup *agLang;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onGenerate();
    void onStop();
    void onCheck();
    void onAbout();
    void switchLanguage(QAction * action);
};

#endif // MAINWINDOW_H
