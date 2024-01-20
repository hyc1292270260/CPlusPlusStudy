using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	abstract class Soft
	{
		public abstract void Run();
	}
	class GameSoft:Soft
	{
		public override void Run()
		{
			Console.WriteLine("运行手机游戏");
		}
	}
	class AddressSoft : Soft
	{
		public override void Run()
		{
			Console.WriteLine("运行通讯录");
		}
	}
	abstract class Phone
	{
		protected Soft soft;
		public void SetSoft(Soft soft)
		{
			this.soft = soft;
		}
		public abstract void Run();
	}
	class Phone1 : Phone
	{
		public override void Run()
		{
			soft.Run();
		}
	}
	class Phone2 : Phone
	{
		public override void Run()
		{
			soft.Run();
		}
	}
	public static class BridgeMain
	{
		public static void Init()
		{
			Phone phone = new Phone1();
			phone.SetSoft(new GameSoft());
			phone.Run();

			phone = new Phone2();
			phone.SetSoft(new AddressSoft());
			phone.Run();

		}

	}
}
/*桥接模式：将抽象部分和实现部分分离，实现系统可以多角度分类，每一种分类都有可能变化，那么就把这种多角度分离出来独立变化
 */
