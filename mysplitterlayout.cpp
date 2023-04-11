#include "mycodeeditor.h"
#include "mysplitterlayout.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>


MySplitterLayout::MySplitterLayout(QWidget *parent,QString dir,QString fontFamily,int fontSize )
    :QSplitter(parent)
    ,mFontFamily(fontFamily)
    ,mFontSize(fontSize)
    ,mDir(dir)

{

    mLabel = createLabel();
    mTreeView =createTreeView();


    QWidget * vLayoutWidget = new QWidget(this);
    mVLayout =createVLayout(vLayoutWidget);

    mVLayout->addWidget(mLabel);
    mVLayout->addWidget(mTreeView);

    mTabWidget =createTabWidget();

    addWidget(vLayoutWidget);
    addWidget(mTabWidget);


    //设置分割比距比例
    QList<int> sizeLists;
    sizeLists<<1000<<4000;
    setSizes(sizeLists);

    setHandleWidth(0);
}

void MySplitterLayout::createTab(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法打开此文件:"+file.errorString());
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();


    int tabCount= mTabWidget->count();
    for(int index =0;index<tabCount;index++){
        qDebug()<<mTabWidget->tabText(index);
        if(mTabWidget->tabText(index)==filePath){
            return;
        }
    }

    //创建对象
    MyCodeEditor * codeEditor = new MyCodeEditor(this,QFont(mFontFamily,mFontSize));
    codeEditor->setPlainText(text);

    //设置文件名
    codeEditor->setFileName(filePath);
    //添加tab
    mTabWidget->addTab(codeEditor,filePath);
    //设置当前索引
    mTabWidget->setCurrentIndex(mTabWidget->count()-1);

    file.close();

    emit finishCreateTab(filePath);

}

void MySplitterLayout::onDataChanged(const QString &preFilePath,const QString &filePath)
{
    int count = mTabWidget->count();
    for(int i = 0; i<count ; i++){
        if(preFilePath==mTabWidget->tabText(i)){
            mTabWidget->setTabText(i,filePath);
            MyCodeEditor * codeEditor =( MyCodeEditor *) mTabWidget->widget(i);
            if(codeEditor)
                codeEditor->setFileName(filePath);
            return;
        }
    }
}

MyTreeView *MySplitterLayout::getTreeView()
{
    return mTreeView;
}

QLabel *MySplitterLayout::getLabel()
{
    return mLabel;
}

QTabWidget *MySplitterLayout::getTabWidget()
{
    return mTabWidget;
}

void MySplitterLayout::setDir(const QString &dir)
{
    mDir = dir;
    mTreeView->setDir(dir);
    mLabel->setText(dir);
}

void MySplitterLayout::setFont(const QFont &font)
{
    mFontFamily = font.family();
    mFontSize =font.pointSize();
    mLabel->setFont(QFont(mFontFamily,mFontSize));
    MyCodeEditor * codeEditor = (MyCodeEditor *)mTabWidget->currentWidget();
    if(codeEditor)
        codeEditor->setAllFont(QFont(mFontFamily,mFontSize));
}


QLabel *MySplitterLayout::createLabel()
{
    QLabel * label = new QLabel(this);
    //设置label
    label->setFont(QFont(mFontFamily,mFontSize));
    label->setText(mDir);
    label->setIndent(5);
    label->setMinimumHeight(25);

    QPalette palette;
    palette.setColor(QPalette::Background,QColor(250,250,250));
    label->setPalette(palette);
    label->setAutoFillBackground(true);

    return label;
}

MyTreeView *MySplitterLayout::createTreeView()
{
    MyTreeView * treeView =   new MyTreeView(this,mDir);

    treeView->setFrameShape(QFrame::NoFrame);

    connect(treeView,SIGNAL(createTab(const QString &)),this,SLOT(createTab(const QString &)));

    connect(treeView,SIGNAL(onDataChanged(const QString & ,const QString &)),this,SLOT(onDataChanged(const QString & ,const QString &)));

    return treeView;
}


QVBoxLayout *MySplitterLayout::createVLayout(QWidget *parent)
{
    QVBoxLayout * vLayout = new QVBoxLayout(parent);

    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    return vLayout;
}

QTabWidget *MySplitterLayout::createTabWidget()
{
    QTabWidget * tabWidget = new QTabWidget(this);

    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setDocumentMode(true);

    connect(tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(onTabWidgetCloseRequested(int)));
    return tabWidget;
}

void MySplitterLayout::onTabWidgetCloseRequested(int index)
{
    MyCodeEditor * codeEditor = (MyCodeEditor*)mTabWidget->currentWidget();
    if(!codeEditor->checkSaved()){
        QMessageBox::StandardButton btn = QMessageBox::question(this,"警告","您还没有保存文档！是否保存？",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if(btn ==QMessageBox::Yes){
            if(codeEditor->saveFile()){
                mTabWidget->setTabText(mTabWidget->currentIndex(),codeEditor->getFileName());
            }
            return;
        }else if(btn ==QMessageBox::Cancel)
            return;
    }
    mTabWidget->removeTab(index);
    emit finishCreateTab(codeEditor->getFileName());
    delete codeEditor;
}
