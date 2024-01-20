using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class Component1
    {
		protected string name;
		public Component1(string name)
		{
			this.name = name;
		}
		public abstract void Add(Component1 c);
		public abstract void Remove(Component1 c);
		public abstract void Display(int depth);
	}
	class Leaf : Component1
	{
		public Leaf(string name):base(name)
		{

		}
		public override void Display(int depth)
		{
			Console.WriteLine(new String('-', depth) + name);
		}
		public override void Add(Component1 c)
		{
			
		}
		public override void Remove(Component1 c)
		{

		}
	}
	class Composite1 : Component1
	{
		private List<Component1> children = new List<Component1>();
		public Composite1(string name) : base(name)
		{

		}
		public override void Display(int depth)
		{
			Console.WriteLine(new String('-', depth) + name);
			foreach (var child in children)
			{
				child.Display(depth + 2);
			}
		}
		public override void Add(Component1 c)
		{
			children.Add(c);
		}
		public override void Remove(Component1 c)
		{
			children.Remove(c);
		}
	}
	public static class CompositeMain
	{
		public static void Init()
		{
			Composite1 root = new Composite1("root");
			root.Add(new Leaf("Leaf A"));
			root.Add(new Leaf("Leaf B"));

			Composite1 comp1 = new Composite1("Composite X");
			comp1.Add(new Leaf("Leaf XA"));
			root.Add(comp1);

			root.Display(1);
		}

	}
}
/*组合模式：将对象组合成树状形式表示部分整体的层次结构，使用具有一致性
 */
