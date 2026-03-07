---
title: "函数式编程"
date: 2019-12-14
description: 
---

先提出一个问题: **为什么C语言可以嵌套定义类,但是不能嵌套定义函数?**

反过来我们可以想想: **如果可以在函数中定义函数会发生什么?**


主要内容

- 匿名函数、lambda表达式
- 闭包
- 高阶函数、科里化
- 纯函数
- 函数式编程
- 模板元编程

C#，C++11通过支持Lambda表达式(本质上是匿名类)来实现类似功能

## 匿名函数

简化程序中使用次数少的函数，不用显式定义函数名，但编译期还是会在背后定义，是一种语法糖（其实还有匿名类…）

```c#
//C# 使用关键字delegate,表示一个参数为(int, double) 返回值为double 的函数 
delegate double (int a,double b) { return a + b ; }
```

## lambda表达式

匿名函数的进步一简化

```c#
//与匿名函数相同,但是可以省略delegate和其他符号(有限制) 
(int x,double y) => { return x * y; }	//自动推断返回值类型 x => x+5; 
() => PI;		//返回常量
```
用途

- 委托
- LINQ

## 闭包

捕获变量

闭包会延长它使用的外部变量的生命周期，直到闭包本身被释放,不会被垃圾回收

```c#
Func<int> T1() { 
    int i = 0;                      //i是局部变量,应该分配在栈上 
    Func<int> T2 = () => ++i;       //捕获了外部变量i return T2; //i的作用范围结束,i应该消失 
} 
var s = T1(); 
s();			//i = 1 
s();			//i = 2 
```

.NET本身并不支持函数对象，它依然满足对象生命周期的规则。编译器在背后会生成一个类,将局部变量i变成该类的一个属性，从而保证了变量的生命周期不会随函数T1调用结束而结束。

C#中，闭包其实和类中其他属性、方法是一样的。它们的原则都是下一层可以调用上一层定义，但上一层则不具备访问下一层设定的能力。即类中方法里的变量可以自由访问类中的所有属性和方法，而闭包又可以访问它的上一层即方法中的各种设定，但类不可以访问方法的局部变量。同理，方法也不可以访问其内部定义的匿名函数所定义的局部变量。

**延迟调用**

```c#
List<Func<int>> funcs = new List<Func<int>>(); 
for (int i = 0; i < 3; i++) {
    funcs.Add(() => { return i; }); 
} 
foreach(var item in funcs) { 
    Console.WriteLine(item().ToString());		// 3,3,3 
}
```

## 高阶函数

函数可以接受另一个函数作为输入参数，同时也可以返回一个函数

```c#
// 使用LINQ查询出数组中的奇数 
int[] ints = { 5, 2, 0, 66, 4, 32, 7, 1 }; 
List<int> list = IntExtension.where(ints, (item) => item % 2 != 0;).ToList(); //等同与下面代码
List[] Find(int[] ints, Func<int,bool> check){  
    List[] result;  
    foreach(int i in ints){
        if(check(i) == true){      
            result.Add(i);    
        }  
    } 
    return result; 
} 
bool Check(int item){  
    if(item % 2 != 0) return true; 
} 
Find(ints,Check);	//将函数Check传入函数Find,类似函数指针
```

## 科里化

Currying就是将需要多个参数的函数转换为「接受一个参数；返回一个值」的函数

实现方法: 当提供较少的参数时，返回一个等待剩余参数的新函数

好处:

1. 参数可复用，对部分参数的复用,无需重复添加
2. 可以提前返回，存在返回值，并且可以继续接收参数的函数
3. 延迟运行，不断的柯里化，累积传入的参数，最后执行

这样对于讨论和优化会更加方便。

```c#
// 原函数 
function add(a, b, c) {
    return a + b + c; 
} 
// 柯里化函数 
function addCurrying(a) {
    return function (b) {
        return function (c) {
            return a + b + c;
        }
    }
} 
// 调用原函数
add(1, 2, 3); // 6
// 调用柯里化函数 
addCurrying(1)(2)(3) // 6 
//参数复用 
var add1 = add(1); 
var add2 = add(2); 
add1(3);	//1+3 
add2(3);	//2+3 
//延迟计算 
add(1,2)(3); 
add(4); 
add(); // 10 
//经过修改还可以接受任意数量的参数 
add(1, 2, 3, 4)(5)	// 15 
add(1, 2)(3, 4)		// 10 
add(1, 2)(3)(4)		// 10
```

## 纯函数

1. 当参数相同时，永远返回相同的结果，并且不依赖于任何外部状态或数据
2. 函数不会发生任何突变(mutation)或产生任何副作用(side effect)，如修改外部状态

优点:

1. 简洁，容易阅读
2. 易于并发编程，不需要考虑死锁(deadlock)
3. 测试方便

```c#
// 函数内部使用的变量是显式传递进去的 
function f(x){  
    return function g(x){
        //g(x)是会依靠f(x)的参数返回的,g(x)相当于拥有f(x)的闭包   
        return x * x;  
    } 
}
```

**问:纯函数式的闭包和不改变函数状态的特性是否矛盾**

闭包虽然可以把闭包外部的变量捕获到闭包内部，但是闭包还是满足不改变状态的特性的。

虽然传入了不同参数，但是闭包里面的整体算法是没有变化的。g(x)虽然每次都会由f(x)传入的x值变化而变化，但是g(x)整体算法就是计算x的平方，这个计算方法是没有变化的，不根据外部状态改变而改变的。

## 函数式编程

```c#
(1 + 2) * 3 - 4 
subtract(multiply(add(1,2), 3), 4) 
add(1,2).multiply(3).subtract(4)
```

1. 函数是“第一等公民”(first class)

   函数与其他数据类型一样,可以赋值给其他变量，也可以作为其他函数的参数和返回值

2. 使用“表达式”代替“语句”

   表达式(expression)是一个单纯的运算过程，总是有返回值；语句(statement)是执行某种操作如赋值，没有返回值。函数式编程要求每一步都是单纯的运算，而且都有返回值

3. 没有"副作用”

   函数式编程强调没有"副作用”，所有功能就是返回一个新的值，没有其他行为如修改外部变量的值。

4. 不修改“状态”

   通常用变量来保存"状态”(state), 但在函数式编程中常使用递归参数保存状态

5. 引用透明(Referential transparency)

   函数的运行不依赖于外部变量或"状态”，只依赖于输入的参数，任何时候只要参数相同，得到的返回值总是相同的

```c#
var c = 10; 
function addC(a, b) {
    return a + b + c; 
} 
addC(1,2)		//1+2+10; 
addC(3,4)		//3+4+10; 
//改变c 
addC(1,2)		
//1+2+10 
c=20; 
addC(1,2)		//1+2+20 
//C就成为了一种状态(State)，它的变化可以左右函数的输出,也就是产生副作用,再来看下面一个例子 
var c = 10; 
function addC(a,b){
    return a + b + (c++); 
} 
addC(1, 2)	//1+2+10; 
addC(1, 2)		//1+2+11;改变了状态
//不同时间调用add()产生的结果不同 
//将输出仅取决于输入的参数
//将语句 c = 10 变成表达式 
function getC(){
    return 10 
} 
function addC(a, b) {
    return a + b + getC()  	
    //return a + b + 10 
}
//输出仅取决于输入的参数。 
//不修改状态意味着我们就不使用赋值和变量了吗? 
//抛弃了“=” 
//不使用状态如何控制程序运行顺序? 
//计算累加 
function countSum (num) {
    var result = 0		
        //var i 作为状态(state)控制了函数内部的循环,但它还是一个纯函数    
        for (var i = 1; i < num; i ++) {
            result += i    
        }    
    return result 
} 
function countSum (num) {
    return num = 1 ? 1 : num + countSum(num-1)		//通过递归,使用函数参数保存状态 
}
```

# 模板元编程

C++ 模板元编程不是设计之初的功能，是意外发现的“黑魔法”，它用来编写编译期运行的程序，也就是可以将运行期间的计算转化为编译期的计算

## 数值计算

```c++
template<int N, int M> struct meta_Add{
    static const int value = N + M; 
} 
meta_Add<1, 2>::value		//3
```
模版元程序在编译期执行，不能使用运行期间的if-else、for、while等语句，但可以通过递归形式实现循环，通过模板特例化实现条件判断，这两点使得其具有和普通语言一样通用的能力（图灵完备性）。

从编程范式上来说，C++模板元编程是函数式编程

```c++
template<int N> struct meta_Sum{    
    enum { Result = meta-Sum<N-1>::Result + N }; 
}; 
template <>			//特化 struct meta_Sum<1>{    enum { Result = 1 }; };
```

## 类型计算

数值计算在模板元编程中用的很少，真正有价值的是类型计算，通过模板提供的参数化的类型，可以补充C++自带的类型，使得类型系统更加智能与完备。一般来说在运行期发生的类型错误很难发现和调试。通过模板元编程，在编译期就可以对类型进行检查，从而避免运行期出错。

一个典型的例子是物理量计算的量纲问题

```c++
typedef tyVector<int, 1, 0, 0, 0, 0, 0, 0> Length;	//长度,单位m 
typedef tyVector<int, 0, 1, 0, 0, 0, 0, 0> Mass;	//质量,单位kg 
typedef tyVector<int, 0, 0, 1, 0, 0, 0, 0> Time;	//时间,单位s 
typedef tyVector<int, 0, 0, 0, 1, 0, 0, 0> I;		//电流,单位A 
typedef tyVector<int, 0, 0, 0, 0, 1, 0, 0> K;		//热力学温度,单位K 
typedef tyVector<int, 0, 0, 0, 0, 0, 1, 0> n;		//物质的量,单位mol 
typedef tyVector<int, 0, 0, 0, 0, 0, 0, 1> lv;		//发光强度,单位cd 

auto velocity={1,0,-1,0,0,0,0}; 
tymeta::quantity<float, tymeta::Length> len(10.23);		//长度 
tymeta::quantity<float, tymeta::Time> t(5);				//时间 
tymeta::quantity<float, tymeta::Mass> m(10);			//质量 

auto speed = len / t;			//速度 //类型为quantity<float,struct  tymeta::tyVector<int,1,0,-1,0,0,0,0>> 
auto a_speed = speed / t;	//加速度 //类型为quantity<float,struct tymeta::tyVector<int,1,0,-2,0,0,0,0>> 
auto force = a_speed * m;	//力 //类型为quantity<float,struct tymeta::tyVector<int,1,1,-2,0,0,0,0>> 

//但一旦出现 
auto r = force + speed; 
//会得到一个编译期的错误
```