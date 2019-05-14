# 编译leveldb
从[https://github.com/google/leveldb.git](https://github.com/google/leveldb.git)获取源码，构建为Debug版本：
```
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .
```

将`libleveldb.a`拷贝到`/usr/local/lib`, `include/leveldb`拷贝到`/usr/local/include`