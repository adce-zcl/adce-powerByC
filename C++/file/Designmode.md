# 重构关键技法

1. 静态到动态
2. 早绑定到晚绑定
3. 继承到组合
4. 编译时依赖到运行时依赖
5. 紧耦合到松耦合


# 设计原则

**变化是复用的天敌**。


**面向对象与软件设计的目的：**

1. 隔离变化：将变化带来的影响降为最小
2. 微观层面：各司其职，新产生的类不影响已存在的类


**对象的作用：**

1. 语言层面：封装了数据和代码
2. 规格层面：一系列可被使用的公共接口
3. 概念层面：拥有某种责任的抽象

## 依赖倒置原则DIP

1. 高层模块（稳定）不应该依赖于低层模块（变化），二者都应该依赖于抽象（稳定）。
2. 抽象（稳定）不应该依赖于实现细节（变化），实现细节应该依赖于抽象（稳定）。

   这两换句话在上述Window的例子中的体现：


   1. Window不应该因为各个形状(Line等)的变化，而需要调整自身，Window和Line等都转而依赖于抽象的Shape
   2. 在Shape中不应该使用具体的（Line等）的操作，而是让Line等自己负责自身的实现细节（draw）


## 开放封闭原则OCP

1. 对扩展开放，对更改封闭
2. 类模块应该是可扩展的，但不可修改

   在Window中，可以扩展更多的形状（Triangle），而不对Window做出更改


## 单一职责原则SRP

1. 一个类应该仅有一个引起它变化的原因
2. 变化的方向隐含着类的责任


## Liskov替换原则LSP

1. 子类必须能够替换他们的基类（IS-A）
2. 继承表达类型抽象


## 接口隔离原则ISP

1. 不应该强迫客户程序依赖它们不用的方法
2. 接口应该小而完备

   只public必要的，仅子类用的就protected，仅自身使用就private


## 优先使用对象组合而不是类继承

1. 类继承通常为白箱复用，对象组合通常为黑箱复用
2. 继承在某种程度上破坏了封装性，子类父类耦合度高继承有时候导致父类对子类暴露的东西过多
3. 而对象组合只要求被组合的对象具有良好的接口，耦合程度低


## 封装变化点

1. 使用封装来创建对象之间的分界层，让设计者可以在分界层的一侧进行修改，而不会对另一侧产生不良影响，从而实现层次之间的松耦合


## 针对接口编程而不是针对实现编程

1. 不将变量类声明为某个特定的具体类，而是声明为某个接口
2. 客户程序无需获知对象的具体类型，只需知道对象所具有的接口
3. 减少系统中各部分的依赖关系，从而实现 高内聚，松耦合 的类型设计方案

   Window的实现中，分解的实现包含了具体类的vector，而抽象实现使用Shape*


# 单例模式-Singleton

**单例**

单例模式保证某个类只会创建一个实例，当某些类创建对象时，内存开销过大或者时间过长，可以考虑使用这个模式。注意：这个只创建一个类你不能由用户去保证，你应该自己保证这个类只会有一个实例。


**要点总结：**

非常简单，static原有的特性。除了static，还有很多可以实现单例模式，比如unique_ptr，call_one等方式。


**代码:**

**饿汉式单例模式:**

不管是否需要，都会在类加载的时候创建一个实例。

因为是在类加载的时候创建实例，所以在后续程序中不会再涉及到类创建，所以它是线程安全的。

```
class ConnectionPool {
public:
	// 获取连接池对象实例
	static ConnectionPool* get_connection_pool();

	// 给外部提供接口，从连接池中获取可用的空闲连接
	// 通过智能指针自动管理外部的连接，不需要用户手动释放
	// 还需要重定义智能指针的删除方式，把连接归还到队列   
private:
	static ConnectionPool pool;
---------实现----
// 初始化
ConnectionPool ConnectionPool::pool;
// 饿汉式单例模式接口
ConnectionPool* ConnectionPool::get_connection_pool() {
	return &pool;
}

```

```
public class Person {
    //饿汉式单例
    private static Person person = new Person();
    private Person(){}

    public static Person getInstance(){
    return person;
    }
}

```


**懒汉式单例模式:**

只有到需要的时候，手动建立实例，它不是线程安全的，需要连同锁的机制一起使用。

```
class Sigleton1
{
private:
    Sigleton1();
    static Sigleton1 *sig1;
public:
    static Sigleton1 *Init()
    {
        // if语句是线程不安全的，如果同时有多线程判断为空，就会实例出多个对象
        // 而且其他对象都是没有指针指向的，无法使用。
        if(sig1 == nullptr)
        {
            sig1 = new Sigleton1();
        }
        return sig1;
    }
};


/* 2.饿汉式-线程安全 */
class Sigleton2
{
private:
    Sigleton2();
    static Sigleton2 *sig2;
public:
    static Sigleton2 *Init();
};
// 因为在类加载的时候就初始化，所以不会有线程问题
Sigleton2* Sigleton2::sig2 = new Sigleton2();
Sigleton2* Sigleton2::Init()
{
    return sig2;
}

/* 3.懒汉式-线程安全*/
// 使用双检查锁，但是可能因为内存读写的问题，不安全，涉及到线程内存模型
```



# 模板方法模式-Template Method

**模板方法**

定义一个操作中的算法的骨架（稳定），而将一些步骤的实现延迟（变化）到子类中。Template Method使得子类可以不改变（复用）一个算法的结构即可重定义（override重写）该算法的某些特定步骤。


**解决什么问题？**

比如说多个业务，它们只有一部分操作不相同，比如说只有A操作不同，而A之前或者A之后都是相同的，如果为每一个业务都重写一个类，就会有大量的代码重复，这是不好的，所以我们将相同的地方构造成模板来复用。


**违背了什么原则？**

它似乎没有违背什么原则，但是它违背了设计模式的初衷：代码复用。


**要点总结：**

* 一个抽象类，定义骨架流程（抽象方法放一起）
* 确定的共同方法步骤，放到抽象类（去除抽象方法标记）
* 不确定的步骤，给子类去差异化实现

模板方法就是C++的虚函数多态机制实现的运行时动态绑定，只不过稳定的算法框架是在基类中固定，变化的部分用虚函数封装，来实现子类的动态绑定。

**早绑定与晚绑定**

**区分稳定与变化**


**代码：**

```
// 面向对象
class Library {
public: 
    // 稳定中包含变化
    void Run() {
        Step1();
  
        if (Step2()) {  // 支持变化 虚函数多态调用
            Step3();
        }
  
        for (...) {
            Step4();// 支持变化 虚函数多态调用
        }
  
        Step5();
    }
  
    virtual ~Library();
private:
    Step1();  
    Step3(); 
    Step5();
  
    virtual Step2();
    virtual Step4();
};

class Application : public Library {
public:
    Step4();
    Step5();
};

int main() {
    Library* pLib = new Application;
    pLib->run();// run()并不是虚函数，此处调用基类的run()，但是在run()内部的Step2()、Step4()又是虚函数，调用的时Application的Step2()、Step4()
    delete pLib;
    ...
}

```



# 策略模式-Strategy

**策略**

定义一系列算法，把它们一个个封装起来，并且使它们可以相互替换（变化）。该模式使得算法可以独立于使用它的客户程序（稳定）而变化（扩展、子类化）。


**解决什么问题？**

在软件构建过程中，某些对象使用的算法可能多种多样，经常改变，如果将这些算法都编码到对象中，会使得对象变得异常复杂，而且有时候支持不使用的算法也是一个性能负担。就是说，你的代码中会随着业务类型的增加，而增加大量的if 分支语句，使得原代码臃肿。

如何在运行时根据需求更透明的更改对象的算法？

将算法与对象本身解耦，从而避免上述问题？


**违背了什么原则？**

* **开闭原则** （对于扩展是开放的，但是对于修改是封闭的）：增加或者删除某个逻辑，都需要修改到原来代码
* **单一原则** （规定一个类应该只有一个发生变化的原因）：修改任何类型的分支逻辑代码，都需要改动当前类的代码。

每增加一个职责，就增加一个if else分支，让一个类负责所有的算法功能，这就是违背了单一职责原则。应该把每个算法独立封装称类，它们共同继承方法基类。

每次增加职责，就要修改源代码，这就是违背开闭原则，严格禁止对现有代码进行大量修改，应支持代码拓展。


**要点总结：**

1. Strategy及其子类为组件提供了一系列可重用的算法，从而使得类型在运行时方便的根据需要在各个算法之间切换
2. Strategy提供了判断语句外的另一种选择
3. 如果Strategy对象没有实例变量，那么各个上下文可以共享同一个Strategy对象，从而节省开销


**代码：**

没有使用策略模式：

```
// 结构化
// 为了区分每一种税收，必须为每一种税收分别做计算方法。

enum TaxBase { // 变化
    CN_Tax,
    US_Tax,
    DE_Tax,
    FR_Tax  // 增加需求
};

class SalesOrder {
public:
// 这些方法，全部在类里面，虽然有枚举，可以跳过其他的方法，但这些方法的增删改都不方便，而且也会使得这个类很庞大
    // 稳定
    double CalculateTax() {
        // ...
  
        if (tax == CN_Tax) {
            // ...
        }
        else if (tax == US_Tax) {
  
        }
        else if (tax == DE_Tax) {
  
        }
        else if (tax == FR_Tax) { // 增加 应该对扩展开放，对修改封闭
  
        }
        //...
    }
  
private:
    TaxBase tax;
};

```



使用策略模式：

```
// Strategy —— 第一层，顶层基类
class TaxStrategy {
public:
    virtual double Calculate(const Context& context)=0;
    virtual ~TaxStrategy(){}// 基类最好都实现一个虚的析构函数
};

// 变化 —— 第二层，可拓展的变化
// 把每一种税收计算方法，都封装成一个类，这个类不能实例化，但却有重写的虚函数
// 这样，如果是增加或者减少方法，只需要增加或减少相应的类，而且，根据类不同，其他类的代码不会冗余进来

class CNTax : public TaxStratygy {
public:
    virtual double Calculate(const Context& context) {
        // ...
    }
};

class USTax : public TaxStratygy {
public:
    virtual double Calculate(const Context& context) {
        // ...
    }
};

class DETax : public TaxStratygy {
public:
    virtual double Calculate(const Context& context) {
        // ...
    }
};

// 增加
class FRTax : public TaxStratygy {
public:
    virtual double Calculate(const Context& context) {
        // ...
    }
};

// 稳定 —— 第三层，给用户的稳定
class SalesOrder {
public:
    SalesOrder(StrategyFactory* strategyFactory) {
        this->strategy = strategyFactory->NewStrategy();
    }
  
    ~SalesOrder() {
        delete this->strategy;
    }
  
    double Calculate() {
        // ...
        Context context();
  	// 这个时候调用的就是实际的税收计算方法类里面的方法
        double val = strategy->Calculate(contex);
  
        // ...
    }
  
private:
    TaxStrategy* strategy;
};

```


# 责任链模式-Chain of Resposibility

**责任链**

使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。


**解决什么问题？**

在软件构建过程中，一个请求可能被多个对象处理，但是每个请求在运行时只能有一个接受者，如果显示指定，将必不可少地带来请求发送者与接受着的紧耦合。

如何使请求的发送者不需要指定具体的接受者？让**请求的接受者自己在运行时决定**来处理请求，从而使两者解耦。

当你想要让一个**以上的对象**有机会能够处理某个请求的时候，就使用 **责任链模式** 。

责任链模式为请求创建了一个接收者对象的链。执行链上有多个对象节点，每个对象节点都有机会（条件匹配）处理请求事务，如果某个对象节点处理完了，就可以根据实际业务需求传递给下一个节点继续处理或者返回处理完毕。这种模式给予请求的类型，对请求的发送者和接收者进行解耦。


**要点总结：**

1. Chain of Responsibility 模式的应用场合在于“一个请求可能有多个接受者，但最后真正的接受者只有一个”，这时候请求发送者与接受者的耦合有可能出现“变化脆弱”的症状，职责链的目的就是将二者解耦，从而更好地应对变化。
2. 应用了Chain of Responsibility模式后，对象的职责分派将更具灵活性。我们可以在运行时动态添加/修改请求的处理职责。
3. 如果请求传递到职责链的末尾仍得不到处理，应该有一个合理的缺省机制。这也是每一个接受对象的责任，而不是发出请求的对象的责任。


**怎么用?**

* 一个接口或者抽象类
* 每个对象差异化处理
* 对象链（数组或者链表）初始化（连起来）


**代码:**

```
// 请求者
class Request {
private:
    string description;
    RequestType reqType;
public:
    Request(const string& desc, RequestType type) : description(desc), reqType(type) {}
    RequestType getReqType() const { return reqType; }
    const string& getDescription() const { return description; }
};

// 接收者链条类
class ChainHandler {
private:
    ChainHandler* nextChain;
    void sendRequestToNextHandler(const Request& req) {
        if (nextChain != nullptr) {
            nextChain->handle(req);
        }
    }
protected:
    virtual bool canHandleRequest(const Request& req) = 0;
    virtual void processRequest(const Request& req) = 0;
public:
    virtual ~ChainHandler() {}
    ChainHandler() {
        nextChain = nullptr;
    }
    void setNextChain(ChainHandler* next) {
        nextChain = next;
    }
    // 每一个接收者接收到看看是不是自己的类型，如果是，处理，不是发送给下一个接受者
    void handle(const Request& req) {
        if (canHandleRequest(req)) {
            processRequest(req);
        }
        else {
            sendRequestToNextHandler(req);
        }
    }
};

// 具体的接收者
class Handler1 : public ChainHandler {
protected:
    bool canHandleRequest(const Request& req) override {
        return req.getReqType() == RequestType::REQ_HANDLER1;
    }
    void processRequest(const Request& req) override {
        // ... 
    }
};

class Handler2 : public ChainHandler {
protected:
    bool canHandleRequest(const Request& req) override {
        return req.getReqType() == RequestType::REQ_HANDLER2;
    }
    void processRequest(const Request& req) override {
        // ... 
    }
};

class Handler3 : public ChainHandler {
protected:
    bool canHandleRequest(const Request& req) override {
        return req.getReqType() == RequestType::REQ_HANDLER3;
    }
    void processRequest(const Request& req) override {
        // ... 
    }
};

int main() {
    Handler1 h1;
    Handler2 h2;
    Handler3 h3;
  
    // 相当于在责任链上注册
    h1.setNextChain(&h2);
    h2.setNextChain(&h3);

    Request request("process task ...", RequestType::REQ_HANDLER3);

    // 虽然这个请求发给h1，但是最后是h3处理
    h1.handle(request);
    return 0;
}

```


# 观察者模式-Observer

**观察者**

定义对象间的一种一对多（变化）的依赖关系，以便当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并自动更新。类似Qt的信号槽机制，信号，条件变量等。


**解决什么问题？**

在软件构件过程中，我们需要为某些对象建立一种”通知依赖关系“，一个对象（目标对象）的状态发送改变，所有的依赖对象（观察者对象）都将得到通知。如果这样的依赖关系过于亲密，将使软件不能很好地抵御变化。

使用面向对象技术，可以将这种依赖关系弱化，并形成一种稳定的依赖关系。从而实现软件体系结构的松耦合。


**要点总结：**

1. 使用面向对象的抽象，Observer模式使得我们可以**独立**地改变目标与观察者，从而使二者之间的依赖关系达致松耦合。
2. 目标发送通知时，无需指定观察者，通知（可以携带通知信息作为参数）会自动传播。
3. 观察者自己决定是否需要订阅通知，目标对象对此一无所知。
4. Observer模式是**基于事件的UI框架中非常常用的设计模式**，也是MVC模式的一个重要组成部分。


* 被观察者（Observerable）：目标对象，状态发生变化时，将通知所有的观察者。
* 观察者（observer）：接受被观察者的状态变化通知，执行预先定义的业务。


**代码:**

// 被观察者

```
public class Observerable {
   
   private List<Observer> observers 
      = new ArrayList<Observer>();
   private int state;
 
   public int getState() {
      return state;
   }
 
   public void setState(int state) {
      notifyAllObservers();
   }
 
   //添加观察者
   public void addServer(Observer observer){
      observers.add(observer);    
   }
   
   //移除观察者
   public void removeServer(Observer observer){
      observers.remove(observer);    
   }
   //通知
   public void notifyAllObservers(int state){
      if(state!=1){
          System.out.println(“不是通知的状态”);
         return ;
      }
   
      for (Observer observer : observers) {
         observer.doEvent();
      }
   }  
}
```



// 观察者

```
//观察者
 interface Observer {  
    void doEvent();  
}  
//Im消息
IMMessageObserver implements Observer{
    void doEvent（）{
       System.out.println("发送IM消息");
    }
}
 
//手机短信
MobileNoObserver implements Observer{
    void doEvent（）{
       System.out.println("发送短信消息");
    }
}
//EmailNo
EmailObserver implements Observer{
    void doEvent（）{
       System.out.println("发送email消息");
    }
}
```

这是最简单的一种实现，只有观察者在被观察者中注册，之后被观察者调用通知函数，所有观察者都有相应。

但是这种接口太单一，只适合特定结构的观察者和被观察者。

可以利用模板的特性和一些C++11新标准改进。

也可以在观察者上面再加一层：观察者类型类，在被观察者下面再加一层，隔离变化。


# 工厂模式-Factory

**工厂**

定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method使得一个类的**实例化延迟**（目的：解耦，手段：虚函数）到子类。


**解决什么问题？**

在软件系统中，经常面临着创建对象的工作；由于需求的变化，**需要创建的对象的具体类型经常变化。**

如何应对这种变化？如何绕过常规的对象创建方法（new），提供一种“封装机制”来避免客户程序和这种“具体对象创建工作”的紧耦合？（new导致的紧耦合）：**并非消除变化，而是将变化关进笼子。**

一般情况下不会看到单独的工厂模式，而是和其他设计模式一起出现，比如策略模式，而且它和策略模式还很相似。


**要点总结:**

1. Factory Method模式用于隔离类对象的使用者和具体类型之间的耦合关系。面对一个经常变化的具体类型，紧耦合关系（new）会导致软件的脆弱。
2. Factory Method模式通过面向对象的手法，将所要创建的具体对象工作延迟到子类，从而实现一种扩展（而非更改）的策略，较好地解决了这种紧耦合关系。
3. Factory Method模式解决“单个对象”的需求变化。缺点在于要求创建方法/参数相同。


**代码:**

```
// 工厂接口
interface IFileResolveFactory{
   void resolve();
}

// 不同子类实现工厂接口
class AFileResolve implements IFileResolveFactory{
   void resolve(){
      System.out.println("文件A类型解析");
   }
}
 
class BFileResolve implements IFileResolveFactory{
   void resolve(){
      System.out.println("文件B类型解析");
   }
}
 
class DefaultFileResolve implements IFileResolveFactory{
   void resolve(){
      System.out.println("默认文件类型解析");
   }
}


// 使用工厂模式
//构造不同的工厂对象
IFileResolveFactory fileResolveFactory;
if(fileType=“A”){
    fileResolveFactory = new AFileResolve();
}else if(fileType=“B”){
    fileResolveFactory = new BFileResolve();
 }else{
    fileResolveFactory = new DefaultFileResolve();
}
 
fileResolveFactory.resolve();

// 一般情况下，对于工厂模式，你不会看到以上的代码。工厂模式会跟配合其他设计模式如策略模式一起出现的。
```
