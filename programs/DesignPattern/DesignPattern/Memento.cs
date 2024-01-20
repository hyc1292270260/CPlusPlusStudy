using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	class Memento
	{
		//备忘录类
		private string state;
		public Memento(string state)
		{
			this.state = state;
		}
		public string State
		{ get { return state; } }
	}
	class Originator
	{
		//发起人类，创建备忘录记录当前状态，并可以恢复内部状态
		public string State { get; set; }

		public Memento CreateMemento()
		{
			return new Memento(State);
		}
		public void SetMemento(Memento memento)
		{
			State = memento.State;
		}
		public void Show()
		{
			Console.WriteLine("State =" + State);
		}
	}
	class Caretaker
	{
		//管理类，负责保存备忘录的状态
		public Memento Memento { get; set; }
	}
	public static class MementoMain
	{
		public static void Init()
		{
			Originator o = new Originator();
			o.State = "1";
			o.Show();

			//保存状态
			Caretaker c = new Caretaker();
			c.Memento = o.CreateMemento();

			o.State = "2";
			o.Show();

			//恢复到备忘录保存的状态
			o.SetMemento(c.Memento);
			o.Show();


			Role r = new Role();
			r.State = new RoleState
			{
				vit = 100,
				atk = 20,
				def = 10
			};
			r.Battle();

			RoleManager rm = new RoleManager();
			rm.state = r.CreateRoleState();

			r.State = new RoleState
			{
				vit = 50,
				atk = 30,
				def = 5
			};
			r.Battle();

			r.ResetRoleState(rm.state);
			r.Battle();
		}

	}
	class RoleState
	{
		public int vit;
		public int atk;
		public int def;

	}
	class Role
	{
		public RoleState State { get; set; }
		public RoleState CreateRoleState()
		{
			return new RoleState
			{
				atk = State.atk,
				vit = State.vit,
				def = State.def
			};

		}
		public void ResetRoleState(RoleState state)
		{
			State = state;
		}
		public void Battle()
		{
		
		}
	}
	class RoleManager
	{
		public RoleState state { get; set; }
	}
}
/*备忘录模式：需要维护或记录历史属性的类，可以存储可撤销的状态
 */

