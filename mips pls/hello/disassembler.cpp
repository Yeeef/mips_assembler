#include "disassemble.h"

disassemble_manager::disassemble_manager()
{
    PC_init = 0;
    PC = PC_init;
    setType();
    setType_R();
    setRegs();
    setFun();
    setCommand();
}
disassemble_manager::~disassemble_manager() {}

void disassemble_manager::setType()
{
    //R-format
    Type["000000"] = "R";

    //I-format
    Type["100011"] = "I-mem"; //lw
    Type["101011"] = "I-mem"; //sw
    Type["000100"] = "I-branch"; //beq
    Type["000101"] = "I-branch"; //bne
    Type["001000"] = "I"; //addi
    Type["001001"] = "I"; //addiu
    Type["001101"] = "I"; //ori
    Type["001100"] = "I"; //andi
    Type["001110"] = "I"; //xori
    Type["001111"] = "I-lui"; //lui
    Type["001010"] = "I"; //slti
    Type["001011"] = "I"; //sltiu
    Type["100000"] = "I-mem"; //lb
    Type["100100"] = "I-mem"; //lbu
    Type["100001"] = "I-mem"; //lh
    Type["100101"] = "I-mem"; //lhu
    Type["101001"] = "I-mem"; //sh
    Type["101000"] = "I-mem"; //sb
    Type["000001"] = "I-branch-2"; //bgez / bgezal

    Type["000111"] = "I-branch-2"; //bgtz
    Type["000110"] = "I-branch-2"; //blez
    Type["000001"] = "I-branch-2"; //bltz bltzal

    //j-format
    Type["000010"] = "J";
    Type["000011"] = "J";

    //other types
    Type["010000"] = "eret"; //eret, mfc0, mtc0






}

void disassemble_manager::setRegs()
{
    Num2Reg["00000"] = "$zero";
    Num2Reg["00001"] = "$at";
    Num2Reg["00010"] = "$v0";
    Num2Reg["00011"] = "$v1";
    Num2Reg["00100"] = "$a0";
    Num2Reg["00101"] = "$a1";
    Num2Reg["00110"] = "$a2";
    Num2Reg["00111"] = "$a3";
    Num2Reg["01000"] = "$t0";
    Num2Reg["01001"] = "$t1";
    Num2Reg["01010"] = "$t2";
    Num2Reg["01011"] = "$t3";
    Num2Reg["01100"] = "$t4";
    Num2Reg["01101"] = "$t5";
    Num2Reg["01110"] = "$t6";
    Num2Reg["01111"] = "$t7";
    Num2Reg["10000"] = "$s0";
    Num2Reg["10001"] = "$s1";
    Num2Reg["10010"] = "$s2";
    Num2Reg["10011"] = "$s3";
    Num2Reg["10100"] = "$s4";
    Num2Reg["10101"] = "$s5";
    Num2Reg["10110"] = "$s6";
    Num2Reg["10111"] = "$s7";
    Num2Reg["11000"] = "$t8";
    Num2Reg["11001"] = "$t9";
    Num2Reg["11010"] = "$k0";
    Num2Reg["11011"] = "$k1";
    Num2Reg["11100"] = "$gp";
    Num2Reg["11101"] = "$sp";
    Num2Reg["11110"] = "$fp";
    Num2Reg["11111"] = "$ra";



}

void disassemble_manager::setFun()
{
    //在座的都是r格式了
    Fun["100000"] = "add";
    Fun["100010"] = "sub";
    Fun["100100"] = "and";
    Fun["100101"] = "or";
    Fun["101010"] = "slt";
    Fun["000010"] = "srl";
    Fun["001000"] = "jr";
    Fun["001001"] = "jalr";
    Fun["100001"] = "addu";
    Fun["100011"] = "subu";
    Fun["100110"] = "xor";
    Fun["100111"] = "nor";
    Fun["000000"] = "sll";
    Fun["000011"] = "sra";
    Fun["000100"] = "sllv";
    Fun["000110"] = "srlv";
    Fun["000111"] = "srav";
    Fun["101011"] = "sltu";
    Fun["001100"] = "syscall";
    Fun["001101"] = "break";
    Fun["011000"] = "mult";
    Fun["011001"] = "multu";
    Fun["011010"] = "div";
    Fun["011011"] = "divu";
    Fun["010000"] = "mfhi";
    Fun["010010"] = "mflo";
    Fun["010001"] = "mthi";
    Fun["010011"] = "mtlo";





}

void disassemble_manager::setCommand()
{
    //这里不考虑r格式，因为r格式由fun决定
    //I 格式需要由前面的 opcode进行一个模糊区分
    Command["100011"] = "lw";
    Command["101011"] = "sw";
    Command["000100"] = "beq";
    Command["000101"] = "bne";
    Command["001000"] = "addi";
    Command["001001"] = "addiu";
    Command["001101"] = "ori";
    Command["001100"] = "andi";
    Command["001110"] = "xori";
    Command["001111"] = "lui";
    Command["001010"] = "slti";
    Command["001011"] = "sltiu";
    Command["100000"] = "lb";
    Command["100100"] = "lbu";
    Command["100001"] = "lh";
    Command["100101"] = "lhu";
    Command["101001"] = "sh";
    Command["101000"] = "sb";

    Command["000001"] = "REGIMM";
    //bgez bgezal bltz bltzal 单独处理
    Command["00001"] = "bgez";
    Command["10001"] = "bgezal";
    Command["00000"] = "bltz";
    Command["10000"] = "bltzal";

    //bgtz blez用前六位就可以区分
    Command["000111"] = "bgtz";
    Command["000110"] = "blez";



    //J-format
    Command["000010"] = "j";
    Command["000011"] = "jal";


}

void disassemble_manager::setType_R()
{
    Type_R["add"] = "R";
    Type_R["sub"] = "R";
    Type_R["and"] = "R";
    Type_R["or"]  = "R";
    Type_R["slt"] = "R";
    Type_R["srl"] = "R-shift";
    Type_R["jr"]  = "R-jump";
    Type_R["jalr"] = "R-jump-2";
    Type_R["addu"] = "R";
    Type_R["subu"] = "R";
    Type_R["xor"] = "R";
    Type_R["nor"] = "R";
    Type_R["sll"] = "R-shift";
    Type_R["sra"] = "R-shift";
    Type_R["sllv"] = "R-shift-2";
    Type_R["srlv"] = "R-shift-2";
    Type_R["srav"] = "R-shift-2";
    Type_R["sltu"] = "R";
    Type_R["syscall"] = "R-sys";
    Type_R["break"] = "R-sys";
    Type_R["mult"] = "R-mult";
    Type_R["multu"] = "R-mult";
    Type_R["div"] = "R-mult";
    Type_R["divu"] = "R-mult";
    Type_R["mfhi"] = "R-transfer";
    Type_R["mflo"] = "R-transfer";
    Type_R["mthi"] = "R-jump";
    Type_R["mtlo"] = "R-jump";

}

void disassemble_manager::convert2lines(QString content)
{
    //建立一个读取流 reader
    QTextStream reader(&content, QIODevice::ReadOnly);
    //把原有数据清空
    raw_lines.clear();


    while(!reader.atEnd())
    {
        //readline自动过滤空格
        raw_lines << reader.readLine();
    }

    //检验是否正常读入

    for(int i = 0; i < raw_lines.size(); i++)
    {
        qDebug() << raw_lines[i] << "\n";
    }



}

bool disassemble_manager::processAline(QString &inst, QString &disassembled_inst)
{

    inst = inst.trimmed();

    //最原始判断, 判断长度与非法字符
    if( !isInst(inst) )
        return false;

    if(inst == "00000000000000000000000000000000")
    {
        disassembled_inst = "add $zero, $zero, $zero;";
        return true;
    }

    //抓取opcode
    QString Opcode;
    int i = 0;
    for(i = 0; i < 6; i++)
        Opcode += inst[i];

    //初步判断格式
    if( !isType(Opcode) )
        return false;

    //格式必然存在了
    QString type = Type.value(Opcode);
    qDebug() << type;

    if(type == "R") {
        //读取Fun
        QString fun = inst.right(6);

        if( !isFun(fun) )
            return false;

        QString command = Fun[fun];
        QString type_R = Type_R[command];
        QString rs = Num2Reg[inst.mid(6, 5)];
        QString rt = Num2Reg[inst.mid(11, 5)];
        QString rd = Num2Reg[inst.mid(16, 5)];
        QString shamtBin = inst.mid(21, 5);




        if(type_R == "R") {
            //最简单的格式
            //add rd rs rt
            //000000_00000_00000_00000_00000_000000

            disassembled_inst = QString("%1 %2, %3, %4;")
                                .arg(command).arg(rd).arg(rs).arg(rt);
            qDebug() << "指令为：" << disassembled_inst;
        }
        else if(type_R == "R-shift") {
            //srl rd, rt, sa

            QString shamt;
            if( UBin2Dec(shamtBin, shamt, 5) == false)
               return false;

            disassembled_inst = QString("%1 %2, %3, %4;")
                                .arg(command).arg(rd).arg(rt).arg(shamt);
            qDebug() << "指令为：" << disassembled_inst;


        }
        else if(type_R == "R-shift-2") {
            //sllv rd, rt, rs
            disassembled_inst = QString("%1 %2, %3, %4;")
                                .arg(command).arg(rd).arg(rt).arg(rs);
            qDebug() << disassembled_inst;

        }
        else if(type_R == "R-jump") {
            //jr rs
            //mthi rs
            //mtlo rs
            disassembled_inst = QString("%1 %2;")
                                .arg(command).arg(rs);
            qDebug() << disassembled_inst;

        }
        else if(type_R == "R-jump-2") {
            //JALR rd, rs
            disassembled_inst = QString("%1 %2, %3;")
                                .arg(command).arg(rd).arg(rs);
            qDebug() << disassembled_inst;


        }
        else if(type_R == "R-sys") {
            //syscall;
            //break;
            disassembled_inst = QString("%1;")
                                .arg(command);
            qDebug() << disassembled_inst;

        }
        else if(type_R == "R-transfer") {
           //mfhi rd
           //mflo rd
            disassembled_inst = QString("%1 %2;")
                                .arg(command).arg(rd);
            qDebug() << disassembled_inst;

        }
        else if(type_R == "R-mult") {
            //mult rs, rt
            disassembled_inst = QString("%1 %2, %3;")
                                .arg(command).arg(rs).arg(rt);
            qDebug() << disassembled_inst;

        }



    }
    else if(type == "J") {
        // j target
        // jal target

        if( !isCommand(Opcode) )
            return false;
        QString command = Command[Opcode];
        //翻译无符号数target
        QString targetBin = inst.right(26);
        QString target;

        if( !UBin2Dec(targetBin, target, 26))
            return false;

        //实际上，target * 4才是我们要跳的位置(字节)
        bool ok;
        uint dec = target.toUInt(&ok, 10);
        dec = dec * 4;
        QString label;
        //先要判断这个位置有没有已经存在的label
        if( Labels.value(dec) == 0) {
            //还不存在这样一个label
            label = QString("Label %1").arg(Labels.size() + 1);
            Labels[dec] = label;

        }
        else {
            //已经存在
            label = Labels[dec];

        }
        disassembled_inst = QString("%1 %2;")
                            .arg(command).arg(label);
        qDebug() << disassembled_inst;





    }
    else if(type == "eret") {
        //eret, mfc0, mtc0

        //eret: 010000_1_19{0}_011000
        if(inst[6] == '1' && inst.right(6) == "011000"
                && inst.mid(7, 19) == "0000000000000000000") {
            //eret 指令

            disassembled_inst = QString("eret;");
            qDebug() << disassembled_inst;

        }
        else if(inst.mid(6, 5) == "00000" && inst.mid(21, 8) == "00000000") {
            //mfc0 rt, rd, sel;
            //010000_00000_rt_rd_00000000_sel

            //抓取rt, rd, sel
            QString rt = Num2Reg[inst.mid(11, 5)];
            QString rd = Num2Reg[inst.mid(16, 5)];
            QString selBin = inst.right(3);
            QString sel;

            if( !UBin2Dec(selBin, sel, 3) )
                return false;

            disassembled_inst = QString("mfc0 %1, %2, %3;")
                                .arg(rt).arg(rd).arg(sel);

            qDebug() << disassembled_inst;
        }
        else if(inst.mid(6, 5) == "00100" && inst.mid(21, 8) == "00000000") {
            //mtc0 rt, rd, sel;
            QString rt = Num2Reg[inst.mid(11, 5)];
            QString rd = Num2Reg[inst.mid(16, 5)];
            QString selBin = inst.right(3);
            QString sel;

            if( !UBin2Dec(selBin, sel, 3) )
                return false;

            disassembled_inst = QString("mtc0 %1, %2, %3;")
                                .arg(rt).arg(rd).arg(sel);

            qDebug() << disassembled_inst;
        }
        else {
            QString error = QString("暂不支持 指令：'%1'").arg(inst);
            setError(error);
            return false;
        }

    }
    else
    {
        //剩下了I格式，集中处理 rt, rs, imm
        if( !isCommand(Opcode) )
            return false;

        QString command = Command[Opcode];
        QString rt = Num2Reg[inst.mid(11, 5)];
        QString rs = Num2Reg[inst.mid(6, 5)];
        QString immBin = inst.right(16);
        QString imm;

        if(type == "I") {
            //最普通的I格式
            //imm转换有两种
            if(command == "ori" || command == "andi"  || command == "xori")
            {
                //imm做无符号扩展
                if( !UBin2Dec(immBin, imm, 16) )
                    return false;

                bool ok;
                uint dec = imm.toUInt(&ok, 10);
                QString hex;
                hex.setNum(dec, 16);

                disassembled_inst = QString("%1 %2, %3, 0x%4;")
                                    .arg(command).arg(rt).arg(rs).arg(hex);
                qDebug() << disassembled_inst;



            }
            else {
                //做符号扩展
                if( !Bin2Dec(immBin, imm, 16) )
                    return false;

                disassembled_inst = QString("%1 %2, %3, %4;")
                                    .arg(command).arg(rt).arg(rs).arg(imm);
                qDebug() << disassembled_inst;

            }


        }
        else if(type == "I-mem") {
            //lw rt imm(rs);
            //imm做有符号扩展(offset)

            if( !Bin2Dec(immBin, imm, 16))
                return false;

            disassembled_inst = QString("%1 %2, %3(%4);")
                                .arg(command).arg(rt).arg(imm).arg(rs);
            qDebug() << disassembled_inst;



        }
        else if(type == "I-lui") {
            //lui rt, imm
            //imm翻译成16进制更加直观

            if( !UBin2Dec(immBin, imm, 16) )
                return false;
            bool ok;
            uint dec = imm.toUInt(&ok, 10);
            QString hex;
            hex.setNum(dec, 16);
            disassembled_inst = QString("%1 %2, 0x%3;")
                                .arg(command).arg(rt).arg(hex);
            qDebug() << disassembled_inst;

        }
        else if(type == "I-branch") {
            //beq rs, rt, offset
            //PC + 4 + offset * 4 = address

            //offset是有符号立即数
            if( !Bin2Dec(immBin, imm, 16) )
                return false;

            bool ok;
            int offset = imm.toInt(&ok, 10);
            offset = offset * 4;
            int address = PC + 4 + offset;

            QString label;
            //先要判断这个位置有没有已经存在的label
            if( Labels.value(address) == 0) {
                //还不存在这样一个label
                label = QString("Label %1").arg(Labels.size() + 1);
                Labels[address] = label;

            }
            else {
                //已经存在
                label = Labels[address];

            }
            disassembled_inst = QString("%1 %2, %3, %4;")
                                .arg(command).arg(rs).arg(rt).arg(label);
            qDebug() << disassembled_inst;






        }
        else if(type == "I-branch-2") {
            //PC + 4 + offset * 4 = address

            //offset是有符号立即数
            if( !Bin2Dec(immBin, imm, 16) )
                return false;

            bool ok;
            int offset = imm.toInt(&ok, 10);
            offset = offset * 4;
            int address = PC + 4 + offset;

            QString label;
            //先要判断这个位置有没有已经存在的label
            if( Labels.value(address) == 0) {
                //还不存在这样一个label
                label = QString("Label %1").arg(Labels.size() + 1);
                Labels[address] = label;

            }
            else {
                //已经存在
                label = Labels[address];

            }

            if(command == "REGIMM") {
                //bgez  bgezal bltz bltzal
                //这四个前六位一样 000001_rs_hint_offset
                //不一样的点在于hint
                //bgez rs, offset
                QString real_command = Command[inst.mid(11, 5)];


                disassembled_inst = QString("%1 %2, %3;")
                                    .arg(real_command).arg(rs).arg(label);
                qDebug() << disassembled_inst;


            }
            else {

                //bgtz rs, offset
                //blez
                //
                disassembled_inst = QString("%1 %2, %3;")
                                    .arg(command).arg(rs).arg(label);
                qDebug() << disassembled_inst;

            }



        }

    }

    PC_increment();

    return true;



}

void disassemble_manager::firstProcess()
{
    QString rawLine;
    first_processed_lines.clear();
    Labels.clear();
    PC_clear();
    clearError();


    for(int i = 0; i < raw_lines.size(); i++)
    {
        QString first_process_line;//自动初始化
        rawLine = raw_lines.at(i);
        if( processAline(rawLine, first_process_line) ) {
            //如果这一行合法
            qDebug() << "合法指令：" << first_process_line;


            first_processed_lines << first_process_line;

        }
        if(isError == true)
        {
            return;
        }

    }


}

void disassemble_manager::finalProcess(QString &process_content)
{
    QString pre_line;
    final_processed_Lines.clear();
    //我需要在label对应的位置插入label即可
    //地址名到label的转换可以直接在first里面完成
    for(int i = 0; i < first_processed_lines.size(); i++)
    {
        pre_line = first_processed_lines.at(i);
        if( Labels.value(i * 4) == 0)
        {

            final_processed_Lines << pre_line;
        }
        else {
            //这个位置有label
            QString label = Labels[i * 4];
            QString final_line = QString("\n%1:\n%2").arg(label).arg(pre_line);
            final_processed_Lines << final_line;
        }


    }


    process_content = final_processed_Lines.join('\n');
}

bool disassemble_manager::coe2bin(QString content, QString & bin_content)
{
    QTextStream converter(&content);
    QString line = converter.readLine();
    QString radix = line.section('=', 1, 1);
    QStringList final_content;

    radix = radix.trimmed();
    radix.chop(1);

    bool ok;
    uint Radix = radix.toUInt(&ok, 10);
    if(ok == false)
    {
        QString error = QString("该coe文件的 radix: '%1' 不合法").arg(radix);
        setError(error);
        qDebug() << error;
        return false;
    }
    converter.readLine();

    while(!converter.atEnd())
    {
        line = converter.readLine();

        qDebug() << line;
        QStringList binList = line.split(',');
        for(int i = 0; i < binList.size(); i++)
        {
            bool ok;
            QString raw = binList.at(i);


            raw = raw.trimmed();
            if(raw.isEmpty())
                continue;
            if(raw.right(1) == ';')
                raw.chop(1);

            uint dec = raw.toUInt(&ok, Radix);
            if(ok == false)
            {
                QString error = QString("'%1' 不是一个%2进制数字或长度过长").arg(raw).arg(Radix);
                setError(error);
                qDebug() << error;
                return false;
            }

            QString bin;
            bin.setNum(dec, 2);
            if(bin.length() < 32)
            {
                bin = bin.rightJustified(32, '0');
            }
            final_content << bin;

        }
    }

    bin_content = final_content.join('\n');
    qDebug() << bin_content;







    return true;
}
/* 操作函数 */
void disassemble_manager::setError(QString &error)
{
    this->error = error;
    isError = true;
}

void disassemble_manager::PC_increment()
{
    PC += 4;
}

void disassemble_manager::PC_clear()
{
    PC = PC_init;
}

void disassemble_manager::clearError()
{
    this->error = "";
    isError = false;
}

bool disassemble_manager::Bin2Dec(const QString &Bin, QString &Dec, int length)
{
    //long
    bool ok;
    //int dec = Bin.toInt();
    if(length == 16) //有符号立即数
    {
        if(Bin[0] == '1') {
            //这是一个负数
            //先来一次手工转换
            QString abs_Bin;
            for(int i = 0; i < Bin.length(); i++)
            {
                if(Bin[i] == '1')
                    abs_Bin += '0';
                else
                    abs_Bin += '1';
            }
            long dec = abs_Bin.toLong(&ok, 2);

            if(ok == false)
            {
                QString error = QString("'%1' 转换失败").arg(Bin);
                setError(error);
                return false;
            }

            dec = -(dec + 1);
            Dec.setNum(dec);
            return true;
        }
        else {
            //这是一个正数
            int dec = Bin.toInt(&ok, 2);
            if(ok == false)
            {
                QString error = QString("'%1' 转换失败").arg(Bin);
                setError(error);
                return false;
            }

            Dec.setNum(dec);
            return true;

        }

    }


    return true;


}

bool disassemble_manager::UBin2Dec(const QString &Bin, QString &Dec, int length)
{
    //shamt imm target
    //因为无符号，我用int转化即可

    bool ok;
    int dec = Bin.toUInt(&ok, 2);

    if(ok == false) {
        QString error = QString("'%1' 无符号转换失败").arg(Bin);
        setError(error);
        return false;
    }
    else{
        Dec.setNum(dec);
        return true;
    }

    return true;


}
/* 判断函数 */
bool disassemble_manager::isBin(const QString &str)
{
    bool ok;
    str.toUInt(&ok, 2);

    if(ok == false)
    {
        //不是一个数字
        QString error = QString(" '%1' 不是一个有效数字").arg(str);
        setError(error);

        qDebug() << error;


    }


    return ok;

}

bool disassemble_manager::isType(const QString &opcode)
{
    if( Type.value(opcode) == 0 ){
        QString error = QString("尚未支持 '%1' 作为 Opcode 的指令 ").arg(opcode);
        setError(error);
        qDebug() << error;

        return false;
    }
    else
        return true;
}

bool disassemble_manager::isInst(const QString &inst)
{
    if( inst.length() != 32 ) {
        QString error = QString("指令 '%1' 长度不合法").arg(inst);
        setError(error);
        qDebug() << error;
        return false;

    }

    bool ok;
    inst.toUInt(&ok, 2);
    if(ok == false) {
        QString error = QString("指令 '%1' 含有非法字符").arg(inst);
        setError(error);
        qDebug() << error;
        return false;
    }
    return true;
}

bool disassemble_manager::isFun(const QString &Func)
{
    if( Fun.value(Func) == 0 )
    {
        //指令尚不支持
        QString error = QString("不支持 fun: '%1' 的指令").arg(Func);
        setError(error);
        qDebug() << error;

        return false;
    }
    return true;
}

bool disassemble_manager::isCommand(const QString &command)
{
    if(Command.value(command) == 0)
    {
        //指令不存在
        QString error = QString("不支持 opcode: '%1' 的指令").arg(command);
        setError(error);
        qDebug() << error;
        return false;
    }
    return true;
}
