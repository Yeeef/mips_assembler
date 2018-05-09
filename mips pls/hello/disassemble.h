#ifndef DISASSEMBLE_H
#define DISASSEMBLE_H

#include <QtGui>
#include <QtWidgets>
#include <QMap>
#include <QString>

class disassemble_manager
{
public:
    disassemble_manager();
    ~disassemble_manager();
    void convert2lines(QString content);
    bool processAline(QString & inst, QString & assembled_inst);
    void firstProcess();//第一遍处理，存进first_processed_lines中
    void finalProcess(QString & process_content); //存进final_processed_lines
    bool coe2bin(QString content, QString & bin_content);
     void clearError();

    //void printLabel();
    QString get_error() { return error; }
    bool get_status() {return isError;}

private:
    QString error;
    bool isError;
    uint PC; //
    uint PC_init;
    QStringList raw_lines;
    QStringList first_processed_lines;
    QStringList final_processed_Lines;

    /* map */
    QMap <QString, QString> Num2Reg;
    QMap <QString, QString> Type;
    QMap <QString, QString> Type_R;
    QMap <QString, QString> Command;
    QMap <QString, QString> Fun;
    QMap <uint, QString> Labels;

    /* 初始化函数 */
    void setType();
    void setRegs();
    void setFun();
    void setCommand();
    void setType_R();

    /* 判断函数 */
    bool isType(const QString & opcode);
    bool isReg(const QString & reg);
    bool isBin(const QString & str);
    bool isInst(const QString & inst);
    bool isFun(const QString & Func);
    bool isCommand(const QString &command);
    bool UBin2Dec(const QString & Bin, QString & Dec, int length);
    bool Bin2Dec(const QString & Bin, QString & Dec, int length);

    /* 操作函数 */
    void PC_clear();
    void PC_increment();
    void setError(QString & error);



};

#endif // DISASSEMBLE_H
