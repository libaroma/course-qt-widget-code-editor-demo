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

