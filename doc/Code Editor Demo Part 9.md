## 九 布局代码重构

### 69 创建SplitterLayout

- mysplitterlayout.h

```c++
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
    explicit MySplitterLayout(QWidget * parent =nullptr,QString dir="E:/");

    MyTreeView * getTreeView();

    QLabel *getLabel();

    QTabWidget *getTabWidget();

    void setDir(const QString &dir);


public slots:
    void createTab(const QString &filePath);

private slots:
    void onDataChanged(const QModelIndex &index);

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

```

- mysplitterlayout.cpp

```c++
#include "mycodeeditor.h"
#include "mysplitterlayout.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>


MySplitterLayout::MySplitterLayout(QWidget *parent,QString dir )
    :QSplitter(parent)
    ,mFontFamily("Consolas")
    ,mFontSize(14)
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
```

### 70 完善SplitterLayout

- mysplitterlayout.cpp

```c++
#include "mycodeeditor.h"
#include "mysplitterlayout.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>


MySplitterLayout::MySplitterLayout(QWidget *parent,QString dir )
    :QSplitter(parent)
    ,mFontFamily("Consolas")
    ,mFontSize(14)
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

QLabel *MySplitterLayout::createLabel()
{
    QLabel * label = new QLabel(this);
    //设置label
    label->setFont(QFont("mFontFamily",11));
    label->setText("mDir");
    label->setIndent(5);

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

    connect(treeView,SIGNAL(onDataChanged(const QModelIndex &)),this,SLOT(onDataChanged(const QModelIndex &)));

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

    tabWidget->setDocumentMode(true);
    return tabWidget;
}

```

### 71 重写TreeView

- mytreeview.h

```c++
#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include "myfilesystemmodel.h"

#include <QTreeView>
#include <QObject>
#include <QWidget>

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit MyTreeView(QWidget * parent=nullptr,QString dir="E:/");

    void newFile();

    void setDir(const QString &dir);

private slots:
    void showCustomContextMenu(const QPoint &pos);
    void onTreeViewDoubleClicked(const QModelIndex &index);
    void onModelDataChanged(const QModelIndex &index);

signals:
    void createTab(const QString &filePath);
    void onDataChanged(const QModelIndex &index);

private:
    QString mFontFamily;
    int mFontSize;
    MyFileSystemModel * mFileSystemModel ;

    QString mDir;

    QString tempFilePath;

    void setTreeViewModel();

};

#endif // MYTREEVIEW_H

```

- mytreeview.cpp

```c++
#include "mycodeeditor.h"
#include "mytreeview.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QClipboard>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>

MyTreeView::MyTreeView(QWidget * parent,QString dir)
    :QTreeView(parent)
    ,mFontFamily("Consolas")
    ,mFontSize(14)
    ,mFileSystemModel(0)
    ,mDir(dir)
{
    //设置model
    setTreeViewModel();

    //隐藏header
    setHeaderHidden(true);

    //设置右键菜单
    setContextMenuPolicy(Qt::CustomContextMenu);

    //添加connect
    //添加右键信号事件
    connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(showCustomContextMenu(const QPoint &)));

    //取消双击编辑
    setEditTriggers(QTreeView::NoEditTriggers);

    //绑定双击事件
    connect(this,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(onTreeViewDoubleClicked(const QModelIndex &)));


}

```

### 72 新建文件

- mainwindow.cpp

```c++
//新建文件
void MainWindow::on_new_file_triggered()
{
    mSplitterLayout->getTreeView()->newFile();

}
```

- mytreeview.cpp

```c++
void MyTreeView::newFile()
{
    QModelIndex index = currentIndex();
    QString filePath =   mFileSystemModel->filePath(index);
    if(!mFileSystemModel->isDir(index)){
        filePath = filePath.left(filePath.length()-mFileSystemModel->fileName(index).length());
    }
    if(filePath.isEmpty()) return;
    QString fileName = filePath+(filePath.endsWith("/")?"":"/")+"新建文件"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss")+".xjy";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::critical(this,"失败","创建新文件失败!可能没有权限或文件已经存在！");
    }
    file.close();

    emit createTab(fileName);
}
```

- mysplitterlayout.cpp

```c++
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
```

### 73 打开文件夹

- mainwindow.cpp

```c++
//打开文件
void MainWindow::on_open_dir_triggered()
{
    QString dirFromSetttings = mSettings->value("dir",mDir).toString();
    QString dir = QFileDialog::getExistingDirectory(this,"选择文件夹",dirFromSetttings,QFileDialog::ShowDirsOnly);
    if(dir.isEmpty()) return;
    mSettings->setValue("config/dir",dir);
    mDir = dir;
    mSplitterLayout->setDir(mDir);
//    setTreeViewModel();
   mSplitterLayout->getLabel()->setText(mDir);
}
```

- mytreeview.cpp

```c++
void MyTreeView::setDir(const QString &dir)
{
    mDir=dir;
    setTreeViewModel();
}
```

### 74 文件、文件夹重命名

```c++
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
```

### 75 Tab标签页的关闭

```c++

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
```

### 76 设置Label

```c++
void MySplitterLayout::setDir(const QString &dir)
{
    mDir = dir;
    mTreeView->setDir(dir);
    mLabel->setText(dir);
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

```

### 77 设置字体

```c++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mFontFamily("Consolas")
    , mFontSize(14)
    , mSplitterLayout(0)
{
    ...

    mSplitterLayout = new MySplitterLayout(this,mDir,mFontFamily,mFontSize);

...
}
```



```c++
void MyCodeEditor::setAllFont(QFont font)
{
    this->setFont(font);
    mHighlighter->setFont(font);
    mHighlighter->rehighlight();
    viewport()->update();
    lineNumberWidget->update();
    updateLineNumberWidgetWidth();
}
```

```c++
void MyHighlighter::highlightBlock(const QString &text)
{
    QRegExp regExp;
    foreach (const HighlightRule &rule, highlightRules) {
        regExp=rule.pattern;
        int index = regExp.indexIn(text);
        while(index>=0){
            int length =regExp.matchedLength();
            QTextCharFormat format =  rule.format;
            format.setFont(QFont(mFontFamily,mFontSize));
            setFormat(index,length,format);
            index = regExp.indexIn(text,index+length);
        }
    }

    //对于多行注释
    addMultiLineCommentFormat(text);
}
```

### 小结 完整代码



