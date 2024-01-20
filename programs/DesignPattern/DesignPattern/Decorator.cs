using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class Component
    {
		public abstract void Operation();
    }
	class ConcreteComponent : Component
	{
		
		public override void Operation()
		{
			// 被装饰者最初的行为
		}
	}
	class Decorator : Component
	{
		protected Component component;
		public void SetComponent(Component component)
		{
			this.component = component;
		}
		public override void Operation()
		{
			if (component != null)
			{
				component.Operation();
			}
		}
	}
	class ConcreteDecoratorA : Decorator
	{
		private void Addbehavior()
		{

		}

		public override void Operation()
		{
			//通过传入的component 先调用上层功能
			base.Operation();
			Addbehavior();

		}
	}
	class ConcreteDecoratorB : Decorator
	{
		private void Addbehavior()
		{

		}

		public override void Operation()
		{
			base.Operation();
			Addbehavior();

		}
	}
	public static class DecoratorMain
	{
		public static void Init()
		{
			ConcreteComponent a = new ConcreteComponent();
			ConcreteDecoratorA A = new ConcreteDecoratorA();
			A.SetComponent(a);
			ConcreteDecoratorB B = new ConcreteDecoratorB();
			B.SetComponent(A);
			B.Operation();

		}

	}
}
/*装饰模式为了已有功能动态地添加更多功能的一种方式，当系统需要新功能时，客户代码可以根据需要有序的选择来包装对象
 * 
 * 
 */
