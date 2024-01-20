using System;
using System.Collections.Generic;
using System.Text;

namespace DesignPattern
{
    abstract class FlyWeight
    {
		public abstract void Operation();
    }

	class ConcreteFlyWeight : FlyWeight
	{
		public override void Operation()
		{
			//共享
		}
	}
	class UnsharedConcreteFlyWeight : FlyWeight
	{
		public override void Operation()
		{
			//非共享
		}
	}
	class FlyWeightFactory
	{
		private Dictionary<int,FlyWeight> dicFlyWeight = new Dictionary<int, FlyWeight>();

		public FlyWeight GetFlyWeight(int key)
		{
			if (!dicFlyWeight.ContainsKey(key))
			{
				FlyWeight flyWeight = new ConcreteFlyWeight();
				dicFlyWeight.Add(key, flyWeight);
				return flyWeight;
			}
			else
				return (FlyWeight)dicFlyWeight[key];
		}
	}
	public static class FlyWeightMain
	{
		public static void Init()
		{
			FlyWeightFactory fw = new FlyWeightFactory();

			FlyWeight f1 = fw.GetFlyWeight(1);
			f1.Operation();
			FlyWeight f2 = fw.GetFlyWeight(2);
			f2.Operation();

			FlyWeight f3 = fw.GetFlyWeight(2);
			f3.Operation();

			FlyWeight f4 = new UnsharedConcreteFlyWeight();
			f4.Operation();

		}

	}
}
/*享元模式：避免大量相似的、小粒度类的开销。用共享对象降低对象数量，提高程序性能；但是需要一些状态外部变化，使程序逻辑复杂化
 */
