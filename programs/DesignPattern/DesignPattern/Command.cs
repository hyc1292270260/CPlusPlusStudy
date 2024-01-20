using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	public abstract class Command
	{
		protected Barbecuer receiver;
		public Command(Barbecuer receiver)
		{
			this.receiver = receiver;
		}

		abstract public void ExcuteCommand();
	}
	class BakeMuttonCommand : Command
	{
		public BakeMuttonCommand(Barbecuer receiver) : base(receiver)
		{

		}
		public override void ExcuteCommand()
		{
			receiver.BakeMutton();
		}
	}
	class BakeChickenWingCommand : Command
	{
		public BakeChickenWingCommand(Barbecuer receiver) : base(receiver)
		{

		}
		public override void ExcuteCommand()
		{
			receiver.BakeChickenWing();
		}
	}
	public class Barbecuer
	{
		public void BakeMutton()
		{
			Console.WriteLine("烤羊肉串");
		}

		public void BakeChickenWing()
		{
			Console.WriteLine("烤鸡翅");
		}
	}
    class Waiter
    {
		private List<Command> orders = new List<Command>();

		public void SetOrder(Command cmd)
		{
			orders.Add(cmd);
		}
		public void CancleOrder(Command cmd)
		{
			orders.Remove(cmd);
		}
		public void Notify()
		{
			foreach (Command cmd in orders)
			{
				cmd.ExcuteCommand();
			}
		}
		public static class CommandMain
		{
			public static void Init()
			{
				Barbecuer barbecuer = new Barbecuer();
				Command command1 = new BakeMuttonCommand(barbecuer);
				Command command2 = new BakeChickenWingCommand(barbecuer);
				Waiter waiter = new Waiter();

				waiter.SetOrder(command1);
				waiter.SetOrder(command2);

				waiter.Notify();

			}

		}
	}

}
/*命令模式：将请求封装成对象，从而使你用不同的请求对客户初始化；对于请求排队或记录请求日志，以及支持可撤销
 */
