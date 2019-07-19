#coding:utf-8
from scipy import interpolate 
#导入内插方式
from numpy import sin 
x=[0.32,0.34,0.36] 
y=[0.314567,0.333487,0.352274] 
x3=0.3367 
for kind in ["linear","quadratic"]: 
    f=interpolate.interp1d(x,y,kind=kind)
    y3=f(x3) 
    print(kind,"插值法%.6f" %y3)

