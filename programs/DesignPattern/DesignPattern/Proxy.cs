using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	interface ISubject
    {
		 void Request();
    }
	class RealSubject : ISubject
	{
		public void Request()
		{

		}
	}
	class ProxySubject : ISubject
	{
		RealSubject realSubject;
		public void Request()
		{
			if (realSubject == null)
			{
				realSubject = new RealSubject();
			}
			realSubject.Request();
		}
	}
	public static class ProxyMain
	{
		public static void Init()
		{
			ProxySubject proxy = new ProxySubject();
			proxy.Request();

		}

	}
}
/*代理模式：远程代理：隐藏一个对象存在于不同地址空间的事实
 *			虚拟代理：帮助我们控制访问创建开销大的资源，虚拟代理作为创建开销大的对象的代表，经常会直到我们真正需要一个对象的时候才创建它。当对象在创建前和创建中时，由虚拟代理地来扮演对象的替身。对象创建后，代理就会将请求直接委托给对象。（通过网络取得图像数据。）
 *			安全代理：控制真是对象的访问权限
 */
