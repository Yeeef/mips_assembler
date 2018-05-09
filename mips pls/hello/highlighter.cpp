#include "highlighter.h"

MyHighLighter::MyHighLighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\badd\\b" << "\\baddi\\b" << "\\bsub\\b"
                    << "\\blw\\b" << "\\bsw\\b" << "\\blb\\b"
                    << "\\blbu\\b" << "\\blh\\b" << "\\blhu\\b"
                    << "\\bsw\\b" << "\\bsb\\b" << "\\bsh\\b"
                    << "\\baddu\\b" << "\\bsubu\\b" << "\\bslt\\b"
                    << "\\bsltu\\b" << "\\band\\b" << "\\bor\\b"
                    << "\\bxor\\b" << "\\bnor\\b" << "\\bsll\\b"
                    << "\\bsrl\\b" << "\\bsra\\b" << "\\bmult\\b"
                    << "\\bmultu\\b" << "\\bdiv\\b" << "\\bdivu\\b"
                    << "\\baddiu\\b" << "\\bandi\\b" << "\\bori\\b"
                    << "\\bxori\\b" << "\\blui\\b" << "\\bslti\\b"
                    << "\\bsltiu\\b" << "\\bbeq\\b" << "\\bbne\\b"
                    << "\\bblez\\b" << "\\bbgtz\\b" << "\\bj\\b"
                    << "\\bbltz\\b" << "\\bbgez\\b" << "\\bjal\\b"
                    << "\\bjalr\\b" << "\\bjr\\b" << "\\bmfhi\\b"
                    << "\\bmflo\\b" << "\\bmthi\\b" << "\\bmtlo\\b"
                    <<"\\beret\\b" << "\\bmfc0\\b" << "\\bmtc0\\b"
                   << "\\bbreak\\b" << "\\bsyscall\\b" << "\\bmove\\b"
                   <<"\\bli\\b" << "\\bla\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    /*
    immediateNumberFormat.setFontWeight(QFont::Bold);
    immediateNumberFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = immediateNumberFormat;
    highlightingRules.append(rule);
    */
    /*
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
    */
    /*
    regFormat.setFontWeight(QFont::Bold);
    regFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\B\\$[0-9]{1,2}\\b");
    rule.format = regFormat;
    highlightingRules.append(rule);
    */

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\B\\$[t0-t9]{1,2}\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);


    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);


    commentStartExpression = QRegExp("/\\*");
    commentStartExpression = QRegExp("/#");
    commentEndExpression = QRegExp("\\*/");
}

void MyHighLighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);


    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
