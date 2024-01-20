using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
	abstract class State
	{
		public abstract void Handle(StateContext context);
	}
	class ConcreteStateA : State
	{
		public override void Handle(StateContext context)
		{
			if (true)
			{
				//Todo
			}
			else
			{
				//chaage State
			}
		}
	}
	class ConcreteStateB : State
	{
		public override void Handle(StateContext context)
		{
			if (true)
			{
				//Todo
			}
			else
			{
				//chaage State
			}
		}
	}
	class StateContext
	{
		private State state;
		public StateContext(State state)
		{
			this.state = state;
		}
		public void SetState(State state)
		{
			this.state = state;
		}
		public void Request()
		{
			state.Handle(this);
		}
	}
	public static class StateMain
	{
		public static void Init()
		{
			StateContext sc = new StateContext(new ConcreteStateB());
			sc.Request();
			sc.Request();

		}

	}
}
/*状态模式：主要解决当控制一个对象状态转换的条件表达式过于复杂的条件，把状态的判断逻辑转移到不同状态的一系列类中，可以把复杂的判断逻辑简化
 */
