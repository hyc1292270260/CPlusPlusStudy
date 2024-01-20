using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	abstract class Manager
	{
		protected string name;
		protected Manager superior;//上级
		public Manager(string name)
		{
			this.name = name;
		}
		public void SetSuperior(Manager superior)
		{
			this.superior = superior;
		}
		abstract public void RequestApplications(Request request);
	}
	class CommonManager : Manager
	{
		public CommonManager(string name) : base(name)
		{

		}
		public override void RequestApplications(Request request)
		{
			if (request.RequestType == "请假" && request.RequestDay < 2)
			{
				Console.WriteLine("批准");
			}
			else 
			{
				if (superior != null)
				{
					superior.RequestApplications(request);
				}
			}
		}
	}

	class MajorManager : Manager
	{
		public MajorManager(string name) : base(name)
		{

		}
		public override void RequestApplications(Request request)
		{
			if (request.RequestType == "请假" && request.RequestDay < 5)
			{
				Console.WriteLine("批准");
			}
			else
			{
				if (superior != null)
				{
					superior.RequestApplications(request);
				}
			}
		}
	}
	class ZongjianManager : Manager
	{
		public ZongjianManager(string name) : base(name)
		{

		}
		public override void RequestApplications(Request request)
		{
			if (request.RequestType == "请假" && request.RequestDay < 2)
			{
				Console.WriteLine("批准");
			}
			else if (request.RequestType == "加薪" && request.RequestDay < 500)
			{
				Console.WriteLine("批准");
			}
			else 
			{
				Console.WriteLine("再等等");
			}
		}
		public static class ResponsibilityMain
		{
			public static void Init()
			{
				CommonManager jingli = new CommonManager("经理");
				MajorManager zhuguan = new MajorManager("主管");
				ZongjianManager zongjian = new ZongjianManager("总监");
				jingli.SetSuperior(zhuguan);
				zhuguan.SetSuperior(zongjian);

				Request request1 = new Request
				{
					RequestDay = 4,
					RequestType = "请假"
				};
				jingli.RequestApplications(request1);

				Request request2 = new Request
				{
					RequestDay = 600,
					RequestType = "加薪"
				};
				jingli.RequestApplications(request1);

			}

		}
	}
	class Request
	{
		public String RequestType;
		public int RequestDay;
	}
}
/*职责链模式：使多个对象都有机会处理请求，将对象连城一条链，并沿着链传递请求，知道有一个对象处理它为止
 */
