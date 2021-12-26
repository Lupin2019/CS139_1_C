<!--
 * @Author: Mathis
 * @Date: 2021-12-21 20:53:24
 * @LastEditTime: 2021-12-26 19:04:58
 * @Description: file content
 * @FilePath: /assignment4/README.md
-->
# CS139-1-C程序与算法分析 assignent4

**github:** [传送门](https://github.com/Lupin2019/CS139_1_C.git)

## 目录结构
```bash
assignment4
|-- CMakeLists.txt
|-- README.md
|-- a.txt
|-- b.txt
|-- bin
|   |-- README
|   |-- answer1
|   |-- answer2
|   |-- answer3
|   |-- answer4
|   |-- answer5
|   `-- demo
|-- build
|-- data
|   |-- 00_table_readme.txt
|   `-- table20_d.txt
|-- include
|   |-- list.h
|   `-- param_deliver.h
|-- lib
|   `-- libMyList.a
`-- src
    |-- CMakeLists.txt
    |-- answer1
    |-- answer2
    |-- answer3
    |-- answer4
    |-- answer5
    |-- demo.c
    |-- list
    `-- param_deliver.h.in

12 directories, 19 files
```
> <span style="color:red">特别说明</span>: data/ 目录下存了20个人的信息， 如果不检测键盘输入信息这一项的话， 可以加快调试的速度

## 作业说明
平台： ubuntu 20.04.2 Linux version 5.11.0-43-generic

### 4.1
采用的是`getchar()` + 空格/字符判断的方法， 用到了一点链表； 后来发现了更好的使用方法， 但是没有时间去优化。

**可能更好的解决方案：**
```c
// linux
char str[100];
setbuf(stdin, NULL); // CLEAR STDIN
fgets(str, SIZE , stdin);
char *find = strchr(data.name, '\n');
if(find){*find = '\0';}
```
> 因为`scanf()`处理不了空格， 但是`fgets()`需要注意缓冲区清空以及最后的换行符替换
> fflush(stdin);在linux上用不了

---
### 4.2
`count_down()`要求输入的参数没有明确规定， 我就默认是“时间结构体”了， 但是也写了一个将“yyyy-mm-dd”格式的字符串转换成"时间结构体"的函数`date_t StrToDate(char* date_string);`

**获取当前时间的方法**
```c
time_t now;
struct tm *tm_now;
time(&now);
tm_now = localtime(&now);
```
---

### 4.3
构建了`list.c` 和 `list.h`两个文件， 内含基于单向链表实现的线性表(list)

**实现有关列表的操作包括并不限于：**
- 初始化， 逆初始化
- 增删查改
- 复制
- 根据成绩排序(堆排)
- 倒序
- 信息打印
- 信息导入与导出
- 信息键盘输入

*启动程序时：* 因为已经在`data`目录下导出过一组<span style="color:red">20</span>人的信息， 名字是随机取的， 与现实无关。 所以， 会询问是否采用键盘输入， 不采用， 则直接导入这些数据，函数`load_from_data_dir(list, data_path, 10);` 范围是[1,20]的整数；

---

### 4.4

因为已经在`list.c`中写好了增删查改， 所以为了匹配题目要求的函数名， 直接给各类操作套了一层马甲， 乏善可陈。

---

### 4.5
逆序用了三个指针， 


---
---


## Valgrind 自检
[在.assets/valgrind检查信息.md中](.assets/valgrind检查信息.md)

## 命名规范
[Google 开源项目风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/)

- 类型：类型名称的每个单词首字母均大写, 不包含下划线 `MyExcitingClass`

- 变量命名： 统一小写 + 下划线 或 全小写

- 类数据成员 ： 普通变量基础上 + `_` 例如
```c++
class TableInfo {
  ...
 private:
  string table_name_;  // 好 - 后加下划线.
  string tablename_;   // 好.
  static Pool<TableInfo>* pool_;  // 好.
};
```

- 结构体变量 ： 和普通变量一样即可

- 常量命名： `k` 
```c
const int kDaysInAWeek = 7;
```

- 枚举命名 : 与常量 或 宏 一致 (优先使用常量形式)

```c++
enum UrlTableErrors {
    kOK = 0,
    kErrorOutOfMemory,
    kErrorMalformedInput,
};
enum AlternateUrlTableErrors {
    OK = 0,
    OUT_OF_MEMORY = 1,
    MALFORMED_INPUT = 2,
};
```

- 宏命名
`MY_MACRO_THAT_SCARES_SMALL_CHILDREN`

[关于预处理宏](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/others/#preprocessor-macros)

- 函数命名
```c++
AddTableEntry()
DeleteUrl()
OpenFileOrDie()
```

## Question
Some questions
1. 头文件中的#ifndef #endif这样的保护措施, 请问下面这些内容哪些应该放入保护中： 
    - [ ] struct
    - [ ] 库文件
    - [ ] 函数声明
    - [ ] 函数定义

2. 链表中的head节点数据项的利用问题
- 如果单节点过大， 那么舍弃head中数据项的空间感觉有点浪费， 虽然有时可以用来存储链表长度..因此想试试这种写法： 数据项单独列出strcut， 节点中只有两个指针(一个指下一个节点， 一个指向自己的数据项)； 例如：
```C
typedef struct _data
{
    int item1;
    char item2;
    char item3[10];
} data_t;

typedef struct _node
{
    data_t *data;
    struct _node *next;
} node_t;
```
 
> 这样写头节点只会多占用一个指针

3. 交的作业能使用Cmake吗？
   
4. 辅助函数也需要写在头文件里吗？ 如果不写会引发函数名冲突吗？