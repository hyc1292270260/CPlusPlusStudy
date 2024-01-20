using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	class Target
	{
		//期待的接口
		public virtual void Request()
		{

		}
	}
	class Adaptee
    {
		//需要适配的类
		public void SpecificRequest()
		{

		}
    }
	class Adapter:Target
	{
		private Adaptee adaptee = new Adaptee();
		public override void Request()
		{
			adaptee.SpecificRequest();
		}
	}
	public static class AdapterMain
	{
		public static void Init()
		{
			//调用Adapter的Request，实际调用的被适配的类SpecificRequest
			Target target = new Adapter();
			target.Request();

		}

	}
}
/*适配器模式：两个类做的事情相同或相似，但是具有不同的接口。是其中一个接口适配另一个接口，调用统一接口就可以了（）适用于无法改变原有设计和代码
 */
