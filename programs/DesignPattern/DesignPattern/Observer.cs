using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class Subject
    {
		private IList<Observer> observers = new List<Observer>();
		public string SubjectState { get; set; }
		public void AddObserver(Observer o)
		{
			observers.Add(o);
		}
		public void DelObserver(Observer o)
		{
			observers.Remove(o);
		}
		public void NotifyAll()
		{
			for (int i = 0;i<observers.Count;i++)
			{
				observers[i].Update();
			}
		}
    }
	abstract class Observer
	{
	
		public abstract void Update();
	}
	class Subject1 : Subject
	{

	}
	class Subject2 : Subject
	{

	}
	class Observer1 : Observer
	{
		public String name;
		public String state;
		public Subject subject;
		public Observer1(string name, string state, Subject subject)
		{
			this.name = name;
			this.state = state;
			this.subject = subject;
		}
		public override void Update()
		{
			state = subject.SubjectState;
			Console.WriteLine("观察者{0 }的新状态为{1}", name, state);
		}
	}
	class Observer2 : Observer
	{
		public override void Update()
		{

		}
	}
	public static class ObserverMain
	{
		public static void Init()
		{
			Subject s1 = new Subject1();

			s1.AddObserver(new Observer1("a", "1", s1));
			s1.AddObserver(new Observer1("b", "2", s1));

			s1.SubjectState = "3";
			s1.NotifyAll();
		}

	}
}
/*观察者模式：一个对象变化通知其他多个对象  没有抽象观察者，每个观察者名字不同，事件委托，委托是对函数的抽象，是特殊的类
 */
