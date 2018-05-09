#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <QtGui>
#include <QtWidgets>
#include <QMap>
#include <QString>

class assemble_manager
{
public:
    assemble_manager();
    ~assemble_manager() {}
    void convert2lines(QString content);
    int processAline(QString line, QString & assembled_line);
    void firstProcess();//第一遍处理，存进first_processed_lines中
    void finalProcess(QString & process_content);
    void convert2coe(QString  bin_content, QString & coe_content);
    void printLabel();
    QString get_error() { return error; }
    bool get_status() {return isError;}
    void clearError();
    void clearCan() {isData = false;}


private:
    QString error;
    bool isError;
    bool isData;
    uint LastPC;
    uint PC; //
    uint PC_init;
    QStringList lines;
    QStringList first_processed_lines;
    QStringList final_processed_Lines;


    QMap <QString, QString> Reg2Num;
    QMap <QString, QString> Type;
    QMap <QString, QString> Opcode;
    QMap <QString, QString> Fun;
    QMap <QString, uint> Labels;
    QMap <QString, uint> dataLabels;
    QMap <uint, uint> addr_data;

    //初始化函数
    void setRegs();
    void setOpcode();
    void setType();
    void setFun();

    //判断函数
    bool isReg(const QString & reg);
    bool isShamt(const QString & shamt);
    bool canInst();


    //操作函数
    void PC_clear();
    bool shamt2Bin(const QString & shamt, QString & outBin);
    bool imm2Bin(const QString & imm, QString & outBin, int length);
    bool signed_imm2Bin(const QString & imm, QString & outBin, int length);
    bool target2Bin(const QString & target, QString & outBin);
    bool sel2Bin(const QString & sel, QString & outBin);
    bool Bin2Dec(const QString &Bin, long & dec, int radix);
    void setError(QString & error);
    void Hex2Bin(QString & Hex, QString & Bin);




};

#endif // ASSEMBLE_H
