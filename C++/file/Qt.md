# Linux创建qt

1. 正常下载qt，下载.run 可执行文件
2. 给.run执行权限
3. 使用sh 或者 ./ 运行.run文件
4. 按照步骤安装
5. 软连接lib64/libGL.so.1 到 lib/libGL.so
6. 软连接 安装路径/bin/qmake 到 /usr/local/bin/
