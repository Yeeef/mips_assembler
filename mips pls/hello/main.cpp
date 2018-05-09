


#include <QApplication>

#include "mainwindow.h"





int main(int argc, char *argv[])
{
   QApplication app(argc, argv);


  MainWindow win;
  win.resize(800,600);
  win.show();

   /*
  bool ok;
  QString str = "0xf0000000";
  uint dec = str.toUInt(&ok, 16);
  qDebug() << dec;
  */



/*
   bool ok;
   QString Bin("1111111111110000");
   for(int i = 0; i < Bin.size(); i++)
   {
       if(Bin[i] == '1')
           Bin[i] = '0';
       else
           Bin[i] = '1';
   }
   qDebug() << Bin;
   short raw_bin = Bin.toShort(&ok, 2);
   short bin = raw_bin + 1;
   qDebug() << (-bin);

   qDebug() << bin;
  // long bin = Bin.toLong(&ok, 0);
   //out.setNum(bin, 2);
   //qDebug() << out;
   */







    return app.exec();
}
