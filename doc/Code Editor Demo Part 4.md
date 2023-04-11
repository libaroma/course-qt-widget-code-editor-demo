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

[【Qt开发项目实战——代码编辑器Code Editor Demo——22 纯代码自定义组件Ⅰ——固定行高】](https://www.bilibili.com/video/BV1zs4y1J7NP/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

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

```

### 23 当前行的高亮

[【Qt开发项目实战——代码编辑器Code Editor Demo——23 纯代码自定义组件Ⅰ——当前行的高亮】](https://www.bilibili.com/video/BV1DT411q7dE/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

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