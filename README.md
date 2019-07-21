# radiometer-GUI
GUI for radiometer

注意：
1、GUI是QT工程，主要包含cpp文件；

2、GUI_RUN是qt运行的环境文件，包括python中间处理件和uvspec的运行环境，
使用时将GUI_RUN下面的所有文件复制到QT工程生成的GUI.exe同级目录下即可。

3、GUI_EXE是可以直接运行的环境，需要配置qt_conf/GUI.ini后，点击GUI.exe即可运行。

4、single.input 是单点模式下的配置例子；multi.input是批处理的配置例子；运行后直接载入即可。