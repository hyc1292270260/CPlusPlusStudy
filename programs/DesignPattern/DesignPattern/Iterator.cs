using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    interface IIterator
    {
		object First();
		object Next();
		bool IsDone();
		object Current();
    }
	abstract class Aggregate
	{
		public abstract IIterator CreateIterator();
	}
	class ConcreteAggregate  : Aggregate
	{
		private IList<object> items = new List<object>();
		public override IIterator CreateIterator()
		{
			return new ConcreteIterate(this);
		}
		public int Count { get { return items.Count; } }
		public object this[int index]
		{
			//索引器
			get { return items[index]; }
			set { items.Insert(index, value); }
		}

	}
	class ConcreteIterate : IIterator
	{
		private ConcreteAggregate aggregate;
		private int current = 0;
		public ConcreteIterate(ConcreteAggregate aggregate)
		{
			this.aggregate = aggregate;
		}
		public  object First()
		{
			return aggregate[0];
		}
		public object Next()
		{
			object ret = null;
			if (current++ < aggregate.Count)
			{
				ret = aggregate[current];
			}
			return ret;
		}
		public bool IsDone()
		{
			return current >= aggregate.Count ? true:false;

		}
		public object Current()
		{
			return aggregate[current];
		}
		public static class IteratorMain
		{
			public static void Init()
			{
				ConcreteAggregate a = new ConcreteAggregate();
				a[0] = "a";
				a[1] = "b";
				a[3] = "c";
				IIterator i = new ConcreteIterate(a);
				object item = i.First();
				while (!i.IsDone())
				{
					Console.WriteLine(i.Current());
					i.Next();
				}
			}

		}
	}
}
/*迭代器模式：提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露该对象的内部表示
 * .Net 通过IEumerator 和 IEumerable 来实现迭代器
 */
