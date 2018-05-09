# 解析老师要求
1. 汇编与反汇编，支持mips指令子集
2. 不小于10k的汇编容量

## 汇编
1. 支持附录 A.10 或 附录子集所有整数指令和伪指令。
2. 生成.bin 和 .coe 文件
COE文件格式
```
memory_initialization_radix = 16;
memory_initialization_vector = 
FF, FF, FF, FF, FF, FF, DA, 02, 03, 04, 05, 06,
00, 40, 1C, F0, 00, 00, 00, 01, 00, 00, 00, 01,
00, 00, 00, 24, 01, 02, 03, 04, 05, 06, 07, 08 
09, 0A, 0B, 0C, 0D, 0E, 0F, 10, 11, 12, 13, 14,
15, 16, 17, 18, 19, 1A, 1B, 1C, 1D, 1E, 1F, 20,
21, 22, 23, 24;
```
3. 汇编指令以 `;`作为结束符，`//` 和 `#` 作为注释符
4. 寄存器符号支持 `r0 - r31`(忽略大小写) 和 mips使用约定（图2-18）

## 反汇编
1. 支持附录 A.10所有整数指令或附录子集。支持 .bin和.coe文件加载

## 文件操作功能
1. 新建 `ctrl+n`
2. 打开 `ctrl+o` (ASM, bin, coe)
3. 保存 `ctrl+s`
4. 保存为 `ctrl + shift + s`

## 汇编器语法
1. 参考附录 A.10.2
* assembler syntax
2. 增加一些伪指令
* 指定代码起始地址：`BaseAddre: 00008c00;` 
* 指定数据起始地址：`DataAddre: 00008d00;`

## 附录中有那些 .data .text的东西
# 注意
1. `jalr` 还是会把PC+4存入$ra
- PC + 4是字节！
- lw, sw 以字节为单位！（C语言以字为单位！）
- j无符号跳
- branch跳转有符号
- 无效指令直接弹出处理，这样就能保证预处理的序列就是pc序列了，因为如果不是，那么我弹出。。。
- sllv竟然是 rd rt rs
- HI, LO寄存器是什么鬼？
- coProcessoer又是什么？
- toint不能处理 32位的数据
- disassembleAction->setShortcut(tr("ctrl+shift+B"));
- menu 和 toolbar的 方式比较奇怪
- 注意ori处理为无符号！
- openfile读取文本的方式很危险
- assemble那里有一个危险，就是uint与负数的比较
- jump拼接pc高四位的问题
- 一些r格式其实没有判断完整，条件允许的情况下可以添加
- 进一步处理，infoconsole的内容不因该没次都是setplaintext，而要有函数和对象进行管理！
- 即便是我想出来的处理ffff的方法，一定要主要转为long,因为最大的ffff变为整数是越界的




# 先实现一个简单的文本编辑器
1. 保存文件，也许需要判断是否有已打开文件
2. 分成两个部分
3. QWidget和 QMainwindow区别是什么？
4. assemble的功能暂且用 slot机制实现
- 通过`QTextStream`来实现流
- `toPlainText()` `setPlainText()`可以把一整个字符串打进去


# assemble_manager
- 要实现32个寄存器(运行时考虑的了)
- 只翻译一行
`add $t0, $t1, $zero`
- 先把所有行读进一个 string 的vector(QStringList更加简单)
- 再一行一行翻译，写入右边
- 先考虑r格式，通过字典，建立 指令


1. 读入 stringlist ,在逐渐分析
- `QTextStream::readline()`会去除 `\n, \n\r`
- `利用 QString::trimmed()` 可以去除 一行中前后的空格
- 读完一行之后需要开始翻译，我们再在类中保留字典
1. 寄存器对应编号的字典（暂且认定 string 到 string
2. 无论怎么约定，他们的本质：二进制序列都是一样的，这个才是核心

- `QString::setNum()` 实现进制转换
- `QString::toUInt(bool, base = 10)` 实现字符串向数字转换，注意 base为用户提供的base, 若base为0，将有另一套规则，具体见参考文档,这个函数其实也可以直接判断是否合法

- `QSplitter`可以实现窗口的分割







































