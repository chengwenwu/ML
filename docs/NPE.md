@[toc]
# 一、实验内容
-  考虑上面表格中点的parzen window估计和分类器。设窗口函数为球面高斯函数：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181120190155145.png)
   - a) 编写一个程序，根据Parzen窗口对任意测试点x进行分类估计。使用三维数据训练你的分类器。设h = 1，分类样本点为：$(0.50;1.0;0.0)^t (0.31;1.51;-0.50)^t和(-0.3;0.44;-0.1)^t$。
   - b) h = 0.1, 重复a)
- 考虑在不同维数下的k-最近邻密度估计

   - (a)编写一个程序，对于一维的情况，当有n个数据样本点时，进行k-紧邻概率密度估计。对表格中的类别w3,中的特征x1，用程序画出当k = 1,3,5时的概率密度估计结果。

    - (b)编写一个程序，对于二维的情况，当有n个数据样本点时，进行k-紧邻概率密度估计。对表格中的类别w2,中的特征$(x1，x2)^T$，用程序画出当k = 1,3,5时的概率密度估计结果。

   - ( c )对上表中三个类别的三维数据编写一个k-近邻分类器。当k=1,3,5时，对下面点的概率密度进行估计。$(-0.41, 0.82,  0.88)^t ,  (0.14,  0.72,  4.1)^t and (-0.81,  0.61,  -0,38)^t.$
- 使用的数据：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181120192908525.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)
# 二、实验环境
- linux系统
- g++编译器6.3.0及以上版本
- matlab 2016a
- 可在windows下使用同样或更高版本的g++编译器编译，但需要修改Makefile文件，删除命令rm改为del, 可执行文件main改为main.exe
# 三、理论知识
- 非参数估计：不假定其分布符合哪种分布，而是直接用样本和待判定向量计算其条件概率。
- 关键公式：$p_n(x)=( k_n/n)/V_n$, Parzen方法是固定体积$V_n$求$K_n$.而KNN方法是固定要包含的样本个数，求几何体体积。

- **估计概率密度**：估计概率密度的时候，我们最终的输出结果应该是一个概率值。
    - Parzen方法：以输入的x为中心，输入的h为半径（边长），做一个球体（超几何体），然后看这个类的样本中有多少个样本在这个球体内部，这个数量就是上面公式中的$k_n$,将其代入公式中求出$p_n(x)$，这个值就是我们想要的值。
    - KNN方法：在这个类别的样本中找到距离x (输入数据）最近的K  (是输入数据）个样本，然后再在找到的这K个样本中找到离他最远的那个样本，以他们之间的距离为半径，以输入的x为中心，做一个球体，这个球体的体积就是$V_n$.将其代入上述公式，求出$p_n(x)$即可。
- **分类**：
    - 将上面的$p_n(x)$带入到贝叶斯公式，最后贝叶斯公式变成了 $p(w_i|x) = k_i/k_n$。
	- parzen方法：$k_i$是在以待判定向量**x**为中心以h为边长（半径）的超几何体所包含的样本中$w_i$样本的数量。$k_n$是上述超几何体所包含的全部样本数量。由于在判定后验概率大小的时候，$k_n$对于所有类别都是相同的。所以我们在计算的时候只需要计算$k_i$。$k_i=\sum_{i = 1}^n\phi((x-x_i)/h)$。最后比较各个类别中$k_i$的大小，那个大则属于哪一类。

   - KNN方法：就是找到距离输入向量**x**最近的K个向量，然后看找到的这些样本中，哪一类的最多则判为哪一类。
# 四、实验过程
## 1、parzen窗
- 由于题目中要求进行分类，所以我们没有必要直接求出$p_n(x)$，只要求出$k_i$,然后哪个大，就属于那类。关键代码如下：

```c
int NPE::judgePar(string vec_str_in, float h)
{
	this->storage.reset();
	Matrix vec1 = this->userInputProcess(vec_str_in);
	float g = - FLT_MAX, temp = 0;//将g赋值为最小浮点数
	int victory = -1;
	for (int counter1 = 1; counter1 <= this->classSize; counter1++)
	{
		temp = 0;
		for (int counter2 = 0; counter2 < this->sampleSize; counter2++)
		{
			Matrix vec2 = vec1 - this->storage.readData();
			temp += exp(-(vec2.trans()*vec2).matrixToFloat()/(2*pow(h,2)));
		}
		if (temp > g)
		{
			g = temp;
			victory = counter1;
		}
	}
	return victory;
}
```
- 结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181121165313989.png)
## 2、kNN
###  新加函数及其正确性说明
- 这次比上次在Matrix类中增加了友元函数eDist来计算欧氏距离，下面验证其正确性,这个函数会在C小题中用到。
- 代码：
就是计算[1.55,2.66]和[2,3]之间的欧式距离

```c
cout<<eDist(npe.userInputProcess("[1.55,2.66]"), npe.userInputProcess("[2,3]"));
```
- 结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181114165857702.png)
- 结果验证：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181114165954171.png)
### a小题
- 找到最近的k个点然后V = 2*dis, dis是x到第k个最近点之间的欧式距离。
x取了[0,3]之间的数，每隔0.01取一个值。
- 结果：
k = 1,3,5
![在这里插入图片描述](https://img-blog.csdnimg.cn/2018112116432838.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)
### b小题
- 基本和a小题一样，不同之处就在于，这里是二维，所以V应该是面积，以**x**为圆心，**x**到离它最近的第k个点的欧式距离为半径，求面积。画图时，x轴取[-3,3]，每隔0.1取一个值，y轴取[-3,4],每隔0.1取一个值。
- 结果：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2018112116512718.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)
### c小题
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181121165243428.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0MyNjgxNTk1ODU4,size_16,color_FFFFFF,t_70)

# 五、遇到的问题
### 1、思路和算法都正确，结果不正确
- 在编写parzen方法时思路就像上面说的，是正确的，结果就是不正确。所以我在思考是我的代码有问题，还是抄数据的时候出了错误。所以，就想百度一个已有的代码，然后用我的样本数据去运行这个代码。如果结果和网上的一样说明我的数据是没有问题的，是代码实现时出错了；反之，就是数据有问题。百度了一个已经写好的代码[^1]（python语言），看了下实现思路，和我的不一样，是直接求概率密度，这样就更好了，两种方法验证，我copy下来，使用我的数据文件运行，发现结果正确，这就说明我的数据是没有问题的，然后就debug。把所有变量一一输出。。。。。。。一大堆操作。最后发现，原来是判决第一个向量后读取文件指针到了文件末尾，然后没有把他移到开头，就开始判断下一个向量了，导致出错。
- matlab不常用三维画图不会，弄了好久好不容易弄出上面的图，虽然很丑。。。。

[^1]:[python版本的代码](https://blog.csdn.net/baidu_34045013/article/details/81238753)
