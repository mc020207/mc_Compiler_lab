1. 在linux环境下输入make a.out 可以得到转换程序
2. check.cpp是自己编写的比较程序，可以比较print出来的语法树和源程序的区别，自动识别!和not的区别以及exp和(exp)不能识别注释
3. make runcomp 可以测试所有测试数据并且利用check程序快速判断（但其实false也不一定一定是错的）