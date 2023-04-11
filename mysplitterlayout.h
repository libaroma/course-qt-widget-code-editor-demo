#ifndef MYSPLITTERLAYOUT_H
#define MYSPLITTERLAYOUT_H

#include "mytreeview.h"

#include <QSplitter>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTreeView>
#include <QVBoxLayout>

class MySplitterLayout : public QSplitter
{
    Q_OBJECT
public:
    explicit MySplitterLayout(QWidget * parent =nullptr,QString dir="E:/",QString fontFamily="Consolas",int fontSize=14);

    MyTreeView * getTreeView();

    QLabel *getLabel();

    QTabWidget *getTabWidget();

    void setDir(const QString &dir);

    void setFont(const QFont &font);


public slots:
    void createTab(const QString &filePath);
    void onTabWidgetCloseRequested(int index);

private slots:
    void onDataChanged(const QString &preFilePath,const QString &filePath);

signals:
    void finishCreateTab(const QString &filePath);

private:
    QLabel * createLabel();

    QVBoxLayout * createVLayout(QWidget * parent);

    QTabWidget * createTabWidget();

    MyTreeView * createTreeView();

    QString mFontFamily;
    int mFontSize;
    QString mDir;

    QLabel *mLabel ;
    MyTreeView * mTreeView ;
    QVBoxLayout * mVLayout;
    QTabWidget * mTabWidget;

};

#endif // MYSPLITTERLAYOUT_H
