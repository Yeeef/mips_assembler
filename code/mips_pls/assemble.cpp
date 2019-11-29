#include "assemble.h"

assemble_manager::assemble_manager()
{
    setRegs();
    setType();
    setOpcode();
    setFun();
    LastPC = 0;
    PC_init = 0;
    PC = PC_init;
    isData = false;



}

void assemble_manager::setType()
{
    //R-format
    Type["add"] = "R";
    Type["sub"] = "R";
    Type["and"] = "R";
    Type["or"]  = "R";
    Type["slt"] = "R";
    Type["srl"] = "R-shift";
    Type["jr"]  = "R-jump";
    Type["jalr"] = "R-jump-2";
    Type["addu"] = "R";
    Type["subu"] = "R";
    Type["xor"] = "R";
    Type["nor"] = "R";
    Type["sll"] = "R-shift";
    Type["sra"] = "R-shift";
    Type["sllv"] = "R-shift-2";
    Type["srlv"] = "R-shift-2";
    Type["srav"] = "R-shift-2";
    Type["sltu"] = "R";
    Type["syscall"] = "R-sys";
    Type["break"] = "R-sys";
    Type["mult"] = "R-mult";
    Type["multu"] = "R-mult";
    Type["div"] = "R-mult";
    Type["divu"] = "R-mult";
    Type["mfhi"] = "R-transfer";
    Type["mflo"] = "R-transfer";
    Type["mthi"] = "R-jump";
    Type["mtlo"] = "R-jump";



    //I-format
    Type["lw"] = "I-mem";
    Type["sw"] = "I-mem";
    Type["beq"] = "I-branch";
    Type["bne"] = "I-branch";
    Type["addi"] = "I";
    Type["addiu"] = "I";
    Type["ori"] = "I";
    Type["andi"] = "I";
    Type["xori"] = "I";
    Type["lui"] = "I-lui";
    Type["slti"] = "I";
    Type["sltiu"] = "I";
    Type["lb"] = "I-mem";
    Type["lbu"] = "I-mem";
    Type["lh"] = "I-mem";
    Type["lhu"] = "I-mem";
    Type["sh"] = "I-mem";
    Type["sb"] = "I-mem";
    Type["bgez"] = "I-branch-2";
    Type["bgezal"] = "I-branch-2";
    Type["bgtz"] = "I-branch-2";
    Type["blez"] = "I-branch-2";
    Type["bltz"] = "I-branch-2";
    Type["bltzal"] = "I-branch-2";

    //J-format
    Type["j"] = "J";
    Type["jal"] = "J";

    //other
    Type["eret"] = "eret";
    Type["mfc0"] = "COP0";
    Type["mtc0"] = "COP0";

    //伪指令
    Type["la"] = "pseudo";
    Type["move"] = "pseudo";
    Type["li"] = "pseudo";
    Type["BaseAddre"] = "pseudo";
    Type["DataAddre"] = "pseudo";

    //数据定义
    Type["dd"] = "data";
    Type["DD"] = "data";
    Type["db"] = "data";
    Type["DB"] = "data";
    Type["dw"] = "data";
    Type["DW"] = "data";



}

void assemble_manager::setOpcode()
{
    //R-format
    QString R_Opcode("000000");
    Opcode["add"] = R_Opcode;
    Opcode["sub"] = R_Opcode;
    Opcode["and"] = R_Opcode;
    Opcode["or"]  = R_Opcode;
    Opcode["slt"] = R_Opcode;
    Opcode["srl"] = R_Opcode;
    Opcode["jr"] =  R_Opcode;
    Opcode["jalr"] = R_Opcode;
    Opcode["addu"] = R_Opcode;
    Opcode["subu"] = R_Opcode;
    Opcode["xor"]  = R_Opcode;
    Opcode["nor"]  = R_Opcode;
    Opcode["sll"]  = R_Opcode;
    Opcode["sra"]  = R_Opcode;
    Opcode["sllv"] = R_Opcode;
    Opcode["srlv"] = R_Opcode;
    Opcode["srav"] = R_Opcode;
    Opcode["sltu"] = R_Opcode;
    Opcode["syscall"] = R_Opcode;
    Opcode["mult"]  = R_Opcode;
    Opcode["multu"] = R_Opcode;
    Opcode["div"]   = R_Opcode;
    Opcode["divu"]  = R_Opcode;
    Opcode["mfhi"] = R_Opcode;
    Opcode["mflo"] = R_Opcode;
    Opcode["mthi"] = R_Opcode;
    Opcode["mtlo"] = R_Opcode;
    Opcode["break"] = R_Opcode;


    //I-format
    Opcode["lw"] = "100011"; //23H
    Opcode["sw"] = "101011"; //2BH
    Opcode["beq"] = "000100"; //4H
    Opcode["bne"] = "000101"; //5H
    Opcode["addi"] = "001000"; //8H
    Opcode["addiu"] = "001001"; //9H
    Opcode["ori"] = "001101"; //DH
    Opcode["andi"] = "001100"; //CH
    Opcode["xori"] = "001110"; //EH
    Opcode["lui"] = "001111";
    Opcode["slti"] = "001010";
    Opcode["sltiu"] = "001011";
    Opcode["lb"] = "100000";
    Opcode["lbu"] = "100100";
    Opcode["lh"] = "100001";
    Opcode["lhu"] = "100101";
    Opcode["sh"] = "101001";
    Opcode["sb"] = "101000";
    Opcode["bgez"] = "000001-00001";
    Opcode["bgezal"] = "000001-10001";
    Opcode["bgtz"] = "000111-00000";
    Opcode["blez"] = "000110-00000";
    Opcode["bltz"] = "000001-00000";
    Opcode["bltzal"] = "000001-10000";

    //J-format
    Opcode["j"] = "000010"; //2H
    Opcode["jal"] = "000011"; //3H




}

void assemble_manager::setFun()
{
    //R-format
    Fun["add"]  = "100000";
    Fun["sub"]  = "100010";
    Fun["and"]  = "100100";
    Fun["or" ]  = "100101";
    Fun["slt"]  = "101010";
    Fun["srl"]  = "000010";
    Fun["jr" ]  = "001000";
    Fun["jalr"] = "001001";
    Fun["addu"] = "100001";
    Fun["subu"] = "100011"; //23H
    Fun["xor"]  = "100110"; //26H
    Fun["nor"]  = "100111"; //27H
    Fun["sll"]  = "000000"; //0H
    Fun["sra"]  = "000011"; //3H
    Fun["sllv"] = "000100";
    Fun["srlv"] = "000110";
    Fun["srav"] = "000111";
    Fun["sltu"] = "101011";
    Fun["syscall"] = "001100";
    Fun["break"] = "001101";
    Fun["mult"] = "011000";
    Fun["multu"] = "011001";
    Fun["div"] = "011010";
    Fun["divu"] = "011011";
    Fun["mfhi"] = "010000";
    Fun["mflo"] = "010010";
    Fun["mthi"] = "010001";
    Fun["mtlo"] = "010011";

    //两个特殊形式
    Fun["mfc0"] = "00000"; //MF
    Fun["mtc0"] = "00100"; //MT







}

void assemble_manager::setRegs()
{

    Reg2Num["$R0"] =  "00000"; Reg2Num["$r0"] =  "00000"; Reg2Num["$zero"] =  "00000";
    Reg2Num["$R1"] =  "00001"; Reg2Num["$r1"] =  "00001"; Reg2Num["$at"] =  "00001";

    Reg2Num["$R2"] =  "00010"; Reg2Num["$r2"] =  "00010"; Reg2Num["$v0"] =  "00010";
    Reg2Num["$R3"] =  "00011"; Reg2Num["$r3"] =  "00011"; Reg2Num["$v1"] =  "00011";

    Reg2Num["$R4"] =  "00100"; Reg2Num["$r4"] =  "00100"; Reg2Num["$a0"] =  "00100";
    Reg2Num["$R5"] =  "00101"; Reg2Num["$r5"] =  "00101"; Reg2Num["$a1"] =  "00101";
    Reg2Num["$R6"] =  "00110"; Reg2Num["$r6"] =  "00110"; Reg2Num["$a2"] =  "00110";
    Reg2Num["$R7"] =  "00111"; Reg2Num["$r7"] =  "00111"; Reg2Num["$a3"] =  "00111";

    Reg2Num["$R8"] =  "01000"; Reg2Num["$r8"] =  "01000"; Reg2Num["$t0"] =  "01000";
    Reg2Num["$R9"] =  "01001"; Reg2Num["$r9"] =  "01001"; Reg2Num["$t1"] =  "01001";
    Reg2Num["$R10"] = "01010"; Reg2Num["$r10"] = "01010"; Reg2Num["$t2"] =  "01010";
    Reg2Num["$R11"] = "01011"; Reg2Num["$r11"] = "01011"; Reg2Num["$t3"] =  "01011";
    Reg2Num["$R12"] = "01100"; Reg2Num["$R12"] = "01100"; Reg2Num["$t4"] =  "01100";
    Reg2Num["$R13"] = "01101"; Reg2Num["$r13"] = "01101"; Reg2Num["$t5"] =  "01101";
    Reg2Num["$R14"] = "01110"; Reg2Num["$r14"] = "01110"; Reg2Num["$t6"] =  "01110";
    Reg2Num["$R15"] = "01111"; Reg2Num["$r15"] = "01111"; Reg2Num["$t7"] =  "01111";

    Reg2Num["$R16"] = "10000"; Reg2Num["$r16"] = "10000"; Reg2Num["$s0"] = "10000";
    Reg2Num["$R17"] = "10001"; Reg2Num["$r17"] = "10001"; Reg2Num["$s1"] = "10001";
    Reg2Num["$R18"] = "10010"; Reg2Num["$r18"] = "10010"; Reg2Num["$s2"] = "10010";
    Reg2Num["$R19"] = "10011"; Reg2Num["$r19"] = "10011"; Reg2Num["$s3"] = "10011";
    Reg2Num["$R20"] = "10100"; Reg2Num["$r20"] = "10100"; Reg2Num["$s4"] = "10100";
    Reg2Num["$R21"] = "10101"; Reg2Num["$r21"] = "10101"; Reg2Num["$s5"] = "10101";
    Reg2Num["$R22"] = "10110"; Reg2Num["$r22"] = "10110"; Reg2Num["$s6"] = "10110";
    Reg2Num["$R23"] = "10111"; Reg2Num["$r23"] = "10111"; Reg2Num["$s7"] = "10111";

    Reg2Num["$R24"] = "11000"; Reg2Num["$r24"] = "11000"; Reg2Num["$t8"] = "11000";
    Reg2Num["$R25"] = "11001"; Reg2Num["$r25"] = "11001"; Reg2Num["$t9"] = "11001";

    Reg2Num["$R26"] = "11010"; Reg2Num["$r26"] = "11010"; Reg2Num["$k0"] = "11010";
    Reg2Num["$R27"] = "11011"; Reg2Num["$r27"] = "11011"; Reg2Num["$k1"] = "11011";

    Reg2Num["$R28"] = "11100"; Reg2Num["$r28"] = "11100"; Reg2Num["$gp"] = "11100";
    Reg2Num["$R29"] = "11101"; Reg2Num["$r29"] = "11101"; Reg2Num["$sp"] = "11101";
    Reg2Num["$R30"] = "11110"; Reg2Num["$r30"] = "11110"; Reg2Num["$fp"] = "11110";

    Reg2Num["$R31"] = "11111"; Reg2Num["$r31"] = "11111"; Reg2Num["$ra"] = "11111";



}

void assemble_manager::convert2lines(QString content)
{
    //建立一个读取流 reader
    QTextStream reader(&content, QIODevice::ReadOnly);
    //把原有数据清空
    lines.clear();


    while(!reader.atEnd())
    {
        //readline自动过滤空格
        lines << reader.readLine();
    }

    //检验是否正常读入
    /*
    for(int i = 0; i < lines.size(); i++)
    {
        qDebug() << lines[i] << "\n";
    }
    */



}

int assemble_manager::processAline(QString line, QString & assembled_line)
{
    int i = 0;
    line = line.trimmed();

    //注释判断
    if(line[0] == "#" || (line[0] == "/" && line[1] == "/")) {
        //什么都不读,直接返回
        return 0;

    }

    //空行判断
    if(line.size() == 0) {
        //不做任何处理
        return 0;
    }

    QString newLabel;
    bool isLabel = false;
    //lable判断
    int j;
    for(j = 0; j < line.size(); j++)
    {
        if(line[j] == ":") {
            isLabel = true;
            break;
        }

        else
            newLabel += line[j];

    }

    if( isLabel ) {
        //这是一个label
        //把空格截去
        newLabel = newLabel.trimmed();
        qDebug() << newLabel << "的位置：" << PC;
        if(isData == true)
        {
            if( dataLabels.value(newLabel) == 0)
                dataLabels[newLabel] = PC;
            else {
                QString error = QString("重复的label名：'%1'").arg(newLabel);
                setError(error);
                return false;
            }
        }

        else {
            //判断label名是否存在
            if( Labels.value(newLabel) == 0)
               Labels [newLabel] = PC;//直接转化为字节地址
            else {
                QString error = QString("重复的label名：'%1'").arg(newLabel);
                setError(error);
                return false;
            }

        }


        i = j + 1; //i从下一个位置开始查找

        //过滤空格
        while(line[i] == " ")
            i++;


    }





    //如果不是注释
    QString command;//类似于 "add" 这样的指令
    QString type;
    QString rs, rt, rd; //先考虑最简单的r格式
    QString shamt, shamtBin;
    QString imm, immBin;
    QString target, targetBin;
    QString label;


    //读取command
    for(; i < line.size(); i++)
    {
        if(line[i] != ' ' && line[i] != ";")
        {
            command += line[i];
        }
        else
            break;

    }
    i++;


    //现在读好了command
    //注意这里要用value,否则会隐性的创造一个
    if(Type.value(command) != 0) {

        type = Type.value(command);

        if(type != "data" && command != "DataAddre") {
            if( !canInst() )
                return false;
        }
        //开始判断类别，从而采用不同的处理方法
        if(type == "R") {

            //定义 shamt
            shamt = "00000";

            //读取 rd, rs, rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rd += line[i];
                else
                    break;
            }
            rd = rd.trimmed(); //把用户非法输入的 空格去掉
            i++; //把这个 , 过去

            //判断rd是否合法
            if( !isReg(rd) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rd);
                setError(error);
                qDebug() << error;

                return 0;
            }

            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed();
            i++; //把这个 , 过去

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;

                return 0;


            }

            for(; i < line.size(); i++)
            {
                if(line[i] != ';')
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed();

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;

                return 0;


            }
            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rd << rs << rt;


            //instruction, rs, rt, rd已经完成
            //开始拼接， opcode rd rs rt shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamt + Fun[command];
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamt << "_" << Fun[command];
            PC += 4;
            return 1;



        }
        else if(type == "R-shift") {
            isData = false;
            //srl $rd, $rt, sa

            //抓取 rd
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rd += line[i];
                else
                    break;
            }
            rd = rd.trimmed(); //把用户非法输入的 空格去掉
            i++; //过滤“，”

            //判断rd是否合法
            if( !isReg(rd) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rd);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rd << "不存在";
                return 0;
            }

            //抓取 rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed(); //把用户非法输入的 空格去掉
            i++; //过滤“，”

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }

            //抓取 shamt
            for(; i < line.size(); i++)
            {
                if(line[i] != ";") {
                    shamt += line[i];
                }
                else
                    break;
            }
            shamt = shamt.trimmed();

            //需要把shamt转成一个二进制数字, 并且做好字符串长度控制！
            bool ok = shamt2Bin(shamt, shamtBin);
            if( ok == false) {
                QString error = QString(" '%1' 不是一个有效数字").arg(shamt);
                setError(error);
                qDebug() << error;
                //qDebug() << shamt << "不是一个有效数字";

                return 0;
            }


            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command;
            qDebug() << rd << "__" << rt << "__" << shamt;

            //instruction, rd, rt已经完成
            //开始拼接， opcode rd rs rt shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += Opcode[command] + "00000" + Reg2Num[rt] + Reg2Num[rd] + shamtBin + Fun[command];
            qDebug() << Opcode[command] << "_" << "00000" << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamtBin << "_" << Fun[command];
            PC += 4;
            return 1;







        }
        else if(type == "R-shift-2") {
            isData = false;
            //sllv rd, rt, rs;

            //读取 rd
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rd += line[i];
                else
                    break;
            }
            rd = rd.trimmed(); //把用户非法输入的 空格去掉
            i++; //把这个 , 过去

            //判断rd是否合法
            if( !isReg(rd) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rd);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rd << "不存在";
                return 0;
            }

            //读取 rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed(); //把用户非法输入的 空格去掉
            i++; //把这个 , 过去

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }

            //读取 rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ';')
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed(); //把用户非法输入的 空格去掉
            i++; //把这个 , 过去

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rs << "不存在";
                return 0;
            }

            qDebug() << "指令为：" << command << rd << rt << rs;


            //instruction, rs, rt, rd已经完成
            //开始拼接， opcode rs rt rd shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            shamt = "00000";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamt + Fun[command];
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamt << "_" << Fun[command];

            PC += 4;
            return 1;



        }
        else if(type == "R-jump") {
            isData = false;

            //jr rs;
            //mthi rs;


            //抓取 rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ";") {
                    rs += line[i];
                }
                else
                    break;
            }
            rs = rs.trimmed();

            if( !isReg(rs) ) {
                qDebug() << "寄存器：" << rs << "不存在";
                return 0;
            }

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rs;


            //instruction, rs已经完成
            //开始拼接， opcode rd rs rt shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            shamtBin = "00000";
            rd = "$zero";
            rt = "$zero";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamtBin + Fun[command];
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamtBin << "_" << Fun[command];
            PC += 4;
            return 1;






        }
        else if(type == "R-jump-2") {
            isData = false;
            //jalr rs;
            //jalr rd, rs;


            QString reg;
            //抓取一个寄存器
            for(; i < line.size(); i++)
            {
                if(line[i] != ";" && line[i] != ",") {
                    reg += line[i];
                }
                else
                    break;
            }
            reg = reg.trimmed();


            if( !isReg(reg) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(reg);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << reg << "不存在";
                return 0;
            }

            if(line[i] == ";") {
                //jalr rs; (rd = ra)
                rs = reg;

                qDebug() << "格式为：" << type;
                qDebug() << "指令为：" << command << rs;


                //instruction, rs已经完成
                //开始拼接， opcode rd rs rt shamt fun
                //我在这里假定了，拥有类型的一定被我定义了opcode
                shamtBin = "00000";
                rd = "$ra";
                rt = "$zero";
                assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamtBin + Fun[command];
                qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                         << shamtBin << "_" << Fun[command];
                PC += 4;
                return 1;

            }
            else {
                i++;
                // jalr rd, rs;
                rd = reg;

                //抓取rs
                for(; i < line.size(); i++)
                {
                    if(line[i] != ";") {
                        rs += line[i];
                    }
                    else
                        break;
                }
                rs = rs.trimmed();
                i++;

                if( !isReg(rs) ) {
                    QString error = QString("寄存器：'%1' 不存在").arg(rs);
                    setError(error);
                    qDebug() << error;
                    qDebug() << "寄存器：" << rs << "不存在";
                    return 0;
                }

                qDebug() << "格式为：" << type;
                qDebug() << "指令为：" << command << rd << rs;


                //instruction, rs已经完成
                //开始拼接， opcode rd rs rt shamt fun
                //我在这里假定了，拥有类型的一定被我定义了opcode
                shamtBin = "00000";
                rt = "$zero";
                assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamtBin + Fun[command];
                qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                         << shamtBin << "_" << Fun[command];
                PC += 4;
                return 1;

            }
        }
        else if(type == "R-sys") {

            //syscall;
            //break;
            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command;


            //instruction, rs已经完成
            //开始拼接， opcode rd rs rt shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            shamtBin = "00000";
            rd = "$zero";
            rs = "$zero";
            rt = "$zero";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamtBin + Fun[command];
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamtBin << "_" << Fun[command];
            PC += 4;


            return 1;
        }
        else if(type == "R-mult") {
            //mult rs, rt;
            //抓取rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed();
            i++; //把这个 , 过去

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rs << "不存在";
                return 0;


            }

            for(; i < line.size(); i++)
            {
                if(line[i] != ';')
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed();

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                qDebug() << "寄存器：" << rt << "不存在";
                return 0;


            }

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rs << rt;

            //instruction, rs, rt, rd已经完成
            //开始拼接， opcode rd rs rt shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            rd = "$zero";
            shamt = "00000";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamt + Fun[command];
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamt << "_" << Fun[command];
            PC += 4;


            return 1;
        }
        else if(type == "R-transfer") {
            //mfhi rd;

            //抓取rd
            for(; i < line.size(); i++)
            {
                if(line[i] != ';')
                    rd += line[i];
                else
                    break;
            }
            rd = rd.trimmed();

            //判断rd是否合法
            if( !isReg(rd) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rd);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rd << "不存在";
                return 0;


            }

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rd;

            //instruction, rs, rt, rd已经完成
            //开始拼接， opcode rd rs rt shamt fun
            //我在这里假定了，拥有类型的一定被我定义了opcode
            rs = "$zero";
            rt = "$zero";
            shamt = "00000";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamt + Fun[command];
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << Reg2Num[rd] << "_"
                     << shamt << "_" << Fun[command];
            PC += 4;

            return 1;

        }
        else if(type == "I") {

            //I-format 普通的
            //addi $rt, $rs, imm;


            //抓取 rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed(); //把用户非法输入的 空格去掉
            i++; //过滤“，”

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }

            //抓取 rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed(); //把用户非法输入的 空格去掉
            i++; //过滤“，”

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rs << "不存在";
                return 0;
            }


            //抓取imm
            for(; i < line.size(); i++)
            {
                if(line[i] != ";") {
                    imm += line[i];
                }
                else
                    break;
            }
            imm = imm.trimmed();

            bool ok;
            //需要把imm转成一个二进制数字, 并且做好字符串长度控制！
            if(command == "ori" || command == "andi" || command == "nori" || command == "xori")
                ok = imm2Bin(imm, immBin, 16);
            else
                ok = signed_imm2Bin(imm, immBin, 16);

            if( ok == false) {
                QString error = QString(" '%1' 不是一个有效数字").arg(imm);
                setError(error);
                qDebug() << error;
                //qDebug() << imm << "不是一个有效数字";

                return 0;
            }

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rt << rs << imm;


            //instruction, rs, rt已经完成
            //开始拼接， opcode rs rt imm
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + immBin;
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << immBin;
            PC += 4;


            return 1;



        }
        else if(type == "I-mem") {

            //lw $rt, imm($rs);

            //抓取rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ",")
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed();
            i++;

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }


            //抓取imm
            for(; i < line.size(); i++)
            {
                if(line[i] != "(")
                    imm += line[i];
                else
                    break;
            }
            imm = imm.trimmed();
            i++;

            //需要把imm转成一个二进制数字, 并且做好字符串长度控制！
            //这里的imm已经以字节为单位了，不需要我额外转化；
            bool ok = imm2Bin(imm, immBin, 16);
            if( ok == false) {
                QString error = QString(" '%1' 不是一个有效的数字").arg(imm);
                setError(error);
                qDebug() << error;
                //qDebug() << imm << "不是一个有效数字";

                return 0;
            }


            //抓取rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ")")
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed();

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rs << "不存在";
                return 0;
            }

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rt << "(" << imm << ")" << rs;


            //instruction, rs, rt已经完成
            //开始拼接， opcode rs rt imm
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + immBin;
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << immBin;
            PC += 4;


            return 1;






        }
        else if(type == "I-branch") {

            //beq $rs, $rt, label;
            //抓取rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ",")
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed();
            i++;

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rs << "不存在";
                return 0;
            }

            //抓取rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ",")
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed();
            i++;

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }

            for(; i < line.size(); i++)
            {
                if(line[i] != ";")
                    label += line[i];
                else
                    break;
            }
            label = label.trimmed();

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rs << rt << label;



            //开始拼接， opcode rs rt target(暂时的）
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += "!";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt];
            assembled_line += "*";
            assembled_line += label;

            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << label;
            PC += 4;


            return 1;



        }
        else if(type == "I-branch-2") {

            //bgez rs, label;
            //抓取rs
            //抓取rs
            for(; i < line.size(); i++)
            {
                if(line[i] != ",")
                    rs += line[i];
                else
                    break;
            }
            rs = rs.trimmed();
            i++;

            //判断rs是否合法
            if( !isReg(rs) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rs);
                setError(error);
                qDebug() << error;
               // qDebug() << "寄存器：" << rs << "不存在";
                return 0;
            }

            //抓取label
            for(; i < line.size(); i++)
            {
                if(line[i] != ";")
                    label += line[i];
                else
                    break;
            }
            label = label.trimmed();

            QString rt_num = Opcode[command].right(5);

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rs << label;



            //开始拼接， opcode rs rt target(暂时的）
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += "!";
            assembled_line += Opcode[command].left(6) + Reg2Num[rs] + rt_num;
            assembled_line += "*";
            assembled_line += label;

            qDebug() << Opcode[command].right(6) << "_" << Reg2Num[rs] << "_" << rt_num << "_" << label;
            PC += 4;


            return 1;





        }
        else if(type == "I-lui") {
            // lui rt, imm;


            //抓取rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ",")
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed();
            i++;

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }


            //抓取imm
            for(; i < line.size(); i++)
            {
                if(line[i] != ";")
                    imm += line[i];
                else
                    break;
            }
            imm = imm.trimmed();
            i++;

            //需要把imm转成一个二进制数字, 并且做好字符串长度控制！
            //这里的imm已经以字节为单位了，不需要我额外转化；
            bool ok = imm2Bin(imm, immBin, 16);
            if( ok == false) {
                QString error = QString(" '%1' 不是一个有效数字").arg(imm);
                setError(error);
                qDebug() << error;
                //qDebug() << imm << "不是一个有效数字";

                return 0;
            }

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << rt << imm;


            //instruction, rs, rt已经完成
            //开始拼接， opcode rs rt imm
            //我在这里假定了，拥有类型的一定被我定义了opcode
            rs = "$zero";
            assembled_line += Opcode[command] + Reg2Num[rs] + Reg2Num[rt] + immBin;
            qDebug() << Opcode[command] << "_" << Reg2Num[rs] << "_" << Reg2Num[rt] << "_" << immBin;
            PC += 4;


            return 1;


        }
        else if(type == "J") {

            //j label;
            //jal label；

            //抓取 label
            for(; i < line.size(); i++)
            {
                if(line[i] != ";")
                    label += line[i];
                else
                    break;

            }
            label = label.trimmed();


            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command << label;


            //开始拼接， opcode target
            //我在这里假定了，拥有类型的一定被我定义了opcode
            assembled_line += "!"; //标识符，表示需要再次处理
            assembled_line += Opcode[command];
            assembled_line += "!"; //表示label开始的地方
            assembled_line += label;
            qDebug() << Opcode[command] << "_" << label;
            PC += 4;


            return 1;



        }
        else if(type == "eret") {
            //eret;
            QString COP0 = "010000";
            QString CO = "1";
            QString Blank = "0000000000000000000";
            QString ERET = "011000";

            qDebug() << "格式为：" << type;
            qDebug() << "指令为：" << command;


            assembled_line = COP0 + CO + Blank + ERET;

            qDebug() << COP0 << CO << Blank << ERET;
            PC += 4;


            return 1;


        }
        else if(type == "COP0") {
            //mfc0 rt, rd;
            //mfc0 rt, rd, sel;


            //抓取rt
            for(; i < line.size(); i++)
            {
                if(line[i] != ',')
                    rt += line[i];
                else
                    break;
            }
            rt = rt.trimmed(); //把用户非法输入的 空格去掉
            i++; //把这个 , 过去

            //判断rt是否合法
            if( !isReg(rt) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rt);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }


            //抓取rd
            for(; i < line.size(); i++)
            {
                if(line[i] != ';' && line[i] != ",")
                    rd += line[i];
                else
                    break;
            }
            rd = rd.trimmed(); //把用户非法输入的 空格去掉

            //判断rd是否合法
            if( !isReg(rd) ) {
                QString error = QString("寄存器：'%1' 不存在").arg(rd);
                setError(error);
                qDebug() << error;
                //qDebug() << "寄存器：" << rt << "不存在";
                return 0;
            }


            QString COP0("010000");

            QString BLANK("00000000");
            QString sel;

            if(line[i] == ";") {
                sel = "000";

                qDebug() << "指令为：" << command << rt << rd;
                assembled_line = COP0 + Fun[command] + Reg2Num[rt] + Reg2Num[rd] + BLANK + sel;
                qDebug() << COP0 << Fun[command] << Reg2Num[rt] << Reg2Num[rd] << BLANK << sel;
                PC += 4;
                return 1;

            }
            else {

                //还要抓取sel
                i++;
                for(;i < line.size(); i++)
                {
                    if(line[i] != ";")
                        sel += line[i];
                    else
                        break;

                }
                sel = sel.trimmed();

                QString selBin;
                //需要把sel转成一个二进制数字, 并且做好字符串长度控制！
                bool ok = sel2Bin(sel, selBin);
                if( ok == false) {
                    QString error = QString(" '%1' 不是一个有效数字").arg(sel);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << sel << "不是一个有效数字";

                    return 0;
                }

                qDebug() << "指令为" << command << rt << rd << selBin;
                assembled_line = COP0 + Fun[command] + Reg2Num[rt] + Reg2Num[rd] + BLANK + selBin;
                qDebug() << COP0 << Fun[command] << Reg2Num[rt] << Reg2Num[rd] << BLANK << selBin;
                PC += 4;
                return 1;





            }

        }
        else if(type == "pseudo") {

            //问题在于这样的话，我的label可能要变了，也很简单，把PC单独拉出来处理

            if(command == "move") {
                //move rdest, rsrc; -> add rdest, rsrc, $zero
                //抓取rdest(rd)
                for(; i < line.size(); i++)
                {
                    if(line[i] != ',')
                        rd += line[i];
                    else
                        break;
                }
                rd = rd.trimmed(); //把用户非法输入的 空格去掉
                i++; //把这个 , 过去

                //判断rd是否合法
                if( !isReg(rd) ) {
                    QString error = QString("寄存器：'%1' 不存在").arg(rd);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << "寄存器：" << rd << "不存在";
                    return 0;
                }

                //抓取 rsrc(rs)
                for(; i < line.size(); i++)
                {
                    if(line[i] != ';')
                        rs += line[i];
                    else
                        break;
                }
                rs = rs.trimmed(); //把用户非法输入的 空格去掉
                i++; //把这个 , 过去

                //判断rs是否合法
                if( !isReg(rs) ) {
                    QString error = QString("寄存器：'%1' 不存在").arg(rs);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << "寄存器：" << rs << "不存在";
                    return 0;
                }

                QString real_command("add");

                rt = "$zero";
                shamtBin = "00000";
                qDebug() << "指令为：" << command << rd << rs;
                qDebug() << "真实指令为：" << real_command << rd << rs << rt;

                assembled_line = Opcode[real_command] + Reg2Num[rs] + Reg2Num[rt] + Reg2Num[rd] + shamtBin + Fun[real_command];
                qDebug() << Opcode[real_command] << Reg2Num[rs] <<  Reg2Num[rt]  << Reg2Num[rd] << shamtBin << Fun[real_command];

                PC += 4;
                return 1;





            }
            else if(command == "li" || command == "la") {

                //la rdest, address -> lui $at, upper; ori $t0, $at, lower;
                //li rdest, imm -> lui $at, upper; ori $t0, $at, lower;

                //抓取rdest(rt)
                for(; i < line.size(); i++)
                {
                    if(line[i] != ',')
                        rt += line[i];
                    else
                        break;
                }
                rt = rt.trimmed(); //把用户非法输入的 空格去掉
                i++; //把这个 , 过去

                //判断rt是否合法
                if( !isReg(rt) ) {
                    QString error = QString("寄存器：'%1' 不存在").arg(rt);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << "寄存器：" << rt << "不存在";
                    return 0;
                }

                //抓取imm
                for(; i < line.size(); i++)
                {
                    if(line[i] != ";")
                        imm += line[i];
                    else
                        break;
                }
                imm = imm.trimmed();

                //需要把imm转成一个二进制数字, 并且做好字符串长度控制！(32位！）
                bool ok = imm2Bin(imm, immBin, 32);
                if( ok == false) {
                    QString error = QString(" '%1' 不是一个有效数字").arg(imm);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << imm << "不是一个有效数字";

                    return 0;
                }

                //la rdest, address -> lui $at, upper; ori $t0, lower;
                //li rdest, imm -> lui $at, upper; ori $t0, $at, lower;
                QString real_command1("lui");
                QString real_command2("ori");

                assembled_line = Opcode[real_command1] + Reg2Num["$zero"] + Reg2Num["$at"] + immBin.left(16); //高16位
                assembled_line += "\n";

                assembled_line += Opcode[real_command2] + Reg2Num["$at"] + Reg2Num[rt] + immBin.right(16); //低16位
                PC += 8;
                qDebug() << "伪指令为: " << command << rt << imm;
                qDebug() << "第一条：" << real_command1 << Reg2Num["$zero"] << Reg2Num["$at"] << immBin.left(16);
                qDebug() << "第二条：" << real_command2 << Reg2Num["$at"] << Reg2Num[rt] << immBin.right(16);

                return 1;




            }
            else if(command == "BaseAddre") {
                //抓取后面的pc指定地址
                QString baseaddre;
                for(; i < line.size(); i++) {
                    if(line[i] != ';')
                        baseaddre += line[i];
                    else
                        break;

                }
                bool ok;
                uint Baseaddre = baseaddre.toUInt(&ok, 16);
                if(ok == false)
                {
                    QString error = QString("'%1'不是一个有效的16进制数字").arg(baseaddre);
                    setError(error);


                    return false;
                }
                if(Baseaddre < PC) {
                    QString error = QString("'0x%1'必须大于当前PC地址！").arg(baseaddre);
                    setError(error);
                    return false;
                }
                assembled_line = "BaseAddre";
                qDebug() << Baseaddre;
                if(Baseaddre % 4 != 0)
                {
                    Baseaddre += 4 - Baseaddre%4;
                }

                LastPC = PC;
                PC = Baseaddre;



            }
            else if(command == "DataAddre") {
                //抓取后面的pc指定地址
                QString dataaddre;
                for(; i < line.size(); i++) {
                    if(line[i] != ';')
                        dataaddre += line[i];
                    else
                        break;

                }
                bool ok;
                uint Dataaddre = dataaddre.toUInt(&ok, 16);


                if(ok == false)
                {
                    QString error = QString("'%1'不是一个有效的16进制数字").arg(dataaddre);
                    setError(error);


                    return false;
                }

                if(Dataaddre < PC) {
                    QString error = QString("'0x%1'必须大于当前PC地址！").arg(dataaddre);
                    setError(error);
                    return false;
                }
                isData = true;
                assembled_line = "DataAddre";
                if(Dataaddre % 4 != 0)
                {
                    Dataaddre += 4 - Dataaddre%4;
                }

                LastPC = PC;
                qDebug() << "LastPC:" << LastPC;


                PC = Dataaddre;
                qDebug() << "PC:" << PC;


            }
        }
        else if(type == "data") {
            if(isData == false) {
                QString error = QString("在代码片段里插入了数据定义！");
                setError(error);
                return false;
            }
            //
            if(command == "dd" || command == "DD") {
                qDebug() << "dd命令";
                QStringList assembled_list;

                QString Hex;
                for(; i < line.size(); i++)
                {

                    if(line[i] != ',' && line[i] != ';')
                        Hex += line[i];

                    if(line[i] == ',' || line[i] == ';') {
                        //一个hex读取完毕
                        Hex = Hex.trimmed();
                        qDebug() << Hex;
                        bool ok;
                        uint dec = Hex.toUInt(&ok, 16);
                        if( ok == false) {

                            QString error = QString("'%1'不是一个有效的16进制数字").arg(Hex);
                            setError(error);
                            return false;
                        }

                        addr_data[PC] = dec;
                        QString Bin;
                        Bin.setNum(dec, 2);
                        Bin = Bin.rightJustified(32, '0');
                        assembled_list << Bin;

                        Hex = "";
                        PC += 4;

                        if(line[i] == ';')
                            break;


                    }

                }
                assembled_line = assembled_list.join('\n');

            }
            else if(command == "db" || command == "DB") {
                //db 后面只能跟4个
                //db 0x55,0x56,0x57,0x58;
                QString Hex;
                QString final_Hex;
                for(; i < line.size(); i++)
                {
                    if(line[i] != ',' && line[i] != ';')
                        Hex += line[i];

                    if(line[i] == ',' || line[i] == ';') {
                        //一个hex读取完毕
                        Hex = Hex.trimmed();
                        bool ok;
                        uint dec = Hex.toUInt(&ok, 16);
                        if( ok == false) {

                            QString error = QString("'%1'不是一个有效的16进制数字").arg(Hex);
                            setError(error);
                            return false;
                        }
                        Hex.setNum(dec, 16);
                        Hex = Hex.rightJustified(2, '0');
                        final_Hex += Hex;
                        Hex = "";
                        if(line[i] == ';')
                            break;
                    }

                }
                bool ok;
                uint dec = final_Hex.toUInt(&ok, 16);
                if( ok == false) {

                    QString error = QString("'%1'不是一个有效的16进制数字").arg(final_Hex);
                    setError(error);
                    return false;
                }
                addr_data[PC] = dec;
                QString Bin;
                Bin.setNum(dec, 2);
                Bin = Bin.rightJustified(32, '0');
                assembled_line = Bin;
                PC += 4;


            }
            else if(command == "dw" || command == "DW") {

                //db 后面只能跟2个
                //db 0x1234,0x1234;
                QString Hex;
                QString final_Hex;
                for(; i < line.size(); i++)
                {
                    if(line[i] != ',' && line[i] != ';')
                        Hex += line[i];

                    if(line[i] == ',' || line[i] == ';') {
                        //一个hex读取完毕
                        Hex = Hex.trimmed();
                        qDebug() << Hex;
                        bool ok;
                        uint dec = Hex.toUInt(&ok, 16);
                        qDebug() << ok;

                        Hex.setNum(dec, 16);
                        Hex = Hex.rightJustified(4, '0');
                        qDebug() << Hex;
                        final_Hex += Hex;
                        Hex = "";
                        if(line[i] == ';')
                            break;
                    }

                }
                bool ok;
                uint dec = final_Hex.toUInt(&ok, 16);
                if( ok == false) {

                    QString error = QString("'%1'不是一个有效的16进制数字").arg(final_Hex);
                    setError(error);
                    return false;
                }
                addr_data[PC] = dec;
                QString Bin;
                Bin.setNum(dec, 2);
                Bin = Bin.rightJustified(32, '0');
                assembled_line = Bin;
                PC += 4;

            }



        }
    }
    else {
        //不存在的指令，需要我们报错
        /*
        error = sprintf("指令：%s 不存在", command);
        setError(error);
        */
        if( !isLabel ) {
            QString error = QString("指令：'%1' 不存在").arg(command);
            setError(error);
            qDebug() << error;
            //qDebug() << "指令： " << command << "不存在";

        }
        return 0;

    }

    return 1;







}

void assemble_manager::firstProcess()
{
    QString rawLine;
    first_processed_lines.clear();
    Labels.clear();
    dataLabels.clear();
    addr_data.clear();
    PC_clear();
    clearError();
    clearCan();


    for(int i = 0; i < lines.size(); i++)
    {
        QString first_process_line;//自动初始化
        rawLine = lines.at(i);
        if( processAline(rawLine, first_process_line) ) {
            //如果这一行不是注释、空行、且合法
            qDebug() << "合法";
            qDebug() << first_process_line;
            if(first_process_line == "BaseAddre")
            {
                //在pc和last pc之间补零
                //lastpc -> pc - 1
                qDebug() << "lastPC:" << LastPC;
                qDebug() << "PC:" << PC;
                if(PC == 0)
                    continue;
                for(int i = LastPC; i <= PC - 4; i += 4 )
                {
                    first_processed_lines << "00000000000000000000000000000000";
                }
            }
            else if(first_process_line == "DataAddre") {
                //在pc和last pc之间补零
                //lastpc -> pc - 1
                qDebug() << "lastPC:" << LastPC;
                qDebug() << "PC:" << PC;
                if(PC == 0)
                    continue;
                for(int i = LastPC; i <= PC - 4; i += 4 )
                {
                    first_processed_lines << "00000000000000000000000000000000";
                }

            }
            else if(first_process_line == "data") {

            }
            else
                first_processed_lines << first_process_line;
            //qDebug() << "PC: " << first_processed_lines.size();
        }
        if(isError == true)
        {
            return;
        }

    }


}

void assemble_manager::finalProcess(QString &process_content)
{
    QString pre_line;
    final_processed_Lines.clear();
    //我需要把合适的指令直接传进来，需要替换的指令进行替换，那么我在第一遍处理的时候，可以在还需处理的指令上加标记
    //label中保存了哪几行指令需要替换
    for(int i = 0; i < first_processed_lines.size(); i++)
    {
        QString final_line;
        QChar signal;
        pre_line = first_processed_lines.at(i);
        if(pre_line[0] == "!") {
            //这里有label
            QString label;
            int j;
            //把有意义部分先提取出来
            for(j = 1; j < pre_line.size(); j++)
            {
                if(pre_line[j] != "!" && pre_line[j] != "*") {
                    final_line += pre_line[j];
                }
                else {
                    signal = pre_line[j];
                    //遇到了label
                    //出去处理label
                    break;
                }
            }

            //抓取label
            j++;
            for(; j < pre_line.size(); j++)
            {
                label += pre_line[j];
            }



            if(signal == "!") {

                //j type 只需直接跳转就好，无符号
                uint address = Labels.value(label, -1);
                if(address == -1) {
                    QString error = QString("标记：'%1' 不存在").arg(label);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << "标记：" << label << "不存在";
                    //final_processed_Lines.clear();
                    break; //直接弹出
                }
                //address = address * 4; //实际要跳到的pc地址(以字节为单位）
                address = address / 4; //jump以字为单位，再回退两位

                QString target;
                target.setNum(address, 2);
                if(target.length() > 26) {
                    qDebug() << "target 数字超过位数限制";
                    target = target.right(26);
                }
                else {
                    //需要在左端补零(无符号）
                    target = target.rightJustified(26, '0');
                }

                final_line += target;
                final_processed_Lines << final_line;

            }
            else {
                //branch type
                //PC + 4 + offset * 4 = label
                //offset = label - PC - 4) / 4

                //要考虑label不存在的情况
                uint address = Labels.value(label, -1);
                if(address == -1) {
                    QString error = QString("标记：'%1' 不存在").arg(label);
                    setError(error);
                    qDebug() << error;
                    //qDebug() << "标记：" << label << "不存在";
                    //final_processed_Lines.clear();
                    break;

                }
                //address = address * 4; //转换为字节地址

                uint PC_address = i * 4; //当前PC字节地址, 考虑到可能有无效指令存在，不如我直接弹出？

                int offset = address - PC_address - 4;
                offset = offset / 4; //转换为字为单位
                qDebug() << "offset为："  << offset;

                QString branch_offset;
                branch_offset.setNum(offset, 2);

                if(branch_offset.length() > 16) {
                    qDebug() << "branch offset数字超过位数限制:" << branch_offset << " offset: " << offset;
                    branch_offset = branch_offset.right(16);
                }
                else {
                    //有问题，不一定补零
                    //应该是算数扩展
                    if(offset < 0) {
                        branch_offset = branch_offset.rightJustified(16, '1');
                    }
                    else {
                        branch_offset = branch_offset.rightJustified(16, '0');
                    }

                }

                final_line += branch_offset;
                final_processed_Lines << final_line;



            }




        }
        else {
            final_line = pre_line;
            final_processed_Lines << final_line;
        }
    }

    process_content = final_processed_Lines.join("\n");



}

void assemble_manager::convert2coe(QString  bin_content, QString &coe_content)
{

    QTextStream converter(&bin_content);
    int nextLine = 1;

    while( !converter.atEnd() )
    {
        QString bin = converter.readLine();
        bin = bin.trimmed();
        bool ok;
        uint Bin = bin.toUInt(&ok, 2);
        QString Hex;
        if(ok == false) {
            QString error = QString("bin 向 coe 文件转化失败，'%1' 不是一个合法数字").arg(bin);
            setError(error);
            return;
        }
        Hex.setNum(Bin, 16);
        if(Hex.length() > 8)
            Hex = Hex.right(8);
        else
            Hex = Hex.rightJustified(8, '0');
        Hex = Hex.toUpper();
        coe_content += Hex;
        if( !converter.atEnd() ) {
            coe_content += ",";
            if(nextLine == 4) {
                coe_content += "\n";
                nextLine = 0;
            }
            else
                coe_content += " ";
            nextLine++;

        }
    }
    coe_content += ";";

    /*
    int size = final_processed_Lines.size();
    for(int i = 0; i < size; i++)
    {
        QString Bin = final_processed_Lines.at(i);
        bool ok;
        uint bin = Bin.toUInt(&ok, 2);
        QString Hex;


        //转换成功
        if(ok == true) {
            Hex.setNum(bin, 16);
            //超过了位数限制/4*8 = 32
            if(Hex.length() > 8) {
                qDebug() << "数字超过位数限制";
                Hex = Hex.right(8);
            }
            else {
                //需要在左端补零
                Hex = Hex.rightJustified(8, '0');
            }
            Hex = Hex.toUpper();
            coe_content += Hex;
            if(i < size - 1)
                coe_content += ", ";
            nextLine++;
            //qDebug() << "nextline :" << nextLine;

            if(nextLine == 4 && (i < size - 1)) {
                //qDebug() << "进来了";
                coe_content += "\n";
                nextLine = 0;

            }



        }
        else {

        }


    }
    coe_content += ";";
    */
}

/* 判断函数 */
bool assemble_manager::isReg(const QString &reg)
{
    if(Reg2Num.value(reg) == 0)
        return false;
    else
        return true;

}

bool assemble_manager::isShamt(const QString &shamt)
{
    //shamt应该是数字
    for(int i = 0; i < shamt.size(); i++)
    {
        if( !(shamt[i] >= '0' && shamt[i] <= '9') ) {
            qDebug() << "不合法字母为：" << shamt[i];
            return false;
        }

    }
    return true;

}

bool assemble_manager::canInst()
{
    if(isData == true)
    {
        QString error = QString("不能在数据区之后插入指令");
        setError(error);
        return false;
    }
    return true;

}
/* 操作函数 */
bool assemble_manager::shamt2Bin(const QString &shamt, QString &outBin)
{
    bool ok;
    uint dec = shamt.toUInt(&ok, 0);

    //转换成功
    if(ok == true) {
        outBin.setNum(dec, 2);
        //超过了位数限制
        if(outBin.length() > 5) {
            qDebug() << "数字超过位数限制";
            outBin = outBin.right(5);
        }
        else {
            //需要在左端补零
            outBin = outBin.rightJustified(5, '0');
        }
    }

    return ok;
}

bool assemble_manager::signed_imm2Bin(const QString &imm, QString &outBin, int length)
{
    bool ok;
    int dec = imm.toInt(&ok, 0);

    //转换成功
    if(ok == true) {
        outBin.setNum(dec, 2);
        //超过了位数限制
        if(outBin.length() > length) {
            qDebug() << "数字超过位数限制";
            outBin = outBin.right(length);
        }
        else {
            //需要在左端补零
            outBin = outBin.rightJustified(length, '0');
        }
    }

    return ok;
}
bool assemble_manager::imm2Bin(const QString &imm, QString &outBin, int length)
{
    bool ok;
    uint dec = imm.toUInt(&ok, 0);

    //转换成功
    if(ok == true) {
        outBin.setNum(dec, 2);
        //超过了位数限制
        if(outBin.length() > length) {
            qDebug() << "数字超过位数限制";
            outBin = outBin.right(length);
        }
        else {
            //需要在左端补零
            outBin = outBin.rightJustified(length, '0');
        }
    }

    return ok;

}

bool assemble_manager::target2Bin(const QString &target, QString &outBin)
{
    bool ok;
    uint dec = target.toUInt(&ok, 0);

    //转换成功
    if(ok == true) {
        outBin.setNum(dec, 2);
        //超过了位数限制
        if(outBin.length() > 26) {
            qDebug() << "数字超过位数限制";
            outBin = outBin.right(26);
        }
        else {
            //需要在左端补零
            outBin = outBin.rightJustified(26, '0');
        }
    }

    return ok;

}

bool assemble_manager::sel2Bin(const QString &sel, QString &outBin)
{
    bool ok;
    uint dec = sel.toUInt(&ok, 0);

    //转换成功
    if(ok == true) {
        outBin.setNum(dec, 2);
        //超过了位数限制
        if(outBin.length() > 3) {
            qDebug() << "数字超过位数限制";
            outBin = outBin.right(3);
        }
        else {
            //需要在左端补零
            outBin = outBin.rightJustified(3, '0');
        }
    }

    return ok;
}

bool assemble_manager::Bin2Dec(const QString &Bin, long & dec, int radix)
{
    //long
    bool ok;
    //int dec = Bin.toInt();

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
            qDebug() << "abs_Bin:" << abs_Bin;
            dec = abs_Bin.toLong(&ok, radix);

            if(ok == false)
            {
                QString error = QString("'%1' 转换失败").arg(Bin);
                setError(error);
                return false;
            }

            dec = -(dec + 1);

            return true;
        }
        else {
            //这是一个正数
            dec = Bin.toLong(&ok, radix);
            if(ok == false)
            {
                QString error = QString("'%1' 转换失败").arg(Bin);
                setError(error);
                return false;
            }


            return true;

        }




    return true;


}

void assemble_manager::Hex2Bin(QString &Hex, QString &Bin)
{
    for(int i = 0; i < Hex.length(); i++)
    {
        if(Hex[i] == '0')
            Bin += "0000";
        if(Hex[i] == '1')
            Bin += "0001";
        if(Hex[i] == '2')
            Bin += "0010";
        if(Hex[i] == '3')
            Bin += "0011";
        if(Hex[i] == '4')
            Bin += "0100";
        if(Hex[i] == '5')
            Bin += "0101";
        if(Hex[i] == '6')
            Bin += "0110";
        if(Hex[i] == '7')
            Bin += "0111";
        if(Hex[i] == '8')
            Bin += "1000";
        if(Hex[i] == '9')
            Bin += "1001";
        if(Hex[i] == 'A' || Hex[i] == 'a')
            Bin += "1010";
        if(Hex[i] == 'B' || Hex[i] == 'b')
            Bin += "1011";
        if(Hex[i] == 'C' || Hex[i] == 'c')
            Bin += "1100";
        if(Hex[i] == 'D' || Hex[i] == 'd')
            Bin += "1101";
        if(Hex[i] == 'E' || Hex[i] == 'e')
            Bin += "1110";
        if(Hex[i] == 'F' || Hex[i] == 'f')
            Bin += "1111";


    }
}

void assemble_manager::PC_clear()
{
    LastPC = PC_init;
    PC = PC_init;

}

void assemble_manager::setError(QString &error)
{
    this->error = error;
    isError = true;
    qDebug() << error;
}

void assemble_manager::clearError()
{
    this->error = "";
    isError = false;
}
/* 测试函数 */
void assemble_manager::printLabel()
{
    QMapIterator <QString, uint> i(Labels);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value();
    }

}
