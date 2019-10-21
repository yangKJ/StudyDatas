##iOS语法技巧

看开源代码时，总会看到一些大神级别的代码，给人眼前一亮的感觉，多数都是被淡忘的C语言语法，总结下objc写码中遇到的各类非主流代码技巧和一些妙用：

[娱乐向]objc最短的方法声明  
[C]结构体的初始化  
[C]三元条件表达式的两元使用  
[C]数组的下标初始化  
[objc]可变参数类型的block  
[objc]readonly属性支持扩展的写法  
[C]小括号内联复合表达式  
[娱乐向]奇葩的C函数写法  
[Macro]预处理时计算可变参数个数  
[Macro]预处理断言  
[多重]带自动提示的keypath宏  

####[娱乐向]objc最短的方法声明
```
返回值的- (TYPE)如果不写括号，编译器默认认为是- (id)类型:
- init;
- (id)init; // 等价于

同理，参数如果不写类型默认也是id类型:
- (void)foo:arg;
- (void)foo:(id)arg; // 等价于

还有，有多参数时方法名和参数提示语可以为空
- (void):(id)arg1 :(id)arg2;
- (void)foo:(id)arg1 bar:(id)arg2; // 省略前

综上，最短的函数可以写成这样：
- _;   // 没错，这是一个oc方法声明
- :_;  // 这是一个带一个参数的oc方法声明
// 等价于
- (id)_;
- (id) :(id)_;

PS: 方法名都没的方法只能靠performSelector来调用了，selector是":"
```

####[C]结构体的初始化
```
// 不加(CGRect)强转也不会warning
CGRect rect1 = {1, 2, 3, 4};
CGRect rect2 = {.origin.x=5, .size={10,10}}; //{5,0,10,10}
CGRect rect3 = {1, 2}; // {1,2,0,0}
```

####[C]三元条件表达式的两元使用
```
三元条件表达式?:是C中唯一一个三目运算符，用来替代简单的if-else语句，同时也是可以两元使用的：
NSString *string = inputString ?: @"default";
NSString *string = inputString ? inputString : @"default"; // 等价
利用这个特性，我们还脑洞出了一个一行代码的 block 调用，平时我们的 block 是这样调用：
if (block0) {
  block0();
}
// or
if (block1) {
  int result = block1(1, 2);
}
居然可以简化成下面的样子：
!block0 ?: block0();
int result = !block1 ?: block1(1, 2);
```

####[C]数组的下标初始化
```
const int numbers[] = {
    [1] = 3,
    [2] = 2,
    [3] = 1,
    [5] = 12306
};
// {0, 3, 2, 1, 0, 12306}

这个特性可以用来做枚举值和字符串的映射
typedef NS_ENUM(NSInteger, XXType){
    XXType1,
    XXType2
};
const NSString *XXTypeNameMapping[] = {
    [XXType1] = @"Type1",
    [XXType2] = @"Type2"
};
```

####[objc]可变参数类型的block
```
一个block像下面一样声明：
void(^block1)(void);
void(^block2)(int a);
void(^block3)(NSNumber *a, NSString *b);

如果block的参数列表为空的话，相当于可变参数（不是void）
void(^block)(); // 返回值为void，参数可变的block
block = block1; // 正常
block = block2; // 正常
block = block3; // 正常
block(@1, @"string");  // 对应上面的block3
block(@1); // block3的第一个参数为@1，第二个为nil

block的主调和回调之间可以通过约定来决定block回传回来的参数是什么，有几个。
如一个对网络层的调用：
- (void)requestDataWithApi:(NSInteger)api block:(void(^)())block {
    if (api == 0) {
        block(1, 2);
    }else if (api == 1) {
        block(@"1", @2, @[@"3", @"4", @"5"]);
    }
}

主调者知道自己请求的是哪个Api，那么根据约定，他就知道block里面应该接受哪几个参数：
[server requestDataWithApi:0 block:^(NSInteger a, NSInteger b){
    // ...
}];
[server requestDataWithApi:1 block:^(NSString *s, NSNumber *n, NSArray *a){
    // ...
}];

这个特性在Reactive Cocoa的-combineLatest:reduce:等类似方法中已经使用的相当好了。
+ (RACSignal *)combineLatest:(id<NSFastEnumeration>)signals reduce:(id (^)())reduceBlock;
```

####[objc]readonly属性支持扩展的写法
```
假如一个类有一个readonly属性：
@interface Sark : NSObject
@property (nonatomic, readonly) NSArray *friends;
@end

.m中可以使用_friends来使用自动合成的这个变量，但假如：
习惯使用self.来set实例变量时（只合成了getter）
希望重写getter进行懒加载时（重写getter时则不会生成下划线的变量，除非手动@synthesize）
允许子类重载这个属性来修改它时（编译报错属性修饰符不匹配）
这种readonly声明方法就行不通了，所以下面的写法更有通用性：
@interface Sark : NSObject
@property (nonatomic,readonly,copy) NSArray *friends;
@end

如想在.m中像正常属性一样使用：
@interface Sark ()
@property (nonatomic, copy) NSArray *friends;
@end
子类化时同理。iOS SDK中很多地方都用到了这个特性。
```

####[C]小括号内联复合表达式
```
RETURN_VALUE_RECEIVER = {(
    // Do whatever you want
    RETURN_VALUE; // 返回值
)};

于是乎可以发挥想象力
self.backgroundView = ({
    UIView *view = [[UIView alloc] initWithFrame:self.view.bounds];
    view.backgroundColor = [UIColor redColor];
    view.alpha = 0.8f;
    view;
});

有点像block和内联函数的结合体，它最大的意义在于将代码整理分块，将同一个逻辑层级的代码包在一起；
同时对于一个无需复用小段逻辑，也免去了重量级的调用函数
self.result = ({
    double result = 0;
    for (int i = 0; i <= M_2_PI; i+= M_PI_4) {
        result += sin(i);
    }
    result;
});
这样使得代码量增大时层次仍然能比较明确。

PS: 返回值和代码块结束点必须在结尾
```

####[娱乐向]奇葩的C函数写法
```
正常编译执行：
int sum(a,b)
int a; int b;
{
    return a + b;
}
```
####[Macro]预处理时计算可变参数个数
```
#define COUNT_PARMS2(_a1, _a2, _a3, _a4, _a5, RESULT, ...) RESULT
#define COUNT_PARMS(...) COUNT_PARMS2(__VA_ARGS__, 5, 4, 3, 2, 1)
int count = COUNT_PARMS(1,2,3); // 预处理时count==3
```
####[Macro]预处理断言
```
下面的断言在编译前就生效
#define C_ASSERT(test) \
    switch(0) {\
          case 0:\
          case test:;\
    }
如断言上面预处理时计算可变参数个数：

C_ASSERT(COUNT_PARMS(1,2,3) == 2);
如果断言失败，相当于switch-case中出现了两个case:0，则编译报错。
```

####[多重]带自动提示的keypath宏
```
源自Reactive Cocoa中的宏：
#define keypath2(OBJ, PATH) \
    (((void)(NO && ((void)OBJ.PATH, NO)), # PATH))
原来写过一篇《介绍RAC宏的文章》中曾经写过。这个宏在写PATH参数的同时是带自动提示的：

逗号表达式
逗号表达式取后值，但前值的表达式参与运算，可用void忽略编译器警告
int a = ((void)(1+2), 2); // a == 2
于是上面的keypath宏的输出结果是#PATH也就是一个c字符串

逻辑最短路径
之前的文章没有弄清上面宏中NO&&NO的含义，其实这用到了编译器优化的特性：
if (NO && [self shouldDo]/*不执行*/) {
    // 不执行
}
编译器知道在NO后且什么的结果都是NO，于是后面的语句被优化掉了。也就是说keypath宏中这个NO && ((void)OBJ.PATH, NO)就使得在编译后后面的部分不出现在最后的代码中，于是乎既实现了keypath的自动提示功能，又保证编译后不执行多余的代码。
```