## 六 项目完善

### 31 打开文档

[【Qt开发项目实战——代码编辑器Code Editor Demo——31 项目完善——打开文档】](https://www.bilibili.com/video/BV1jN411P7Jd/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mainwindow.cpp

```c++
...

//打开最近文件
void MainWindow::on_open_rencent_file()
{
    QAction * action = (QAction *)sender();

    QString fileName = action->text();

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法打开此文件"+file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();

    MyCodeEditor * codeEditor = new MyCodeEditor(this,QFont(mFontFamily,mFontSize));
    codeEditor->setPlainText(text);

    ui->tabWidget->addTab(codeEditor,currentFile);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    file.close();
    saveHistory(currentFile);
    initMenu();
}

//打开文件
void MainWindow::on_open_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"打开文件");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法打开此文件:"+file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();

    MyCodeEditor * codeEditor = new MyCodeEditor(this,QFont(mFontFamily,mFontSize));
    codeEditor->setPlainText(text);

    ui->tabWidget->addTab(codeEditor,currentFile);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    file.close();
    saveHistory(currentFile);
    initMenu();
}

...
```

### 32 保存文档Ⅰ

[【Qt开发项目实战——代码编辑器Code Editor Demo——32 项目完善——保存文档Ⅰ】](https://www.bilibili.com/video/BV1Fm4y1B7ot/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.cpp

```c++
...
    
bool MyCodeEditor::saveFile()
{
    QString fileName;
    if(mFileName.isEmpty()){
        fileName =QFileDialog::getSaveFileName(this,"保存文件");
        mFileName =fileName;
    }else{
        fileName =mFileName;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    QTextStream out(&file);

    out<<toPlainText();
    file.close();

    isSaved = true;
    return  true;
}

void MyCodeEditor::setFileName(QString fileName)
{
    mFileName=fileName;
}

QString MyCodeEditor::getFileName()
{
    return mFileName;
}
```

- mainwindow.h

```c++
...

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ...

    void saveSuccessAction( MyCodeEditor * codeEditor);
    
...
    
};

...
```

- mainwindow.cpp

```c++
...

//保存文件
void MainWindow::on_save_file_triggered()
{    
    QString fileName;
    if(mFileName.isEmpty()){
        fileName =QFileDialog::getSaveFileName(this,"保存文件");
        currentFile =fileName;
    }else{
        fileName =currentFile;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    QTextStream out(&file);

    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        out<<codeEditor.toPlainText();
    }
    file.close();
    
    //保存历史
    saveHistory(currentFile);
    //设置tab标题
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileName);
    //初始化菜单
    initMenu();

}

...
```

### 33 保存文档Ⅱ

[【Qt开发项目实战——代码编辑器Code Editor Demo——33 项目完善——保存文档Ⅱ】](https://www.bilibili.com/video/BV1Fm4y1B7ot/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.h

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...
        
    bool saveFile();

    void setFileName(QString fileName);
    QString getFileName();
    
    ...
        
...

private:
    ...

    QString mFileName;
...

};

...
```



- mycodeeditor.cpp

```c++
...
    
bool MyCodeEditor::saveFile()
{
    QString fileName;
    if(mFileName.isEmpty()){
        fileName =QFileDialog::getSaveFileName(this,"保存文件");
        mFileName =fileName;
    }else{
        fileName =mFileName;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    QTextStream out(&file);

    out<<toPlainText();
    file.close();

    isSaved = true;
    return  true;
}

void MyCodeEditor::setFileName(QString fileName)
{
    mFileName=fileName;
}

QString MyCodeEditor::getFileName()
{
    return mFileName;
}
```

- mainwindow.h

```c++
...

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ...

    void saveSuccessAction( MyCodeEditor * codeEditor);
    
...
    
};

...
```



- mainwindow.cpp

```c++
...

//保存文件
void MainWindow::on_save_file_triggered()
{    
    //把保存交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

void MainWindow::saveSuccessAction( MyCodeEditor * codeEditor)
{
    QString fileName  = codeEditor->getFileName();
    //保存历史
    saveHistory(fileName);
    //设置tab标题
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileName);
    //初始化菜单
    initMenu();
}

```

- 

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...
        
    bool saveFile();

    void setFileName(QString fileName);
    QString getFileName();
    
    ...
        
...

private:
    ...

    QString mFileName;
...

};

...
```



- mycodeeditor.cpp

```c++
...
    
bool MyCodeEditor::saveFile()
{
    QString fileName;
    if(mFileName.isEmpty()){
        fileName =QFileDialog::getSaveFileName(this,"保存文件");
        mFileName =fileName;
    }else{
        fileName =mFileName;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    QTextStream out(&file);

    out<<toPlainText();
    file.close();

    isSaved = true;
    return  true;
}

void MyCodeEditor::setFileName(QString fileName)
{
    mFileName=fileName;
}

QString MyCodeEditor::getFileName()
{
    return mFileName;
}
```

- mainwindow.h

```c++
...

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ...

    void saveSuccessAction( MyCodeEditor * codeEditor);
    
...
    
};

...
```



- mainwindow.cpp

```c++
...

//保存文件
void MainWindow::on_save_file_triggered()
{    
    //把保存交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

void MainWindow::saveSuccessAction( MyCodeEditor * codeEditor)
{
    QString fileName  = codeEditor->getFileName();
    //保存历史
    saveHistory(fileName);
    //设置tab标题
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileName);
    //初始化菜单
    initMenu();
}

```



### 34 另存文档

[【Qt开发项目实战——代码编辑器Code Editor Demo——34 项目完善——另存文档】](https://www.bilibili.com/video/BV1pa4y1T74X/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.h

```c++
...
    
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...
        
    bool saveAsFile();

    ...
...

};

...
```

- mycodeeditor.cpp

```c++
...
    
bool MyCodeEditor::saveAsFile()
{
    QString fileName=QFileDialog::getSaveFileName(this,"另存文件");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    mFileName =fileName;
    QTextStream out(&file);
    QString text =toPlainText();
    out<<text;
    file.close();

    isSaved = true;
    return true;
}

...
```

- mainwindow.cpp

```c++
...

//另存为
void MainWindow::on_save_as_triggered()
{
    //把另存为交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveAsFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

...
```

### 35 添加析构函数

[【Qt开发项目实战——代码编辑器Code Editor Demo——35 项目完善——添加析构函数】](https://www.bilibili.com/video/BV1em4y1B7Ph/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.h



```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...
        
    ~MyCodeEditor();
    
    ...
...
};
...

```

- mycodeeditor.cpp

```c++
...
    
MyCodeEditor::~MyCodeEditor()
{
    delete  lineNumberWidget;
}

...
```

- mytexteditbycode.h

```c++
...
    
class MyTextEditByCode : public QWidget
{
    Q_OBJECT
public:
    ...
        
    ~MyTextEditByCode();
    
    ...
        
...
};
...
```

- mytexteditbycode.cpp

```c++
...
    
MyTextEditByCode::~MyTextEditByCode()
{
    delete textEdit;
    delete textBrowser;
    delete scrollBar;
}

...
```

### 36 复制粘贴剪切打印

[【Qt开发项目实战——代码编辑器Code Editor Demo——36 项目完善——复制粘贴剪切打印】](https://www.bilibili.com/video/BV1aN411P7Eb/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mainwindow.cpp

```c++
...

//复制
void MainWindow::on_copy_triggered()
{
    //把复制交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->copy();
    }
}

//粘贴
void MainWindow::on_paste_triggered()
{
    //把粘贴交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->paste();
    }
}

//剪切
void MainWindow::on_cut_triggered()
{
    //把剪切交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->cut();
    }
}

//撤销
void MainWindow::on_undo_triggered()
{
    //把撤销交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->undo();
    }
}

//取消撤销
void MainWindow::on_redo_triggered()
{
    //把取消撤销交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->redo();
    }
}
...
    
//打印
void MainWindow::on_print_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev,this);
    if(dialog.exec()==QDialog::Rejected)
        return;
#endif
    //把打印交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->print(&printDev);
    }
#endif
}

...
```

### 37 设置字体Ⅰ

[【Qt开发项目实战——代码编辑器Code Editor Demo——37 项目完善——设置字体Ⅰ】]()

- mainwindow.h

```c++
...

#include "QSettings"

...

class MainWindow : public QMainWindow
{
    ...
private:
    
    ...

    QSettings * mSettings;

    QList<QString> getHistory();
    void saveHistory(QString path);

};
...
```

- mainwindow.cpp

```c++
...


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ...

    mSettings = new QSettings("settings.ini",QSettings::IniFormat);

    //初始化字体
    initFont();

    ...
}

...

void MainWindow::initFont(){
    mFontFamily = mSettings->value("font_family","Consolas").toString();
    mFontSize = mSettings->value("font_size",14).toInt();
}

...

//获取历史记录
QList<QString> MainWindow::getHistory(){
    ...
}


//保存打开历史记录
void MainWindow::saveHistory(QString path){
    ...
}

...

//字体
void MainWindow::on_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected,QFont(mFontFamily,mFontSize),this);
    if(fontSelected){
        //把字体交给CodeEditor
        MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
        if(codeEditor){
            codeEditor->setAllFont(font);
        }
        mSettings->setValue("font_family",font.family());
        mSettings->setValue("font_size",font.pixelSize());
    }
}

...
```

- mycodeeditor.h

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void setAllFont(QFont font);

...

};

...

```

- mycodeeditor.cpp

```c++
...

MyCodeEditor::MyCodeEditor(QWidget *parent,QFont font) : QPlainTextEdit(parent)
{
    ...

    //设置字体
    setAllFont(font);

    ...
}

...

void MyCodeEditor::setAllFont(QFont font)
{
    this->setFont(font);
    mHighlighter->setFont(font);
    updateLineNumberWidgetWidth();
}

...
```

- myhighlighter.h

```c++
...
    
class MyHighlighter: public QSyntaxHighlighter
{
public:
    ...
        
    void setFont(QFont font);
    
...
    
};

...
```

- myhighlighter.cpp

```c++
...
    
void MyHighlighter::setFont(QFont font)
{
    mFontFamily = font.family();
    mFontSize = font.pixelSize();
}

...
```

### 38 设置字体Ⅱ

[【Qt开发项目实战——代码编辑器Code Editor Demo——38 项目完善——设置字体Ⅱ】]()

- mainwindow.cpp

```c++
...

//字体
void MainWindow::on_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected,QFont(mFontFamily,mFontSize),this);
    if(fontSelected){
        //把字体交给CodeEditor
        MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
        if(codeEditor){
            codeEditor->setAllFont(font);
        }
        mSettings->setValue("font_family",font.family());
        mSettings->setValue("font_size",font.pointSize());
    }
}

...
```

- mycodeeditor.cpp

```c++
...

MyCodeEditor::MyCodeEditor(QWidget *parent,QFont font) : QPlainTextEdit(parent)
{
    ...

    //高亮
    initHighlighter();

    //设置字体
    setAllFont(font);

    ...
}

...
```

### 39 退出保存提示Ⅰ

[【Qt开发项目实战——代码编辑器Code Editor Demo——39 项目完善——退出保存提示Ⅰ】]()

- mycodeeditor.h

```c++
...
    
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...
        
    bool checkSaved();

...

private:
    ...
        
    bool isSaved = false;

...

};

...

```

- mycodeeditor.cpp

```c++
...

void MyCodeEditor::updateSaveState()
{
    //更新保存状态
    isSaved = false;
}

...

bool MyCodeEditor::saveFile()
{
    ...
        
    isSaved = true;
    
    ...
}

bool MyCodeEditor::saveAsFile()
{
    ...
        
    isSaved = true;
    
    ...
}

...
```



- mainwindow.h

```c++
...

class MainWindow : public QMainWindow
{
    ...

private slots:
    ...

    void on_tabWidget_tabCloseRequested(int index);

...

};
...
```

- mainwindow.cpp

```c++
...

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    MyCodeEditor * codeEditor = (MyCodeEditor*)ui->tabWidget->currentWidget();

    if(!codeEditor->checkSaved()){
       QMessageBox::StandardButton btn = QMessageBox::question(this,"警告","您还没有保存文档！是否保存？",QMessageBox::Yes|QMessageBox::No);
       if(btn ==QMessageBox::Yes){
           if(codeEditor->saveFile()){
              saveSuccessAction(codeEditor);
           }
       }
    }
    delete codeEditor;
    ui->tabWidget->removeTab(index);
}

...
```

### 40 退出保存提示Ⅱ

[【Qt开发项目实战——代码编辑器Code Editor Demo——40 项目完善——退出保存提示Ⅱ】]()

- mycodeeditor.h

```c++
...
    
class MyCodeEditor : public QPlainTextEdit
{
    ...

private slots:
    ...
        
    void updateSaveState();

...

};

...

```

- mycodeeditor.cpp

```c++
...

void MyCodeEditor::initConnection()
{
    ...

    //textChanged
    connect(this,SIGNAL(textChanged()),this,SLOT(updateSaveState()));

    ...
}

...

void MyCodeEditor::updateSaveState()
{
    //更新保存状态
    isSaved = false;
}

...
```

### 41 设置工具状态

[【Qt开发项目实战——代码编辑器Code Editor Demo——41 项目完善——设置工具状态】]()

- mainwindow.h

```c++
...

class MainWindow : public QMainWindow
{
    ...

private:
    ...

    void initAction();

...

};
...
```

- mainwindow.cpp

```c++
...

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ...

    //初始化动作
    initAction();

...
    
}

...

void MainWindow::initAction()
{
    bool valid =ui->tabWidget->count()>0;
    ui->save_file->setEnabled(valid);
    ui->save_as->setEnabled(valid);
    ui->copy->setEnabled(valid);
    ui->paste->setEnabled(valid);
    ui->cut->setEnabled(valid);
    ui->undo->setEnabled(valid);
    ui->redo->setEnabled(valid);
}

...
```

### 42 退出保存提示Ⅲ

[【Qt开发项目实战——代码编辑器Code Editor Demo——42 项目完善——退出保存提示Ⅲ】]()

- mainwindow.cpp

```c++
...

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    MyCodeEditor * codeEditor = (MyCodeEditor*)ui->tabWidget->currentWidget();

    if(!codeEditor->checkSaved()){
        QMessageBox::StandardButton btn = QMessageBox::question(this,"警告","您还没有保存文档！是否保存？" , QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(btn ==QMessageBox::Yes){
            if(codeEditor->saveFile())
                saveSuccessAction(codeEditor);
            return;
        }else if(btn ==QMessageBox::Cancel)
            return;
    }
    ui->tabWidget->removeTab(index);
    delete codeEditor;
    initAction();
}

...
```

### 43 窗口关闭事件

[【Qt开发项目实战——代码编辑器Code Editor Demo——43 项目完善——窗口关闭事件】]()

- mainwindow.h

```c++
...

class MainWindow : public QMainWindow
{
    ...

protected:
    void closeEvent(QCloseEvent *event);

...

};
...
```

- mainwindow.cpp

```c++
...

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->tabWidget->count()>0){
        QMessageBox::question(this,
                              "警告",
                              "有未保存的文件，确定要关闭吗？",
                              QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes?event->accept():event->ignore();
    }
}

```

### 44 关闭标签页问题修复

[【Qt开发项目实战——代码编辑器Code Editor Demo——39 项目完善——关闭标签页问题修复】]()

- mainwindow.cpp

```c++
...

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ...
        
    ui->tabWidget->removeTab(index);
    delete codeEditor;
}

...
```

### 45 关键字保留字配置

[【Qt开发项目实战——代码编辑器Code Editor Demo——45 项目完善——关键字保留字配置】]()

- c++关键字

```c++
alignas
alignof
andb
and_eqb
asma
auto
bitandb
bitorb
bool
break
case
catch
char
char8_tc
char16_t
char32_t
class
complb
conceptc
const
const_cast
constevalc
constexpr
constinitc
continue
co_awaitc
co_returnc
co_yieldc
decltype
default
delete
do
double
dynamic_cast
else
enum
explicit
exportc
extern
false
float
for
friend
goto
if
inline
int
long
mutable
namespace
new
noexcept
notb
not_eqb
nullptr
operator
orb
or_eqb
private
protected
public
register reinterpret_cast
requiresc
return
short
signed
sizeof
static
static_assert
static_cast
struct
switch
template
this
thread_local
throw
true
try
typedef
typeid
typename
union
unsigned
using
using
virtual
void
volatile
wchar_t
while
xorb
xor_eqb
```

- java关键字

```c++
abstract
assert
boolean
break
byte
case
catch
char
class
continue
default
do
double
else
enum
extends
final
finally
float
for
if
implements
import
int
interface
instanceof
long
native
new
package
private
protected
public
return
short
static
strictfp
super
switch
synchronized
this
throw
throws
transient
try
void
volatile
while
```

### 小结——完整代码

- mainwindow.cpp

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "QFileDialog"
#include "QMessageBox"
#include "QFontDialog"
#include <QDateTime>


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#endif
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSettings = new QSettings("settings.ini",QSettings::IniFormat);

    //初始化菜单
    initMenu();

    //初始化字体
    initFont();

    //初始化动作
    initAction();


#if !QT_CONFIG(printer)
    ui->print->setEnabled(false);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initFont(){
    mFontFamily = mSettings->value("font_family","Consolas").toString();
    mFontSize = mSettings->value("font_size",14).toInt();
}

void MainWindow::initAction()
{
    bool valid =ui->tabWidget->count()>0;
    ui->save_file->setEnabled(valid);
    ui->save_as->setEnabled(valid);
    ui->copy->setEnabled(valid);
    ui->paste->setEnabled(valid);
    ui->cut->setEnabled(valid);
    ui->undo->setEnabled(valid);
    ui->redo->setEnabled(valid);
}


//初始化菜单
void MainWindow::initMenu()
{
    //获取Menu
    QMenu * recent = this->findChild<QMenu *>("recent");
    //获取Action
    QList<QObject *> chLists =recent->children();
    foreach(QObject * ch,chLists){
        QAction *action = (QAction *)ch;
        //清空子菜单Action
        recent->removeAction(action);
    }

    QList<QString> lists = getHistory();


    for(int i=lists.size()-1 ;i>=0;i--){
        //生成子菜单Action
        recent->addAction(lists[i],this,&MainWindow::on_open_rencent_file);
    }

    if(lists.size()>0){
        recent->addAction("清除历史记录",this,&MainWindow::on_clear_history_triggered,QKeySequence("Ctrl+Alt+Shift+C"));
    }

}


//获取历史记录
QList<QString> MainWindow::getHistory(){
    //打开开始读
    int size =mSettings->beginReadArray("history");

    //创建返回对象
    QList<QString> lists;
    for(int i = 0;i<size;i++){
        mSettings->setArrayIndex(i);
        QString path = mSettings->value("path").toString();
        lists.append(path);
    }
    //关闭读
    mSettings->endArray();

    return lists;
}



//保存打开历史记录
void MainWindow::saveHistory(QString path){

    //获取历史
    QList<QString> lists = getHistory();
    foreach(QString str,lists){
        if(str==path){
            lists.removeOne(str);
        }
    }
    lists.append(path);

    //打开开始写入
    mSettings->beginWriteArray("history");
    for(int i =0;i<lists.size();i++){
        mSettings->setArrayIndex(i);
        //保存字符串
        mSettings->setValue("path",lists[i]);
    }

    //关闭开始写入
    mSettings->endArray();
}



//新建文件
void MainWindow::on_new_file_triggered()
{
    ui->tabWidget->addTab(new MyCodeEditor(this,QFont(mFontFamily,mFontSize)),"NewFile.xjy");
    initAction();
}


//打开最近文件
void MainWindow::on_open_rencent_file()
{
    createTab(((QAction *)sender())->text());
}

//打开文件
void MainWindow::on_open_file_triggered()
{
    createTab(QFileDialog::getOpenFileName(this,"打开文件"));
}

//创建tab
void MainWindow::createTab(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法打开此文件:"+file.errorString());
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    //创建对象
    MyCodeEditor * codeEditor = new MyCodeEditor(this,QFont(mFontFamily,mFontSize));
    codeEditor->setPlainText(text);

    //设置文件名
    codeEditor->setFileName(fileName);
    //添加tab
    ui->tabWidget->addTab(codeEditor,fileName);
    //设置当前索引
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    file.close();
    saveHistory(fileName);
    initMenu();
    initAction();
}


//保存文件
void MainWindow::on_save_file_triggered()
{    
    //把保存交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

//另存为
void MainWindow::on_save_as_triggered()
{
    //把另存为交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveAsFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

//复制
void MainWindow::on_copy_triggered()
{
    //把复制交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->copy();
    }
}

//粘贴
void MainWindow::on_paste_triggered()
{
    //把粘贴交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->paste();
    }
}

//剪切
void MainWindow::on_cut_triggered()
{
    //把剪切交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->cut();
    }
}

//撤销
void MainWindow::on_undo_triggered()
{
    //把撤销交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->undo();
    }
}

//取消撤销
void MainWindow::on_redo_triggered()
{
    //把取消撤销交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->redo();
    }
}

//字体
void MainWindow::on_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected,QFont(mFontFamily,mFontSize),this);
    if(fontSelected){
        //把字体交给CodeEditor
        MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
        if(codeEditor){
            codeEditor->setAllFont(font);
        }
        mSettings->setValue("font_family",font.family());
        mSettings->setValue("font_size",font.pointSize());
    }
}

//打印
void MainWindow::on_print_triggered()
{
    //把打印交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
        QPrinter printDev;
#if QT_CONFIG(printdialog)
        QPrintDialog dialog(&printDev,this);
        if(dialog.exec()==QDialog::Rejected)
            return;
#endif
        codeEditor->print(&printDev);
#endif
    }
}

//关于
void MainWindow::on_about_triggered()
{
    QMessageBox::about(this,"这是我的Notepad！","这是我的Notepad，欢迎学习和使用！");
}


//退出
void MainWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}


void MainWindow::on_clear_history_triggered()
{
    mSettings->remove("history");
    initMenu();
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    MyCodeEditor * codeEditor = (MyCodeEditor*)ui->tabWidget->currentWidget();

    if(!codeEditor->checkSaved()){
        QMessageBox::StandardButton btn = QMessageBox::question(this,"警告","您还没有保存文档！是否保存？",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if(btn ==QMessageBox::Yes){
            if(codeEditor->saveFile())
                saveSuccessAction(codeEditor);
            return;
        }else if(btn ==QMessageBox::Cancel)
            return;
    }
    ui->tabWidget->removeTab(index);
    delete codeEditor;
    initAction();
}


void MainWindow::saveSuccessAction( MyCodeEditor * codeEditor)
{
    QString fileName  = codeEditor->getFileName();
    //保存历史
    saveHistory(fileName);
    //设置tab标题
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileName);
    //初始化菜单
    initMenu();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->tabWidget->count()>0){
        QMessageBox::question(this,
                              "警告",
                              "有未保存的文件，确定要关闭吗？",
                              QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes?event->accept():event->ignore();
    }
}
```

- mycodeeditor.cpp

```c++
#include "mycodeeditor.h"
#include "myhighlighter.h"

#include <QPainter>
#include <QTextStream>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>

#include<QDebug>

MyCodeEditor::MyCodeEditor(QWidget *parent,QFont font) : QPlainTextEdit(parent)
{
    lineNumberWidget = new LineNumberWidget(this);

    //绑定
    initConnection();

    //高亮
    initHighlighter();

    //设置字体
    setAllFont(font);

    //行高亮
    highlightCurrentLine();

    //设置边距
    updateLineNumberWidgetWidth();

    setLineWrapMode(QPlainTextEdit::NoWrap);
}

MyCodeEditor::~MyCodeEditor()
{
    delete  lineNumberWidget;
}

void MyCodeEditor::initConnection()
{
    //cursor
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(highlightCurrentLine()));

    //textChanged
    connect(this,SIGNAL(textChanged()),this,SLOT(updateSaveState()));

    //blockCount
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberWidgetWidth()));

    //updateRequest
    connect(this,SIGNAL(updateRequest(QRect,int)),this,SLOT(updateLineNumberWidget(QRect,int)));
}

void MyCodeEditor::setAllFont(QFont font)
{
    this->setFont(font);
    mHighlighter->setFont(font);
    updateLineNumberWidgetWidth();
}

bool MyCodeEditor::checkSaved()
{
    return isSaved;
}

void MyCodeEditor::initHighlighter()
{
   mHighlighter =  new MyHighlighter(document());
}

int MyCodeEditor::getLineNumberWidgetWidth()
{
    //获取宽度（合适）
    return 8+QString::number(blockCount()+1).length()*fontMetrics().horizontalAdvance(QChar('0'));
}


void MyCodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(0,100,100,20));
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor =textCursor();

    extraSelections.append(selection);
    setExtraSelections(extraSelections);

}

void MyCodeEditor::updateLineNumberWidget(QRect rect, int dy)
{
    if(dy)
        lineNumberWidget->scroll(0,dy);
    else
        lineNumberWidget->update(0,rect.y(),getLineNumberWidgetWidth(),rect.height());
}

void MyCodeEditor::updateLineNumberWidgetWidth()
{
    //设置边距
    setViewportMargins(getLineNumberWidgetWidth(),0,0,0);
}

void MyCodeEditor::updateSaveState()
{
    //更新保存状态
    isSaved = false;
}

void MyCodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    lineNumberWidget->setGeometry(0,0,getLineNumberWidgetWidth(),contentsRect().height());
}

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberWidget);
    //绘制行号区域
    painter.fillRect(event->rect(),QColor(100,100,100,20));

    //拿到block
    QTextBlock block = firstVisibleBlock();

    //拿到行号
    int blockNumber =block.blockNumber();

    //拿到当前的block的top
    int cursorTop = blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top();

    //拿到block的top
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();

    //拿到block的bottom
    int bottom = top +blockBoundingRect(block).height();

    while(block.isValid()&&top<=event->rect().bottom()){
        //设置画笔颜色
        painter.setPen(cursorTop==top?Qt::black:Qt::gray);
        //绘制文字
        painter.drawText(0,top,getLineNumberWidgetWidth()-3,bottom-top,Qt::AlignRight,QString::number(blockNumber+1));

        //拿到下一个block
        block = block.next();

        top = bottom;
        bottom =  top +blockBoundingRect(block).height();
        blockNumber++;
    }
}

void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event)
{
    setTextCursor(QTextCursor(document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value())));
}

void MyCodeEditor::lineNumberWidgetWheelEvent(QWheelEvent *event)
{
    if(event->orientation()==Qt::Horizontal){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->delta());
    }else {
       verticalScrollBar()->setValue(verticalScrollBar()->value()-event->delta());
    }
    event->accept();
}

bool MyCodeEditor::saveFile()
{
    QString fileName;
    if(mFileName.isEmpty()){
        fileName =QFileDialog::getSaveFileName(this,"保存文件");
        mFileName =fileName;
    }else{
        fileName =mFileName;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    QTextStream out(&file);

    out<<toPlainText();
    file.close();

    isSaved = true;
    return  true;
}

bool MyCodeEditor::saveAsFile()
{
    QString fileName=QFileDialog::getSaveFileName(this,"另存文件");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法保存文件:"+file.errorString());
        return false;
    }
    mFileName =fileName;
    QTextStream out(&file);
    QString text =toPlainText();
    out<<text;
    file.close();

    isSaved = true;
    return true;
}

void MyCodeEditor::setFileName(QString fileName)
{
    mFileName=fileName;
}

QString MyCodeEditor::getFileName()
{
    return mFileName;
}
```