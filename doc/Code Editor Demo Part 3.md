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

### 

