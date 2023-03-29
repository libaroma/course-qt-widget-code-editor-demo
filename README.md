## 〇 项目介绍

![](https://files.hyz.cool/files/articles/61f47a0b4b1a1a5d921573dc25c0cc23.jpg)

基于上一个项目[Notepad demo](https://www.hyz.cool/articles/170)来继续完善优化和提高的一个新的项目，

会用到上一个项目的代码，没有的话可以通过上一个项目来同步学习自己写一下，熟悉一下这个项目；

或者在我的博客网站里面的文章里面获取。

那么这个项目呢，主要实现下面这些效果

- Tab标签页实现：首先呢，你可以新建文件，然后你会发现这里的新建文件会新生成一个tab标签页，就类似于咱们浏览器的标签页一样。

- 文字行数实现：我们可以在这里输入文字，注意看这个文本输入框的左侧显示了行数。
- 代码高亮显示：我们发现我们的文本是有高亮显示的

主要是上述功能

主要会学到以下知识：

- Tab标签组件
- 动态生成组件
- 布局
- 信号的绑定
- 滚动条的绑定
- 自定义组件的多种形式
- 如何实现代码高亮

### B站

[【Qt开发项目实战——代码编辑器Code Editor Demo——00 项目介绍】 ](https://www.bilibili.com/video/BV16M4y167tB/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

### Github

[course-qt-widget-notepad-demo](https://github.com/libaroma/course-qt-widget-code-editor-demo)

## 一 项目创建

### 01 项目创建

[【Qt开发项目实战——代码编辑器Code Editor Demo——01 项目创建】 ](https://www.bilibili.com/video/BV1Xv4y1L7U3/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- 复制上一个项目
- 重命名为code editor demo
- 打开项目

### 02 添加Tab标签页

[【Qt开发项目实战——代码编辑器Code Editor Demo——02 添加Tab标签页】 ](https://www.bilibili.com/video/BV15v4y1j7qa/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- ui界面中插入Tab Widget
- 在mainwindow.cpp中，设为中心组件：

```c++
//mainwindow.cpp

...
    
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);
    
    ...
        
}

...
    
```

### 03 新建Tab标签页

[【Qt开发项目实战——代码编辑器Code Editor Demo——03 新建Tab标签页】 ](https://www.bilibili.com/video/BV1Vm4y1k76j/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

```c++
...

//新建文件
void MainWindow::on_new_file_triggered()
{
    ui->tabWidget->addTab(new QTextEdit(),"NewTab.xjy");

//    qDebug()<<"Start Create New File ...";
//    currentFile.clear();
//    ui->textEdit->setText("");
}

...
```

### 04 修改项目名称

[【Qt开发项目实战——代码编辑器Code Editor Demo——04 修改项目名称】 ](https://www.bilibili.com/video/BV1No4y1B7qN/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- 找到.pro文件，修改名称，删除.pro.user文件
- 重新打开项目

## 二 自定义组件

### 05 UI建立

[【Qt开发项目实战——代码编辑器Code Editor Demo——05 自定义组件——UI建立】 ](https://www.bilibili.com/video/BV1zs4y1p7xr/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- Add New——>Qt——>设计师组件——>选择Widget——>命名MyTextEdit
- ui界面插入组件
- 显示ui：

```c++
...

//新建文件
void MainWindow::on_new_file_triggered()
{
    MyTextEdit * myTextEdit = new MyTextEdit(this);
    ui->tabWidget->addTab(myTextEdit,"NewTab.xjy");

//    qDebug()<<"Start Create New File ...";
//    currentFile.clear();
//    ui->textEdit->setText("");
}

...
```

### 06 滚动条绑定

[【Qt开发项目实战——代码编辑器Code Editor Demo——06 自定义组件——水平滚动条绑定】]( https://www.bilibili.com/video/BV1nY4y1Q7FR/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytextedit.h

```c++
//mytextedit.h

...
    
private slots:
    void textEditHScrollBarChanged();
    void scrollBarChanged();

...

```

- mytextedit.cpp

```c++
//mytextedit.cpp

#include "mytextedit.h"
#include "ui_mytextedit.h"

MyTextEdit::MyTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTextEdit)
{
    ui->setupUi(this);

    connect(ui->textEdit->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textEditHScrollBarChanged()));
    connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollBarChanged()));
}

void MyTextEdit::scrollBarChanged()
{
    ui->textEdit->horizontalScrollBar()->setValue(ui->horizontalScrollBar->value());
}

void MyTextEdit::textEditVScrollBarChanged()
{
    ui->textBrowser->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
}
```

### 07 设置字体

[【Qt开发项目实战——代码编辑器Code Editor Demo——07 自定义组件——设置字体】](https://www.bilibili.com/video/BV1vM411u7xf/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytextedit.h

```c++
//mytextedit.h

...

private:
    Ui::MyTextEdit *ui;
    void initConnect();
    void initFont();
};

#endif // MYTEXTEDIT_H
```

- mytextedit.cpp

```c++
//mytextedit.cpp

#include "mytextedit.h"
#include "ui_mytextedit.h"
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTextEdit)
{
    ui->setupUi(this);

    //绑定滚动条
    initConnect();

    //初始化字体
    initFont();
}

...


void MyTextEdit::initConnect()
{
    connect(ui->textEdit->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textEditHScrollBarChanged()));
    connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollBarChanged()));
}

void MyTextEdit::initFont()
{
    QFont font("Consolas",14);
    ui->textEdit->setFont(font);
    ui->textBrowser->setFont(font);
}

...
```

### 08 显示行号

[【Qt开发项目实战——代码编辑器Code Editor Demo——08 自定义组件——显示行号】 ](https://www.bilibili.com/video/BV1EX4y1d7mg/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytextedit.h

```c++
//mytextedit.h

...

private slots:
    ...

    void onTextChanged();

...

#endif // MYTEXTEDIT_H

```

- mytextedit.cpp

```c++
//mytextedit.cpp

...


void MyTextEdit::initConnect()
{
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));

    ...
}

...
    
void MyTextEdit::onTextChanged()
{
    int lineCount = ui->textEdit->document()->lineCount();
    for(int i = 0;i<lineCount;i++){
            text+= QString::number(i+1)+"\n";
        }

    ui->textBrowser->setMaximumWidth(25+QString::number(lineCount).length()*7);
    ui->textBrowser->setText(text);
}

```

### 09 竖直滚动条绑定

[【Qt开发项目实战——代码编辑器Code Editor Demo——09 自定义组件——竖直滚动条绑定】 ](https://www.bilibili.com/video/BV1Ec41177Qv/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytextedit.h

```c++
//mytextedit.h

...

private slots:
   
    ...
        
    void textEditVScrollBarChanged();
    void textBrowserVScrollBarChanged();

...

```

- mytextedit.cpp

```c++
//mytextedit.cpp

...

void MyTextEdit::initConnect()
{
    ...
    
    //竖直滚动条
    connect(ui->textEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textEditVScrollBarChanged()));
    connect(ui->textBrowser->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textBrowserVScrollBarChanged()));

}

...
    
void MyTextEdit::textEditVScrollBarChanged()
{
    ui->textBrowser->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
}

void MyTextEdit::textBrowserVScrollBarChanged()
{
    ui->textEdit->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->value());
}

...
```

### 10 行号生成代码优化

[【Qt开发项目实战——代码编辑器Code Editor Demo——10 自定义组件——行号生成代码优化】 ](https://www.bilibili.com/video/BV1dY4y1D775/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytextedit.cpp

```c++
//mytextedit.cpp

...

void MyTextEdit::onTextChanged()
{
    int lineCountOfTextEdit = ui->textEdit->document()->lineCount();
    qDebug()<<"lineCountOfTextEdit:"<<lineCountOfTextEdit;
    QString text = ui->textBrowser->toPlainText();

    int lineCountOfTextBrowser = text.trimmed().split("\n").length();
    qDebug()<<"lineCountOfTextBrowser:"<<lineCountOfTextBrowser;

    if(lineCountOfTextBrowser>lineCountOfTextEdit){
        for(int i = lineCountOfTextBrowser;i>lineCountOfTextEdit;i--){
            text.chop((QString::number(i)+"\n").length());
        }
    } else if (lineCountOfTextBrowser==1&&text.length()<1){
         text+= "1\n";
    }    else if(lineCountOfTextBrowser<lineCountOfTextEdit){
        for(int i = lineCountOfTextBrowser;i<lineCountOfTextEdit;i++){
            text+= QString::number(i+1)+"\n";
        }
    }

    ui->textBrowser->setMaximumWidth(25+QString::number(lineCountOfTextEdit).length()*7);
    ui->textBrowser->setText(text);

}
```

### 小结——完整代码

- mytextedit.h

```c++
#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QWidget>

namespace Ui {
class MyTextEdit;
}

class MyTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MyTextEdit(QWidget *parent = nullptr);
    ~MyTextEdit();

private slots:
    void textEditHScrollBarChanged();
    void scrollBarChanged();

    void textEditVScrollBarChanged();
    void textBrowserVScrollBarChanged();

    void onTextChanged();

private:
    Ui::MyTextEdit *ui;
    void initConnect();
    void initFont();
};

#endif // MYTEXTEDIT_H

```

- mytextedit.cpp

```c++
#include "mytextedit.h"
#include "ui_mytextedit.h"
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTextEdit)
{
    ui->setupUi(this);

    //绑定滚动条
    initConnect();

    //初始化字体
    initFont();
}

MyTextEdit::~MyTextEdit()
{
    delete ui;
}


void MyTextEdit::initConnect()
{
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));

    connect(ui->textEdit->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textEditHScrollBarChanged()));
    connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollBarChanged()));

    connect(ui->textEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textEditVScrollBarChanged()));
    connect(ui->textBrowser->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textBrowserVScrollBarChanged()));

}

void MyTextEdit::initFont()
{
    QFont font("Consolas",14);
    ui->textEdit->setFont(font);
    ui->textBrowser->setFont(font);
}

void MyTextEdit::textEditHScrollBarChanged()
{
    ui->horizontalScrollBar->setMinimum(ui->textEdit->horizontalScrollBar()->minimum());
    ui->horizontalScrollBar->setMaximum(ui->textEdit->horizontalScrollBar()->maximum());
    ui->horizontalScrollBar->setPageStep(ui->textEdit->horizontalScrollBar()->pageStep());
    ui->horizontalScrollBar->setValue(ui->textEdit->horizontalScrollBar()->value());
}

void MyTextEdit::scrollBarChanged()
{
    ui->textEdit->horizontalScrollBar()->setValue(ui->horizontalScrollBar->value());
}

void MyTextEdit::textEditVScrollBarChanged()
{
    ui->textBrowser->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
}

void MyTextEdit::textBrowserVScrollBarChanged()
{
    ui->textEdit->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->value());
}

void MyTextEdit::onTextChanged()
{
    int lineCountOfTextEdit = ui->textEdit->document()->lineCount();
//    qDebug()<<"lineCountOfTextEdit:"<<lineCountOfTextEdit;
    QString text = ui->textBrowser->toPlainText();

    int lineCountOfTextBrowser = text.trimmed().split("\n").length();
//    qDebug()<<"lineCountOfTextBrowser:"<<lineCountOfTextBrowser;

    if(lineCountOfTextBrowser>lineCountOfTextEdit){
        for(int i = lineCountOfTextBrowser;i>lineCountOfTextEdit;i--){
            text.chop((QString::number(i)+"\n").length());
        }
    } else if (lineCountOfTextBrowser==1&&text.length()<1){
         text+= "1\n";
    }    else if(lineCountOfTextBrowser<lineCountOfTextEdit){
        for(int i = lineCountOfTextBrowser;i<lineCountOfTextEdit;i++){
            text+= QString::number(i+1)+"\n";
        }
    }

    ui->textBrowser->setMaximumWidth(25+QString::number(lineCountOfTextEdit).length()*7);
    ui->textBrowser->setText(text);

}
```

## 三 代码高亮

### 11 普通文本

[【Qt开发项目实战——代码编辑器Code Editor Demo——11 代码高亮——普通文本】 ](https://www.bilibili.com/video/BV1Ym4y1k79K/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- 创建MyHighlighter类，继承QSyntaxHighlighter，include QObject

- myhighlighter.h

```c++
#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QObject>

class MyHighlighter : public QSyntaxHighlighter
{
public:
    explicit MyHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightRule{
      QRegExp pattern;
      QTextCharFormat format;
    };

    QString mFontFamily = "Consolas" ;
    int mFontSize =14 ;

    QVector<HighlightRule> highlightRules;

    void addNormalTextFormat();
};

#endif // MYHIGHLIGHTER_H
```

- myhighlighter.cpp

```c++
#include "myhighlighter.h"

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    addNormalTextFormat();
}

void MyHighlighter::addNormalTextFormat()
{
    HighlightRule rule;
    QTextCharFormat normalTextFormat;
    normalTextFormat.setForeground(QColor(0,0,0));
    normalTextFormat.setFont(QFont(mFontFamily,mFontSize));

    rule.pattern = QRegExp("[a-zA-Z0-9]+");
    rule.format = normalTextFormat;

    highlightRules.append(rule);
}

void MyHighlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightRule &rule,highlightRules){
        QRegExp regExp(rule.pattern);
        int index = regExp.indexIn(text);
        while(index>=0){
            int length = regExp.matchedLength();
            setFormat(index,length,rule.format);
            index = regExp.indexIn(text,index+length);
        }
    }
}
```

- 调用——mytextedit.cpp

```c++
#include "myhighlighter.h"
...

MyTextEdit::MyTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTextEdit)
{
    ...

    //初始化高亮
    initHighlighter();
}

...

void MyTextEdit::initHighlighter()
{
    new MyHighlighter(ui->textEdit->document());
}

...
```

### 12 数字

[【Qt开发项目实战——代码编辑器Code Editor Demo——12 代码高亮——数字】](https://www.bilibili.com/video/BV1L24y177HV/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addNumberFormat();
};

...
```

- myhighlighter.cpp

```c++
...

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    ...
    
    addNumberFormat();
}

void MyHighlighter::addNumberFormat()
{
    HighlightRule rule;
    QTextCharFormat numberFormat;
    numberFormat.setForeground(QColor(250,80,50));
    numberFormat.setFont(QFont(mFontFamily,mFontSize));

    rule.pattern = QRegExp("\\b\\d+|\\d+\\.\\d+\\b");
    rule.format = numberFormat;

    highlightRules.append(rule);
}

```

### 13 字符串

[【Qt开发项目实战——代码编辑器Code Editor Demo——13 代码高亮——字符串】](https://www.bilibili.com/video/BV1Rs4y1E77M/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addStringFormat();
};

...
```

- myhighlighter.cpp

```c++
...

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    ...
    
    addStringFormat();
}

void MyHighlighter::addStringFormat()
{
    QTextCharFormat stringFormat;
    stringFormat.setForeground(QColor(0,180,180));
    stringFormat.setFont(QFont(mFontFamily,mFontSize));
    
    HighlightRule rule;
    
    rule.pattern = QRegExp("'[^']*'");
    rule.format = stringFormat;
    highlightRules.append(rule);

    rule.pattern = QRegExp("\"[^\"]*\"");
    highlightRules.append(rule);

    rule.pattern = QRegExp("`[^`]*`");
    highlightRules.append(rule);
}

```

### 14 注释

[【Qt开发项目实战——代码编辑器Code Editor Demo——14 代码高亮——注释】]( https://www.bilibili.com/video/BV1fV4y1X7T2/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addCommentFormat();
};

...
```

- myhighlighter.cpp

```c++
...
    
void MyHighlighter::addCommentFormat()
{
    QTextCharFormat commnetFormat;

    commnetFormat.setFont(QFont(mFontFamily,mFontSize));
    commnetFormat.setForeground(Qt::darkGreen);
    commnetFormat.setFontItalic(true);


    HighlightRule rule;

    rule.format = commnetFormat;

    // //dada
    rule.pattern = QRegExp("\\/\\/.*$");
    highlightRules.append(rule);

    // /*dada***ddd****/
    rule.pattern = QRegExp("\\/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*\\/");
    highlightRules.append(rule);
}

```

### 15 多行注释

[【Qt开发项目实战——代码编辑器Code Editor Demo——15 代码高亮——多行注释】](https://www.bilibili.com/video/BV1Kv4y1L7UY/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addMultiLineCommentFormat();
};

...
```

- myhighlighter.cpp

```c++
...

void MyHighlighter::addMultiLineCommentFormat()
{
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setFont(QFont(mFontFamily,mFontSize));
    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);


    setCurrentBlockState(0);

    QRegExp commentStartRegExp("/\\*");
    QRegExp commentEndRegExp("\\*/");
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartRegExp.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndRegExp.indexIn(text, startIndex);
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + commentEndRegExp.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartRegExp.indexIn(text, startIndex + commentLength);
    }
}

void MyHighlighter::highlightBlock(const QString &text)
{
    ...
    
    //多行注释
    addMultiLineCommentFormat();
}

```

### 16 关键字/保留字

[【Qt开发项目实战——代码编辑器Code Editor Demo——16 代码高亮——关键字/保留字】](https://www.bilibili.com/video/BV1Zc411L7za/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addKeywordsFormat();
};

...
```

- myhighlighter.cpp

```c++
...

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    ...
    //关键字/保留字
    void addKeywordsFormat();
}

void MyHighlighter::addKeywordsFormat(){
    QFile file(":/code/config/keywords.txt");
    QTextStream keywordsStream(&file);
    HighlightRule rule;
    QTextCharFormat keywordsFormat;
    keywordsFormat.setFont(QFont(mFontFamily,mFontSize));
    keywordsFormat.setForeground(Qt::darkMagenta);
    
    rule.format = keywordsFormat;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString line;
        keywordsStream.seek(0);
        while(!keywordsStream.atEnd()){
            line = keywordsStream.readLine();
            if (line != ""){//防止空行
                rule.pattern = QRegExp("\\b"+line+"\\b");
                highlightRules.append(rule);
            }
        }
        file.close();
    }
}
```

### 17 类名

[【Qt开发项目实战——代码编辑器Code Editor Demo——17 代码高亮——类名】]([https://www.bilibili.com/video/BV1TM411M76t/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addClassNameFormat();
};

...
```

- myhighlighter.cpp

```c++
...

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    ...
    //类名
    void addClassNameFormat();
}

void MyHighlighter::addClassNameFormat(){
    HighlightRule rule;
    
    QTextCharFormat classNameFormat;
    classNameFormat.setForeground(QColor(150,20,100));
    classNameFormat.setFont(QFont(mFontFamily,mFontSize));
    numberFormat.setFontWeight(600);
    
    rule.format = classNameFormat;
        
    rule.pattern = QRegExp("\\b[A-Z]+\\w*");
    highlightRules.append(rule);
}
```

### 18 函数

[【Qt开发项目实战——代码编辑器Code Editor Demo——18 代码高亮——函数】](https://www.bilibili.com/video/BV1LL411X7q3/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- myhighlighter.h

```c++
...
    
private:
    ...
        
    void addFunctionFormat();
};

...
```

- myhighlighter.cpp

```c++
...

MyHighlighter::MyHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    ...
    //函数
    void addFunctionFormat();
}

void MyHighlighter::addFunctionFormat(){
    HighlightRule rule;

    QTextCharFormat functionFormat;
    functionFormat.setFont(QFont(mFontFamily,mFontSize));
    functionFormat.setForeground(QColor(200,0,150));

    rule.format = functionFormat;

    rule.pattern = QRegExp("\\b[a-zA-Z0-9_]+\\(");
    highlightRules.append(rule);
    rule.pattern = QRegExp("\\)");
    highlightRules.append(rule);
}
```

### 小结——完整代码

- myhighlighter.h

```c++
#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

class MyHighlighter: public QSyntaxHighlighter
{
public:
    explicit MyHighlighter(QTextDocument *parent = nullptr,QString fontFamily="Consolas",int fontSize=14);
protected:
    void highlightBlock(const QString &text) ;

private:

    QString mFontFamily ;
    int mFontSize ;

    struct HighlightRule{
      QRegExp pattern;
      QTextCharFormat format;
    };

    QVector<HighlightRule> highlightRules;

    void addNormalTextFormat();
    void addNumberFormat();
    void addStringFormat();
    void addCommentFormat();

    void addMultiLineCommentFormat(const QString &text);

    void addKeywordsFromat();
    void addClassNameFormat();
    void addFunctionFormat();
};

#endif // MYHIGHLIGHTER_H

```

- myhighlighter.cpp

```c++
#include "myhighlighter.h"

#include <QDebug>


MyHighlighter::MyHighlighter(QTextDocument *parent, QString fontFamily, int fontSize): QSyntaxHighlighter(parent)
{
    mFontFamily =fontFamily;
    mFontSize = fontSize;

    //对于普通文本
    addNormalTextFormat();

    //对于数字
    addNumberFormat();

    //对于字符串
    addStringFormat();

    //对于注释
    addCommentFormat();

    //对于关键字/保留字
    addKeywordsFromat();

    //对于类名
    addClassNameFormat();

    //对于方法/函数
    addFunctionFormat();
}


void MyHighlighter::addNormalTextFormat()
{
    HighlightRule rule;
    rule.pattern = QRegExp("[a-z0-9A-Z]+");

    QTextCharFormat normalTextFormat;

    normalTextFormat.setFont(QFont(mFontFamily,mFontSize));
    normalTextFormat.setForeground(QColor(0,0,0));

    rule.format = normalTextFormat;

    highlightRules.append(rule);
}

void MyHighlighter::addNumberFormat()
{
    HighlightRule rule;
    rule.pattern = QRegExp("\\b\\d+|\\d+\\.\\d+\\b");

    QTextCharFormat numberFormat;

    numberFormat.setFont(QFont(mFontFamily,mFontSize));
    numberFormat.setForeground(QColor(250,80,50));

    rule.format = numberFormat;

    highlightRules.append(rule);
}

void MyHighlighter::addStringFormat()
{
    QTextCharFormat stringFormat;

    stringFormat.setFont(QFont(mFontFamily,mFontSize));
    stringFormat.setForeground(QColor(0,180,180));


    HighlightRule rule;

    rule.format = stringFormat;

    //''
    rule.pattern = QRegExp("'[^']*'");
    highlightRules.append(rule);

    //""
    rule.pattern = QRegExp("\"[^\"]*\"");
    highlightRules.append(rule);

    //``
    rule.pattern = QRegExp("`[^`]*`");
    highlightRules.append(rule);

}

void MyHighlighter::addCommentFormat()
{
    QTextCharFormat commnetFormat;

    commnetFormat.setFont(QFont(mFontFamily,mFontSize));
    commnetFormat.setForeground(Qt::darkGreen);
    commnetFormat.setFontItalic(true);


    HighlightRule rule;

    rule.format = commnetFormat;

    // //dada
    rule.pattern = QRegExp("\\/\\/.*$");
    highlightRules.append(rule);
}

void MyHighlighter::addMultiLineCommentFormat(const QString &text)
{
    setCurrentBlockState(0);

    // /*
    QRegExp commentStartRegExp("/\\*");
    // */
    QRegExp commentEndRegExp("\\*/");

    //高亮格式
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setFont(QFont(mFontFamily,mFontSize));
    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);

    int startIndex = 0;
    if(previousBlockState()!=1)
       startIndex= commentStartRegExp.indexIn(text);

    while(startIndex>=0){
        int endIndex = commentEndRegExp.indexIn(text,startIndex);
        int commentLength = 0;
        if(endIndex==-1){//没有结束位置
            setCurrentBlockState(1);
            commentLength = text.length()-startIndex;
        }else{//有结束位置
            commentLength = endIndex-startIndex+commentEndRegExp.matchedLength();
        }
        //设置格式
        setFormat(startIndex,
                  commentLength,
                  multiLineCommentFormat);
        startIndex = commentStartRegExp.indexIn(text,commentLength+startIndex);
    }
}

void MyHighlighter::addKeywordsFromat()
{
    QFile file(":/config/config/keywords.txt");
    QTextStream keywordsStream(&file);

    HighlightRule rule ;
    QTextCharFormat keywordsFormat;
    keywordsFormat.setFont(QFont(mFontFamily,mFontSize));
    keywordsFormat.setForeground(Qt::darkYellow);
    rule.format = keywordsFormat;

    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        keywordsStream.seek(0);
        QString line ;
        while (!keywordsStream.atEnd()) {
           line = keywordsStream.readLine();
           if(line!=""){
               rule.pattern = QRegExp("\\b"+line+"\\b");
               highlightRules.append(rule);
           }
        }
        file.close();
    }
}

void MyHighlighter::addClassNameFormat()
{
    HighlightRule rule;

    QTextCharFormat classNameFormat;
    classNameFormat.setFont(QFont(mFontFamily,mFontSize));
    classNameFormat.setForeground(QColor(150,20,100));
    classNameFormat.setFontWeight(99);

    rule.format = classNameFormat;

    rule.pattern = QRegExp("\\b[A-Z]+\\w*");
    highlightRules.append(rule);
}

void MyHighlighter::addFunctionFormat()
{
    HighlightRule rule;

    QTextCharFormat functionFormat;
    functionFormat.setFont(QFont(mFontFamily,mFontSize));
    functionFormat.setForeground(QColor(200,0,150));

    rule.format = functionFormat;

    rule.pattern = QRegExp("\\w+\\(");
    highlightRules.append(rule);
    rule.pattern = QRegExp("\\)");
    highlightRules.append(rule);
}



//按行来传入的
void MyHighlighter::highlightBlock(const QString &text)
{
    QRegExp regExp;
    foreach (const HighlightRule &rule, highlightRules) {
        regExp=rule.pattern;
        int index = regExp.indexIn(text);
        while(index>=0){
            int length =regExp.matchedLength();
            setFormat(index,length,rule.format);
            index = regExp.indexIn(text,index+length);
        }
    }

    //对于多行注释
    addMultiLineCommentFormat(text);
}


```

## 四 纯代码自定义组件Ⅰ

### 19 UI创建

[【Qt开发项目实战——代码编辑器Code Editor Demo——19 纯代码自定义组件Ⅰ——UI创建】](https://www.bilibili.com/video/BV1Nv4y1V7oL/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytexteditbycode.h

```c++
#ifndef MYTEXTEDITBYCODE_H
#define MYTEXTEDITBYCODE_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QScrollBar>

class MyTextEditByCode : public QWidget
{
    Q_OBJECT
public:
    explicit MyTextEditByCode(QWidget *parent = nullptr);

signals:

};

#endif // MYTEXTEDITBYCODE_H

```

- mytexteditbycode.cpp

```c++
#include "myhighlighter.h"
#include "mytexteditbycode.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


MyTextEditByCode::MyTextEditByCode(QWidget *parent) : QWidget(parent)
{

    QWidget * horizontalLayoutWidget = new QWidget();
    //竖向布局
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);

    //横向布局
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setMargin(0);

    QTextEdit *textEdit = new QTextEdit();
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    QTextBrowser *textBrowser = new QTextBrowser();
    textBrowser->setMaximumWidth(25);
    textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QScrollBar *scrollBar = new QScrollBar();
    scrollBar->setOrientation(Qt::Horizontal);

    horizontalLayout->addWidget(textBrowser);
    horizontalLayout->addWidget(textEdit);

    verticalLayout->addWidget(horizontalLayoutWidget);
    verticalLayout->addWidget(scrollBar);
}
```

### 20 滚动条绑定

[【Qt开发项目实战——代码编辑器Code Editor Demo——20 纯代码自定义组件Ⅰ——滚动条绑定】](https://www.bilibili.com/video/BV1fM411T7rs/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytexteditbycode.h

```c++
#ifndef MYTEXTEDITBYCODE_H
#define MYTEXTEDITBYCODE_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QScrollBar>

class MyTextEditByCode : public QWidget
{
    Q_OBJECT
public:
    explicit MyTextEditByCode(QWidget *parent = nullptr);

private slots:
    void onTextEditHorizontalScrollBarChanged();
    void onTextEditVerticalScrollBarChanged();
    void onScrollBarChanged();
    void onTextBrowserHorizontalScrollBarChanged();


private:
    QTextEdit *textEdit ;
    QTextBrowser *textBrowser;
    QScrollBar *scrollBar ;

    void initWidget();
    void initFont();
    void initConnection();
signals:

};

#endif // MYTEXTEDITBYCODE_H

```

- mytexteditbycode.cpp

```c++
#include "myhighlighter.h"
#include "mytexteditbycode.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


MyTextEditByCode::MyTextEditByCode(QWidget *parent) : QWidget(parent)
{

    //UI组件
    initWidget();

    //字体
    initFont();

    //绑定
    initConnection();

}

void MyTextEditByCode::initWidget()
{
    QWidget * horizontalLayoutWidget = new QWidget();
    //竖向布局
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);

    //横向布局
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setMargin(0);

    textEdit = new QTextEdit();
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    textBrowser = new QTextBrowser();
    textBrowser->setMaximumWidth(25);
    textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scrollBar = new QScrollBar();
    scrollBar->setOrientation(Qt::Horizontal);

    horizontalLayout->addWidget(textBrowser);
    horizontalLayout->addWidget(textEdit);

    verticalLayout->addWidget(horizontalLayoutWidget);
    verticalLayout->addWidget(scrollBar);
}

void MyTextEditByCode::initFont()
{
    textEdit->setFont(QFont("Consolas",14));
    textBrowser->setFont(QFont("Consolas",14));
}

void MyTextEditByCode::initConnection()
{
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));

    connect(textEdit->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onTextEditHorizontalScrollBarChanged()));
    connect(textEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onTextEditVerticalScrollBarChanged()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(onScrollBarChanged()));
    connect(textBrowser->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onTextBrowserHorizontalScrollBarChanged()));
}

void MyTextEditByCode::onTextEditHorizontalScrollBarChanged(){
    scrollBar->setMaximum(textEdit->horizontalScrollBar()->maximum());
    scrollBar->setMinimum(textEdit->horizontalScrollBar()->minimum());
    scrollBar->setPageStep(textEdit->horizontalScrollBar()->pageStep());
    scrollBar->setValue(textEdit->horizontalScrollBar()->value());
}

void MyTextEditByCode::onTextEditVerticalScrollBarChanged(){
    textBrowser->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->value());
}

void MyTextEditByCode::onScrollBarChanged(){
    textEdit->horizontalScrollBar()->setValue(scrollBar->value());
}

void MyTextEditByCode::onTextBrowserHorizontalScrollBarChanged(){
    textEdit->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->value());
}
```

### 21 行号及高亮

[【Qt开发项目实战——代码编辑器Code Editor Demo——21 纯代码自定义组件Ⅰ——行号及高亮】](https://www.bilibili.com/video/BV1uN411T781/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mytexteditbycode.h

```c++
...
    
private slots:
    ...
        
    void onTextChanged();

private:
    ...
        
    void initHighlighter();

...
```

- mytexteditbycode.cpp

```c++
#include "myhighlighter.h"

...

MyTextEditByCode::MyTextEditByCode(QWidget *parent) : QWidget(parent)
{
    ...

    //高亮
    initHighlighter();
}

...

void MyTextEditByCode::initConnection()
{
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));

    ...
}

void MyTextEditByCode::initHighlighter()
{
    new MyHighlighter(textEdit->document());
}

...

void MyTextEditByCode::onTextChanged()
{
    int lineContOfTextEdit = textEdit->document()->lineCount();

    QString text = textBrowser->toPlainText();
    int lineContOfTextBrowser = text.trimmed().split("\n").length();

    if(lineContOfTextBrowser>lineContOfTextEdit){
        for(int i = lineContOfTextBrowser;i>lineContOfTextEdit;i--)
            text.chop((QString::number(i)+"\n").length());
    }else if(lineContOfTextBrowser==1&text.length()<1){
        text ="1\n";
    }else if(lineContOfTextBrowser<lineContOfTextEdit){
        for(int i = lineContOfTextBrowser;i<lineContOfTextEdit;i++)
            text +=QString::number(i+1)+"\n";
    }
    textBrowser->setText(text);
}
```

### 22 固定行高

[【Qt开发项目实战——代码编辑器Code Editor Demo——22 纯代码自定义组件Ⅰ——固定行高】]()

```c++
...

void MyTextEditByCode::initFont()
{
    mFont = QFont("Consolas",14);
    
    ...
        
    QTextBlockFormat format ;
    format.setLineHeight(QFontMetrics(mFont).height()*1.1,QTextBlockFormat::FixedHeight);

    QTextCursor cursor =  textEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);

    ...

}

...

void MyTextEditByCode::onTextChanged()
{
    ...

    QTextBlockFormat format ;
    format.setLineHeight(QFontMetrics(mFont).height()*1.1,QTextBlockFormat::FixedHeight);
    format.setAlignment(Qt::AlignRight);
    QTextCursor cursor =  textBrowser->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
}
```

### 23 当前行的高亮

[【Qt开发项目实战——代码编辑器Code Editor Demo——23 纯代码自定义组件Ⅰ——当前行的高亮】]()

- mytexteditbycode.h

```c++
...
    
private slots:
    ...
        
    void highlightCurrentLine();

...
```

- mytexteditbycode.cpp

```c++
#include "myhighlighter.h"

...

MyTextEditByCode::MyTextEditByCode(QWidget *parent) : QWidget(parent)
{
    ...

    //高亮当前行
    highlightCurrentLine();
}

...

void MyTextEditByCode::initConnection()
{
    //cursor改变信号
    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    ...
}

...

void MyTextEditByCode::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;
    
    selection.format.setBackground(QColor(0,100,100,20).lighter(30));
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textEdit->textCursor();
    //selection.cursor.clearSelection();
    extraSelections.append(selection);
    
    textEdit->setExtraSelections(extraSelections);
}
```

### 小结——完整代码

- mytexteditbycode.h

```c++
#ifndef MYTEXTEDITBYCODE_H
#define MYTEXTEDITBYCODE_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QScrollBar>

class MyTextEditByCode : public QWidget
{
    Q_OBJECT
public:
    explicit MyTextEditByCode(QWidget *parent = nullptr);

private slots:
    void onTextEditHorizontalScrollBarChanged();
    void onTextEditVerticalScrollBarChanged();
    void onScrollBarChanged();
    void onTextBrowserHorizontalScrollBarChanged();

    void onTextChanged();
    void highlightCurrentLine();

private:
    QTextEdit *textEdit ;
    QTextBrowser *textBrowser;
    QScrollBar *scrollBar ;
    QFont mFont;

    void initWidget();
    void initFont();
    void initConnection();
    void initHighlighter();


signals:

};

#endif // MYTEXTEDITBYCODE_H
```

- mytexteditbycode.cpp

```c++
#include "myhighlighter.h"
#include "mytexteditbycode.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


MyTextEditByCode::MyTextEditByCode(QWidget *parent) : QWidget(parent)
{
    //UI组件
    initWidget();

    //字体
    initFont();

    //绑定
    initConnection();

    //高亮
    initHighlighter();

    //行的高亮
    highlightCurrentLine();
}

void MyTextEditByCode::initWidget()
{
    QWidget * horizontalLayoutWidget = new QWidget();
    //竖向布局
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);

    //横向布局
    QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setMargin(0);

    textEdit = new QTextEdit();
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    textBrowser = new QTextBrowser();
    textBrowser->setMaximumWidth(25);
    textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scrollBar = new QScrollBar();
    scrollBar->setOrientation(Qt::Horizontal);

    horizontalLayout->addWidget(textBrowser);
    horizontalLayout->addWidget(textEdit);

    verticalLayout->addWidget(horizontalLayoutWidget);
    verticalLayout->addWidget(scrollBar);
}

void MyTextEditByCode::initFont()
{
    mFont = QFont("Consolas",14);
    textEdit->setFont(mFont);
    QTextBlockFormat format ;
    format.setLineHeight(QFontMetrics(mFont).height()*1.1,QTextBlockFormat::FixedHeight);

    QTextCursor cursor =  textEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);

    textBrowser->setFont(mFont);

}

void MyTextEditByCode::initConnection()
{
    //textChange
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));

    //滚动条
    connect(textEdit->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onTextEditHorizontalScrollBarChanged()));
    connect(textEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onTextEditVerticalScrollBarChanged()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(onScrollBarChanged()));
    connect(textBrowser->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onTextBrowserHorizontalScrollBarChanged()));

    //cursor
    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(highlightCurrentLine()));
}

void MyTextEditByCode::initHighlighter()
{
    new MyHighlighter(textEdit->document());
}

void MyTextEditByCode::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(0,100,100,20));
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor=textEdit->textCursor();

    //selection.cursor.clearSelection();

    extraSelections.append(selection);

    textEdit->setExtraSelections(extraSelections);

}

void MyTextEditByCode::onTextEditHorizontalScrollBarChanged(){
    scrollBar->setMaximum(textEdit->horizontalScrollBar()->maximum());
    scrollBar->setMinimum(textEdit->horizontalScrollBar()->minimum());
    scrollBar->setPageStep(textEdit->horizontalScrollBar()->pageStep());
    scrollBar->setValue(textEdit->horizontalScrollBar()->value());
}

void MyTextEditByCode::onTextEditVerticalScrollBarChanged(){
    textBrowser->verticalScrollBar()->setMaximum(textEdit->verticalScrollBar()->maximum());
    textBrowser->verticalScrollBar()->setMinimum(textEdit->verticalScrollBar()->minimum());
    textBrowser->verticalScrollBar()->setPageStep(textEdit->verticalScrollBar()->pageStep());
    textBrowser->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->value());
}

void MyTextEditByCode::onScrollBarChanged(){
    textEdit->horizontalScrollBar()->setValue(scrollBar->value());
}

void MyTextEditByCode::onTextBrowserHorizontalScrollBarChanged(){
    textEdit->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->value());
}

void MyTextEditByCode::onTextChanged()
{
    int lineContOfTextEdit = textEdit->document()->lineCount();

    QString text = textBrowser->toPlainText();
    int lineContOfTextBrowser = text.trimmed().split("\n").length();

    if(lineContOfTextBrowser>lineContOfTextEdit){
        for(int i = lineContOfTextBrowser;i>lineContOfTextEdit;i--)
            text.chop((QString::number(i)+"\n").length());
    }else if(lineContOfTextBrowser==1&text.length()<1){
        text ="1\n";
    }else if(lineContOfTextBrowser<lineContOfTextEdit){
        for(int i = lineContOfTextBrowser;i<lineContOfTextEdit;i++)
            text +=QString::number(i+1)+"\n";
    }
    textBrowser->setMaximumWidth(25+QString::number(lineContOfTextEdit).length()*7);
    textBrowser->setText(text);

    QTextBlockFormat format ;
    format.setLineHeight(QFontMetrics(mFont).height()*1.1,QTextBlockFormat::FixedHeight);
    format.setAlignment(Qt::AlignRight);
    QTextCursor cursor =  textBrowser->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
}


```

## 五 纯代码自定义组件Ⅱ

### 24 类创建

[【Qt开发项目实战——代码编辑器Code Editor Demo——24 纯代码自定义组件Ⅱ——类创建】]()

- 新建类MyCodeEditor，选择Widget
- 修改继承——QPlainTextEdit
- 修改字体
- 添加行高亮
- 添加高亮

- mycodeeditor.h

```c++
#ifndef MYTEXTEDITBYCODE_H
#define MYTEXTEDITBYCODE_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QScrollBar>

class MyTextEditByCode : public QWidget
{
    Q_OBJECT
public:
    explicit MyTextEditByCode(QWidget *parent = nullptr);

private slots:
    void onTextEditHorizontalScrollBarChanged();
    void onTextEditVerticalScrollBarChanged();
    void onScrollBarChanged();
    void onTextBrowserHorizontalScrollBarChanged();

    void onTextChanged();

    void highlightCurrentLine();

private:
    QTextEdit *textEdit ;
    QTextBrowser *textBrowser;
    QScrollBar *scrollBar ;
    QFont mFont;

    void initWidget();
    void initFont();
    void initConnection();
    void initHighlighter();

signals:

};

#endif // MYTEXTEDITBYCODE_H

```

- mycodeeditor.cpp

```c++
#include "mycodeeditor.h"
#include "myhighlighter.h"

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    //绑定
    initConnection();
    //初始字体
    initFont();

    //高亮
    initHighlighter();

    //行高亮
    highlightCurrentLine();
}


void MyCodeEditor::initConnection()
{
    //cursor
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(highlightCurrentLine()));
}

void MyCodeEditor::initFont()
{
    this->setFont(QFont("Consolas",14));
}

void MyCodeEditor::initHighlighter()
{
    new MyHighlighter(document());
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
```

### 25 绘制行号区域

[【Qt开发项目实战——代码编辑器Code Editor Demo——25 纯代码自定义组件Ⅱ——绘制行号区域】]()

- mycodeeditor.h

```c++
...

class LineNumberWidget;

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void lineNumberWidgetPaintEvent(QPaintEvent *event);

...
    
protected:
    void resizeEvent(QResizeEvent *event);

private:
    ...
        
    LineNumberWidget *lineNumberWidget;
signals:

};


class LineNumberWidget :public QWidget
{
public:
    LineNumberWidget(MyCodeEditor * editor=nullptr):QWidget(editor){
        codeEditor = editor;
    }

protected:
    void paintEvent(QPaintEvent *event){
        codeEditor->lineNumberWidgetPaintEvent(event);
    }

private:
    MyCodeEditor * codeEditor;
};

...
```

- mycodeeditor.cpp

```c++
...

#include <QPainter>

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    //行号
    lineNumberWidget = new LineNumberWidget(this);

    ...

    //设置边距
    setViewportMargins(25,0,0,0);
}

...
    
void MyCodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect rect =    contentsRect();
    lineNumberWidget->setGeometry(QRect(rect.left(),rect.top(),25,rect.height()));
}


void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberWidget);
    painter.fillRect(event->rect(),QColor(100,100,100,100));
}

```

### 26 绘制行号文字

[【Qt开发项目实战——代码编辑器Code Editor Demo——26 纯代码自定义组件Ⅱ——绘制行号文字】]()

- mycodeeditor.h

```c++
...
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
...
private slots:
    ...
    void updateLineNumberWidget(QRect rect,int dy);

...

private:
    ...
    int getLineNumberWidgetWidth();

    ...
}
...
```

- mycodeeditor.cpp

```c++
...

void MyCodeEditor::initConnection()
{
    ...

    //updateRequest
    connect(this,SIGNAL(updateRequest(QRect, int)),this,SLOT(updateLineNumberWidget(QRect, int)));
}

...

void MyCodeEditor::updateLineNumberWidget(QRect rect, int dy)
{
    if(dy)
        lineNumberWidget->scroll(0,dy);
    else
        lineNumberWidget->update(0,rect.y(),25,rect.height());
}

...

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberWidget);
    //绘制行号区域
    painter.fillRect(event->rect(),QColor(100,100,100,20));

    //拿到block
    QTextBlock block = firstVisibleBlock();

    //拿到行号
    int blockNumber =block.blockNumber();

    //拿到block的top
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();

    //拿到block的bottom
    int bottom = top +blockBoundingRect(block).height();

    while(block.isValid()&&top<=event->rect().bottom()){
        //设置画笔颜色
        painter.setPen(Qt::black);
        //绘制文字
        painter.drawText(0,top,25,bottom-top,Qt::AlignRight,QString::number(blockNumber+1));

        //拿到下一个block
        block = block.next();

        top = bottom;
        bottom =  top +blockBoundingRect(block).height();
        blockNumber++;
    }
}
```

### 27 行号宽度及高亮

[【Qt开发项目实战——代码编辑器Code Editor Demo——27 纯代码自定义组件Ⅱ——行号宽度及高亮】]()

- mycodeeditor.h

```c++
...
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
...
        
private slots:
    ...
    void updateLineNumberWidgetWidth();
    ...

...

private:
    ...
    int getLineNumberWidgetWidth();

    ...
}
...
```

- mycodeeditor.cpp

```c++
...

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    ...

    //设置边距
    updateLineNumberWidgetWidth();
}

void MyCodeEditor::initConnection()
{
    ...
        
    //blockCount
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberWidgetWidth()));

    ...
}

...

int MyCodeEditor::getLineNumberWidgetWidth()
{
    //获取宽度（合适）
    return 8+QString::number(blockCount()+1).length()*fontMetrics().horizontalAdvance(QChar('0'));
}

...

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

...

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    ...

    //拿到当前的block的top
    int cursorTop = blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top();

    ...

    while(block.isValid()&&top<=event->rect().bottom()){
        //设置画笔颜色
        painter.setPen(cursorTop==top?Qt::black:Qt::gray);
        
        ...
    }
}
```

### 28 行号点击事件Ⅰ

[【Qt开发项目实战——代码编辑器Code Editor Demo——28 纯代码自定义组件Ⅱ——行号点击事件Ⅰ】]()

- mycodeeditor.h

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void lineNumberWidgetMousePressEvent(QMouseEvent *event);

...

};

class LineNumberWidget :public QWidget{
    
...

protected:
    ...
        
    void mousePressEvent(QMouseEvent *event) override{
        //把鼠标点击任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetMousePressEvent(event);
    }
};
...

```

- mycodeeditor.cpp

```c++
...

void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event)
{
    setTextCursor(QTextCursor(document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value())));
}
```

### 29 行号点击事件Ⅱ

[【Qt开发项目实战——代码编辑器Code Editor Demo——29 纯代码自定义组件Ⅱ——行号点击事件Ⅱ】]()

- mycodeeditor.cpp

```c++
...
    
#include <QScrollBar>
    
...
    
void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event)
{
    setTextCursor(QTextCursor(document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value())));
}
```

### 30 行号滚动事件

[【Qt开发项目实战——代码编辑器Code Editor Demo——30 纯代码自定义组件Ⅱ——行号滚动事件】]()

- mycodeeditor.h

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void lineNumberWidgetWheelEvent(QWheelEvent *event);
...

};

class LineNumberWidget :public QWidget{
...

protected:
    ...

    void wheelEvent(QWheelEvent *event) override{
        //把滚轮任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetWheelEvent(event);
    }
...
    
};

...
```

- mycodeeditor.cpp

```c++
...

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    ...

    setLineWrapMode(QPlainTextEdit::NoWrap);
}

...

void MyCodeEditor::lineNumberWidgetWheelEvent(QWheelEvent *event)
{
    if(event->orientation()==Qt::Horizontal){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->delta());
    }else {
       verticalScrollBar()->setValue(verticalScrollBar()->value()-event->delta());
    }
    event->accept();
}
```

### 小结——完整代码

- mycodeeditor.h

```c++
#ifndef MYCODEEDITOR_H
#define MYCODEEDITOR_H

#include <QPlainTextEdit>

class LineNumberWidget;

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MyCodeEditor(QWidget *parent = nullptr);

    void lineNumberWidgetPaintEvent(QPaintEvent * event);

    void lineNumberWidgetMousePressEvent(QMouseEvent *event);

    void lineNumberWidgetWheelEvent(QWheelEvent *event);

private slots:
    void highlightCurrentLine();
    void updateLineNumberWidget(QRect rect, int dy);
    void updateLineNumberWidgetWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initConnection();
    void initFont();
    void initHighlighter();
    int getLineNumberWidgetWidth();


    LineNumberWidget * lineNumberWidget;
signals:

};

class LineNumberWidget :public QWidget{
public:
    explicit LineNumberWidget(MyCodeEditor *editor=nullptr):QWidget(editor){
        codeEditor=editor;
    }

protected:
    void  paintEvent(QPaintEvent *event) override{
        //把绘制任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetPaintEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override{
        //把鼠标点击任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetMousePressEvent(event);
    }

    void wheelEvent(QWheelEvent *event) override{
        //把滚轮任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetWheelEvent(event);
    }

private:
    MyCodeEditor *codeEditor;
};

#endif // MYCODEEDITOR_H
```

- mycodeeditor.cpp

```c++
#include "mycodeeditor.h"
#include "myhighlighter.h"

#include <QPainter>
#include <QDebug>
#include <QScrollBar>

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberWidget = new LineNumberWidget(this);
    //绑定
    initConnection();

    //初始字体
    initFont();

    //高亮
    initHighlighter();

    //行高亮
    highlightCurrentLine();

    //设置边距
    updateLineNumberWidgetWidth();

    setLineWrapMode(QPlainTextEdit::NoWrap);
}

void MyCodeEditor::initConnection()
{
    //cursor
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(highlightCurrentLine()));

    //blockCount
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberWidgetWidth()));

    //updateRequest
    connect(this,SIGNAL(updateRequest(QRect, int)),this,SLOT(updateLineNumberWidget(QRect, int)));
}

void MyCodeEditor::initFont()
{
    this->setFont(QFont("Consolas",14));
}

void MyCodeEditor::initHighlighter()
{
    new MyHighlighter(document());
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
```

## 六 项目完善

### 31 打开文档

[【Qt开发项目实战——代码编辑器Code Editor Demo——31 项目完善——打开文档】]()

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

### 32 保存文档

[【Qt开发项目实战——代码编辑器Code Editor Demo——32 项目完善——保存文档】]()

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

### 33 另存文档

[【Qt开发项目实战——代码编辑器Code Editor Demo——33 项目完善——另存文档】]()

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

### 34 添加析构函数

[【Qt开发项目实战——代码编辑器Code Editor Demo——34 项目完善——添加析构函数】]()

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

### 35 复制粘贴剪切打印

[【Qt开发项目实战——代码编辑器Code Editor Demo——35 项目完善——复制粘贴剪切打印】]()

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

### 36 设置字体

[【Qt开发项目实战——代码编辑器Code Editor Demo——36 项目完善——设置字体】]()

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
        mSettings->setValue("font_size",font.pointSize());
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

    //高亮
    initHighlighter();

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
    mFontSize = font.pointSize();
}

...
```



### 37 退出保存提示

[【Qt开发项目实战——代码编辑器Code Editor Demo——37 项目完善——退出保存提示】]()

- mycodeeditor.h

```c++
...
    
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...
        
    bool checkSaved();


private slots:
    ...
        
    void updateSaveState();

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

### 小结——完整代码

- mainwindow.cpp

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "QFileDialog"
#include "QMessageBox"
#include "QFontDialog"


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
    this->setCentralWidget(ui->tabWidget);

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

## 七 打包安装程序

### 38 打包

- 图标下载地址：[logo.ico](https://files.hyz.cool/files/articles/63b3c5bbcb7c0e2a09a99853959f4eab.ico)

- 先设置为release模式

- 点击编译

- 拷贝exe到打包的目录

- 打开编译程序MinGw

- 输入

```shell
windeployqt .exe
```

- 下载打包安装程序

[Inno Setup Downloads (jrsoftware.org)](https://jrsoftware.org/isdl.php#stable)

